// cl: /O1 /arch:SSE /G7 /EHsc /MD /Gy /Ireference/shims/bfme2_ascii
// MessageBoxOk 0x0044C0A8 (ZH GameClient/MessageBox.cpp lineage): wrap the callback
// in a ref-counted holder (rowed ctors 0x0044BC76 / 0x004F6986 / 0x0051732A) and
// hand the single-callback ctor 0x0044BF77 result to the prompt core 0x00437F61.
// Facts from target evidence: native EH cdecl body, kind 0, holder copied inline
// after the receiver slot (outer ctor Rva0044BF77, by-value Rva0051732ABase).
// The null callback is the shared bare-ret 0x004B3FD0. Inferences: the exact
// class hierarchy of the holder (Rva0051732ABase/Rva0051732A split mirrors what
// the byte shape needs: the dtor-less by-value view vs the owning temp).
#include "unicode_string.h"
struct TargetRef00217D4C { void *m_vtbl; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva0044BC76 {
public:
    Rva0044BC76(const int *);
    __forceinline Rva0044BC76(const Rva0044BC76 &o) : m_ptr(o.m_ptr) {}
    __forceinline Rva0044BC76(int, int) : m_ptr(0) {}
    TargetRef00217D4C *m_ptr;
};
void *__cdecl operator new(unsigned int size);
struct ImplRef0044BC76 { virtual ~ImplRef0044BC76() {} int m_ref; ImplRef0044BC76() : m_ref(0) {} };
struct Impl0044BC76 : ImplRef0044BC76 { int m_value; Impl0044BC76(const int &v) : m_value(v) {} };
Rva0044BC76::Rva0044BC76(const int *arg)
{
    Impl0044BC76 *p = new Impl0044BC76(*arg);
    m_ptr = (TargetRef00217D4C *)p;
    if (p != 0) ++p->m_ref;
}
struct Rva004F6986Member : public Rva0044BC76 {
    __forceinline Rva004F6986Member() : Rva0044BC76(0, 0) {}
    __forceinline Rva004F6986Member(const int *fn) : Rva0044BC76(fn) {}
    __forceinline Rva004F6986Member(const Rva004F6986Member &other) : Rva0044BC76(*(const Rva0044BC76*)&other) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~Rva004F6986Member() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva0051732ABase { TargetRef00217D4C *m_ptr;
    __forceinline Rva0051732ABase(const Rva0051732ABase &other) : m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
    Rva0051732ABase(Rva004F6986Member value); };
struct Rva0051732A : Rva0051732ABase { Rva0051732A(Rva004F6986Member value);
    __forceinline ~Rva0051732A() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); } };
struct Rva0044BF77 {
    TargetRef00217D4C *m_ptr;
    Rva0044BF77(Rva0051732ABase single);
    __forceinline Rva0044BF77(const Rva0044BF77 &other):m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
    __forceinline ~Rva0044BF77(){ if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
namespace nok { extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0044BF77); }
typedef void(*GameWinMsgBoxFunc)();
class DebugDisplayInterface;
struct _iobuf;
void __cdecl rva000B3FD0DebugDisplay(DebugDisplayInterface *, void *, _iobuf *);
#define MessageBoxNullCallback ((GameWinMsgBoxFunc)rva000B3FD0DebugDisplay)
void MessageBoxOk(UnicodeString title,UnicodeString message,GameWinMsgBoxFunc ok) {
    GameWinMsgBoxFunc cb=ok?ok:MessageBoxNullCallback;
    ok=cb;
    nok::Rva00437F61(0,title,message,Rva0044BF77(Rva0051732A(Rva004F6986Member((const int*)&ok))));
}
