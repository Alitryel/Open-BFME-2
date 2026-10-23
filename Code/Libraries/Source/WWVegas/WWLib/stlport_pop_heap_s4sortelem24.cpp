// cl: /DNDEBUG /MD /EHsc
// STLport __pop_heap over the same24-byte element/comparator view as the
// matched push/adjust-heap family. Historical element names are unknown.
// Full133-byte body at0x009F5440; direct caller0x009F5C00+0x319;
// only callee is the matched223-byte __adjust_heap at0x009F4CA0.

struct S4SortElem24
{
    int m_key;
    int m_values[5];
};

struct S4Cmp009F4BF0
{
    bool operator()(const S4SortElem24 &left,
        const S4SortElem24 &right) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
    Distance len, Tp value, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
    RandomAccessIterator result, Tp value, Compare comp, Distance *)
{
    *result = *first;
    __adjust_heap(first, 0, last - first, value, comp);
}

// Explicit instantiation for the complete retail specialization.
template void __pop_heap<S4SortElem24 *, int, S4SortElem24, S4Cmp009F4BF0>(
    S4SortElem24 *, S4SortElem24 *, S4SortElem24 *, S4SortElem24,
    S4Cmp009F4BF0, int *);

}

// The BFME1 donor exposes these two __pop_heap wrappers as Rva009F5630 and
// Rva009F5920. Their target identities stay address-derived; retail at the
// two boundaries copies a 24-byte terminal element and calls the matched
// specialization above at 0x00627A10.
void Rva00627B30PopHeap(S4SortElem24 *first, S4SortElem24 *last,
    S4SortElem24 *, S4Cmp009F4BF0 comp)
{
    _STL::__pop_heap(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}

void Rva00627D90PopHeap(S4SortElem24 *first, S4SortElem24 *last,
    S4Cmp009F4BF0 comp)
{
    _STL::__pop_heap(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}
