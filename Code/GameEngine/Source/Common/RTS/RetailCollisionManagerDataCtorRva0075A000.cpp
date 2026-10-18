// ??0RetailCollisionManagerData@@QAE@XZ
// cl: /O2 /arch:SSE /DNDEBUG /MD /EHsc
// Retail 0x0075A000 (117 B): the 0xC070-byte collision data object CollisionManager::CollisionManager
// allocates (CollisionManagerConstructor.cpp); its destructor is 0x0075A080 (Rva009A4620Destructor.cpp).
// Layout from that destructor and from these stores (target facts): three leading words, two embedded
// tables at +0x18 (0x2B7B cells) and +0xAE10 (0x493 cells), each cells[] + count + two words, then a
// word set to 3 and two bytes. Each table constructor clears its two trailing words, memsets the cells
// (rep stosd) and zeroes the count; the tail is its own member object (its constructor fixes retail's
// store schedule). Type and member names are structural inferences.
#include <string.h>
template <int N>
struct RetailCollisionTable
{
	int m_cells[N];
	int m_count;
	int m_a;
	int m_b;
	RetailCollisionTable()
	{
		m_a = 0;
		m_b = 0;
		memset(m_cells, 0, sizeof(m_cells));
		m_count = 0;
	}
};
struct RetailCollisionTail
{
	int m_mode;
	unsigned char m_flagA;
	unsigned char m_flagB;
	RetailCollisionTail()
	{
		m_flagA = 0;
		m_flagB = 0;
		m_mode = 3;
	}
};
class RetailCollisionManagerData
{
public:
	RetailCollisionManagerData();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	RetailCollisionTable<0x2B7B> m_vmn;
	RetailCollisionTable<0x493> m_vdb;
	RetailCollisionTail m_tail;
};
RetailCollisionManagerData::RetailCollisionManagerData() : m_00(0), m_04(0), m_08(0)
{
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
}
