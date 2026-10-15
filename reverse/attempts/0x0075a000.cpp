// ??0RetailCollisionManagerData@@QAE@XZ
// partial score=0.89 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc
// ??0RetailCollisionManagerData@@QAE@XZ retail 0x0075A000 117 B (region /O2 /G6 /arch:SSE). Layout from retail offsets: two Pool<N>{items[N],count,a,b} members at +0x18/+0xAE10.
#include <string.h>
template <int N> struct Pool { int m_items[N]; int m_count; int m_a; int m_b;
 Pool() : m_a(0), m_b(0) { clear(); }
 void clear() { memset(m_items,0,sizeof(m_items)); m_count=0; } };
class RetailCollisionManagerData { public: RetailCollisionManagerData();
private: int m_00,m_04,m_08,m_0c,m_10,m_14; Pool<0x2B7B> m_A; Pool<0x493> m_B; int m_C068; unsigned char m_C06C,m_C06D; };
RetailCollisionManagerData::RetailCollisionManagerData() : m_00(0), m_04(0), m_08(0)
{ m_C06C=0; m_C06D=0; m_C068=3; m_0c=0; m_10=0; m_14=0; }
