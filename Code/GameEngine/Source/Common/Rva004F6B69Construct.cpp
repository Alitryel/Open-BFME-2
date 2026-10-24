// cl: /DNDEBUG /MD
// Retail 0x004F6B69 (18B): STLport _Construct<Rva004F6966,Rva004F6966>, the
// null-tested placement copy through the rowed copy ctor
// ??0Rva004F6966@@QAE@ABU0@@Z at 0x004F6966, no EH frame. Callers at
// 0x004F6B9B 0x004F6BC6 0x004F8A8B 0x004F902A walk 0xC-sized elements; the
// __uninitialized_copy 0x004F6B8D reaches it under the library name, which
// symbols.csv pins here. The template is STLport's generic placement-new
// body, declared locally with a nothrow placement new that has no placement
// delete (<new>'s pulls an EH state; retail has no frame here), whose
// non-throwing contract gives retail's null test.
inline void *__cdecl operator new(unsigned int, void *p) throw() { return p; }

namespace _STL {
template <class _T1, class _T2>
inline void _Construct(_T1 *__p, const _T2 &__val)
{
	new (__p) _T1(__val);
}
}

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
};

template void _STL::_Construct<Rva004F6966, Rva004F6966>(
	Rva004F6966 *, const Rva004F6966 &);
