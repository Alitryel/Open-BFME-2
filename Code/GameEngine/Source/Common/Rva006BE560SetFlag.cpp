// Ported from Open-BFME-1's game/GameEngine/Source/Common/UnclaimedSmallLeaves01.cpp
// (donor revision: reference/open-bfme-1 @ 6d943426, base compiler flags) by
// tools/bfme1_sweep.py, which found this body byte-identical between
// lotrbfme.exe and game.dat once relocation slots are set aside:
// 0x0087ECC0 (56B) -> 0x006BE560 (56B), tier T1 "clean transfer".
//
// The donor file was held at copy-tier S: it defines six further leaves the
// sweep did not place, and find_declared_unmatched refuses a source with any
// definition the ledger lacks. This TU carries ONLY the placed body and keeps
// the layout its bytes depend on: a record vector (begin/end) at this+0x2C and
// a 0x24-byte record whose flag byte sits at +0x20.
//
// IDENTITY IS NOT RECOVERED. The names derive from the BFME 2 address; the
// donor's BFME 1 address names are not target facts.

struct Rva006BE560Record
{
	char m_lead[ 0x20 ];
	char m_flag;
	char m_pad[ 3 ];
};

struct Rva006BE560Records
{
	Rva006BE560Record *m_begin;
	Rva006BE560Record *m_end;

	unsigned int size() const { return (unsigned int)( m_end - m_begin ); }
	Rva006BE560Record &operator[]( unsigned int index ) { return *( m_begin + index ); }
};

class Rva006BE560Owner
{
public:
	void setFlag( int index, char flag );

	char               m_lead[ 0x2C ];
	Rva006BE560Records m_records;
};

void Rva006BE560Owner::setFlag( int index, char flag )
{
	if ( index >= 0 && (unsigned int)index < m_records.size() )
		m_records[ index ].m_flag = flag;
}
