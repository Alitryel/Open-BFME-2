// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Native052D2..052E1 (15B), unreferenced: the wide twin of AsciiString.cpp's
// Rva000052C4LengthOrZero. It tests the cdecl pointer, returns 0 for null and
// otherwise tail-jumps through the msvcr71 wcslen import (IAT BBA6AC) rather
// than a thunk, so this unit declares wcslen dllimport itself instead of
// taking <string.h>'s spelling. Original name unknown; address-named.
typedef unsigned int size_t;
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const unsigned short *text);

unsigned int Rva000052D2WideLengthOrZero(const unsigned short *text)
{
    return text ? (unsigned int)wcslen(text) : 0u;
}
