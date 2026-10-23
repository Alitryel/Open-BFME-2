// cl: /DNDEBUG /MD /EHs-c-
// Transferred unchanged from Open-BFME-1 5cae4bdff game/Libraries/Source/string/StringBaseWideScan.cpp;
// bfme1_sweep places the same masked body: Rva00887300Scan at BFME2 0x00035860. Addresses in the donor text are BFME1.
// Retail 0x00887300: file-static wide-character scan. File-static
// scope is what keeps the pointer in EAX and the character in DX
// (mov cx,[eax] / cmp cx,dx) instead of stack slots. The do-while
// spelling with two early returns is what reproduces retail's
// test-first loop and twin je targets.

// Retail 0x00035840 (21 B), immediately before the wide scan: the narrow
// twin of the same file-static scan (pointer in EAX, character in DL),
// likewise unreferenced in retail and kept by a visible call site.
static const char *Rva00035840Scan(const char *s, char c)
{
	char v;
	do
	{
		v = *s;
		if (!v)
			return 0;
		if (v == c)
			return s;
		++s;
	} while (1);
}

// ?<Rva00035840Keep> absent-from-retail
const char *Rva00035840Keep(const char *s, char c)
{
	return Rva00035840Scan(s, c);
}

static const unsigned short *Rva00887300Scan(const unsigned short *s, unsigned short c)
{
	unsigned short v;
	do
	{
		v = *s;
		if (!v)
			return 0;
		if (v == c)
			return s;
		++s;
	} while (1);
}

// Visible call site so the static is emitted; not claimed.
const unsigned short *Rva00887300Keep(const unsigned short *s, unsigned short c)
{
	return Rva00887300Scan(s, c);
}
