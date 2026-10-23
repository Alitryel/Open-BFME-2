// cl: /DNDEBUG /MD
// ??1AptMessengerOnline@@UAE@XZ @0x005AE66B 36B evidence: vtable 0x00872760 store at [this] plus second vtable 0x0087275C store at +0x218 plus singleton clear of g_00E0644C when equal to this plus tail-jmp to pinned base dtor ??1AptMessenger@@UAE@XZ @0x005125ED; caller scalar deleting dtor; ghidra 36B vs 132B trust ret plus int3 gate
// Identity: the AptMessengerOnline constructor 0x005AEF6B stores the same two
// tables (0x00872760 at +0, 0x0087275C at +0x218) and sets g_00E0644C to this.
extern void *g_00E0644C;
// g_00E0644C: the AptMessengerOnline singleton; matched references (this
// dtor and the constructor 0x005AEF6B) place it at VA 0xe0644c (zero-filled .bss).
void *g_00E0644C;

class GameWindow
{
public:
	virtual ~GameWindow();
	unsigned char m_pad[0x214];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class AptMessenger : public GameWindow, public Rva005248D0
{
public:
	virtual ~AptMessenger();
};

class AptMessengerOnline : public AptMessenger
{
public:
	virtual ~AptMessengerOnline();
};

AptMessengerOnline::~AptMessengerOnline()
{
	if (g_00E0644C == this)
		g_00E0644C = 0;
}
