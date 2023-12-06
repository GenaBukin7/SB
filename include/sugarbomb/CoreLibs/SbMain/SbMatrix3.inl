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

// TODO: temp
#define verify(something)

//*****************************************************************************

ID_INLINE SbMat3::SbMat3()
{
}

ID_INLINE SbMat3::SbMat3( const SbVec3& x, const SbVec3& y, const SbVec3& z )
{
	mat[ 0 ].x = x.x;
	mat[ 0 ].y = x.y;
	mat[ 0 ].z = x.z;
	mat[ 1 ].x = y.x;
	mat[ 1 ].y = y.y;
	mat[ 1 ].z = y.z;
	mat[ 2 ].x = z.x;
	mat[ 2 ].y = z.y;
	mat[ 2 ].z = z.z;
}

ID_INLINE SbMat3::SbMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz )
{
	mat[ 0 ].x = xx;
	mat[ 0 ].y = xy;
	mat[ 0 ].z = xz;
	mat[ 1 ].x = yx;
	mat[ 1 ].y = yy;
	mat[ 1 ].z = yz;
	mat[ 2 ].x = zx;
	mat[ 2 ].y = zy;
	mat[ 2 ].z = zz;
}

ID_INLINE SbMat3::SbMat3( const float src[ 3 ][ 3 ] )
{
	memcpy( mat, src, 3 * 3 * sizeof( float ) );
}

ID_INLINE const SbVec3& SbMat3::operator[]( int index ) const
{
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

ID_INLINE SbVec3& SbMat3::operator[]( int index )
{
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

ID_INLINE SbMat3 SbMat3::operator-() const
{
	return SbMat3(	-mat[0][0], -mat[0][1], -mat[0][2],
					-mat[1][0], -mat[1][1], -mat[1][2],
					-mat[2][0], -mat[2][1], -mat[2][2] );
}

ID_INLINE SbVec3 SbMat3::operator*( const SbVec3& vec ) const
{
	return SbVec3(
			   mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z,
			   mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z,
			   mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z );
}

ID_INLINE SbMat3 SbMat3::operator*( const SbMat3& a ) const
{
	int i, j;
	const float* m1Ptr, *m2Ptr;
	float* dstPtr;
	SbMat3 dst;
	
	m1Ptr = reinterpret_cast<const float*>( this );
	m2Ptr = reinterpret_cast<const float*>( &a );
	dstPtr = reinterpret_cast<float*>( &dst );
	
	for( i = 0; i < 3; i++ )
	{
		for( j = 0; j < 3; j++ )
		{
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					  + m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					  + m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
			dstPtr++;
		}
		m1Ptr += 3;
	}
	return dst;
}

ID_INLINE SbMat3 SbMat3::operator*( const float a ) const
{
	return SbMat3(
			   mat[0].x * a, mat[0].y * a, mat[0].z * a,
			   mat[1].x * a, mat[1].y * a, mat[1].z * a,
			   mat[2].x * a, mat[2].y * a, mat[2].z * a );
}

ID_INLINE SbMat3 SbMat3::operator+( const SbMat3& a ) const
{
	return SbMat3(
			   mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z,
			   mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z,
			   mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z );
}

ID_INLINE SbMat3 SbMat3::operator-( const SbMat3& a ) const
{
	return SbMat3(
			   mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z,
			   mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z,
			   mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z );
}

ID_INLINE SbMat3& SbMat3::operator*=( const float a )
{
	mat[0].x *= a;
	mat[0].y *= a;
	mat[0].z *= a;
	mat[1].x *= a;
	mat[1].y *= a;
	mat[1].z *= a;
	mat[2].x *= a;
	mat[2].y *= a;
	mat[2].z *= a;
	
	return *this;
}

ID_INLINE SbMat3& SbMat3::operator*=( const SbMat3& a )
{
	int i, j;
	const float* m2Ptr;
	float* m1Ptr, dst[3];
	
	m1Ptr = reinterpret_cast<float*>( this );
	m2Ptr = reinterpret_cast<const float*>( &a );
	
	for( i = 0; i < 3; i++ )
	{
		for( j = 0; j < 3; j++ )
		{
			dst[j]  = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					  + m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					  + m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
		}
		m1Ptr[0] = dst[0];
		m1Ptr[1] = dst[1];
		m1Ptr[2] = dst[2];
		m1Ptr += 3;
	}
	return *this;
}

ID_INLINE SbMat3& SbMat3::operator+=( const SbMat3& a )
{
	mat[0].x += a[0].x;
	mat[0].y += a[0].y;
	mat[0].z += a[0].z;
	mat[1].x += a[1].x;
	mat[1].y += a[1].y;
	mat[1].z += a[1].z;
	mat[2].x += a[2].x;
	mat[2].y += a[2].y;
	mat[2].z += a[2].z;
	
	return *this;
}

ID_INLINE SbMat3& SbMat3::operator-=( const SbMat3& a )
{
	mat[0].x -= a[0].x;
	mat[0].y -= a[0].y;
	mat[0].z -= a[0].z;
	mat[1].x -= a[1].x;
	mat[1].y -= a[1].y;
	mat[1].z -= a[1].z;
	mat[2].x -= a[2].x;
	mat[2].y -= a[2].y;
	mat[2].z -= a[2].z;
	
	return *this;
}

ID_INLINE SbVec3 operator*( const SbVec3& vec, const SbMat3& mat )
{
	return mat * vec;
}

ID_INLINE SbMat3 operator*( const float a, const SbMat3& mat )
{
	return mat * a;
}

ID_INLINE SbVec3& operator*=( SbVec3& vec, const SbMat3& mat )
{
	float x = mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z;
	float y = mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z;
	vec.z = mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z;
	vec.x = x;
	vec.y = y;
	return vec;
}

ID_INLINE bool SbMat3::Compare( const SbMat3& a ) const
{
	if( mat[0].Compare( a[0] ) &&
			mat[1].Compare( a[1] ) &&
			mat[2].Compare( a[2] ) )
	{
		return true;
	}
	return false;
}

ID_INLINE bool SbMat3::Compare( const SbMat3& a, const float epsilon ) const
{
	if( mat[0].Compare( a[0], epsilon ) &&
			mat[1].Compare( a[1], epsilon ) &&
			mat[2].Compare( a[2], epsilon ) )
	{
		return true;
	}
	return false;
}

ID_INLINE bool SbMat3::operator==( const SbMat3& a ) const
{
	return Compare( a );
}

ID_INLINE bool SbMat3::operator!=( const SbMat3& a ) const
{
	return !Compare( a );
}

ID_INLINE void SbMat3::Zero()
{
	memset( mat, 0, sizeof( SbMat3 ) );
}

ID_INLINE void SbMat3::Identity()
{
	*this = mat3_identity;
}

ID_INLINE bool SbMat3::IsIdentity( const float epsilon ) const
{
	return Compare( mat3_identity, epsilon );
}

ID_INLINE bool SbMat3::IsSymmetric( const float epsilon ) const
{
	if( SbMath::Fabs( mat[0][1] - mat[1][0] ) > epsilon )
	{
		return false;
	}
	if( SbMath::Fabs( mat[0][2] - mat[2][0] ) > epsilon )
	{
		return false;
	}
	if( SbMath::Fabs( mat[1][2] - mat[2][1] ) > epsilon )
	{
		return false;
	}
	return true;
}

ID_INLINE bool SbMat3::IsDiagonal( const float epsilon ) const
{
	if( SbMath::Fabs( mat[0][1] ) > epsilon ||
			SbMath::Fabs( mat[0][2] ) > epsilon ||
			SbMath::Fabs( mat[1][0] ) > epsilon ||
			SbMath::Fabs( mat[1][2] ) > epsilon ||
			SbMath::Fabs( mat[2][0] ) > epsilon ||
			SbMath::Fabs( mat[2][1] ) > epsilon )
	{
		return false;
	}
	return true;
}

ID_INLINE bool SbMat3::IsRotated() const
{
	return !Compare( mat3_identity );
}

ID_INLINE void SbMat3::ProjectVector( const SbVec3& src, SbVec3& dst ) const
{
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
}

ID_INLINE void SbMat3::UnprojectVector( const SbVec3& src, SbVec3& dst ) const
{
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z;
}

ID_INLINE bool SbMat3::FixDegeneracies()
{
	bool r = mat[0].FixDegenerateNormal();
	r |= mat[1].FixDegenerateNormal();
	r |= mat[2].FixDegenerateNormal();
	return r;
}

ID_INLINE bool SbMat3::FixDenormals()
{
	bool r = mat[0].FixDenormals();
	r |= mat[1].FixDenormals();
	r |= mat[2].FixDenormals();
	return r;
}

ID_INLINE float SbMat3::Trace() const
{
	return ( mat[0][0] + mat[1][1] + mat[2][2] );
}

ID_INLINE SbMat3 SbMat3::OrthoNormalize() const
{
	SbMat3 ortho;
	
	ortho = *this;
	ortho[ 0 ].Normalize();
	ortho[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	ortho[ 2 ].Normalize();
	ortho[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	ortho[ 1 ].Normalize();
	return ortho;
}

ID_INLINE SbMat3& SbMat3::OrthoNormalizeSelf()
{
	mat[ 0 ].Normalize();
	mat[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	mat[ 2 ].Normalize();
	mat[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	mat[ 1 ].Normalize();
	return *this;
}

ID_INLINE SbMat3 SbMat3::Transpose() const
{
	return SbMat3(	mat[0][0], mat[1][0], mat[2][0],
					mat[0][1], mat[1][1], mat[2][1],
					mat[0][2], mat[1][2], mat[2][2] );
}

ID_INLINE SbMat3& SbMat3::TransposeSelf()
{
	float tmp0, tmp1, tmp2;
	
	tmp0 = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp0;
	tmp1 = mat[0][2];
	mat[0][2] = mat[2][0];
	mat[2][0] = tmp1;
	tmp2 = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = tmp2;
	
	return *this;
}

ID_INLINE SbMat3 SbMat3::Inverse() const
{
	SbMat3 invMat;
	
	invMat = *this;
	verify( invMat.InverseSelf() );
	return invMat;
}

ID_INLINE SbMat3 SbMat3::InverseFast() const
{
	SbMat3 invMat;
	
	invMat = *this;
	verify( invMat.InverseFastSelf() );
	return invMat;
}

ID_INLINE SbMat3 SbMat3::TransposeMultiply( const SbMat3& b ) const
{
	return SbMat3(	mat[0].x * b[0].x + mat[1].x * b[1].x + mat[2].x * b[2].x,
					mat[0].x * b[0].y + mat[1].x * b[1].y + mat[2].x * b[2].y,
					mat[0].x * b[0].z + mat[1].x * b[1].z + mat[2].x * b[2].z,
					mat[0].y * b[0].x + mat[1].y * b[1].x + mat[2].y * b[2].x,
					mat[0].y * b[0].y + mat[1].y * b[1].y + mat[2].y * b[2].y,
					mat[0].y * b[0].z + mat[1].y * b[1].z + mat[2].y * b[2].z,
					mat[0].z * b[0].x + mat[1].z * b[1].x + mat[2].z * b[2].x,
					mat[0].z * b[0].y + mat[1].z * b[1].y + mat[2].z * b[2].y,
					mat[0].z * b[0].z + mat[1].z * b[1].z + mat[2].z * b[2].z );
}

ID_INLINE void TransposeMultiply( const SbMat3& transpose, const SbMat3& b, SbMat3& dst )
{
	dst[0].x = transpose[0].x * b[0].x + transpose[1].x * b[1].x + transpose[2].x * b[2].x;
	dst[0].y = transpose[0].x * b[0].y + transpose[1].x * b[1].y + transpose[2].x * b[2].y;
	dst[0].z = transpose[0].x * b[0].z + transpose[1].x * b[1].z + transpose[2].x * b[2].z;
	dst[1].x = transpose[0].y * b[0].x + transpose[1].y * b[1].x + transpose[2].y * b[2].x;
	dst[1].y = transpose[0].y * b[0].y + transpose[1].y * b[1].y + transpose[2].y * b[2].y;
	dst[1].z = transpose[0].y * b[0].z + transpose[1].y * b[1].z + transpose[2].y * b[2].z;
	dst[2].x = transpose[0].z * b[0].x + transpose[1].z * b[1].x + transpose[2].z * b[2].x;
	dst[2].y = transpose[0].z * b[0].y + transpose[1].z * b[1].y + transpose[2].z * b[2].y;
	dst[2].z = transpose[0].z * b[0].z + transpose[1].z * b[1].z + transpose[2].z * b[2].z;
}

ID_INLINE SbMat3 SkewSymmetric( SbVec3 const& src )
{
	return SbMat3( 0.0f, -src.z,  src.y, src.z,   0.0f, -src.x, -src.y,  src.x,   0.0f );
}

ID_INLINE int SbMat3::GetDimension() const
{
	return 9;
}

ID_INLINE const float* SbMat3::ToFloatPtr() const
{
	return mat[0].ToFloatPtr();
}

ID_INLINE float* SbMat3::ToFloatPtr()
{
	return mat[0].ToFloatPtr();
}