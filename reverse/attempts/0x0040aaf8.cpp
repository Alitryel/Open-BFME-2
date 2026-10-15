// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// partial score=0.92 date=2026-10-15
// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmePod104
{
	int a[26];
};

namespace _STL
{
template <class _Tp> class allocator {};
template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
	_Tp *begin() const { return _M_start; }
	_Tp *end() const { return _M_finish; }
	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }
	_Tp &operator[](unsigned int i) { return *(_M_start + i); }
	void push_back(const _Tp &x);
};
template <class _It, class _Tp> _It find(_It first, _It last, const _Tp &value);
}

class Rva0040AF66
{
public:
	int m_00;
};

class Rva0040BAD0
{
public:
	bool rva0040BAD0(Rva0040AF66 *arg);
	int rva0040AAF8(int key);
private:
	char m_pad00[0x18];
	_STL::vector<BfmePod104, _STL::allocator<BfmePod104> > m_stats;
};

bool Rva0040BAD0::rva0040BAD0(Rva0040AF66 *arg)
{
	if (rva0040AAF8(arg->m_00) == 0)
	{
		m_stats.push_back(*(BfmePod104 *)arg);
		return true;
	}
	return false;
}

// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z @0x0040AAF8 (173B, ret 4).
// Record-key lookup over 0x68-byte BfmePod104 records between +0x18/+0x1C:
// the rowed _STL::find first (returns the hit or _last), then a warming scan
// that rebuilds a keyToName AsciiString temporary per record.
// Callers 0x0040BAD0 and 5 units in the link census.
int Rva0040BAD0::rva0040AAF8(int key)
{
	BfmePod104 *last = m_stats.end();
	BfmePod104 *found = _STL::find(m_stats.begin(), last, (const BfmePod104 &)key);
	if (found != last)
		return (int)found;
	AsciiString s1(TheNameKeyGenerator->keyToName((NameKeyType)key));
	for (unsigned int i = 0; i < m_stats.size(); ++i)
	{
		AsciiString s = TheNameKeyGenerator->keyToName((NameKeyType)m_stats[i].a[0]);
	}
	return 0;
}
