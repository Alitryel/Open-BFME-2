# E8 deque ownership repair, 2026-10-21

The /O2 and no-exception map units explicitly instantiated the whole STLport
`deque<BfmeE8>` class, emitting competing bodies for other verified providers.
Instantiate their six and four existing rowed operations instead. Keep the
actual bfmealloc shim bodies inline for allocation/release and iterator
increment without emitting competing external copies. The /O2 constructor
calls the rowed no-exception map initializer; the no-exception iterator `-=`
wrapper calls the existing /O1 advance provider out of line.

All ten rows pass the complete byte, relocation, string, float and import gates
with self-strict reusable receipts. Every retained COMDAT digest is identical;
no COMDAT is added. `proof.json` records object hashes and all removed names.
No compiler setting, pin, alias, identity, layout or extent changes. The E8
placeholder size and existing target/donor identity limitations remain as
explained in the source. No new authored C++ coverage is claimed.

Paired legacy current-object previews of both owners and three related units
change 2 -> 4 linked units and 814 -> 1,579 nonpadding matched bytes (+765).
The edited units individually change 0 -> 436 and 0 -> 329 bytes. Both previously
linked sibling units remain linked; ShroudManagerImplGetNearestGroupWithValue
retains independent bit-vector and allocator conflicts. These are legacy
preview gains, not closed-strict or runtime results. Frozen-file, new-variant
and normal hook checks apply. No full census, link cycle or runtime runner used.

One allocation trial initially used the vendor __sgi_alloc spelling instead of
the active bfmealloc shim's direct free; byte verification rejected it. Corrected
to the actual shim body. Forcing advance inline made the -= wrapper call an
unrowed += helper; declaration-only advance restores its original complete body.

Donor review reuses the unchanged BFME1
5987fd1b859e86801d093256eadc6fb63d87785f ownership review in
../link-seat-20261021/readme.md. This is a BFME2 instantiation ownership repair,
not a transfer of donor addresses or layouts.
