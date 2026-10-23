// cl: /Od /GZ /GS /MD /DNDEBUG

int memcmp( const void *first, const void *second, unsigned int count );

struct Rva0080D890Entry
{
	int m_value;
	int m_length;
	unsigned char m_bytes[ 0x10 ];
};

// Matched DIR32 witnesses (w=5) place this table at VA 0x00CE40A8
// (.rdata). It has nine live entries plus the m_value==0 terminator at +0xD8;
// the ten 24-byte entries end at VA 0x00CE4198. No closer named symbol is
// recorded in reverse/symbols.csv.
#pragma data_seg(".rdata")
struct Rva0080D890Entry g_Rva0112C8D0[] = {
	{ 1, 3, { 0x55, 0x04, 0x06 } },
	{ 3, 3, { 0x55, 0x04, 0x07 } },
	{ 2, 3, { 0x55, 0x04, 0x08 } },
	{ 4, 3, { 0x55, 0x04, 0x0A } },
	{ 5, 3, { 0x55, 0x04, 0x0B } },
	{ 6, 3, { 0x55, 0x04, 0x03 } },
	{ 7, 9, { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01 } },
	{ 8, 9, { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x04 } },
	{ 9, 9, { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05 } },
	{ 0, 0, { 0 } },
};
#pragma data_seg()

int Rva0080D890( const void *bytes, int length )
{
	int result;
	int index;

	result = 0;
	index = 0;
	for ( ; g_Rva0112C8D0[ index ].m_value != 0; index++ )
	{
		if ( length >= g_Rva0112C8D0[ index ].m_length
			&& memcmp( bytes, g_Rva0112C8D0[ index ].m_bytes,
				g_Rva0112C8D0[ index ].m_length ) == 0 )
		{
			result = g_Rva0112C8D0[ index ].m_value;
			break;
		}
	}

	return result;
}
