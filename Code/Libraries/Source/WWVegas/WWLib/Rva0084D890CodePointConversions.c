// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef struct Rva0084D890CodePage
{
    unsigned long locale;
    unsigned int codePage;
} Rva0084D890CodePage;

__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int, unsigned long, const char *, int, unsigned short *, int);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int, unsigned long, const unsigned short *, int, char *, int,
    const char *, int *);
__declspec(dllimport) int __stdcall LCMapStringW(
    unsigned long, unsigned long, const unsigned short *, int,
    unsigned short *, int);

unsigned short Rva0084D890ByteToWide(Rva0084D890CodePage *locale, int character)
{
    unsigned short converted;
    if (character == -1)
        return (unsigned short)-1;
    MultiByteToWideChar(locale->codePage, 1, (const char *)&character, 1, &converted, 1);
    return converted;
}

int Rva0084D8D0WideToByte(Rva0084D890CodePage *locale, unsigned short character)
{
    char converted;
    int result = WideCharToMultiByte(locale->codePage, 0x240,
        &character, 1, &converted, 1, 0, 0);
    if (!result)
        return 0xffff;
    return (signed char)converted;
}

// Retail 0x00020AC0 is named by address: the BFME1 Rva0084D7F0 donor is
// ICF-folded across two BFME1 addresses, so its symbol is not target identity.
// Target bytes read the first dword of the input as LCMapStringW's LCID,
// apply flags 0x200 to the one-WCHAR source, and return the output word.
unsigned short Rva00020AC0(Rva0084D890CodePage *owner, int character)
{
    unsigned short converted;
    LCMapStringW(owner->locale, 0x200,
        (const unsigned short *)&character, 1, &converted, 1);
    return converted;
}

/* BFME2 0x00020E30; Open-BFME-1 5cae4bdff Rva0084DB70 (BFME1 0x0084DB70), written
   against this file's code-page record: the LCID is its first dword. */
int Rva0084DB70(Rva0084D890CodePage *owner, unsigned short *to, int count,
    const unsigned short *from, int fromCount)
{
    return LCMapStringW(owner->locale, 0x400, from, fromCount, to, count);
}
