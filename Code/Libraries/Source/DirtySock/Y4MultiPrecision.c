// cl: /Od /GZ /GS /MD /DNDEBUG
/* Target-derived RC4 and RSA padding bodies. The seven independently
 * identified RSA arithmetic helpers now live in cryptrsa.c; see
 * docs/reconstruction/dirtysdk-crypto.md for their donor and target evidence. */

/* Used by the retained RSA padding body below. */
void *memcpy( void *dest, const void *src, unsigned int count );

/* RC4 STATE.  The two indices sit at +0x00 and +0x01 and the permutation
 * follows at +0x02, so the object is 258 bytes.  The layout is read from the
 * two bodies below, both of which address the table as base plus index plus
 * two.
 */
struct Rva0080F200Rc4
{
	unsigned char m_x;              /* +0x00 */
	unsigned char m_y;              /* +0x01 */
	unsigned char m_s[ 256 ];       /* +0x02 */
};

/* 0x0080F200 IS THE RC4 KEY SCHEDULE, with one departure from the standard:
 * IT TAKES A ROUND COUNT and repeats the whole mixing pass that many times.
 * Textbook RC4 does exactly one pass.  A round count below 1 is clamped up to
 * 1, so the caller cannot skip the schedule entirely.
 *
 * The identification rests on the shape, not on any string: a 256-byte
 * identity permutation, then j accumulating S[i] plus a key byte cycled with
 * i modulo the key length, swapping S[i] and S[j].  That is RC4's KSA and
 * nothing else.
 *
 * A ZERO-LENGTH KEY SKIPS THE MIXING ENTIRELY -- the table is left as the
 * identity permutation and both indices at zero, which is a valid state that
 * enciphers nothing.  The test is signed, so a negative length behaves the
 * same way; the modulo inside the loop is UNSIGNED, which is why the length
 * has to be rejected before it is reached rather than after.
 */
void Rva0080F200( struct Rva0080F200Rc4 *state, const unsigned char *key,
	int keyLength, int rounds )
{
	unsigned int i;
	unsigned char j;
	unsigned char t1;
	unsigned char t2;

	if ( rounds < 1 )
		rounds = 1;

	state->m_x = 0;
	state->m_y = 0;

	for ( i = 0; i < 0x100; i++ )
		state->m_s[ i ] = (unsigned char)i;

	if ( keyLength > 0 )
	{
		j = 0;

		for ( ; rounds > 0; rounds-- )
		{
			for ( i = 0; i < 0x100; i++ )
			{
				/* += , not a three-term sum: retail adds the key byte to
				 * S[i] FIRST and folds the result into j last, which is the
				 * grouping a compound assignment produces and a left-to-right
				 * sum does not. */
				j += state->m_s[ i ] + key[ i % keyLength ];

				t1 = state->m_s[ i ];
				t2 = state->m_s[ j ];

				state->m_s[ i ] = t2;
				state->m_s[ j ] = t1;
			}
		}
	}
}

/* 0x0080F300 IS THE RC4 STREAM STEP: it enciphers IN PLACE, so the caller's
 * buffer is overwritten, and because the operation is an exclusive-or the same
 * body both encrypts and decrypts.
 *
 * The two indices are LOADED INTO LOCALS at the top and written back at the
 * end rather than being updated through the object each step.  That is what
 * makes a partial run resumable -- state left in the object is always
 * consistent with how many bytes have actually been processed -- and it is why
 * the body is safe to call repeatedly over a stream.
 *
 * The keystream index is the sum of the two swapped values masked to a byte;
 * the mask is explicit in the bytes rather than implied by a narrow type.
 */
void Rva0080F300( struct Rva0080F200Rc4 *state, unsigned char *data,
	int length )
{
	unsigned char t1;
	unsigned char t2;
	unsigned char x;
	unsigned char y;

	x = state->m_x;
	y = state->m_y;

	for ( ; length > 0; length-- )
	{
		/* Both compound: the increment is an 8-BIT `add dl,1` rather than a
		 * widened one, and the index update folds S[x] into y the same way
		 * the key schedule folds its sum into j. */
		x++;
		y += state->m_s[ x ];

		t1 = state->m_s[ x ];
		t2 = state->m_s[ y ];

		state->m_s[ x ] = t2;
		state->m_s[ y ] = t1;

		/* Compound again -- retail computes the keystream byte BEFORE loading
		 * the plaintext, which is what ^= produces; an explicit
		 * `*data = *data ^ ...` loads the destination first. */
		*data ^= state->m_s[ ( t1 + t2 ) & 0xFF ];
		data++;
	}

	state->m_x = x;
	state->m_y = y;
}

unsigned int Rva007FEA00( void );

/* The padded block: a fixed 0x400-byte buffer with its used length beside it. */
struct Rva0080F430Block
{
	unsigned char m_data[ 0x400 ];
	int m_size;                     /* +0x400 */
};

/* 0x0080F430 BUILDS A PKCS#1 v1.5 TYPE-2 ENCRYPTION BLOCK: a leading 0x00, a
 * 0x02, non-zero random padding, a 0x00 separator, then the payload
 * right-aligned at the end.  Every one of those five pieces is in the bytes,
 * and together they are the padding scheme rather than a resemblance to it.
 *
 * THE RANDOMNESS IS A TICK COUNT RUN THROUGH AN LCG, and the multiplier is
 * 0x10DCD -- 69069, the Knuth/VAX constant.  The seed is the millisecond
 * clock, so the padding is PREDICTABLE to anyone who can guess when the block
 * was built; PKCS#1 assumes a cryptographic source here and this is not one.
 * That is retail's, and it is worth writing down rather than passing over,
 * because the code looks correct in every other respect.
 *
 * The first pass spreads the seed's 32 bits over the whole buffer as 0/1
 * bytes, cycling every 32 positions; the second overwrites each byte by
 * xoring successive LCG outputs into it, REPEATING UNTIL THE BYTE IS NON-ZERO.
 * That retry is what PKCS#1 requires of padding bytes -- a zero would be
 * mistaken for the separator -- and it is a do-while, so a byte is always
 * xored at least once regardless of what the first pass left.
 *
 * The separator is written at one BEFORE the payload's start, so a payload
 * exactly filling the buffer would write outside it; nothing here checks the
 * length against the size.
 */
void Rva0080F430( struct Rva0080F430Block *block, const void *data,
	int length )
{
	int i;
	unsigned int uSeed;

	uSeed = Rva007FEA00();

	for ( i = 0; i < block->m_size; i++ )
		block->m_data[ i ] = ( uSeed & ( 1 << ( i & 0x1F ) ) ) != 0;

	for ( i = 0; i < block->m_size; i++ )
	{
		do
		{
			uSeed = uSeed * 0x10DCD + 0x10DCD;
			block->m_data[ i ] ^= (char)uSeed;
		}
		while ( block->m_data[ i ] == 0 );
	}

	block->m_data[ 0 ] = 0;
	block->m_data[ 1 ] = 2;

	i = block->m_size - length;
	block->m_data[ i - 1 ] = 0;

	memcpy( &block->m_data[ i ], data, length );
}
