/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2019, 2023 SugarBombEngine Developers

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

#include <cstring>

#include "SbMath.hpp"
#include "SbVec3.hpp"

//#include <CoreLibs/SbSystem/SbSystemDefs.hpp>

//*****************************************************************************

namespace sbe::SbMain
{

//class SbVec3;
class SbAngles;
class SbQuat;
class idCQuat;
class idRotation;
class SbMat4;

//===============================================================
//
//	idMat3 - 3x3 matrix
//
//	NOTE:	matrix is column-major
//
//===============================================================

class SbMat3
{
public:
	SbMat3();
	explicit SbMat3( const SbVec3& x, const SbVec3& y, const SbVec3& z );
	explicit SbMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz );
	explicit SbMat3( const float src[ 3 ][ 3 ] );
	
	const SbVec3& 	operator[]( int index ) const;
	SbVec3& 		operator[]( int index );
	SbMat3			operator-() const;
	SbMat3			operator*( const float a ) const;
	SbVec3			operator*( const SbVec3& vec ) const;
	SbMat3			operator*( const SbMat3& a ) const;
	SbMat3			operator+( const SbMat3& a ) const;
	SbMat3			operator-( const SbMat3& a ) const;
	SbMat3& 		operator*=( const float a );
	SbMat3& 		operator*=( const SbMat3& a );
	SbMat3& 		operator+=( const SbMat3& a );
	SbMat3& 		operator-=( const SbMat3& a );
	
	friend SbMat3	operator*( const float a, const SbMat3& mat );
	friend SbVec3	operator*( const SbVec3& vec, const SbMat3& mat );
	friend SbVec3& 	operator*=( SbVec3& vec, const SbMat3& mat );
	
	bool			Compare( const SbMat3& a ) const;						// exact compare, no epsilon
	bool			Compare( const SbMat3& a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const SbMat3& a ) const;					// exact compare, no epsilon
	bool			operator!=( const SbMat3& a ) const;					// exact compare, no epsilon
	
	void			Zero();
	void			Identity();
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated() const;
	
	void			ProjectVector( const SbVec3& src, SbVec3& dst ) const;
	void			UnprojectVector( const SbVec3& src, SbVec3& dst ) const;
	
	bool			FixDegeneracies();	// fix degenerate axial cases
	bool			FixDenormals();		// change tiny numbers to zero
	
	float			Trace() const;
	float			Determinant() const;
	SbMat3			OrthoNormalize() const;
	SbMat3& 		OrthoNormalizeSelf();
	SbMat3			Transpose() const;	// returns transpose
	SbMat3& 		TransposeSelf();
	SbMat3			Inverse() const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf();		// returns false if determinant is zero
	SbMat3			InverseFast() const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf();	// returns false if determinant is zero
	SbMat3			TransposeMultiply( const SbMat3& b ) const;
	
	SbMat3			InertiaTranslate( const float mass, const SbVec3& centerOfMass, const SbVec3& translation ) const;
	SbMat3& 		InertiaTranslateSelf( const float mass, const SbVec3& centerOfMass, const SbVec3& translation );
	SbMat3			InertiaRotate( const SbMat3& rotation ) const;
	SbMat3& 		InertiaRotateSelf( const SbMat3& rotation );
	
	int				GetDimension() const;
	
	SbAngles		ToAngles() const;
	SbQuat			ToQuat() const;
	idCQuat			ToCQuat() const;
	idRotation		ToRotation() const;
	SbMat4			ToMat4() const;
	SbVec3			ToAngularVelocity() const;
	const float* 	ToFloatPtr() const;
	float* 			ToFloatPtr();
	const char* 	ToString( int precision = 2 ) const;
	
	friend void		TransposeMultiply( const SbMat3& inv, const SbMat3& b, SbMat3& dst );
	friend SbMat3	SkewSymmetric( SbVec3 const& src );
	
private:
	SbVec3			mat[ 3 ];
};

extern SbMat3 mat3_zero;
extern SbMat3 mat3_identity;
#define mat3_default	mat3_identity

#include "SbMatrix3.inl"

}; // namespace sbe::SbMain