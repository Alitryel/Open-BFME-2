# Integer hash-table ownership repair, 2026-10-21

At BFME2 c7d922b190, with published census d08db10acb (2026-10-21
18:42 UTC), current objects for hash_map_int, hash_map_int_next_size and
hash_map_int_resize predict 0/1306 nonpadding bytes linked. The final same-index
preview predicts 1062/1306: hash_map_int 1013 B and next_size 49 B link;
resize's independent conflicts remain. These are legacy predictions, not
closed-strict or runtime results.

The main unit's iterator comparison used the wrong /O2 out-of-line copy;
next_size already owns the exact 18-byte comparison at 169CA0. Keep the same
STLport pointer comparison inline in the main unit without exporting another
copy. No final object has an __imp_ relocation. A declaration-only trial broke
the matched operator[] at 6215B0: retail inlines the comparison, while that
trial called it and enlarged the frame from 8 to 18 hex bytes. Keep the verified
inline form instead of changing the unit's compiler settings.

The main unit also instantiated an unrowed erase(iterator) wrapper which called
the separate pinned hashtable erase at 2BFA86. Its available copies are not
retail's. Declare that unrelated wrapper instead of emitting it. In next_size,
instantiate only its two rowed comparison functions rather than the whole map;
remove the now-unused vector and allocator emission controls. Its final object
contains exactly those two COMDATs. No row, pin, identity, ABI or extent changes.

A resize-only instantiation trial preserved its 244-byte body but still linked
0 B because allocator/proxy destructors, fill_n, swap and other helpers differ.
That unit is restored exactly. Revisit only with verified canonical dependency
providers; neither suppressing its comparison alone nor whole-map instantiation
repairs that dependency set.

Acceptance: ./build.sh stlport_hash_map_int verifies 62/62 rows in eight units;
link_check --prepare-current verifies all 29/29 rows of both changed providers
with self-strict reusable receipts. EH verification has zero EH-bearing rows.
Frozen-file and CSV checks pass. Current paired link preview changes 0 -> 1062 B.
BFME1 review reuses the unchanged cea1e973 freshness/link review in
../20261021-bfme1-freshness-link-review.md; this repair uses the existing STLport
4.5.3 bodies and target row owners, without donor address or layout transfers.
