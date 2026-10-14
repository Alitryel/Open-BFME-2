// cl: -GR- -EHsc-
// ??0AptOnlineOpenPlay@@QAE@H@Z @0x005BA1FD 55B: composing constructor. Builds
// the base with (0, arg) through the pinned base ctor, installs the three
// polymorphic tables (all DIR32, copied from retail by the gate), publishes
// this to the 0xE06544 global when clear, and returns this. Targets from
// retail REL32/DIR32; table symbols declared never defined.
class Rva005BA1FDBase
{
public:
	Rva005BA1FDBase(int x, int y);
	virtual void BaseVirt();
};

struct Rva005BA1FDM60
{
	virtual void M60Virt();
	char pad[8];
};

struct Rva005BA1FDM6C
{
	virtual void M6CVirt();
};

class AptOnlineOpenPlay;
// g_rva005BA1FDInst is only an alias of the owned global g_Va00E06544 (ledger names column); this unit reads the owner through its own view type.
extern int g_Va00E06544;
#define g_rva005BA1FDInst (*(AptOnlineOpenPlay * *)&g_Va00E06544)

class AptOnlineOpenPlay : public Rva005BA1FDBase
{
	char pad[0x60 - 4];
	Rva005BA1FDM60 m_60;
	Rva005BA1FDM6C m_6c;

public:
	AptOnlineOpenPlay(int arg);
	virtual void BoxVirt();
};

AptOnlineOpenPlay::AptOnlineOpenPlay(int arg)
	: Rva005BA1FDBase(arg, 0)
{
	if (g_rva005BA1FDInst == 0)
		g_rva005BA1FDInst = this;
}

// ??0Rva005BA28E@@QAE@H@Z @0x005BA28E 55B: sibling composing constructor,
// same skeleton as AptOnlineOpenPlay above. Builds the shared base with
// (arg, 1), installs its three tables (C73DCC/C73D70/C73D60, DIR32 copied
// from retail) and publishes this to the 0xE06548 screen-instance global
// that the rowed destructor 0x005BA2CB clears. Original class name unknown.
extern int g_Va00E06548;
#define g_rva005BA28EInst (*(Rva005BA28E * *)&g_Va00E06548)

struct Rva005BA28EM60
{
	virtual void M60Virt();
	char pad[8];
};

struct Rva005BA28EM6C
{
	virtual void M6CVirt();
};

class Rva005BA28E : public Rva005BA1FDBase
{
	char pad[0x60 - 4];
	Rva005BA28EM60 m_60;
	Rva005BA28EM6C m_6c;

public:
	Rva005BA28E(int arg);
	virtual void BoxVirt();
};

Rva005BA28E::Rva005BA28E(int arg)
	: Rva005BA1FDBase(arg, 1)
{
	if (g_rva005BA28EInst == 0)
		g_rva005BA28EInst = this;
}
