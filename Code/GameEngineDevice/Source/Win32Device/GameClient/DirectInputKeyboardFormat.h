#pragma once

// DirectInput 8 SDK record layout. The keyboard table is immutable in retail;
// retain a const pointer in this read-only view of DIDATAFORMAT.
struct GUID;

struct DIOBJECTDATAFORMAT
{
    const GUID *pguid;
    unsigned long dwOfs;
    unsigned long dwType;
    unsigned long dwFlags;
};

struct DIDATAFORMAT
{
    unsigned long dwSize;
    unsigned long dwObjSize;
    unsigned long dwFlags;
    unsigned long dwDataSize;
    unsigned long dwNumObjs;
    const DIOBJECTDATAFORMAT *rgodf;
};

extern "C" const DIOBJECTDATAFORMAT BFMEKeyboardObjectFormats[256];
