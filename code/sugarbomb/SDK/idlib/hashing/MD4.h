#ifndef __MD4_H__
#define __MD4_H__
//*****************************************************************************


//*****************************************************************************

//namespace BFG
//{

/*
===============================================================================

	Calculates a checksum for a block of data
	using the MD4 message-digest algorithm.

===============================================================================
*/

// RB: 64 bit fix, changed long to int
unsigned int MD4_BlockChecksum( const void* data, int length );
// RB end

//} // namespace BFG

#endif /* !__MD4_H__ */
