// cl: /O1 /MD /DNDEBUG
// The already-covered29B copy wrapper at3F6619 is rehomed here.
// Its legacy ledger name is a code-generation alias; object-symbol names
// the address-derived C++ definition below. Native29 ignores the fourth
// argument and delegates to the rowed50B3F6477 copy loop with a tag and
// null distance pointer. The declaration consumes only that proven ABI.
// Record width28 follows the copy loop; full application layout/name and
// the original empty-tag parameter spelling are unproved. This view passes
// a const-reference tag as the range-erase caller3F6975 visibly does.
// Existing STLport donor source still emits an exact copy of the old wrapper;
// the row moves once and does not claim a second retail range.
struct Rva003F6975Record {~Rva003F6975Record();unsigned char consumed[28];};
struct Rva003F6975Empty {};
// The 50B loop at 0x003F6477 is rowed as STLport's __copy over its 28-byte
// element (StlSweepW5Rva003F6477.cpp); call it by that name. The tag is the
// view's random_access_iterator_tag, built as the same empty temporary.
struct Rva003F6477Element;
namespace _STL {
struct random_access_iterator_tag {random_access_iterator_tag(){}};
template <class _RandomAccessIter, class _OutputIter, class _Distance>
_OutputIter __copy(_RandomAccessIter, _RandomAccessIter, _OutputIter, const random_access_iterator_tag &, _Distance *);
}
// ??$__copy_ptrs@PAUBfmeAssignRecord28@@PAU1@@_STL@@YAPAUBfmeAssignRecord28@@PAU1@00U__false_type@0@@Z
__declspec(noinline) Rva003F6975Record* rva003F6619Copy(Rva003F6975Record*first,Rva003F6975Record*last,Rva003F6975Record*out,const Rva003F6975Empty&) {
 return (Rva003F6975Record*)_STL::__copy((Rva003F6477Element*)first,(Rva003F6477Element*)last,(Rva003F6477Element*)out,_STL::random_access_iterator_tag(),(int*)0);
}



// Native [3F6975,3F69A8) range erase: copy the surviving tail into first;
// destroy vacated28B records; update finish; return first. RET8 proves
// two pointer arguments. Record fields remain opaque. Visible copy wrapper
// proves the empty dispatch argument unused and preserves native temp placement.
// The vacated records are destroyed by the rowed _Destroy over the same
// 28-byte record (0x003F6636, named for BfmeStringRecord00111ACF).
struct BfmeStringRecord00111ACF;
namespace _STL { template <class _ForwardIterator> void _Destroy(_ForwardIterator, _ForwardIterator); }
class Rva003F6975Vector {public:Rva003F6975Record* erase(Rva003F6975Record*first,Rva003F6975Record*last);
private:Rva003F6975Record*start;Rva003F6975Record*finish;Rva003F6975Record*limit;};
Rva003F6975Record* Rva003F6975Vector::erase(Rva003F6975Record*first,Rva003F6975Record*last) {
 Rva003F6975Record*result=rva003F6619Copy(last,finish,first,Rva003F6975Empty());
 _STL::_Destroy((BfmeStringRecord00111ACF*)result,(BfmeStringRecord00111ACF*)finish);finish=result;return first;
}

