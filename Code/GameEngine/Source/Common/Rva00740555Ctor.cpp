// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva00740555@@QAE@XZ @0x00740157 (18B). Default constructor of the SimpleSceneClass-derived
// class whose destructor is rowed at 0x00740555 (TailJumpWrappers5B.cpp) and whose scalar
// deleting destructor is 0x001042CF (slot in vtable 0x00CF1578): rowed SimpleSceneClass
// constructor 0x00142960, then the derived vtable; no member initialisation. Same shape as
// Rva00135E35Ctor.cpp. Owner of the class beyond the scene base is unproven.
class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
};

class Rva00740555 : public SimpleSceneClass
{
public:
	Rva00740555();
	virtual ~Rva00740555();
};

__declspec(noinline) inline Rva00740555::Rva00740555()
{
}
// Select-any: another unit compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva00740555Ctor absent-from-retail
void bfmeAnchorRva00740555Ctor(Rva00740555 *p) { p->Rva00740555::Rva00740555(); }
