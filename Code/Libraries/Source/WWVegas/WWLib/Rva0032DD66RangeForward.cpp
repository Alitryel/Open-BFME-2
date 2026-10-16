// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee 0x0032D490 is rowed as STLport copy<Rva0032CD3BRecord*>; retail
// still pushes the iterator-category tag as a fourth argument, which the
// callee never reads, so the call goes through a four-argument cast.
struct Rva0032CD3BRecord;
namespace _STL
{
template <class _InputIter, class _OutputIter>
_OutputIter copy(_InputIter first, _InputIter last, _OutputIter result);
}
struct Rva0032DD66Input;
struct Rva0032DD66Output;
struct Rva0032DD66IteratorTag {};
typedef Rva0032DD66Output* (__cdecl *Rva0032DD66RangeCallee)(Rva0032DD66Input*,Rva0032DD66Input*,Rva0032DD66Output*,const Rva0032DD66IteratorTag&);

Rva0032DD66Output* __cdecl Rva0032DD66RangeForward(Rva0032DD66Input*first,Rva0032DD66Input*last,Rva0032DD66Output*result)
{
    Rva0032CD3BRecord* (__cdecl *callee)(Rva0032CD3BRecord*,Rva0032CD3BRecord*,Rva0032CD3BRecord*) = &_STL::copy<Rva0032CD3BRecord*, Rva0032CD3BRecord*>;
    Rva0032DD66IteratorTag category;
    return ((Rva0032DD66RangeCallee)callee)(first,last,result,category);
}
