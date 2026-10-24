# Twelve-byte deque copy callbacks

Inputs: BFME2 after published FireLogic903a1d4281, follower index at the same
commit. BFME1 remains verified32774ab0; its reviewed linking changes are
unchanged. This recovery uses STLport4.5.3's reference copy loop and native
callee/stride evidence, with no shared-tool change.

## Ownership correction

Native584E0E is73 bytes. It calls construction2CA82C and iterator increment
421B1E twice. Construction's29-byte body null-checks the destination and
copies three32-bit words. Increment's36-byte body advances by12 and resets
the node end to begin+120. Thus the copy operation is a twelve-byte element
operation; the primary matched40-byte template spelling was not supported.
Its masked placement and two inherited pins hid incompatible constructor
and increment definitions. Retire that row and its explicit instantiation
in a separate reviewable commit. The remaining40-byte operations are not
claimed repaired by this change.

The previous read-only handoff incorrectly inferred element size from that
owner spelling. Independent native callees now establish the missing fact.

## Isolated hypotheses

A field-wise twelve-byte copy-constructor view reproduces both const and
mutable73-byte callbacks and construction29 exactly with strict relocations,
but only13/15 existing o1-unit rows: its two POD push-back bodies change.
Both unsigned and float fields and empty/zero defaults behave the same.
Do not change the shared placeholder's constructor semantics from this.

Instead preserve its existing POD view and specialize the reference copy
loop to use the observed null-checked three-field construction operation.
The actual C++ helper starts the POD lifetime with placement new and assigns
its three fields. All29 bytes and every relocation match the existing
construction owner. The loop calls that proven body, so it cannot throw a
C++ exception and needs no unwind rollback. Both73-byte callbacks and all
15 existing unit rows are exact in isolated compilation. Whole memcpy gives
26 bytes and three separate memcpy calls59; neither is retained.

No original element name or additional field meaning is claimed. BfmeE12
retains its prior size-only spelling/view. The helper's address name records
an operation, not a new original-type identity. Production gates and linked
gain remain pending.

Baseline: o1 unit1455 bytes, no-exceptions new-elements unit1477, and old
40-byte owner358; all three fail to link in the current903a1d4281 preview.
