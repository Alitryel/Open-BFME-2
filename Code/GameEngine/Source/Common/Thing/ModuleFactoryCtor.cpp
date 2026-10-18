// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /GF
// stlport
// ??0Rva0041386B@@QAE@XZ @0x0041386B 54B: thiscall ctor with vector at +0 and ModuleTemplateMap at +0xC.
// Evidence: chain/unlock lane, EH prolog, rowed Vector_base BfmeE16 at 0x00211E58 and rowed map ctor at 0x00413727, caller at 0x00413B88.
#include <vector>
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
#include "../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
enum NameKeyType { NK_ZERO = 0 };
class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		int m_whichInterfaces;
	};
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree_base<pair<NameKeyType const ,ModuleFactory::ModuleTemplate>,allocator<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> > >::_Rb_tree_base(allocator<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> > const &); }
struct FieldParse
{
 const char *name;
 void (*parse)(class INI *, void *, void *, const void *);
 const void *userData;
 int offset;
};
void Rva002E2612Parse(INI *, void *, void *, const void *);
void Rva004138C7Parse(INI *, void *, void *, const void *);

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

// Native table: two named fields and a complete null terminator. The
// callbacks and their existing rowed consumers establish the vector at +0
// and science-bonus map at +0x0C independently of this ctor's old class view.
extern const FieldParse g_00C39AF8[3] = {
 { "Sides", Rva002E2612Parse, 0, 0 },
 { "Bonus", Rva004138C7Parse, 0, 0x0C },
 { 0, 0, 0, 0 }
};

class Rva0041386B
{
public:
	Rva0041386B();
	void rva0041393F(class INI *ini);
private:
	_STL::vector<BfmeE16> m_vec00;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map0C;
};
Rva0041386B::Rva0041386B()
{
}

// ?rva0041393F@Rva0041386B@@QAEXPAVINI@@@Z @0x0041393F 18B: INI-field init
// forwarder. Caller 0x00413B95 passes ecx = Rva0041386B local and INI * in esi;
// retail pushes the FieldParse table 0x00839AF8 then this, then calls rowed
// INI::initFromINI 0x0002DE78 with ecx = INI *. Honest address name; table is
// owned above with both callbacks and its terminator.
void Rva0041386B::rva0041393F(INI *ini)
{
	ini->initFromINI(this, g_00C39AF8);
}
