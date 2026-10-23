// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /arch:SSE
// stlport
// ??0SelectionTranslator@@QAE@XZ, retail 0x0042FD9E, 129 bytes.
// Ctor with vtable 0x00C3C960 (ledger-named data_ledger vtable), map<int,void*> at +0x28, ints/floats zeroed, int at +0x0C
// set to -1, and TheSelectionTranslator (0x00A03220) storing this. Evidence: target bytes; map ctor 0x0033C432 rowed
// (signed-key mangling kept); clear respelled to rowed unsigned-key 0x00357416 via the unsigned-map reference cast;
// WorldBuilder SelectionTranslator constructor identifies the body. Store order: every member store is a volatile cast
// (volatile zero stores escape the or/and read-modify-write hoist and, unlike a fence, do not pin the EH-state store,
// which then lands next to the clear() call as in retail).
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
// bfme link decl-only end
template<class T> __forceinline volatile T &r1_vwrite(T &value) 

{
 return *(volatile T *)&value;
 
}
extern "C" const void *const __identifier("??_7Rva0042FCE6@@6B@")[];
class SelectionTranslator;
extern SelectionTranslator *TheSelectionTranslator;
// Retail's unwind of this base subobject calls the rowed 0x00429191
// translator base destructor (??1Rva0042CBB6).
class Rva0042CBB6
{
public:
	virtual ~Rva0042CBB6();
};

class EmptyBase0042FD9E

{
 public:
 EmptyBase0042FD9E() 
 
 {
  
 }
 ~EmptyBase0042FD9E() { ((Rva0042CBB6 *)this)->Rva0042CBB6::~Rva0042CBB6(); }
 
}
;
class SelectionTranslator : public EmptyBase0042FD9E

{
 public:
 SelectionTranslator();
 private:
 const void *m_vtable;
 bool m_b04;
 bool m_b05;
 bool m_b06;
 bool m_b07;
 int m_i08;
 int m_i0C;
 int m_i10;
 int m_i14;
 int m_i18;
 int m_i1C;
 bool m_b20;
 int m_i24;
 _STL::map<int, void *> m_map28;
 float m_f34;
 float m_f38;
 float m_f3C;
 
}
;
SelectionTranslator::SelectionTranslator()
: EmptyBase0042FD9E()
, m_vtable(__identifier("??_7Rva0042FCE6@@6B@"))

{
 m_i0C = -1;
 r1_vwrite(((&(m_b04)) ? (m_b04) : (m_b04))) = false;
 m_b05 = false;
 m_b06 = false;
 r1_vwrite(((&(m_b07)) ? (m_b07) : (m_b07))) = false;
 *(volatile int *)&m_i08 = 0;
 *(volatile int *)&m_i10 = 0;
 *(volatile int *)&m_i14 = 0;
 *(volatile int *)&m_i18 = 0;
 *(volatile int *)&m_i1C = 0;
 *(volatile int *)&m_i24 = 0;
 *(volatile float *)&m_f34 = 0.0f;
 *(volatile float *)&m_f38 = 0.0f;
 *(volatile float *)&m_f3C = 0.0f;
 *(volatile bool *)&m_b20 = false;
 reinterpret_cast<_STL::map<unsigned int, void *> &>(m_map28).clear();
 TheSelectionTranslator = this;
 
}
