# ProductionPrerequisite vector link repair

Baseline 134c75cf0c; published census c2c5ac8c27 (2026-10-18 11:36).
All three units emit a non-retail size() copy. Keep STLport
_vector.h's pointer-distance calculation inline with a TU specialization.
The assign unit keeps its existing local class view and member offsets.
The push-back unit previously instantiated every vector member, including
an unrowed copy worker that resolved to a non-retail selected provider.
Instantiate its recovered push_back and uninitialized_fill_n members only.
No pins, aliases, globals, layouts, ledger or shared-header changes.
BFME1 verified reference revision reviewed remains
64d369b90170b7e9ec917d646f020b11f13eb0d5; upstream pointer freshness update
is separately blocked by another seat's reference submodule claim. This fix
is established by target bytes and paired objects, not inferred donor identity.

13/13 ordinary byte rows pass; one EH graph is EXACT. Strict reusable
receipts prove self-strict currency of all three objects. On the same frozen
index, legacy prediction improves 0 to 729 nonpadding bytes, 3/3 clean.
Closed-strict closure and a full link cycle remain unmeasured.

proof.py uses ignored scratch baseline objects in
build/vector-size-link-seat-20261018/before. It verifies no added or changed
COMDAT, exact retained nondebug section bytes/flags/definitions/symbolic
relocations, and no change to any reachable removed name's kept provider.
Unreferenced sole incidental members can disappear; every referenced name
retains the same kept definition. proof.json records hashes and paired results.
The narrow instantiation removes 65 incidental COMDATs; the other units
each remove only size().

Class, declared-unmatched, data enforce, converged-data, new-variants,
case-collision and diff checks pass. Separate blocked trial witnesses
(narrow string teardown and stale filter census) are in re_attempts.log.

On publication rebase, upstream already has the equivalent inline-only
size specialization in the overflow unit. Retain that source verbatim; the
paired +729 B above is the historical measurement, and upstream overlap
must not be counted a second time. Assign and push-back adaptations remain.
