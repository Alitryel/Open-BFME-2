// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ
// partial score=0.867337106752665 date=2026-10-15
// ?rva005B59FD@Class@AptCreateAHero@@QAEXXZ
// Native005B59FD..005B5AAF is the complete178-byte callback registration body.
// WB0157BFF0 names AptCreateAHero::Class::OnMapLoaded and shows Exit and
// OnMapClick bindings. Target strings, two descriptor constructions and
// owner+21C calls independently establish the registration flow.
// Declarations are carried from the matched AptCreateAHeroClassConstructor.cpp;
// this bank is not the515-byte constructor described by its former header.
// Reusing one descriptor restores retail's0x14-byte frame and shared -20/-1C
// homes. The177-byte candidate still caches21C in EDI instead of retail's
// two LEAs, with the extra saved register and dependent scheduling differences.
// Round39:9 flag trials,12 descriptor shapes and4 lifetime trials. Production
// compile_function/permute fitness rises .840400158 -> .867337107; no exact
// byte, DIR32, EH or link claim. No new pins and no production-source changes.
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /G7
#include "ascii_string.h"

class Rva005B3676Owner;
class AptExternHandler;
class AptCommandMap;
class AptScreenInitGadgets;
class GameWindow;

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

DelegateDesc() {}
	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

// Keep the matched constructor TU's existing inline-release AptRef view.
// This bank does not establish a new canonical layout or COMDAT selection.
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47 &other);void*ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc &desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);

class BfmeAptWindowManager
{
public:
	void rva00225375(const AsciiString &, const AsciiString &, bool);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005B3676Owner
{
	char m_pad00[0x21C];
	union {
		char m_commands[0x228 - 0x21C];
		AptCommandMapAdder m_adder;
	};
	char m_externs[1];
};
class Rva005B566B
{
public:
	void rva005B566B();
};

class Rva0040A530
{
public:
	Rva0040A530(bool flag);
	~Rva0040A530();
private:
	char m_pad[0x14];
};

class Rva005B5420Base
{
public:
	Rva005B5420Base(Rva005B3676Owner *owner) : m_owner(owner) {}
	virtual ~Rva005B5420Base() {}
protected:
	Rva005B3676Owner *m_owner;
};

class Rva005B57C6Box
{
public:
	void Run(char *);
};

namespace AptCreateAHero
{
class Class : public Rva005B5420Base
{
public:
	Class(Rva005B3676Owner *owner);
	virtual ~Class();
	void rva005B59FD();
	void rva005B5418(const char *);
	void rva0047A69C(const char *);
	void rva000D1407(const char *, void *, GameWindow *);
	void ExternFunc(int, char *, bool);
private:
	char m_pad08[0x14 - 0x08];
	bool m_flag14;
	char m_pad15[3];
	int m_word18;
	Rva0040A530 m_heroes;
};
}


void AptCreateAHero::Class::rva005B59FD()
{
 DelegateDesc desc;
	{ AsciiString name("AptCreateAHero::Class::Exit"); desc=MakeDelegate(this, &Class::rva005B5418); m_owner->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(desc)); }
	{ AsciiString name("AptCreateAHero::Class::OnMapClick"); desc=MakeDelegate(this, &Class::rva0047A69C); m_owner->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(desc)); }
}
