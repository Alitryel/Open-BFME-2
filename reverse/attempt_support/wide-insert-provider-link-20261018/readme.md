# Wide-string insert provider link repair

Declare the wide basic_string::_M_insert_aux specialization in
stlport_wide_string.cpp and retain its rowed _Construct<unsigned short,
unsigned short> dependency by explicit instantiation. The header emits a
233-byte non-retail helper; the real provider is the independently rowed
232-byte stlport_wide_string_insert_aux.cpp body at RVA 0x12D10. The calls
already left the unit, so the declaration changes no retained COMDAT bytes
or relocations: all 53 retained digests agree, with only that helper removed
and no new COMDAT. proof.json records the objects and removed helper.

The paired preview refreshes exactly these two strict-current objects in memory
against the same published census c2c5ac8c27 (2026-10-18 11:36), index SHA256
90bd1bed6c06692963e0e6e96411614d502ca33f48b3e26d5338daaae99cf761.
Before: the provider has one wrong-selected finding. After: it links all
232 existing bytes; total local legacy linked bytes 0 -> 232. The wider
instantiation unit still has independent string/append/assignment blockers.
This is a local legacy link gain with strict byte receipts, not a measured
self-strict or closed-strict link gain. No census, status or index is updated.

Acceptance: strict prepare-current before/after and ./build.sh pass all
20 matched rows; new-variants passes; data --enforce/--converged report zero
findings; class/frozen checks pass; EH reports zero applicable rows. Donor
technique: BFME 1 95ca17f14ba05e33d507a804525eae4584c5be4a reviewed;
explicit specialization suppression is already established in this target
unit (reserve), adapted to the independently verified target helper. The
provider and its sole competing copy were checked together. Scratch objects,
receipts and preview logs remain in build/wide-insert-link-20261018/.
