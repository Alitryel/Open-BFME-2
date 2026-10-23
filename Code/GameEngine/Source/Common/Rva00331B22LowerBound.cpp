// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x00331B22/27: the four-argument lower_bound entry over the same
// 12-byte records, forwarding range, key and the empty comparator to the
// rowed binary search Rva00331987 (Rva00331987.cpp) with a null distance
// tag, as STLport's lower_bound calls __lower_bound. The original target
// name remains unknown; the name is address-derived.
struct S4LowerBoundLess {};
void *Rva00331987(void *first, void *last, const int *key, S4LowerBoundLess, int *);

void *Rva00331B22(void *first, void *last, const int *key, S4LowerBoundLess comp)
{
    return Rva00331987(first, last, key, comp, 0);
}
