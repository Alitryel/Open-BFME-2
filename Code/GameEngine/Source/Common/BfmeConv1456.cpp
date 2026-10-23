// cl: /Od /Ob1
// Native 0x00029490..0x00029529 (153 bytes; thiscall RET8).
// STLport 4.5.3 _string.c assign(size_type,char) supplies the control flow;
// reviewed at Open-BFME-1 644b1863ec6ec70c7eb3313432ab438c5735d347.
// Retail independently proves start/finish at +0/+4 and the canonical traits
// fill 1C680, erase 12150 and append 29380 calls. Keep the established neutral
// entry name; the three-pointer basic_string view supplies only these operations.
// The visible vendor erase/move bodies are required at /Od /Ob1: the compiler
// declines the erase inline expansion but retains two genuine temporary slots,
// reproducing the native 0x14 frame without the former assembly/padding array.

#include <string.h>

namespace _STL {
template<class T> class char_traits {
public:
    static T *assign(T *, unsigned, T);
};
template<class T> class allocator;
template<class T, class Traits, class Alloc> class basic_string {
public:
    T *erase(T *first, T *last) {
        if (first != last) {
            move(first, last, (m_finish - last) + 1);
            T *new_finish = m_finish - (last - first);
            m_finish = new_finish;
        }
        return first;
    }
    static T *move(T *a, const T *b, unsigned n) {
        return n == 0 ? a : (T *)memmove(a, b, n * sizeof(T));
    }
    basic_string &append(unsigned, T);
    T *m_start, *m_finish, *m_end_of_storage;
};
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowStringAssignView;

class BfmeStrV16
{
public:
    BfmeStrV16 *bfmeAssignV16(unsigned n, char v);
    unsigned size() const { return e - b; }
    char *begin() { return b; }
    char *end() { return e; }
    char *b;
    char *e;
};

BfmeStrV16 *BfmeStrV16::bfmeAssignV16(unsigned n, char v)
{
    if (n <= size()) {
        _STL::char_traits<char>::assign(b, n, v);
        reinterpret_cast<NarrowStringAssignView *>(this)->erase(begin() + n, end());
    } else {
        _STL::char_traits<char>::assign(b, size(), v);
        reinterpret_cast<NarrowStringAssignView *>(this)->append(n - size(), v);
    }
    return this;
}
