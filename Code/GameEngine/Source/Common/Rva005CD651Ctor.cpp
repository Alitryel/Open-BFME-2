// cl: /EHsc /MD
// ??0Rva005CD651@@QAE@H@Z @0x005CD651 63B:
// Ctor with vtable 0x00874FF4: +4=arg +8=0 +0xC=1 then tail Enable 0x0052340D.
// Empty inline base plus declared dtor arms EH state 0 per ModuleData recipe.
// Caller 0x00577720 passes int from 0x00328A83 getter. Sibling of 0x005CD167.
void __cdecl Rva0052340DEnable(void);
struct EmptyBase005CD651 { EmptyBase005CD651() {} ~EmptyBase005CD651(); };
struct Rva005CD651 : EmptyBase005CD651 {
	virtual ~Rva005CD651();
	Rva005CD651(int v);
	int m_4;
	int m_8;
	bool m_C;
};
Rva005CD651::Rva005CD651(int v)
	: m_4(v)
	, m_8(0)
	, m_C(true)
{
	Rva0052340DEnable();
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1EmptyBase005CD651@@QAE@XZ=??1Rva005011DA@@QAE@XZ")
