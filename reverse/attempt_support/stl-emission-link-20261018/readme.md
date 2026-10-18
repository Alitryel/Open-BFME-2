# Bounded STL emission repair, 2026-10-18

The door-exit unit's typed list comparison performs the same node-pointer
comparison as its former base-class operator. A TU-local overload retains
all 261 parent bytes and its 10-byte EH handler while avoiding a non-retail
out-of-line base comparison. This is the established typed-iterator pattern
already used by NetPacket.cpp, applied only after the target byte gate passed.

The two tree cleanup units no longer explicitly instantiate every map method.
Their owned release wrappers still naturally emit each rowed 122-byte tree
destructor and 10-byte EH handler, as well as the 5-byte wrapper. Removing the
unused map instantiation removes references to the incorrectly selected int
comparator, without modifying or renaming that comparator or its provider.

Before and after bounded link_check previews against published census
c2c5ac8c27 show 0/3 -> 3/3 units, 0 -> 545 existing authored bytes linked
(271 + 137 + 137). These are legacy selection previews with self-strict
current byte receipts, not a closed-strict census or runtime result. Each
changed source passed link_check --prepare-current and ordinary full-body,
string, float and import gates, 8/8 rows total. Frozen-source, ledger and
whitespace checks passed. No new coverage, pin, alias, pragma or baseline.

Donor linking review: verified BFME 1 pointer 64d369b9; upstream 95ca17f1,
97a7c973 and d348fca1 reviewed as canonical-view and sole-provider leads.
This repair uses BFME 2's existing STLport dependencies and target receipts;
no new donor source, type identity or layout is inferred. The BFME 1 pointer
update remains deferred pending its previously recorded comparative gate.

The formation sibling was tried twice and restored: removing its noinline
find body changes MSVC's caller stack allocation and list-distance spills.
Its blocker was recorded with re_log.py and all its claims released.
