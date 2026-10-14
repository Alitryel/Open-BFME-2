// cl: /O1 /Oy- /G7 /arch:SSE /MD /DNDEBUG /EHs-c-
//
// Motion-channel encoding-filter validity flag and its CRT dynamic
// initializer, retail 0x007ACFB0..0x007ACFBB (11B):
//
//     call ?Rva001B20E5Init@@YA_NXZ   ; generator, 0x001B20E5
//     mov  byte ptr [0x00DFD8E8], al  ; table-valid flag
//     ret
//
// ZH motchan.cpp's AdaptiveDeltaMotionChannelClass ctor keeps the same
// filter table and flag (`static bool table_valid` next to the same
// filtertable, set to true after generating entries 16..255); BFME2 split
// the generator into Rva001B20E5Init (BFME2EncodingFilterTableInit.cpp,
// which owns filtertable at VA 0x00DB6C28) and initializes the flag from its
// bool result. The flag is write-only in retail (its only .text reference is
// this store) and zero-filled at load. The target spelling is not recovered,
// so the flag gets a neutral descriptive name; the initializer keeps its
// address-derived name.
extern bool Rva001B20E5Init();

bool g_bfmeEncodingFilterTableValid = false;

void Rva007ACFB0StoreTableValid()
{
	g_bfmeEncodingFilterTableValid = Rva001B20E5Init();
}
