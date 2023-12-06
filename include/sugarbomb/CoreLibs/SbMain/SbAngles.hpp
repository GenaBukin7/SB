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

/*
===============================================================================

	Euler angles

===============================================================================
*/

namespace sbe::SbMain
{

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

class SbVec3;
class SbQuat;
class SbRotation;
class SbMat3;
class SbMat4;

class SbAngles
{
public:
	float			pitch;
	float			yaw;
	float			roll;
	
	SbAngles();
	SbAngles( float pitch, float yaw, float roll );
	explicit SbAngles( const SbVec3& v );
	
	void 			Set( float pitch, float yaw, float roll );
	SbAngles& 		Zero();
	
	float			operator[]( int index ) const;
	float& 			operator[]( int index );
	SbAngles		operator-() const;			// negate angles, in general not the inverse rotation
	SbAngles& 		operator=( const SbAngles& a );
	SbAngles		operator+( const SbAngles& a ) const;
	SbAngles& 		operator+=( const SbAngles& a );
	SbAngles		operator-( const SbAngles& a ) const;
	SbAngles& 		operator-=( const SbAngles& a );
	SbAngles		operator*( const float a ) const;
	SbAngles& 		operator*=( const float a );
	SbAngles		operator/( const float a ) const;
	SbAngles& 		operator/=( const float a );
	
	friend SbAngles	operator*( const float a, const SbAngles& b );
	
	bool			Compare( const SbAngles& a ) const;							// exact compare, no epsilon
	bool			Compare( const SbAngles& a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const SbAngles& a ) const;						// exact compare, no epsilon
	bool			operator!=(	const SbAngles& a ) const;						// exact compare, no epsilon
	
	SbAngles& 		Normalize360();	// normalizes 'this'
	SbAngles& 		Normalize180();	// normalizes 'this'
	
	void			Clamp( const SbAngles& min, const SbAngles& max );
	
	int				GetDimension() const;
	
	void			ToVectors( SbVec3* forward, SbVec3* right = nullptr, SbVec3* up = nullptr ) const;
	SbVec3			ToForward() const;
	SbQuat			ToQuat() const;
	SbRotation		ToRotation() const;
	SbMat3			ToMat3() const;
	SbMat4			ToMat4() const;
	SbVec3			ToAngularVelocity() const;
	const float* 	ToFloatPtr() const;
	float* 			ToFloatPtr();
	const char* 	ToString( int precision = 2 ) const;
};

extern SbAngles ang_zero;

#include "SbAngles.inl"

}; // namespace sbe::SbMain