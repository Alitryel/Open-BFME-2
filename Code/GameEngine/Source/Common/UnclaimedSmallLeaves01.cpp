// One unclaimed leaf body carried from Open-BFME-1's
// game/GameEngine/Source/Common/UnclaimedSmallLeaves01.cpp (BFME 1 RVA
// 0x0087ECC0), whose bytes reappear unchanged in game.dat at 0x006BE560.
// Only this body is carried; the donor's other leaves do not place here.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the BFME 1 address;
// member names say only what the bytes do.

// Bounds-checked store of one byte into element i of a vector of 36-byte
// records whose begin/end pointers sit at +0x2C/+0x30.
struct Rva0087ECC0Record
{
	char m_lead[ 0x20 ];
	char m_flag;
	char m_pad[ 3 ];
};

struct Rva0087ECC0Records
{
	Rva0087ECC0Record *m_begin;
	Rva0087ECC0Record *m_end;

	unsigned int size() const { return (unsigned int)( m_end - m_begin ); }
	Rva0087ECC0Record &operator[]( unsigned int index ) { return *( m_begin + index ); }
};

class Rva0087ECC0Owner
{
public:
	void setFlag( int index, char flag );

	char               m_lead[ 0x2C ];
	Rva0087ECC0Records m_records;
};

void Rva0087ECC0Owner::setFlag( int index, char flag )
{
	if ( index >= 0 && (unsigned int)index < m_records.size() )
		m_records[ index ].m_flag = flag;
}
