# Prop storage link prerequisite, 2026-10-21

Baseline 51154cbc5c; published index 17918792f6 (09:22). BFME1 donor
5987fd1b859e86801d093256eadc6fb63d87785f. Existing seven rows are exact.
Legacy preview is 0/319 nonpadding bytes, with undefined private storage ctor
and dtor. Target ctor EF008 calls empty-storage fold 1F81BF; native unwind
763976 calls wrapper 8B4CD, which forwards to rowed destructor 8B470.
Element identity remains unknown. Rva000EEEF4Dtor independently has the same
12-byte member and cleanup chain.

The diagnostic constructs a storage-only int allocator base through an
inline Rva0008B470 constructor and retains that existing destructor. Its
wrapper destructor is the correct five-byte jump. Declaring the unused
_Vector_base<int> destructor removes three losing helper COMDATs, and all
seven original rows remain byte exact; the bounded legacy preview becomes
319 bytes. This is NOT an accepted repair: the newly defined PropList ctor
is 12 bytes calling the 19-byte Rva0008B470 ctor, while retail calls the
19-byte fold directly. add_match correctly rejects the ICF claim and rolls
it back. __forceinline on the nested constructor leaves that result unchanged.
No additional pins or aliases were added. A further source shape must prove
all new helper bodies as well as the parent; the favorable link result alone
is insufficient. Original Code source restored and claims released.

The first setup compile lacked the stlport marker; the two actual fold
verification trials both failed as recorded in constructor-mismatch.log.
Use the preserved diagnostic as a starting point, not a landed provider.
