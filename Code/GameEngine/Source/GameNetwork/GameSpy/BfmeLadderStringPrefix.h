#pragma once

// Preserve the CRT import declaration before string/STL headers during TU composition.
// BFME 2's shared AsciiString (out-of-line compare/set/release, as retail
// calls them) instead of the Zero Hour header's inline bodies, so this unit
// emits no private copies of shared-class methods.
// Retail calls atoi through msvcrt's import table while the STL frees through
// the game's own _free (0x00030830); _CRTIMP is empty for the latter, so
// stdlib's atoi is set aside and redeclared as the import (PeerThread.cpp).
#define atoi atoi_unimported
#include <stdlib.h>
#undef atoi
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
#define ASCIISTRING_H
#include "ascii_string.h"
#include "unicode_string.h"
#define UNICODESTRING_H
