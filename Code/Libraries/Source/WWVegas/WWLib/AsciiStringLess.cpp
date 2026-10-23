// cl: /O1 /DNDEBUG /MD

// Free AsciiString::operator< at 0x0005598C (23B). Leaf over the matched
// StringBase<char>::compare row at 0x69D6.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#pragma inline_depth(0)
// ?bfmeEmitAsciiStringLess@@YAXPBVAsciiString@@0@Z present-unmatched
void bfmeEmitAsciiStringLess(const AsciiString *asciiString, const AsciiString *b)
{
    operator<(*asciiString, *b);
}
#pragma inline_depth()
