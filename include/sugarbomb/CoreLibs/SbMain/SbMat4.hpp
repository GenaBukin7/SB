/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2023 SugarBombEngine Developers

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

#include "SbMath.hpp"
#include "SbVec4.hpp"

//#include <CoreLibs/SbSystem/SbSystemDefs.hpp>

//*****************************************************************************

namespace sbe::SbMain
{

class SbMat3;
class SbVec3;

//===============================================================
//
//	idMat4 - 4x4 matrix
//
//===============================================================

class SbMat4
{
public:
	SbMat4();
	explicit SbMat4( const SbVec4& x, const SbVec4& y, const SbVec4& z, const SbVec4& w );
	explicit SbMat4( const float xx, const float xy, const float xz, const float xw,
					 const float yx, const float yy, const float yz, const float yw,
					 const float zx, const float zy, const float zz, const float zw,
					 const float wx, const float wy, const float wz, const float ww );
	explicit SbMat4( const SbMat3& rotation, const SbVec3& translation );
	explicit SbMat4( const float src[ 4 ][ 4 ] );
	
	const SbVec4& 	operator[]( int index ) const;
	SbVec4& 		operator[]( int index );
	SbMat4			operator*( const float a ) const;
	SbVec4			operator*( const SbVec4& vec ) const;
	SbVec3			operator*( const SbVec3& vec ) const;
	SbMat4			operator*( const SbMat4& a ) const;
	SbMat4			operator+( const SbMat4& a ) const;
	SbMat4			operator-( const SbMat4& a ) const;
	SbMat4& 		operator*=( const float a );
	SbMat4& 		operator*=( const SbMat4& a );
	SbMat4& 		operator+=( const SbMat4& a );
	SbMat4& 		operator-=( const SbMat4& a );
	
	friend SbMat4	operator*( const float a, const SbMat4& mat );
	friend SbVec4	operator*( const SbVec4& vec, const SbMat4& mat );
	friend SbVec3	operator*( const SbVec3& vec, const SbMat4& mat );
	friend SbVec4& 	operator*=( SbVec4& vec, const SbMat4& mat );
	friend SbVec3& 	operator*=( SbVec3& vec, const SbMat4& mat );
	
	bool			Compare( const SbMat4& a ) const;						// exact compare, no epsilon
	bool			Compare( const SbMat4& a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const SbMat4& a ) const;					// exact compare, no epsilon
	bool			operator!=( const SbMat4& a ) const;					// exact compare, no epsilon
	
	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated() const;
	
	void			ProjectVector( const SbVec4& src, SbVec4& dst ) const;
	void			UnprojectVector( const SbVec4& src, SbVec4& dst ) const;
	
	float			Trace() const;
	float			Determinant() const;
	SbMat4			Transpose() const;	// returns transpose
	SbMat4& 		TransposeSelf();
	SbMat4			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	SbMat4			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero
	SbMat4			TransposeMultiply( const SbMat4& b ) const;
	
	int				GetDimension() const;
	
	const float* 	ToFloatPtr() const;
	float* 			ToFloatPtr();
	const char* 	ToString( int precision = 2 ) const;
	
private:
	SbVec4			mat[ 4 ];
};

extern SbMat4 mat4_zero;
extern SbMat4 mat4_identity;
#define mat4_default	mat4_identity

#include "SbMat4.inl"

}; // namespace sbe::SbMain