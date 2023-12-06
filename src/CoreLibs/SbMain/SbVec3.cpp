/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2019-2020, 2023 SugarBombEngine Developers

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

#include <CoreLibs/SbMain/SbVec3.hpp>
#include <CoreLibs/SbMain/SbAngles.hpp>
#include <CoreLibs/SbMain/SbPolar3.hpp>
#include <CoreLibs/SbMain/SbMatrix3.hpp>
//#include <CoreLibs/SbMain/SbVec2.hpp>

#include <CoreLibs/SbMain/SbString.hpp>

//*****************************************************************************

namespace sbe::SbMain
{

//===============================================================
//
//	idVec3
//
//===============================================================

SbVec3 vec3_origin(0.0f, 0.0f, 0.0f);

/*
=============
idVec3::ToYaw
=============
*/
float SbVec3::ToYaw() const
{
	float yaw;
	
	if( ( y == 0.0f ) && ( x == 0.0f ) )
	{
		yaw = 0.0f;
	}
	else
	{
		yaw = SbMath::Rad2Deg( atan2( y, x ) );
		if( yaw < 0.0f )
		{
			yaw += 360.0f;
		}
	}
	
	return yaw;
}

/*
=============
idVec3::ToPitch
=============
*/
float SbVec3::ToPitch() const
{
	float	forward;
	float	pitch;
	
	if( ( x == 0.0f ) && ( y == 0.0f ) )
	{
		if( z > 0.0f )
		{
			pitch = 90.0f;
		}
		else
		{
			pitch = 270.0f;
		}
	}
	else
	{
		forward = ( float )SbMath::Sqrt( x * x + y * y );
		pitch = SbMath::Rad2Deg( atan2( z, forward ) );
		if( pitch < 0.0f )
		{
			pitch += 360.0f;
		}
	}
	
	return pitch;
}

/*
=============
idVec3::ToAngles
=============
*/
SbAngles SbVec3::ToAngles() const
{
	float forward;
	float yaw;
	float pitch;
	
	if( ( x == 0.0f ) && ( y == 0.0f ) )
	{
		yaw = 0.0f;
		if( z > 0.0f )
		{
			pitch = 90.0f;
		}
		else
		{
			pitch = 270.0f;
		}
	}
	else
	{
		yaw = SbMath::Rad2Deg( atan2( y, x ) );
		if( yaw < 0.0f )
		{
			yaw += 360.0f;
		}
		
		forward = ( float )SbMath::Sqrt( x * x + y * y );
		pitch = SbMath::Rad2Deg( atan2( z, forward ) );
		if( pitch < 0.0f )
		{
			pitch += 360.0f;
		}
	}
	
	return SbAngles( -pitch, yaw, 0.0f );
}

/*
=============
idVec3::ToPolar
=============
*/
SbPolar3 SbVec3::ToPolar() const
{
	float forward;
	float yaw;
	float pitch;
	
	if( ( x == 0.0f ) && ( y == 0.0f ) )
	{
		yaw = 0.0f;
		if( z > 0.0f )
		{
			pitch = 90.0f;
		}
		else
		{
			pitch = 270.0f;
		}
	}
	else
	{
		yaw = SbMath::Rad2Deg( atan2( y, x ) );
		if( yaw < 0.0f )
		{
			yaw += 360.0f;
		}
		
		forward = ( float )SbMath::Sqrt( x * x + y * y );
		pitch = SbMath::Rad2Deg( atan2( z, forward ) );
		if( pitch < 0.0f )
		{
			pitch += 360.0f;
		}
	}
	return SbPolar3( SbMath::Sqrt( x * x + y * y + z * z ), yaw, -pitch );
}

/*
=============
idVec3::ToMat3
=============
*/
SbMat3 SbVec3::ToMat3() const
{
	SbMat3	mat;
	float	d;
	
	mat[0] = *this;
	d = x * x + y * y;
	if( !d )
	{
		mat[1][0] = 1.0f;
		mat[1][1] = 0.0f;
		mat[1][2] = 0.0f;
	}
	else
	{
		d = SbMath::InvSqrt( d );
		mat[1][0] = -y * d;
		mat[1][1] = x * d;
		mat[1][2] = 0.0f;
	}
	mat[2] = Cross( mat[1] );
	
	return mat;
}

/*
=============
idVec3::ToString
=============
*/
const char* SbVec3::ToString( int precision ) const
{
	return SbString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void SbVec3::Lerp( const SbVec3& v1, const SbVec3& v2, const float l )
{
	if( l <= 0.0f )
	{
		( *this ) = v1;
	}
	else if( l >= 1.0f )
	{
		( *this ) = v2;
	}
	else
	{
		( *this ) = v1 + l * ( v2 - v1 );
	}
}

/*
=============
SLerp

Spherical linear interpolation from v1 to v2.
Vectors are expected to be normalized.
=============
*/
#define LERP_DELTA 1e-6

void SbVec3::SLerp( const SbVec3& v1, const SbVec3& v2, const float t )
{
	float omega, cosom, sinom, scale0, scale1;
	
	if( t <= 0.0f )
	{
		( *this ) = v1;
		return;
	}
	else if( t >= 1.0f )
	{
		( *this ) = v2;
		return;
	}
	
	cosom = v1 * v2;
	if( ( 1.0f - cosom ) > LERP_DELTA )
	{
		omega = acos( cosom );
		sinom = sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) / sinom;
		scale1 = sin( t * omega ) / sinom;
	}
	else
	{
		scale0 = 1.0f - t;
		scale1 = t;
	}
	
	( *this ) = ( v1 * scale0 + v2 * scale1 );
}

/*
=============
ProjectSelfOntoSphere

Projects the z component onto a sphere.
=============
*/
void SbVec3::ProjectSelfOntoSphere( const float radius )
{
	float rsqr = radius * radius;
	float len = Length();
	if( len  < rsqr * 0.5f )
	{
		z = sqrt( rsqr - len );
	}
	else
	{
		z = rsqr / ( 2.0f * sqrt( len ) );
	}
}

}; // namespace sbe::SbMain