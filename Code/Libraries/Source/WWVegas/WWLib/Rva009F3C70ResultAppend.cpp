// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The 103-byte method appends one two-int record to the result payload.
// The body at 0x009F3C00 has the same layout and helper call, so this source
// keeps the candidate's separate address-derived identity.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}

class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_bfmeFirst;
		int m_bfmeSecond;
	};
};

struct Rva009F3C70Payload
{
	_STL::vector<OCLSpecialPowerModuleData::Upgrades> m_upgrades;
	void *m_cursor;
	int m_refCount;
};

struct Rva009F3C70Result
{
	Rva009F3C70Payload *m_value;

	void append(int first, int second);
};

__declspec(noinline) void Rva009F3C70Result::append(int first, int second)
{
	m_value->m_upgrades.push_back();

	m_value->m_upgrades.end()[-1].m_bfmeFirst = first;
	m_value->m_upgrades.end()[-1].m_bfmeSecond = second;
	m_value->m_cursor = m_value->m_upgrades.begin();
}
