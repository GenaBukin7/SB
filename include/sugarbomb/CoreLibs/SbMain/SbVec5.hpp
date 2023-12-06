/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2020, 2023 SugarBombEngine Developers

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

#pragma once

//#include "SbMath.hpp"
#include "SbVec2.hpp"
#include "SbVec3.hpp"

#include <CoreLibs/SbSystem/SbSystemDefs.hpp>

//*****************************************************************************

namespace sbe::SbMain
{

class SbVec2;
class SbVec3;

//===============================================================
//
//	SbVec5 - 5D vector
//
//===============================================================

class SbVec5
{
public:
	float			x;
	float			y;
	float			z;
	float			s;
	float			t;
	
	SbVec5();
	explicit SbVec5( const SbVec3& xyz, const SbVec2& st );
	explicit SbVec5( const float x, const float y, const float z, const float s, const float t );
	
	float			operator[]( int index ) const;
	float& 			operator[]( int index );
	SbVec5& 		operator=( const SbVec3& a );
	
	int				GetDimension() const;
	
	const SbVec3& 	ToVec3() const;
	SbVec3& 		ToVec3();
	const float* 	ToFloatPtr() const;
	float* 			ToFloatPtr();
	const char* 	ToString( int precision = 2 ) const;
	
	void			Lerp( const SbVec5& v1, const SbVec5& v2, const float l );
};

extern SbVec5 vec5_origin;
#define vec5_zero vec5_origin

#include "SbVec5.inl"

}; // namespace sbe::SbMain