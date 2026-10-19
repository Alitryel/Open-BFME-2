// ?Rva007E8B00@@YAHPAEHPBD@Z
// partial score=0.957 date=2026-10-19
// cl: /GS
// BANK (seat6 d8): FESL record-field replacer, retail 0x00655B90..0x00655DB5 (549B,
// cdecl, 3 args: buffer, size, field; returns written length - 1). This is the
// optimized FESL-TU copy of DirtySock's matched /Od C body _Rva007EC780
// (Code/Libraries/Source/DirtySock/Y4TextToValue.c, 0x006596B0): the function
// below is that body verbatim with the FESL tables substituted, the field index
// cast to unsigned char (retail movzx edx,bl), compiled inside the owner unit
// Rva007E8D30FeslSetField.cpp. 544B vs 549B; the whole control flow, loops,
// inline memcmp/memcpy and memmove calls match. Remaining residue (only two):
//  1. register roles: retail pValue=EBX (shares EBX with the *field byte BL) and
//     the field length i=EBP pushed late at 0x00655CE7; cl gives i=EBX, pValue=EBP
//     and pushes EBP in the prologue (+1 byte shift and every EBX/EBP operand).
//  2. tail: retail cmp byte [sep],0Ah then reloads sep in the else arm; cl hoists
//     one mov al,[sep] above the pValue[i]==0 branch.
// Inert (all 544B, identical residue): separate length variable (int/unsigned,
// first/last decl), pValue decl first/last, register keyword, pTail/pValue
// assignment forms (4), static helper + direct call from Rva007E8D30, plain .c
// compile (signed/unsigned index), /G5 /G6 /Ox /Ob1 /Oi /Ot, vc71-sp1 and
// vc71-ddk-4035 profiles; /G7 555B, /O1|/Os 443B, /Oy- 579B; tail forms (unsigned
// casts, inverted if, early return, ternary 548B, i-- first); permute.py 793
// trials no gain. No volatile/barrier in this bank.
// 0x007E8D30: the FESL message TU's private copy of the escaped string-field
// writer (compare the DirtySock copy Rva007ECE60 at 0x007ECE60).  It is a
// file-static helper whose only caller, 0x007E8EF0, hands it the field name in
// ECX and the value in EAX: MSVC's private register convention for a static
// function, reproduced here by compiling it with that caller.
// UPDATE (same seat, later): writing the length loop as
// for (i = 1; field[i - 1] >= ' '; i++) {}   (same value as the donor's
// for (i = 0; field[i] >= ' '; i++) {} i++;) flips cl to retail's roles:
// pValue=EBX, i=EBP with the late push ebp, and retail's epilogue order; the
// body is exact up to 0x00655CE7. Score 0.883 -> 0.957. Remaining: that loop is
// rotated as mov ebp,1 / [esi+ebp-1] instead of retail's xor ebp,ebp / [esi+ebp]
// / trailing inc ebp, plus the hoisted separator load in the tail. A +1 index
// (field[i + 1]) flips the roles too; plain field[i] with i=1, unsigned/long/short
// i, cast spellings, while/for/do forms, ++i inside iDelta, separate length
// variables, early-initialised length, and tail if/else/early-return/store-first
// forms on this base do not give both. permute.py 836 trials from it: no gain.
// 0x007E8D30: the FESL message TU's private copy of the escaped string-field
// writer (compare the DirtySock copy Rva007ECE60 at 0x007ECE60).  It is a
// file-static helper whose only caller, 0x007E8EF0, hands it the field name in
// ECX and the value in EAX: MSVC's private register convention for a static
// function, reproduced here by compiling it with that caller.

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern void *bfmeGo929C();

// 0x007EC030: deletes the named field from the record.
int Rva007EC030( char *text, const char *tag );

// 0x007E8B00: replaces or appends one field in the record; still a dump.
extern void d_007e8b00( void );
typedef int ( __cdecl *Rva007E8B00Replace )( char *record, int size, char *field );

// g_Rva011293A0HexFirst: matched references place it at VA 0xce0c10; retail contents, sized to the
// 0x108-byte gap before the next known global there.
char g_Rva011293A0HexFirst[264] = {
	48, 48, 48, 48, 48, 48, 48, 48,
	48, 48, 48, 48, 48, 48, 48, 48,
	49, 49, 49, 49, 49, 49, 49, 49,
	49, 49, 49, 49, 49, 49, 49, 49,
	50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50,
	51, 51, 51, 51, 51, 51, 51, 51,
	51, 51, 51, 51, 51, 51, 51, 51,
	52, 52, 52, 52, 52, 52, 52, 52,
	52, 52, 52, 52, 52, 52, 52, 52,
	53, 53, 53, 53, 53, 53, 53, 53,
	53, 53, 53, 53, 53, 53, 53, 53,
	54, 54, 54, 54, 54, 54, 54, 54,
	54, 54, 54, 54, 54, 54, 54, 54,
	55, 55, 55, 55, 55, 55, 55, 55,
	55, 55, 55, 55, 55, 55, 55, 55,
	56, 56, 56, 56, 56, 56, 56, 56,
	56, 56, 56, 56, 56, 56, 56, 56,
	57, 57, 57, 57, 57, 57, 57, 57,
	57, 57, 57, 57, 57, 57, 57, 57,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	98, 98, 98, 98, 98, 98, 98, 98,
	98, 98, 98, 98, 98, 98, 98, 98,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100,
	101, 101, 101, 101, 101, 101, 101, 101,
	101, 101, 101, 101, 101, 101, 101, 101,
	102, 102, 102, 102, 102, 102, 102, 102,
	102, 102, 102, 102, 102, 102, 102, 102,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_Rva011294A8HexSecond: matched references place it at VA 0xce0d18 (.rdata); retail bytes.
char g_Rva011294A8HexSecond[256] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
};


// g_bfmeFeslFieldClassTable: FESL record-field name class table, retail VA
// 0xce0e20 (256 bytes, .rdata) directly after g_Rva011294A8HexSecond. Every
// consumer is the FESL record-field replacer d_007e8b00 (0x00655b90): it
// compares record and field characters by table class (0 = invalid/end, 1 =
// field separator ':' or '=', >=2 = the upper-cased character value, so
// 'a'-'z' fold to 'A'-'Z' and digits/underscore stay). Values read from
// retail; the BFME 1 copy names it Rva007E8B00ClassTable (no EA identifier
// recovered), so this is a neutral descriptive name.
extern const unsigned char g_bfmeFeslFieldClassTable[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x5f,
	0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// g_bfmeFeslFieldSeparator: the '\n' appended after a replaced field by the
// same FESL record-field replacer (retail .data byte 0x00dd7f45 = 0x0A,
// between the "or@@" literal run and the 0x009d7f48 pointer table); BFME 1's
// bank calls the same byte Rva007E8B00Separator and compares it with '\n'.
char g_bfmeFeslFieldSeparator = '\n';

extern "C" void * __cdecl memmove( void *dest, const void *src, unsigned int count );
extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
extern "C" void * __cdecl memcpy( void *dest, const void *src, unsigned int count );

int Rva007E8B00( unsigned char *buffer, int size, const char *field )
{
	int i;
	int iDelta;
	unsigned char *p;
	unsigned char *pValue;
	unsigned char *pTail;
	unsigned char cClassBuffer;
	unsigned char cClassField;
	unsigned char *pBuffer;

	pBuffer = buffer;

	if ( pBuffer == 0 )
	{
		return -1;
	}

	if ( field == 0 || (unsigned int)*field <= ' ' )
	{
		return -1;
	}

	if ( *field == '~' )
	{
		for ( p = pBuffer; *p != 0; p++ )
		{
		}

		if ( p != pBuffer && p[ -1 ] >= ' '
			&& p[ -1 ] != g_bfmeFeslFieldSeparator
			&& p < pBuffer + size - 1 )
		{
			*p = g_bfmeFeslFieldSeparator;
			p++;
			*p = 0;
		}

		pTail = p;
		pValue = pTail;
	}
	else
	{
		p = pBuffer;

		for ( ;; )
		{
			if ( *p == 0 )
			{
				if ( p != pBuffer && p[ -1 ] >= ' '
					&& p[ -1 ] != g_bfmeFeslFieldSeparator
					&& p < pBuffer + size - 1 )
				{
					*p = g_bfmeFeslFieldSeparator;
					p++;
					*p = 0;
				}

				pTail = p;
				pValue = pTail;
				break;
			}

			if ( *p <= ' ' )
			{
				p++;
				continue;
			}

			if ( g_bfmeFeslFieldClassTable[ *p ] == 1 )
			{
				pTail = p;
				pValue = pTail;
				break;
			}

			for ( i = 0; ; i++ )
			{
				cClassBuffer = g_bfmeFeslFieldClassTable[ p[ i ] ];
				cClassField = g_bfmeFeslFieldClassTable[ (unsigned char)field[ i ] ];

				if ( cClassBuffer != cClassField || cClassBuffer < 2 )
				{
					break;
				}
			}

			if ( cClassBuffer + cClassField == 2 )
			{
				pTail = p;
				pValue = pTail;

				for ( ; *pTail >= ' '; pTail++ )
				{
				}

				if ( *pTail > 0 )
				{
					pTail++;
				}

				break;
			}

			do
			{
				p++;
			}
			while ( *p >= ' ' );
		}
	}

	for ( i = 1; (unsigned int)field[ i - 1 ] >= ' '; i++ )
	{
	}

	iDelta = i - ( pTail - pValue );

	for ( p = pTail; *p != 0; p++ )
	{
	}

	p++;

	if ( iDelta > 0 && pBuffer + size - p < iDelta )
	{
		return -1;
	}

	if ( iDelta == 0 && memcmp( pValue, field, i ) == 0 )
	{
		return 0;
	}

	if ( iDelta > 0 )
	{
		memmove( pTail + iDelta, pTail, p - pTail );
	}

	if ( iDelta < 0 )
	{
		memmove( pValue, pValue - iDelta, p - ( pValue - iDelta ) );
	}

	memcpy( pValue, field, i );

	if ( pValue[ i ] == 0 && g_bfmeFeslFieldSeparator != '\n' )
	{
		pValue[ i - 1 ] = 0;
	}
	else
	{
		pValue[ i - 1 ] = g_bfmeFeslFieldSeparator;
	}

	return i - 1;
}

// The record's "name=" prefix, as the DirtySock copy's Rva007EC730 writes it:
// a null name empties the record instead.
static char *Rva007E8D30Name( char *empty, char *dest, const char *src )
{
	if( src == 0 )
	{
		*empty = 0;
	}
	else
	{
		while( *src != 0 )
		{
			*dest = *src;
			dest++;
			src++;
		}

		*dest = '=';
		dest++;
	}

	return dest;
}

static int Rva007E8D30( const char *name, const char *value, char *record, int size )
{
	char *item;
	char *p;
	const unsigned char *pScan;
	const unsigned char *pSrc;
	unsigned int iLeft;
	int iResult;

	item = ( char * )( ( Rva007EFFC0Allocator * )bfmeGo929C() )->allocate( 0x32200, 2 );
	pSrc = ( const unsigned char * )value;

	if( pSrc == 0 )
	{
		Rva007EC030( record, name );
		return 0;
	}

	p = Rva007E8D30Name( record, item, name );

	// Retail starts the unsigned budget at 4 (add esi,4): sizeof the item
	// POINTER, so it wraps and never limits the 0x32200-byte block.
	iLeft = sizeof( item );
	iLeft -= p - item;

	for( pScan = pSrc; *pScan != 0 && *pScan != ' '; pScan++ )
	{
	}

	if( *pScan == ' ' )
	{
		*p = '"';
		p++;
		iLeft--;
	}

	for( ; *pSrc != 0 && iLeft > 0; pSrc++ )
	{
		if( *pSrc < ' ' || *pSrc == 0x7F || *pSrc == '=' || *pSrc == '"'
			|| *pSrc == ':' || *pSrc == '%' || *pSrc == '^' )
		{
			if( iLeft >= 3 )
			{
				*p = '%';
				p++;
				*p = g_Rva011293A0HexFirst[ *pSrc ];
				p++;
				*p = g_Rva011294A8HexSecond[ *pSrc ];
				p++;
			}

			iLeft -= 3;
		}
		else
		{
			*p = *pSrc;
			p++;
			iLeft--;
		}
	}

	if( iLeft <= 0 )
	{
		return -1;
	}

	if( *pScan == ' ' )
	{
		*p = '"';
		p++;
	}

	*p = 0;

	iResult = ( ( Rva007E8B00Replace )d_007e8b00 )( record, size, item );
	( ( Rva007EFFC0Allocator * )bfmeGo929C() )->release( item, 0 );
	return iResult;
}

// 0x007E8EF0, the helper's only caller: stores the escaped field into the
// message record at +0x10 (size +0x14) and records -100 at +0x24 on failure.
class Rva007E8810Message
{
public:
	void rva007E8EF0( const char *key, const char *value );

private:
	char m_pad[0x10];
	char *m_10;
	int m_14;
	char m_pad18[0x0c];
	int m_24;
};

void Rva007E8810Message::rva007E8EF0( const char *key, const char *value )
{
	if( Rva007E8D30( key, value, m_10, m_14 ) < 0 )
		m_24 = -100;
}
