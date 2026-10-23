// cl: /O2
// Byte-identical port of BFME1 StringBase<char>::startsWithNoCase worker.
// Retail at 0x000359B0 holds the string's own length in edx and the argument
// length in ecx; the donor's noinline + named-length spelling reproduces it.
// The TU links the dynamic CRT, so _memicmp goes through the import table.
#define _DLL
#include <string.h>

#include "string_base.h"

inline bool StringBase<char>::startsWithNoCase(const char *str, int len) const
{
    if (str[0] == '\0') {
        return true;
    }
    int myLen = m_data ? m_data->length : 0;
    if (myLen < len) {
        return false;
    }
    const char *data = &m_data->data[0];
    return _memicmp(data, str, len) == 0;
}

// BFME1 donor find worker: counted for-loop over [start, end). Retail at
// 0x00035AB0 is the wchar_t instantiation.
template <typename T>
const T *StringBase<T>::find(T c) const
{
    const T *start = m_data ? &m_data->data[0] : (const T *)"";
    const T *end = start + (m_data ? m_data->length : 0);

    for (const T *p = start; p != end; ++p) {
        if (*p == c) {
            return p;
        }
    }

    return 0;
}

template const wchar_t *StringBase<wchar_t>::find(wchar_t c) const;

// startsWithNoCase is a header inline in retail: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStringBaseStartsWithNoCase@@YAXPAV?$StringBase@D@@@Z present-unmatched
void bfmeEmitStringBaseStartsWithNoCase(StringBase<char> *p)
{
    p->startsWithNoCase((const char *)0, 0);
}
#pragma inline_depth()
