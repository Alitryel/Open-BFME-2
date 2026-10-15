// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// partial score=0.8 date=2026-10-15
// cl: /O1 /MD /EHsc
#include <new>
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
namespace _STL
{
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &x);
};
}

class AsciiString;
struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};
template <typename T>
class StringBase
{
	friend class AsciiString;
private:
	StringBase(const StringBase<T> &other) throw();
	void releaseBuffer() throw();
	BfmeStringData *m_data;
};
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) throw() : StringBase<char>(other) {}
	__forceinline ~AsciiString() { releaseBuffer(); }
};
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
	int rva0040AAF8(int x);
private:
	char m_pad00[0x18];
	_STL::vector<Rva0040AF66, _STL::allocator<Rva0040AF66> > m_vec18;
};

bool Rva0040BAD0::rva0040BAD0(Rva0040AF66 *arg)
{
	if (rva0040AAF8(arg->m_00) == 0)
	{
		m_vec18.push_back(*arg);
		return true;
	}
	return false;
}

// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z @0x0040AAF8 (173B, ret 4).
// Record-key lookup over 0x68-byte BfmePod104 records between +0x18/+0x1C:
// the rowed _STL::find first (returns the hit or _last), then a warming scan
// that rebuilds a keyToName AsciiString temporary per record in the dead
// incoming argument slot.  Callers 0x0040BAD0 and 7 units in the link census.
int Rva0040BAD0::rva0040AAF8(int key)
{
	BfmePod104 *first = *(BfmePod104 **)((char *)this + 0x18);
	BfmePod104 *last = *(BfmePod104 **)((char *)this + 0x1c);
	BfmePod104 *found = _STL::find(first, last, *(const BfmePod104 *)&key);
	if (found != last)
		return (int)found;
	AsciiString s1(TheNameKeyGenerator->keyToName((NameKeyType)key));
	unsigned int i = 0;
	unsigned int off = 0;
	while (i < (unsigned int)((last - first) / 0x68))
	{
		AsciiString *s2 = new ((void *)&key) AsciiString(
			TheNameKeyGenerator->keyToName((NameKeyType)*(int *)((char *)first + off)));
		s2->~AsciiString();
		++i;
		off += 0x68;
	}
	return 0;
}
