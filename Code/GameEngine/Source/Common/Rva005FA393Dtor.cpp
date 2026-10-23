// cl: /MD
//
// StrategicHUD::BattlePromptMovieClip's destructor at 0x005FA393 (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the guarded-delete helper at 0x005FA146
// (pinned opaque ?clear: nulls its pointer at +0, runs the element dtor at
// 0x005F9877, then operator delete; exact method unproven). Same shape as the
// three Rva000AD6F4Members.cpp bodies (0x328A75/0x577936/0x5F83DF) and the
// 0x005F7750 twin; the helper type is only declared here (defined nowhere --
// it resolves via the pin). Owner: see the class comment below.
// The 77B constructor at 0x005FA7EB allocates 0x64 bytes, calls 0x005FA3B1
// with this plus three pointer-sized args, and stores the returned inner
// object at +4. It writes the folded 0x008078DC vtable; because that table has
// several aliases, the constructor keeps its address-derived Rva005FA7EB name.
class AsciiString;
struct Rva005F91F3Src;
class Rva005F9877
{
public:
	~Rva005F9877();
};

class Rva005FA146
{
public:
	void clear();

private:
	Rva005F9877 *m_ptr;
};

// 0x005FA393 is StrategicHUD::BattlePromptMovieClip's destructor: the
// prompt clip Rva005E9625, whose ctor 0x005E9CC3 runs the BattlePromptMovieClip
// ctor 0x005FA7EB, destroys its base through it (0x005E9625), and the ctor's
// +4 Impl holder is what it clears.
namespace StrategicHUD {
class BattlePromptMovieClip
{
public:
	class Impl
	{
	public:
		Impl(BattlePromptMovieClip *owner, int a, const AsciiString &b, const Rva005F91F3Src &c); // rowed 0x005FA3B1
		char m_opaque[0x64];
	};
	virtual ~BattlePromptMovieClip();

private:
	Rva005FA146 m_member04;
};
}
class Rva005FA3B1Inner
{
public:
	Rva005FA3B1Inner(void *owner, void *a, void *b, void *c);
	char m_opaque[0x64];
};

extern const void *const g_00C078DC[];

class Rva005FA7EB
{
public:
	Rva005FA7EB(void *a, void *b, void *c);

private:
	const void *const *m_vtable;
	StrategicHUD::BattlePromptMovieClip::Impl *m_member04;
};

// ?Rva005FA7EB::Rva005FA7EB present-unmatched
Rva005FA7EB::Rva005FA7EB(void *a, void *b, void *c)
	: m_vtable(g_00C078DC)
{
	m_member04 = new StrategicHUD::BattlePromptMovieClip::Impl((StrategicHUD::BattlePromptMovieClip*)this, (int)a, *(const AsciiString*)b, *(const Rva005F91F3Src*)c);
}

void __cdecl operator delete(void *);

StrategicHUD::BattlePromptMovieClip::~BattlePromptMovieClip()
{
	m_member04.clear();
}

// ?clear@Rva005FA146@@QAEXXZ @0x005FA146 26B: guarded-delete helper for
// BattlePromptMovieClip member at +4. Nulls its pointer, runs element dtor at
// 0x005F9877 (??1Rva005F9877@@QAE@XZ pin), then operator delete
// (??3@YAXPAX@Z row mem_ops.cpp). Caller jmp at 0x005FA39C in
// ??1BattlePromptMovieClip@StrategicHUD@@UAE@XZ. LINK BONUS names this exact mangling.
void Rva005FA146::clear()
{
	Rva005F9877 *p = m_ptr;
	m_ptr = 0;
	if (p) {
		p->~Rva005F9877();
		operator delete(p);
	}
}
