// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// cl: /O1 /MD /Ireference/shims/bfme2_ascii
//
// ?rva0040BAD0@Rva0040BAD0@@QAE_NPAVRva0040AF66@@@Z @0x0040BAD0 39B.
// If the 0x0040AAF8 member (unclaimed, address pinned) on our object reports
// zero for the argument's first dword, push the whole argument record into
// the +0x18 vector through the rowed push_back at 0x0040BA6A and return true.
// Evidence: retail push esi/edi / edi=[esp+0xc] / push [edi] / esi=this /
// call 0x40AAF8 / test eax / jne false / push edi / lea ecx,[esi+0x18] /
// call 0x40BA6A / mov al,1 / jmp ret / false: xor al,al / pop edi,esi /
// ret 4. The push_back spelling is copied from its rowed TU so the call
// resolves to the matched body; the argument deref passes edi itself.
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
template <class _InputIter, class _Tp> _InputIter find(_InputIter first, _InputIter last, const _Tp &val);
template <> BfmePod104 *find(BfmePod104 *first, BfmePod104 *last, const BfmePod104 &val);
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &x);
	unsigned int size() const { return _M_finish - _M_start; }
	_Tp &operator[](unsigned int n) { return *(_M_start + n); }
	const _Tp &at2(unsigned int n) const { return _M_start[n]; }
	_Tp *_M_start;
	_Tp *_M_finish;
};
}

class Rva0040AF66
{
public:
	int m_00;
	char m_04[0x64];
};

class Rva0040BAD0
{
public:
	bool rva0040BAD0(Rva0040AF66 *arg);
	int rva0040AAF8(int x);
private:
	char m_pad00[0x18];
	union
	{
		_STL::vector<Rva0040AF66, _STL::allocator<Rva0040AF66> > m_vec18;
		struct
		{
			BfmePod104 *m_begin;
			BfmePod104 *m_end;
		};
	};
};

struct InParamSlot {};
inline void *operator new(size_t, void *p, InParamSlot) { return p; }
static __forceinline const AsciiString &nameOfI(const int &k) { return TheNameKeyGenerator->keyToName((NameKeyType)k); }
inline const AsciiString &nameOfInl(const int &k) { return TheNameKeyGenerator->keyToName((NameKeyType)k); }
//<<V

int Rva0040BAD0::rva0040AAF8(int key)
{
	BfmePod104 *begin = m_begin;
	BfmePod104 *end = m_end;
	BfmePod104 *found = _STL::find(begin, end, *(const BfmePod104 *)&key);
	if (found != end)
		return (int)found;
	AsciiString name = TheNameKeyGenerator->keyToName((NameKeyType)key);
	if (0 < m_vec18.size())
	{
	unsigned int off = 0;
	unsigned int i = 0;
	do
	{
		const char *base = (const char *)m_begin;
		const char *element = base + off;
		new ((void *)&key, InParamSlot()) AsciiString(nameOfI(*(const int *)element));
		__asm nop
		((AsciiString *)&key)->~AsciiString();
		++i;
		off += sizeof(BfmePod104);
	} while (i < m_vec18.size());
	}
	return 0;
}

//V>>

bool Rva0040BAD0::rva0040BAD0(Rva0040AF66 *arg)
{
	if (rva0040AAF8(arg->m_00) == 0)
	{
		m_vec18.push_back(*arg);
		return true;
	}
	return false;
}
