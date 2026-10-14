// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x00332B0D/27: a three-argument cdecl forward to virtual slot 0x98
// of the debug manager through theDebug (VA 0x00DE0880), the same shape as
// the rowed static forward Debug::SetBuildInfo 0x00001705 (WinMain.cpp),
// which reaches slot 0x9C. It sits among the Lua script engine bodies; the
// slot's identity and the argument types are not established, so the name
// is address-derived and the view below spells only the slots up to 0x98.
class Debug
{
public:
#define V(n) virtual void slot##n();
	V(00) V(04) V(08) V(0C) V(10) V(14) V(18) V(1C)
	V(20) V(24) V(28) V(2C) V(30) V(34) V(38) V(3C)
	V(40) V(44) V(48) V(4C) V(50) V(54) V(58) V(5C)
	V(60) V(64) V(68) V(6C) V(70) V(74) V(78) V(7C)
	V(80) V(84) V(88) V(8C) V(90) V(94)
#undef V
	virtual void slot98(int a, int b, int c);
};

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

void Rva00332B0D(int a, int b, int c)
{
	theDebug->slot98(a, b, c);
}
