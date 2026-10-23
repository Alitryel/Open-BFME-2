#pragma once
#include <string>
// Native 0x0041A617 copy and 0x0041A820 assignment establish text at0,
// unsigned short at12 and flag at14. Deque increment419DF6 proves16-byte
// stride and128-byte nodes. Original record name and scalar meanings unknown.
struct BfmeNarrowRecord0041A617 {
    _STL::basic_string<char> text;
    unsigned short short0;
    unsigned char flag;
    BfmeNarrowRecord0041A617(const BfmeNarrowRecord0041A617&);
    BfmeNarrowRecord0041A617& operator=(const BfmeNarrowRecord0041A617&);
    __forceinline ~BfmeNarrowRecord0041A617();
};

// The pop/copy/push users retain the inline teardown observed in retail.
// The destruction-loop TU calls the existing emitted destructor instead;
// hiding its definition avoids emitting unused competing STL string bases.
#ifndef BFME_NARROW_RECORD16_EXTERNAL_DTOR
__forceinline BfmeNarrowRecord0041A617::~BfmeNarrowRecord0041A617() {}
#endif
