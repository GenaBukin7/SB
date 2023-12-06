/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2019-2020, 2023 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

In addition, SugarBombEngine is using id Tech 4 (BFG) pieces and thus
subject to certain additional terms (all header and source files which 
contains such pieces has this additional part appended to the license 
header). You should have received a copy of these additional terms 
stated in a separate file (LICENSE-idTech4) which accompanied the 
SugarBombEngine source code. If not, please request a copy in 
writing from id Software at the address below.

If you have questions concerning this license or the applicable additional
terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc.,
Suite 120, Rockville, Maryland 20850 USA.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#pragma once

//*****************************************************************************


ID_INLINE SbAngles::SbAngles()
{
}

ID_INLINE SbAngles::SbAngles( float pitch, float yaw, float roll )
{
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

ID_INLINE SbAngles::SbAngles( const SbVec3& v )
{
	this->pitch = v[0];
	this->yaw	= v[1];
	this->roll	= v[2];
}

ID_INLINE void SbAngles::Set( float pitch, float yaw, float roll )
{
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

ID_INLINE SbAngles& SbAngles::Zero()
{
	pitch = yaw = roll = 0.0f;
	return *this;
}

ID_INLINE float SbAngles::operator[]( int index ) const
{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

ID_INLINE float& SbAngles::operator[]( int index )
{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

ID_INLINE SbAngles SbAngles::operator-() const
{
	return SbAngles( -pitch, -yaw, -roll );
}

ID_INLINE SbAngles& SbAngles::operator=( const SbAngles& a )
{
	pitch	= a.pitch;
	yaw		= a.yaw;
	roll	= a.roll;
	return *this;
}

ID_INLINE SbAngles SbAngles::operator+( const SbAngles& a ) const
{
	return SbAngles( pitch + a.pitch, yaw + a.yaw, roll + a.roll );
}

ID_INLINE SbAngles& SbAngles::operator+=( const SbAngles& a )
{
	pitch	+= a.pitch;
	yaw		+= a.yaw;
	roll	+= a.roll;
	
	return *this;
}

ID_INLINE SbAngles SbAngles::operator-( const SbAngles& a ) const
{
	return SbAngles( pitch - a.pitch, yaw - a.yaw, roll - a.roll );
}

ID_INLINE SbAngles& SbAngles::operator-=( const SbAngles& a )
{
	pitch	-= a.pitch;
	yaw		-= a.yaw;
	roll	-= a.roll;
	
	return *this;
}

ID_INLINE SbAngles SbAngles::operator*( const float a ) const
{
	return SbAngles( pitch * a, yaw * a, roll * a );
}

ID_INLINE SbAngles& SbAngles::operator*=( float a )
{
	pitch	*= a;
	yaw		*= a;
	roll	*= a;
	return *this;
}

ID_INLINE SbAngles SbAngles::operator/( const float a ) const
{
	float inva = 1.0f / a;
	return SbAngles( pitch * inva, yaw * inva, roll * inva );
}

ID_INLINE SbAngles& SbAngles::operator/=( float a )
{
	float inva = 1.0f / a;
	pitch	*= inva;
	yaw		*= inva;
	roll	*= inva;
	return *this;
}

ID_INLINE SbAngles operator*( const float a, const SbAngles& b )
{
	return SbAngles( a * b.pitch, a * b.yaw, a * b.roll );
}

ID_INLINE bool SbAngles::Compare( const SbAngles& a ) const
{
	return ( ( a.pitch == pitch ) && ( a.yaw == yaw ) && ( a.roll == roll ) );
}

ID_INLINE bool SbAngles::Compare( const SbAngles& a, const float epsilon ) const
{
	if( SbMath::Fabs( pitch - a.pitch ) > epsilon )
	{
		return false;
	}
	
	if( SbMath::Fabs( yaw - a.yaw ) > epsilon )
	{
		return false;
	}
	
	if( SbMath::Fabs( roll - a.roll ) > epsilon )
	{
		return false;
	}
	
	return true;
}

ID_INLINE bool SbAngles::operator==( const SbAngles& a ) const
{
	return Compare( a );
}

ID_INLINE bool SbAngles::operator!=( const SbAngles& a ) const
{
	return !Compare( a );
}

ID_INLINE void SbAngles::Clamp( const SbAngles& min, const SbAngles& max )
{
	if( pitch < min.pitch )
	{
		pitch = min.pitch;
	}
	else if( pitch > max.pitch )
	{
		pitch = max.pitch;
	}
	if( yaw < min.yaw )
	{
		yaw = min.yaw;
	}
	else if( yaw > max.yaw )
	{
		yaw = max.yaw;
	}
	if( roll < min.roll )
	{
		roll = min.roll;
	}
	else if( roll > max.roll )
	{
		roll = max.roll;
	}
}

ID_INLINE int SbAngles::GetDimension() const
{
	return 3;
}

ID_INLINE const float* SbAngles::ToFloatPtr() const
{
	return &pitch;
}

ID_INLINE float* SbAngles::ToFloatPtr()
{
	return &pitch;
}