// cl: /O1 /Ireference/shims/bfme2_ascii
// Upstream implementation and layout: Open-BFME-1 ascii_string.h.

#include "ascii_string.h"

// A PooledString is one pointer to a shared entry whose text starts at +8, and
// the entry is never null, so there is no empty-string fallback here.
struct PooledStringEntry
{
    void *m_unknown0;
    PooledStringEntry *m_noCase;
    char m_text[1];
};

AsciiString &AsciiString::operator+=(const PooledString &that)
{
    const PooledStringEntry *entry = *(const PooledStringEntry *const *)&that;

    ((StringBase<char> *)this)->concat(entry->m_text);

    return *this;
}

// Every member ascii_string.h defines in its class is a header inline in
// retail, which keeps one out-of-line copy of each (0x00326BE6, 0x001D8F56,
// 0x0000654A, 0x0048BA39, 0x00001733, 0x000065B8, 0x00006572, 0x0000655C,
// 0x0000659E, 0x00006584, 0x000065CA, 0x00006D12, 0x000065FA, 0x000065E8):
// the COMDATs of calls MSVC did not inline, kept alive by the exports. With
// inlining off, these calls emit the same COMDATs here, where their rows live,
// as selectany copies rather than strong definitions that collide with every
// other TU's inline copy in the linked build.
#pragma inline_depth(0)
// ?bfmeEmitAsciiStringInlines@@YAXPAVAsciiString@@ABV1@PBD@Z present-unmatched
void bfmeEmitAsciiStringInlines(AsciiString *out, const AsciiString &that, const char *text)
{
    AsciiString empty;
    AsciiString copy(that);
    AsciiString fromText(text);
    AsciiString fromChar(*text);
    AsciiString prefix(text, 1);
    AsciiString middle(text, 0, 1);
    AsciiString part(that, 0, 1);
    *out = that;
    *out = text;
    *out = *text;
    *out += that;
    *out += *text;
    *out += text;
}
#pragma inline_depth()
