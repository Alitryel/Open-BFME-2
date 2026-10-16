// Target containment list ABI: 36ADF9 copies a list through the four-byte
// element insertion chain BB975 -> 2C526D -> 5925E2 -> B6447, and
// 36AE51 returns a one-word STLport list from an eight-byte descriptor.
// The original element identity remains unresolved. The copier wrapper
// alone does not establish element width; the allocation/insertion chain does.
#ifndef BFME_CONTAINMENT_LIST_VIEW_H
#define BFME_CONTAINMENT_LIST_VIEW_H
#include <list>
struct Rva0036ADF9Element {
    int rawWords[1];
    bool operator<(const Rva0036ADF9Element &) const;
    bool operator==(const Rva0036ADF9Element &) const;
};
typedef _STL::list<Rva0036ADF9Element> ContainmentList;
// Consumers read the first dword as an object pointer or identifier. Preserve
// its bits without treating the opaque element as a different C++ object type.
inline const int &containmentFirstWord(const Rva0036ADF9Element &element)
{
    return element.rawWords[0];
}
// The destructor is user-declared and empty in release: WB's debug twin of
// 0x0046AD8B destroys the returned view through a conditional-temporary flag
// (cleared at entry, set after the 46247D call), and retail 0x0046AD8B keeps
// only that entry clear ([ebp-0x14] = 0) once the empty body inlines away.
class Rva0036AE51ListView {
public:
    ~Rva0036AE51ListView() {}
    void *a;
    ContainmentList *b;
    ContainmentList rva0036AE51();
};
#endif
