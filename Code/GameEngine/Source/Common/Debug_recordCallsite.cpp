// cl: /DNDEBUG /MD /EHs-c- /Oy-

// Forward the caller address and diagnostic kind to the shared BFME debug
// manager. WWDebug's SkipNext uses this same frame-pointer capture idiom and
// explicitly requires a valid frame pointer; the rest of the body is C++.

class Gen001336E5C
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(void *returnAddress, int kind);
};

extern Gen001336E5C *TheGen001336E5C;

// ?_bfme_debugRecordCallsite@@YAXH@Z
void _bfme_debugRecordCallsite(int kind)
{
	unsigned returnAddress;
	__asm
	{
		mov eax, [ebp + 4]
		mov returnAddress, eax
	}
	TheGen001336E5C->slot5C(reinterpret_cast<void *>(returnAddress), kind);
}

class Debug
{
public:
#define V(n) virtual void slot##n();
	V(00) V(04) V(08) V(0C) V(10) V(14) V(18) V(1C)
	V(20) V(24) V(28) V(2C) V(30) V(34) V(38) V(3C)
	V(40) V(44) V(48) V(4C) V(50) V(54) V(58)
#undef V
	virtual void SetCrashAddress(void *returnAddress, bool set);
	static bool SkipNext(bool set);
};

extern Debug * volatile theDebug;

// The matched ProfileAllocMemory caller uses this spelling before the
// separate virtual SkipNext call. The static body records the caller address.
bool Debug::SkipNext(bool set)
{
	unsigned returnAddress;
	__asm
	{
		mov eax, [ebp + 4]
		mov returnAddress, eax
	}
	theDebug->SetCrashAddress(reinterpret_cast<void *>(returnAddress), set);
}
// ?TheGen001336E5C@@3PAVGen001336E5C@@A: the global at VA 0xde0880 is ?theDebug@@3PAVDebug@@A.
#pragma comment(linker, "/alternatename:?TheGen001336E5C@@3PAVGen001336E5C@@A=?theDebug@@3PAVDebug@@A")
// ?theDebug@@3RAVDebug@@A: the global at VA 0xde0880 is ?theDebug@@3PAVDebug@@A.
#pragma comment(linker, "/alternatename:?theDebug@@3RAVDebug@@A=?theDebug@@3PAVDebug@@A")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?SkipNext@BfmeResetDebug@@SA_N_N@Z=?SkipNext@Debug@@SA_N_N@Z")
