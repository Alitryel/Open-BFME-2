# Hash/list subscript linking repair (2026-10-22)

At census 08160bc2c9, current-object legacy checking of the subscript and its
unchanged companion moves 0 -> 176 linked bytes for the subscript. The companion
remains blocked at 0/249 bytes. No closed-strict gain is claimed.

The existing _M_find<int> fold pin names retail 0x002888D4, with the companion
as its original proof source. The subscript emitted a different out-of-line
lookup. Declaring that member template only triggers VC7.1 C1001 in
_hashtable.h:488. An imported forceinline specialization retaining the vendor
lookup body preserves all four rowed bodies and removes the competing copy.
No pin, layout or function identity changes.

Validation: build.sh 4/4, find_declared_unmatched clean, check_csv clean,
and link_check --prepare-current provides self-strict receipts. Legacy check
includes the unchanged companion; before: build/three-link-next-before.txt;
after: build/hash-list-final-legacy.txt. These scratch diagnostics are local;
reproduce with link_check on both stlport_hash_map_int_list_pod264*.cpp units.

Companion sweep: the same inline specialization plus declaration-only resize
preserves 8/8 bytes, but leaves resize undefined and changes the emitted find
wrapper, which then conflicts across both units. Restored the complete companion
and verified 8/8. A shared resize provider and wrapper reconciliation are required
before that sweep is useful; no zero-gain source change retained.
