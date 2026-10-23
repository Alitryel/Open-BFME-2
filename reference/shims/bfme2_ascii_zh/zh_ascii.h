#pragma once

// Force-included (/FIzh_ascii.h) into Zero Hour ports that reach AsciiString
// through Zero Hour's Common/AsciiString.h (PreRTS.h): gives them BFME2's
// shared AsciiString (reference/shims/bfme2_ascii) and defines Zero Hour's
// include guard, so its own class is skipped. Needs
// /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii first.
#include "ascii_string.h"
#define ASCIISTRING_H
