#ifndef BFME_NARROW_RECORD0041A5D2_H
#define BFME_NARROW_RECORD0041A5D2_H
#include <string>
// Target copy41A5D2 and assignment41A7F7 establish strings at0/16 and
// the two-byte scalar at12. Deque pop/push and increment419DD2 establish
// a28-byte element and four elements per112-byte node. Original names
// and scalar meaning/signedness remain unproved; retain existing spelling.
struct BfmeNarrowRecord0041A5D2 {
    _STL::basic_string<char> text0;
    unsigned short short0;
    _STL::basic_string<char> text1;
    BfmeNarrowRecord0041A5D2();
    BfmeNarrowRecord0041A5D2(const BfmeNarrowRecord0041A5D2&);
    BfmeNarrowRecord0041A5D2& operator=(const BfmeNarrowRecord0041A5D2&);
    ~BfmeNarrowRecord0041A5D2();
    void* rva0041A241(unsigned int flags);
};
#endif
