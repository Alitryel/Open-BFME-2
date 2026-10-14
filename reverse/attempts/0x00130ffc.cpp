// ??0Rva00130FFC@@QAE@PAVRva00116680@@PAPAXPAH_N@Z
// partial score=0.8 date=2026-10-14
// ??0Rva00130FFC@@QAE@PAVRva00116680@@PAPAXPAH_N@Z, retail 0x00130FFC (34B).
// A lock holder's constructor: remembers the surface at +0, locks it through
// the rowed ?rva00116680@Rva00116680@@QAEPAXPAH_N@Z (0x00116680, pitch out
// and discard flag passed through) and writes the returned bits pointer to
// the caller's slot; returns this (ret 0x10). It sits in the texture.cpp run
// after StringClass::Is_Empty 0x00130FEA. No direct caller reaches it in
// retail, so the class and its name stay address-derived.
class Rva00116680
{
public:
	void *rva00116680(int *pitch, bool discard);
};

class Rva00130FFC
{
public:
	Rva00130FFC(Rva00116680 *surface, void **bits, int *pitch, bool discard);
private:
	Rva00116680 *m_surface;	// +0x00
};

Rva00130FFC::Rva00130FFC(Rva00116680 *surface, void **bits, int *pitch, bool discard)
	: m_surface(surface)
{
	*bits = surface->rva00116680(pitch, discard);
}
