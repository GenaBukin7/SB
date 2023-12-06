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

//*****************************************************************************

ID_INLINE idMat4::idMat4()
{
}

ID_INLINE idMat4::idMat4( const idVec4& x, const idVec4& y, const idVec4& z, const idVec4& w )
{
	mat[ 0 ] = x;
	mat[ 1 ] = y;
	mat[ 2 ] = z;
	mat[ 3 ] = w;
}

ID_INLINE idMat4::idMat4( const float xx, const float xy, const float xz, const float xw,
						  const float yx, const float yy, const float yz, const float yw,
						  const float zx, const float zy, const float zz, const float zw,
						  const float wx, const float wy, const float wz, const float ww )
{
	mat[0][0] = xx;
	mat[0][1] = xy;
	mat[0][2] = xz;
	mat[0][3] = xw;
	mat[1][0] = yx;
	mat[1][1] = yy;
	mat[1][2] = yz;
	mat[1][3] = yw;
	mat[2][0] = zx;
	mat[2][1] = zy;
	mat[2][2] = zz;
	mat[2][3] = zw;
	mat[3][0] = wx;
	mat[3][1] = wy;
	mat[3][2] = wz;
	mat[3][3] = ww;
}

ID_INLINE idMat4::idMat4( const idMat3& rotation, const idVec3& translation )
{
	// NOTE: idMat3 is transposed because it is column-major
	mat[ 0 ][ 0 ] = rotation[0][0];
	mat[ 0 ][ 1 ] = rotation[1][0];
	mat[ 0 ][ 2 ] = rotation[2][0];
	mat[ 0 ][ 3 ] = translation[0];
	mat[ 1 ][ 0 ] = rotation[0][1];
	mat[ 1 ][ 1 ] = rotation[1][1];
	mat[ 1 ][ 2 ] = rotation[2][1];
	mat[ 1 ][ 3 ] = translation[1];
	mat[ 2 ][ 0 ] = rotation[0][2];
	mat[ 2 ][ 1 ] = rotation[1][2];
	mat[ 2 ][ 2 ] = rotation[2][2];
	mat[ 2 ][ 3 ] = translation[2];
	mat[ 3 ][ 0 ] = 0.0f;
	mat[ 3 ][ 1 ] = 0.0f;
	mat[ 3 ][ 2 ] = 0.0f;
	mat[ 3 ][ 3 ] = 1.0f;
}

ID_INLINE idMat4::idMat4( const float src[ 4 ][ 4 ] )
{
	memcpy( mat, src, 4 * 4 * sizeof( float ) );
}

ID_INLINE const idVec4& idMat4::operator[]( int index ) const
{
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

ID_INLINE idVec4& idMat4::operator[]( int index )
{
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

ID_INLINE idMat4 idMat4::operator*( const float a ) const
{
	return idMat4(
			   mat[0].x * a, mat[0].y * a, mat[0].z * a, mat[0].w * a,
			   mat[1].x * a, mat[1].y * a, mat[1].z * a, mat[1].w * a,
			   mat[2].x * a, mat[2].y * a, mat[2].z * a, mat[2].w * a,
			   mat[3].x * a, mat[3].y * a, mat[3].z * a, mat[3].w * a );
}

ID_INLINE idVec4 idMat4::operator*( const idVec4& vec ) const
{
	return idVec4(
			   mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w * vec.w,
			   mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w * vec.w,
			   mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w * vec.w,
			   mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w * vec.w );
}

ID_INLINE idVec3 idMat4::operator*( const idVec3& vec ) const
{
	float s = mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w;
	if( s == 0.0f )
	{
		return idVec3( 0.0f, 0.0f, 0.0f );
	}
	if( s == 1.0f )
	{
		return idVec3(
				   mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w,
				   mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w,
				   mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w );
	}
	else
	{
		float invS = 1.0f / s;
		return idVec3(
				   ( mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w ) * invS,
				   ( mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w ) * invS,
				   ( mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w ) * invS );
	}
}

ID_INLINE idMat4 idMat4::operator*( const idMat4& a ) const
{
	int i, j;
	const float* m1Ptr, *m2Ptr;
	float* dstPtr;
	idMat4 dst;
	
	m1Ptr = reinterpret_cast<const float*>( this );
	m2Ptr = reinterpret_cast<const float*>( &a );
	dstPtr = reinterpret_cast<float*>( &dst );
	
	for( i = 0; i < 4; i++ )
	{
		for( j = 0; j < 4; j++ )
		{
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
					  + m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
					  + m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
					  + m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
	return dst;
}

ID_INLINE idMat4 idMat4::operator+( const idMat4& a ) const
{
	return idMat4(
			   mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z, mat[0].w + a[0].w,
			   mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z, mat[1].w + a[1].w,
			   mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z, mat[2].w + a[2].w,
			   mat[3].x + a[3].x, mat[3].y + a[3].y, mat[3].z + a[3].z, mat[3].w + a[3].w );
}

ID_INLINE idMat4 idMat4::operator-( const idMat4& a ) const
{
	return idMat4(
			   mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z, mat[0].w - a[0].w,
			   mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z, mat[1].w - a[1].w,
			   mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z, mat[2].w - a[2].w,
			   mat[3].x - a[3].x, mat[3].y - a[3].y, mat[3].z - a[3].z, mat[3].w - a[3].w );
}

ID_INLINE idMat4& idMat4::operator*=( const float a )
{
	mat[0].x *= a;
	mat[0].y *= a;
	mat[0].z *= a;
	mat[0].w *= a;
	mat[1].x *= a;
	mat[1].y *= a;
	mat[1].z *= a;
	mat[1].w *= a;
	mat[2].x *= a;
	mat[2].y *= a;
	mat[2].z *= a;
	mat[2].w *= a;
	mat[3].x *= a;
	mat[3].y *= a;
	mat[3].z *= a;
	mat[3].w *= a;
	return *this;
}

ID_INLINE idMat4& idMat4::operator*=( const idMat4& a )
{
	*this = ( *this ) * a;
	return *this;
}

ID_INLINE idMat4& idMat4::operator+=( const idMat4& a )
{
	mat[0].x += a[0].x;
	mat[0].y += a[0].y;
	mat[0].z += a[0].z;
	mat[0].w += a[0].w;
	mat[1].x += a[1].x;
	mat[1].y += a[1].y;
	mat[1].z += a[1].z;
	mat[1].w += a[1].w;
	mat[2].x += a[2].x;
	mat[2].y += a[2].y;
	mat[2].z += a[2].z;
	mat[2].w += a[2].w;
	mat[3].x += a[3].x;
	mat[3].y += a[3].y;
	mat[3].z += a[3].z;
	mat[3].w += a[3].w;
	return *this;
}

ID_INLINE idMat4& idMat4::operator-=( const idMat4& a )
{
	mat[0].x -= a[0].x;
	mat[0].y -= a[0].y;
	mat[0].z -= a[0].z;
	mat[0].w -= a[0].w;
	mat[1].x -= a[1].x;
	mat[1].y -= a[1].y;
	mat[1].z -= a[1].z;
	mat[1].w -= a[1].w;
	mat[2].x -= a[2].x;
	mat[2].y -= a[2].y;
	mat[2].z -= a[2].z;
	mat[2].w -= a[2].w;
	mat[3].x -= a[3].x;
	mat[3].y -= a[3].y;
	mat[3].z -= a[3].z;
	mat[3].w -= a[3].w;
	return *this;
}

ID_INLINE idMat4 operator*( const float a, const idMat4& mat )
{
	return mat * a;
}

ID_INLINE idVec4 operator*( const idVec4& vec, const idMat4& mat )
{
	return mat * vec;
}

ID_INLINE idVec3 operator*( const idVec3& vec, const idMat4& mat )
{
	return mat * vec;
}

ID_INLINE idVec4& operator*=( idVec4& vec, const idMat4& mat )
{
	vec = mat * vec;
	return vec;
}

ID_INLINE idVec3& operator*=( idVec3& vec, const idMat4& mat )
{
	vec = mat * vec;
	return vec;
}

ID_INLINE bool idMat4::Compare( const idMat4& a ) const
{
	dword i;
	const float* ptr1, *ptr2;
	
	ptr1 = reinterpret_cast<const float*>( mat );
	ptr2 = reinterpret_cast<const float*>( a.mat );
	for( i = 0; i < 4 * 4; i++ )
	{
		if( ptr1[i] != ptr2[i] )
		{
			return false;
		}
	}
	return true;
}

ID_INLINE bool idMat4::Compare( const idMat4& a, const float epsilon ) const
{
	dword i;
	const float* ptr1, *ptr2;
	
	ptr1 = reinterpret_cast<const float*>( mat );
	ptr2 = reinterpret_cast<const float*>( a.mat );
	for( i = 0; i < 4 * 4; i++ )
	{
		if( idMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon )
		{
			return false;
		}
	}
	return true;
}

ID_INLINE bool idMat4::operator==( const idMat4& a ) const
{
	return Compare( a );
}

ID_INLINE bool idMat4::operator!=( const idMat4& a ) const
{
	return !Compare( a );
}

ID_INLINE void idMat4::Zero()
{
	memset( mat, 0, sizeof( idMat4 ) );
}

ID_INLINE void idMat4::Identity()
{
	*this = mat4_identity;
}

ID_INLINE bool idMat4::IsIdentity( const float epsilon ) const
{
	return Compare( mat4_identity, epsilon );
}

ID_INLINE bool idMat4::IsSymmetric( const float epsilon ) const
{
	for( int i = 1; i < 4; i++ )
	{
		for( int j = 0; j < i; j++ )
		{
			if( idMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon )
			{
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool idMat4::IsDiagonal( const float epsilon ) const
{
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			if( i != j && idMath::Fabs( mat[i][j] ) > epsilon )
			{
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool idMat4::IsRotated() const
{
	if( !mat[ 0 ][ 1 ] && !mat[ 0 ][ 2 ] &&
			!mat[ 1 ][ 0 ] && !mat[ 1 ][ 2 ] &&
			!mat[ 2 ][ 0 ] && !mat[ 2 ][ 1 ] )
	{
		return false;
	}
	return true;
}

ID_INLINE void idMat4::ProjectVector( const idVec4& src, idVec4& dst ) const
{
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
	dst.w = src * mat[ 3 ];
}

ID_INLINE void idMat4::UnprojectVector( const idVec4& src, idVec4& dst ) const
{
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z + mat[ 3 ] * src.w;
}

ID_INLINE float idMat4::Trace() const
{
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] );
}

ID_INLINE idMat4 idMat4::Inverse() const
{
	idMat4 invMat;
	
	invMat = *this;
	verify( invMat.InverseSelf() );
	return invMat;
}

ID_INLINE idMat4 idMat4::InverseFast() const
{
	idMat4 invMat;
	
	invMat = *this;
	verify( invMat.InverseFastSelf() );
	return invMat;
}

ID_INLINE idMat4 idMat3::ToMat4() const
{
	// NOTE: idMat3 is transposed because it is column-major
	return idMat4(	mat[0][0],	mat[1][0],	mat[2][0],	0.0f,
					mat[0][1],	mat[1][1],	mat[2][1],	0.0f,
					mat[0][2],	mat[1][2],	mat[2][2],	0.0f,
					0.0f,		0.0f,		0.0f,		1.0f );
}

ID_INLINE int idMat4::GetDimension() const
{
	return 16;
}

ID_INLINE const float* idMat4::ToFloatPtr() const
{
	return mat[0].ToFloatPtr();
}

ID_INLINE float* idMat4::ToFloatPtr()
{
	return mat[0].ToFloatPtr();
}