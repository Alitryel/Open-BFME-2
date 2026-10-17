// ?bfmeImplV21@BfmeStrV21@@QAEXPAD000@Z
// partial score=0.237 date=2026-10-17
// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3, BFME1 donor revision 1281192f682.
// Native 0x00028200..0x000284CB: reverse-iterator find_if with a
// not-within-char-range predicate. Its four-way unroll, reverse steps,
// predicate calls to 0x00026C60 and returned iterator establish the identity.
// The char find_if / __find_if instantiations independently reproduce the
// existing 34B/349B providers at 0x00026C60/0x00025B80.
/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include <string>

namespace _STL {
template <class _Tp>
__declspec(dllimport) _Tp *__copy_trivial(const _Tp *__first, const _Tp *__last, _Tp *__result);
}
struct PadTmp { char *v; unsigned char pad[4]; };

class BfmeStrV21 {
public:
    char *m_start;
    char *m_finish;
    char *m_end_of_storage;

    void bfmeImplV21(char *, char *, char *, char *);
};

void BfmeStrV21::bfmeImplV21(char *p0, char *p1, char *p2, char *p3)
{
    ptrdiff_t n = 0;
    PadTmp t1; PadTmp t2; PadTmp t3; (void)t1; (void)t2; (void)t3;
    {
    char _buf[76];
    (void)_buf;
    }
    if (p1 != p2) {
    n = p2 - p1;

    if ((m_end_of_storage - m_finish) >= n + 1) {
        ptrdiff_t off = m_finish - p0;
        char *cur_finish = m_finish;
        if (off >= n) {
            _STL::__copy_trivial(m_finish + 1 - n, m_finish + 1, m_finish + 1);
            m_finish += n;
            _STL::__copy_trivial(p0, p0 + n, p0 + n + 1);
            *(p0 + n) = '\0';
        } else {
            char *old_finish = m_finish;
            char *tmp = p1 + off + 1;
            _STL::__copy_trivial(p2, tmp, m_finish + 1);
            m_finish += n - off;
            _STL::__copy_trivial(p0, old_finish + 1, p0);
            m_finish += off;
            _STL::__copy_trivial(p1, tmp, p0);
        }
    } else {
        ptrdiff_t old_size = m_finish - m_start;
        if (old_size < n)
            old_size = n;
        old_size += 1;
        char *new_buf = old_size ? (char *)::operator new(old_size) : 0;
        (void)new_buf;
    }
    }
}
