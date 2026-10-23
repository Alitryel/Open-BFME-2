// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $06 / N=7) ctor
// Retail: shim construct then three vtbl stores at +0/+4/+8.

namespace FXParticleSystem
{

class DefaultModuleTemplate7CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate6_vtbl0;
extern "C" char DefaultModuleTemplate6_vtbl4;
extern "C" char DefaultModuleTemplate6_vtbl8;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate();

private:
	void *m_v0;
	void *m_v4;
	void *m_v8;
};

// MSVC mangles DefaultModuleTemplate<7> as @$06
template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate()
{
	((DefaultModuleTemplate7CtorShim *)this)->construct();
	m_v0 = &DefaultModuleTemplate6_vtbl0;
	m_v4 = &DefaultModuleTemplate6_vtbl4;
	m_v8 = &DefaultModuleTemplate6_vtbl8;
}

template DefaultModuleTemplate<7>::DefaultModuleTemplate();
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x001F448D -> ??0?$CategoryModuleTemplate@$06@FXParticleSystem@@QAE@XZ
#pragma comment(linker, "/alternatename:?construct@DefaultModuleTemplate7CtorShim@FXParticleSystem@@QAEXXZ=??0?$CategoryModuleTemplate@$06@FXParticleSystem@@QAE@XZ")
