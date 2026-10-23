// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Two guarded explicit copy-constructions (18B each): mov ecx, [esp+4],
// test ecx, ecx, je ret, push [esp+8], call <copy-ctor>, ret. Each
// copy-constructs the source into the given buffer unless it is null.
// Nothrow copy ctors keep placement new free of EH scaffolding.
// 0x000A9DF8 and 0x000A9E0A are STLport's _Construct for the two APT
// geometry element vectors: their push_back, uninitialized copy/fill and
// insert-overflow callers call them by that name. The copy ctors are the
// rowed 0x000A9851 and 0x000A987D. Element identities unproven (opaque
// element types, address-derived names). One ledger row per construction.

#include <new>

struct Rva000AB3E2Element
{
	Rva000AB3E2Element(const Rva000AB3E2Element &other) throw();
};

struct Rva000AB419Element
{
	Rva000AB419Element(const Rva000AB419Element &other) throw();
};

namespace _STL
{

template <class _T1, class _T2>
inline void _Construct(_T1 *__p, const _T2 &__value)
{
	new (__p) _T1(__value);
}

}

template void _STL::_Construct<Rva000AB3E2Element, Rva000AB3E2Element>(Rva000AB3E2Element *, const Rva000AB3E2Element &);
template void _STL::_Construct<Rva000AB419Element, Rva000AB419Element>(Rva000AB419Element *, const Rva000AB419Element &);
