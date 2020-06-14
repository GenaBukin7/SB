/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2013 Robert Beckebans
Copyright (C) 2019-2020 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

In addition, SugarBombEngine is using id Tech 4 (BFG) pieces and thus subject to certain additional terms (all header and source files which 
contains such pieces has this additional part appended to the license header). You should have received a copy of these additional terms 
stated in a separate file (LICENSE-idTech4) which accompanied the SugarBombEngine source code. If not, please request a copy in 
writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc.,
Suite 120, Rockville, Maryland 20850 USA.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#include "SbBufferObject.hpp"

#include "CoreLibs/SbSystem/ISystem.hpp"

//*****************************************************************************

namespace sbe::SbGLCoreRenderer
{

/*
================================================================================================

	idIndexBuffer

================================================================================================
*/

/*
========================
idIndexBuffer::idIndexBuffer
========================
*/
SbIndexBuffer::SbIndexBuffer(ISystem &aSystem) : mSystem(aSystem)
{
	size = 0;
	offsetInOtherBuffer = OWNS_BUFFER_FLAG;
	apiObject = nullptr;
	SetUnmapped();
};

/*
========================
idIndexBuffer::~idIndexBuffer
========================
*/
SbIndexBuffer::~SbIndexBuffer()
{
	FreeBufferObject();
};

/*
========================
idIndexBuffer::AllocBufferObject
========================
*/
bool SbIndexBuffer::AllocBufferObject(const void *data, int allocSize)
{
	assert(apiObject == nullptr);
	assert_16_byte_aligned(data);

	if(allocSize <= 0)
		mSystem.Error("idIndexBuffer::AllocBufferObject: allocSize = %i", allocSize);

	size = allocSize;

	bool allocationFailed = false;

	int numBytes = GetAllocedSize();

	// clear out any previous error
	glGetError();

	GLuint bufferObject = 0xFFFF;
	glGenBuffers(1, &bufferObject);
	if(bufferObject == 0xFFFF)
	{
		GLenum error = glGetError();
		mSystem.FatalError("idIndexBuffer::AllocBufferObject: failed - GL_Error %d", error);
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject);

	// these are rewritten every frame
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numBytes, nullptr, bufferUsage);
	apiObject = reinterpret_cast<void *>(bufferObject);

	GLenum err = glGetError();
	if(err == GL_OUT_OF_MEMORY)
	{
		mSystem.Warning("idIndexBuffer:AllocBufferObject: allocation failed");
		allocationFailed = true;
	};

	if(r_showBuffers.GetBool())
		mSystem.Printf("index buffer alloc %p, api %p (%i bytes)\n", this, GetAPIObject(), GetSize());

	// copy the data
	if(data != nullptr)
		Update(data, allocSize);

	return !allocationFailed;
};

/*
========================
idIndexBuffer::FreeBufferObject
========================
*/
void SbIndexBuffer::FreeBufferObject()
{
	if(IsMapped())
		UnmapBuffer();

	// if this is a sub-allocation inside a larger buffer, don't actually free anything.
	if(OwnsBuffer() == false)
	{
		ClearWithoutFreeing();
		return;
	};

	if(apiObject == nullptr)
		return;

	if(r_showBuffers.GetBool())
		mSystem.Printf("index buffer free %p, api %p (%i bytes)\n", this, GetAPIObject(), GetSize());

	// RB: 64 bit fixes, changed GLuint to GLintptrARB
	GLintptr bufferObject = reinterpret_cast<GLintptr>(apiObject);
	glDeleteBuffers(1, (const unsigned int *)&bufferObject);
	// RB end

	ClearWithoutFreeing();
};

/*
========================
idIndexBuffer::Reference
========================
*/
void SbIndexBuffer::Reference(const SbIndexBuffer &other)
{
	assert(IsMapped() == false);
	//assert( other.IsMapped() == false );	// this happens when building idTriangles while at the same time setting up triIndex_t
	assert(other.GetAPIObject() != nullptr);
	assert(other.GetSize() > 0);

	FreeBufferObject();
	size = other.GetSize();                  // this strips the MAPPED_FLAG
	offsetInOtherBuffer = other.GetOffset(); // this strips the OWNS_BUFFER_FLAG
	apiObject = other.apiObject;
	assert(OwnsBuffer() == false);
};

/*
========================
idIndexBuffer::Reference
========================
*/
void SbIndexBuffer::Reference(const SbIndexBuffer &other, int refOffset, int refSize)
{
	assert(IsMapped() == false);
	//assert( other.IsMapped() == false );	// this happens when building idTriangles while at the same time setting up triIndex_t
	assert(other.GetAPIObject() != nullptr);
	assert(refOffset >= 0);
	assert(refSize >= 0);
	assert(refOffset + refSize <= other.GetSize());

	FreeBufferObject();
	size = refSize;
	offsetInOtherBuffer = other.GetOffset() + refOffset;
	apiObject = other.apiObject;
	assert(OwnsBuffer() == false);
};

/*
========================
idIndexBuffer::Update
========================
*/
void SbIndexBuffer::Update(const void *data, int updateSize) const
{
	assert(apiObject != nullptr);
	assert(IsMapped() == false);
	assert_16_byte_aligned(data);
	assert((GetOffset() & 15) == 0);

	if(updateSize > size)
		mSystem.FatalError("idIndexBuffer::Update: size overrun, %i > %i\n", updateSize, GetSize());

	int numBytes = (updateSize + 15) & ~15;

	// RB: 64 bit fixes, changed GLuint to GLintptrARB
	GLintptr bufferObject = reinterpret_cast<GLintptr>(apiObject);
	// RB end

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, GetOffset(), (GLsizeiptr)numBytes, data);
	/*
		void * buffer = MapBuffer( BM_WRITE );
		CopyBuffer( (byte *)buffer + GetOffset(), (byte *)data, numBytes );
		UnmapBuffer();
	*/
};

/*
========================
idIndexBuffer::MapBuffer
========================
*/
void *SbIndexBuffer::MapBuffer(bufferMapType_t mapType) const
{
	assert(apiObject != nullptr);
	assert(IsMapped() == false);

	void *buffer = nullptr;

	// RB: 64 bit fixes, changed GLuint to GLintptrARB
	GLintptr bufferObject = reinterpret_cast<GLintptr>(apiObject);
	// RB end

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject);

	if(mapType == BM_READ)
	{
		//buffer = glMapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_READ_ONLY_ARB );
		buffer = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, GetAllocedSize(), GL_MAP_READ_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
		if(buffer != nullptr)
			buffer = (byte *)buffer + GetOffset();
	}
	else if(mapType == BM_WRITE)
	{
		//buffer = glMapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB );

		// RB: removed GL_MAP_INVALIDATE_RANGE_BIT as it breaks with an optimization in the Nvidia WHQL drivers >= 344.11
		buffer = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, GetAllocedSize(), GL_MAP_WRITE_BIT /*| GL_MAP_INVALIDATE_RANGE_BIT*/ | GL_MAP_UNSYNCHRONIZED_BIT);
		if(buffer != nullptr)
			buffer = (byte *)buffer + GetOffset();

		// assert( IsWriteCombined( buffer ) ); // commented out because it spams the console
	}
	else
		assert(false);

	SetMapped();

	if(buffer == nullptr)
		mSystem.FatalError("idIndexBuffer::MapBuffer: failed");

	return buffer;
};

/*
========================
idIndexBuffer::UnmapBuffer
========================
*/
void SbIndexBuffer::UnmapBuffer() const
{
	assert(apiObject != nullptr);
	assert(IsMapped());

	// RB: 64 bit fixes, changed GLuint to GLintptrARB
	GLintptr bufferObject = reinterpret_cast<GLintptr>(apiObject);
	// RB end

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject);
	if(!glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER))
		mSystem.Printf("idIndexBuffer::UnmapBuffer failed\n");

	SetUnmapped();
};

/*
========================
idIndexBuffer::ClearWithoutFreeing
========================
*/
void SbIndexBuffer::ClearWithoutFreeing()
{
	size = 0;
	offsetInOtherBuffer = OWNS_BUFFER_FLAG;
	apiObject = nullptr;
};

}; // namespace sbe::SbGLCoreRenderer