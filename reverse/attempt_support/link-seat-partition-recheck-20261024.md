# Partition filter provider repair, 2026-10-24

BFME 2 production input `49e88f596a`; published retail-truth-4 index
`268f876e3b`, 2026-10-24 02:54, fetched with its objects. The paired scoped
legacy preview changes from one linked unit / 125 B to two / 209 B: **+84 B**.
This is not a closed-strict or full-census measurement.

The native constructor at 2611F2 has three byte-exact rows (84 B unique,
119 B including alias rows). Its three-slot table BF8FF0 selects deleting
destructor 395A19, public predicate 261B7E and inherited mask 36CC7A.
The native base carries its next pointer at +4, with derived fields +8/+C.
The predicate already links and remains byte-exact at its existing provider.

The competing first table came from PartitionManager.cpp's older donor
view in reference/shims/aiupdatelayout/GameLogic/PartitionManager.h: a base
without a virtual destructor, fields at +4/+8 and protected allow. The only
uses of this derived type in that TU were two present-unmatched definitions:
the const-Object constructor and protected predicate. The indexed constructor
has no kept callers; the protected predicate is referenced only by that old
table. Removing these unused donor definitions removes the incompatible
one-slot table and leaves the native constructor/predicate providers.
No native row, header, class layout, symbol pin or verifier was changed.

The earlier blocked recheck correctly identified a provider reconciliation
prerequisite. The reference graph and absence of callers establish that the
obsolete definitions can be removed, resolving that prerequisite. Copying the
old table, suppressing the native table or changing access would preserve the
wrong native layout; none of those approaches was used.

The normal scoped byte gate passes all seven function rows and the one data
row across the constructor and donor units. The predicate was also included
in paired link previews. Class and frozen-file checks pass, converged-data
checking reports no second names, and whitespace checking passes. Strict
reusable receipts are prepared before/after; that verifies these explicit
providers, not whole-tree closure. PartitionManager still has separate
unresolved callees and non-retail selected helpers (see after.txt); no linked
credit is claimed for its own 116 B.

Selection audit: the 29-unit sole-blocker preview found five already-linked
units totaling 2,722 B (wide_ifstream, MapCache clearUnseenMaps,
StructureToppleUpdateCtor, simplevec_float_cleanup, Rva00534A2AMapSubscript).
These are inherited repairs. Native DynamicVector destructor codegen,
request-set allocator proxies, GeometryShape ownership, GUI parse callbacks,
shader provider graphs and large private class views retain their recorded
prerequisites. No unchanged blocked codegen variants were retried.

Paired logs and the before graph are retained in the sibling
link-seat-partition-recheck-20261024/ directory. Remaining broad selection
logs are ignored build/seat-{sole-current,broad-postbuild,current-top}.txt.
