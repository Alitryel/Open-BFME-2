// ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ
// partial score=0.86 date=2026-10-16
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /O1 /arch:SSE /G7 /MD /EHa /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Diagnostic bank: STLport vector<Object*>::~vector (debug twin WB B09640 shows _Destroy
// locals + one-byte tag, then the inlined _Vector_base body under one EH state). /EHa is the
// only flag found that keeps an EH frame here (43/43B, 6 bytes: our state 0 protects the base
// subobject and is reset to -1 at the inlined base dtor; retail sets state 0 there for the
// _M_end_of_storage proxy at this+8, funclet jmp to the empty ret B3FD0). /EHa is otherwise
// used only by debug-library units, so the flag is a lead, not a fact.
#include <vector>
class Object;
template class _STL::vector<Object *>;
