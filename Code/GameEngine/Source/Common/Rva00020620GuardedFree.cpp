// cl: /DNDEBUG /MD /EHsc
// The three BFME 1 guarded-free donors were ICF-folded, so their names do not
// identify this target. Retail bytes at 0x20620 show a null check and a tail
// jump through the imported free slot; keep the target identity address-named.
extern "C" __declspec(dllimport) void __cdecl free(void *p);

void rva00020620(void *p)
{
	if (p != 0)
		free(p);
}
