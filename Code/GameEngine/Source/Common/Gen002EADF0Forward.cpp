// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc
// Retail 0x003377BC forwards a record to the rowed partial-sort heap helper.
// The record's copy and destruction use the same owners as that helper.

// AsciiString and its StringBase<char> base come from the canonical header
// (reverse/canonical_classes.csv): the donor's private copies are the views the
// class gate refuses. Only the 20-byte sort element stays local.
// stlport
#include <vector>
#include "ascii_string.h"

struct BfmeStringRecord000331962
{
    unsigned int word;
    AsciiString text;
    unsigned char flag;
    ~BfmeStringRecord000331962();
};

class Rva003371B1
{
public:
    Rva003371B1(const Rva003371B1 &other);
    Rva003371B1 &operator=(const Rva003371B1 &other);
    ~Rva003371B1();
    AsciiString m_str;
    unsigned char m_flag;
    _STL::vector<BfmeStringRecord000331962> m_vec;
};

struct Rva00337C55Less
{
    bool operator()(const Rva003371B1 &, const Rva003371B1 &) const;
};
namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
    RandomAccessIterator result, Tp value, Compare comp, Distance *distance);

}
// Forward the record preceding last, preserving the caller's comparator slot.
void gen002EADF0(void *a, void *b, int, void *c)
{
    _STL::__pop_heap<Rva003371B1 *, Rva003371B1, Rva00337C55Less, int>(
        (Rva003371B1 *)a, (Rva003371B1 *)b - 1,
        (Rva003371B1 *)b - 1, *((Rva003371B1 *)b - 1),
        *(Rva00337C55Less *)&c, (int *)0);
}
