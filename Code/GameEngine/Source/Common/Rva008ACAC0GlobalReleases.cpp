// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Shutdown release sweep at retail 0x006EC1A0, ported from the BFME1
// Rva008ACAC0GlobalReleases.cpp donor: 26 blocks transfer unchanged,
// BFME2 appends one trailing global (0x00E18200).

class Acac0Releaseable
{
public:
	virtual void unusedSlot(void);
	virtual void release(void);
};

extern Acac0Releaseable *g_Va00E1819C;
// g_Va00E1819C: matched references place it at VA 0xe1819c (zero-filled .bss).
Acac0Releaseable * g_Va00E1819C;
extern Acac0Releaseable *g_Va00E18198;
// g_Va00E18198: matched references place it at VA 0xe18198 (zero-filled .bss).
Acac0Releaseable * g_Va00E18198;
extern Acac0Releaseable *g_Va00E181E8;
// g_Va00E181E8: matched references place it at VA 0xe181e8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181E8;
extern Acac0Releaseable *g_Va00E181E4;
// g_Va00E181E4: matched references place it at VA 0xe181e4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181E4;
extern Acac0Releaseable *g_Va00E181DC;
// g_Va00E181DC: matched references place it at VA 0xe181dc (zero-filled .bss).
Acac0Releaseable * g_Va00E181DC;
extern Acac0Releaseable *g_Va00E181E0;
// g_Va00E181E0: matched references place it at VA 0xe181e0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181E0;
extern Acac0Releaseable *g_Va00E181D8;
// g_Va00E181D8: matched references place it at VA 0xe181d8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181D8;
extern Acac0Releaseable *g_Va00E181A0;
// g_Va00E181A0: matched references place it at VA 0xe181a0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181A0;
extern Acac0Releaseable *g_Va00E181A4;
// g_Va00E181A4: matched references place it at VA 0xe181a4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181A4;
extern Acac0Releaseable *g_Va00E181A8;
// g_Va00E181A8: matched references place it at VA 0xe181a8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181A8;
extern Acac0Releaseable *g_Va00E181AC;
// g_Va00E181AC: matched references place it at VA 0xe181ac (zero-filled .bss).
Acac0Releaseable * g_Va00E181AC;
extern Acac0Releaseable *g_Va00E181B0;
// g_Va00E181B0: matched references place it at VA 0xe181b0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181B0;
extern Acac0Releaseable *g_Va00E181B8;
// g_Va00E181B8: matched references place it at VA 0xe181b8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181B8;
extern Acac0Releaseable *g_Va00E181B4;
// g_Va00E181B4: matched references place it at VA 0xe181b4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181B4;
extern Acac0Releaseable *g_Va00E181BC;
// g_Va00E181BC: matched references place it at VA 0xe181bc (zero-filled .bss).
Acac0Releaseable * g_Va00E181BC;
extern Acac0Releaseable *g_Va00E181C8;
// g_Va00E181C8: matched references place it at VA 0xe181c8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181C8;
extern Acac0Releaseable *g_Va00E181D0;
// g_Va00E181D0: matched references place it at VA 0xe181d0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181D0;
extern Acac0Releaseable *g_Va00E181CC;
// g_Va00E181CC: matched references place it at VA 0xe181cc (zero-filled .bss).
Acac0Releaseable * g_Va00E181CC;
extern Acac0Releaseable *g_Va00E181D4;
// g_Va00E181D4: matched references place it at VA 0xe181d4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181D4;
extern Acac0Releaseable *g_Va00E181F8;
// g_Va00E181F8: matched references place it at VA 0xe181f8 (zero-filled .bss).
Acac0Releaseable * g_Va00E181F8;
extern Acac0Releaseable *g_Va00E181FC;
// g_Va00E181FC: matched references place it at VA 0xe181fc (zero-filled .bss).
Acac0Releaseable * g_Va00E181FC;
extern Acac0Releaseable *g_Va00E181F4;
// g_Va00E181F4: matched references place it at VA 0xe181f4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181F4;
extern Acac0Releaseable *g_Va00E181EC;
// g_Va00E181EC: matched references place it at VA 0xe181ec (zero-filled .bss).
Acac0Releaseable * g_Va00E181EC;
extern Acac0Releaseable *g_Va00E181F0;
// g_Va00E181F0: matched references place it at VA 0xe181f0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181F0;
extern Acac0Releaseable *g_Va00E181C0;
// g_Va00E181C0: matched references place it at VA 0xe181c0 (zero-filled .bss).
Acac0Releaseable * g_Va00E181C0;
extern Acac0Releaseable *g_Va00E181C4;
// g_Va00E181C4: matched references place it at VA 0xe181c4 (zero-filled .bss).
Acac0Releaseable * g_Va00E181C4;
extern Acac0Releaseable *g_Va00E18200;
// g_Va00E18200: matched references place it at VA 0xe18200 (zero-filled .bss).
Acac0Releaseable * g_Va00E18200;

void d_008acac0(void)
{
	Acac0Releaseable *released;

	released = g_Va00E1819C;
	if (released)
	{
		released->release();
		g_Va00E1819C = 0;
	}

	released = g_Va00E18198;
	if (released)
	{
		released->release();
		g_Va00E18198 = 0;
	}

	released = g_Va00E181E8;
	if (released)
	{
		released->release();
		g_Va00E181E8 = 0;
	}

	released = g_Va00E181E4;
	if (released)
	{
		released->release();
		g_Va00E181E4 = 0;
	}

	released = g_Va00E181DC;
	if (released)
	{
		released->release();
		g_Va00E181DC = 0;
	}

	released = g_Va00E181E0;
	if (released)
	{
		released->release();
		g_Va00E181E0 = 0;
	}

	released = g_Va00E181D8;
	if (released)
	{
		released->release();
		g_Va00E181D8 = 0;
	}

	released = g_Va00E181A0;
	if (released)
	{
		released->release();
		g_Va00E181A0 = 0;
	}

	released = g_Va00E181A4;
	if (released)
	{
		released->release();
		g_Va00E181A4 = 0;
	}

	released = g_Va00E181A8;
	if (released)
	{
		released->release();
		g_Va00E181A8 = 0;
	}

	released = g_Va00E181AC;
	if (released)
	{
		released->release();
		g_Va00E181AC = 0;
	}

	released = g_Va00E181B0;
	if (released)
	{
		released->release();
		g_Va00E181B0 = 0;
	}

	released = g_Va00E181B8;
	if (released)
	{
		released->release();
		g_Va00E181B8 = 0;
	}

	released = g_Va00E181B4;
	if (released)
	{
		released->release();
		g_Va00E181B4 = 0;
	}

	released = g_Va00E181BC;
	if (released)
	{
		released->release();
		g_Va00E181BC = 0;
	}

	released = g_Va00E181C8;
	if (released)
	{
		released->release();
		g_Va00E181C8 = 0;
	}

	released = g_Va00E181D0;
	if (released)
	{
		released->release();
		g_Va00E181D0 = 0;
	}

	released = g_Va00E181CC;
	if (released)
	{
		released->release();
		g_Va00E181CC = 0;
	}

	released = g_Va00E181D4;
	if (released)
	{
		released->release();
		g_Va00E181D4 = 0;
	}

	released = g_Va00E181F8;
	if (released)
	{
		released->release();
		g_Va00E181F8 = 0;
	}

	released = g_Va00E181FC;
	if (released)
	{
		released->release();
		g_Va00E181FC = 0;
	}

	released = g_Va00E181F4;
	if (released)
	{
		released->release();
		g_Va00E181F4 = 0;
	}

	released = g_Va00E181EC;
	if (released)
	{
		released->release();
		g_Va00E181EC = 0;
	}

	released = g_Va00E181F0;
	if (released)
	{
		released->release();
		g_Va00E181F0 = 0;
	}

	released = g_Va00E181C0;
	if (released)
	{
		released->release();
		g_Va00E181C0 = 0;
	}

	released = g_Va00E181C4;
	if (released)
	{
		released->release();
		g_Va00E181C4 = 0;
	}

	released = g_Va00E18200;
	if (released)
	{
		released->release();
		g_Va00E18200 = 0;
	}

}