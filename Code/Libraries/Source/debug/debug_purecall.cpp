// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// _purecall, retail 0x0003B810 (62 bytes): Zero Hour's debug_purecall.cpp,
// the debug library's replacement for MSVCRT's _purecall. Its body is
// DCRASH_RELEASE("Pure virtual function called."); return 0; and BFME's
// release form of that macro is the out-of-line call-site recorder
// (0x00038790, kind 1) followed by SkipNext (slot 0x60), CrashBegin(0, 0, 0)
// (0x6C), the const char * stream operator (0x38) and CrashDone(1) (0x4C),
// each a virtual through theDebug (0x00DE0880). Retail does not import
// _purecall from MSVCR71; 2,396 .rdata vtable slots point here instead.

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);

// Pure virtual function called
extern "C" int __cdecl _purecall(void)
{
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Pure virtual function called.").CrashDone(1);
	return 0;
}
