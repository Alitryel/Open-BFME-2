// cl: /O1 /MD
// ??_GRva004E2382@@QAEPAXI@Z @ 0x004E2CB9 (28B).
// Deleting dtor of Rva004E2382 whose dtor is 0x004E2941: calls ??1 then
// rowed operator delete 0x0002FD60 when flag bit set. Caller chain from
// 0x004E2941 landing.
class Rva004E2382 {
public:
    ~Rva004E2382();
private:
    char m_pad[32];
};

void famgenDelete(Rva004E2382 *p) { delete p; }

namespace _STL {
template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
// ??$_Destroy@PAVRva004E2382@@@_STL@@YAXPAVRva004E2382@@0@Z @ 0x004E377E (25B).
// Range destroy over 0x20-byte Rva004E2382 via rowed dtor 0x004E2941.
// Caller 0x004E3C32 passes vector start/finish at +0/+4. Prev 0x004E3759
// in stlport TU proves /O1 flags which this TU shares. Retail loops
// destroy then add 0x20.
template <>
inline void _Destroy<Rva004E2382 *>(Rva004E2382 *__first, Rva004E2382 *__last)
{
    for (; __first != __last; ++__first)
        __first->~Rva004E2382();
}
}

// This _STL::_Destroy specialization is a header inline in copier units. The
// anchor retains this unit's matched row body, but the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeFamilyDeletingDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFamilyDeletingDtorInlineAnchor()
{
	_STL::_Destroy<Rva004E2382 *>(0, 0);
}
#pragma inline_depth()
