// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva003552BDJump@@YAXXZ @0x003552BD 5B
// Evidence: 5B jmp to rowed dup_00355257; callers are Unwind funclets
void __cdecl dup_00355257();
void __cdecl Rva003552BDJump()
{
	dup_00355257();
}

// dup_00355257 has no object of its own: its row is a gen-alias of the hashtable destructor ArmorStoreCtor.cpp emits.
#pragma comment(linker, "/alternatename:?dup_00355257@@YAXXZ=??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@2@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@XZ")
