// cl: /DNDEBUG /MD /EHsc
// stlport
// ?Rva006FD060Forward@@YAXPAX000@Z @0x006FD060 149B
// Evidence: LINK body for 0x006E5050 0x0070E900 via Aux 0x006FC670 pin asserts for aActionStream pBase aConstantFile lines 0x379 0x37A 0x37B callers 0x006E54A2 0x0070EADB.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)
extern "C" void BfmeAux006FC670(void *first, void *last, void *sentinel, void *comp);

void __cdecl Rva006FD060Forward(void *a1, void *a2, void *a3, void *a4)
{
	if (!a1) {
		g_bfmeAptAssertAtE17734("aActionStream", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x379);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!a2) {
		g_bfmeAptAssertAtE17734("pBase", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x37A);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (!a3) {
		g_bfmeAptAssertAtE17734("aConstantFile", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x37B);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	BfmeAux006FC670(a1, a2, a3, a4);
}
