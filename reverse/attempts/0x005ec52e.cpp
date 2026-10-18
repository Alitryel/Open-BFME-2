// ?BfmeLess00574AA0@S4SortElem8@@QBE_NABU1@@Z
// partial score=0.9 date=2026-10-18
// cl: /DNDEBUG /MD /EHsc
// candidate M: both sides read a by-value copy of the flags word
class AsciiString;
bool __cdecl operator<(const AsciiString &left, const AsciiString &right);

struct RvaBits
{
	unsigned int m_bits;
	bool test( int bit ) const { return ( m_bits & ( 1 << bit ) ) != 0; }
};

struct S4SortElem8Army
{
	char m_padToKey[ 0x9c ];
	int m_key;
};

class S4SortElem8Record
{
public:
	RvaBits getFlags() const { return m_flags; }

	char m_pad00[ 0x110 ];
	RvaBits m_flags;
};

struct S4SortElem8
{
	S4SortElem8Army *m_army;
	S4SortElem8Record *m_record;
	bool BfmeLess00574AA0( const S4SortElem8 &other ) const;
};

bool S4SortElem8::BfmeLess00574AA0( const S4SortElem8 &other ) const
{
	if ( m_record->getFlags().test( 26 ) != other.m_record->getFlags().test( 26 ) )
		return m_record->getFlags().test( 26 );
	int leftKey = m_army->m_key;
	int rightKey = other.m_army->m_key;
	if ( leftKey != rightKey )
		return leftKey > rightKey;
	return operator<( *(const AsciiString *)( (const char *)m_army + 4 ),
		*(const AsciiString *)( (const char *)other.m_army + 4 ) );
}
