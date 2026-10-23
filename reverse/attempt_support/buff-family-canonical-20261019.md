# Buff snapshot family: native class reconciliation

The native tables at VA C16FE8 (GlowMaterial), C17068 (BuffInstance) and
C17088 (BuffManager) each have four slots. Their name getters identify the
classes independently of source naming. Slot RVAs in order:

| Class | Deleting destructor | Post-load | Name | Transfer |
|---|---|---|---|---|
| GlowMaterial | 362E73 | 3624FE | 362493 | 3624C4 |
| BuffInstance | 362E8F | B3FD0 | 362D66 | 3628D3 |
| BuffManager | 362EAB | B3FD0 | 362E16 | 362702 |

The former GlowMaterial constructor stored the string "s.v": its four
bytes masqueraded as the first pointer in the native vtable. It now emits
the real table. Constructors 36247C/362D25 prove sizes14/44 hex and material
at30; manager constructor and Drawable allocation prove nine44B entries
and total26C. Save/load and lifecycle accesses independently witness fields.
Keep both smaller constructors together: retail retains EDX/XMM0 over the
embedded material call. The constructors do only nonthrowing initialization.

The BF1 BuffManagerLifecycle source is a semantic guide, not layout proof:
its manager entry count and Snapshot API differ. Existing WB-derived method
names are retained; the glow-effect type remains address-named. The canonical
header uses the capitalized Snapshot API already consumed by Drawable.

All private family declarations were removed from the 17 affected units.
Scalar deleting destructors moved from incomplete emission-only classes to
their real constructors; their existing complete28B rows still verify.
Both empty post-load methods are independently verified whole1B RET twins
of the existing B3FD0 owner. Existing destructor pins were renamed in place;
no pins were added.

Drawable.cpp retains its pre-existing renamed donor Snapshot and donor
BaseType RGBColor. Its donor Snapshot guard is saved/restored while including
the canonical family. Both RGBColor definitions have the same three float
fields; the existing donor definition remains in that one consumer. This
does not silently substitute donor headers or alter their definitions.

Validation before commit:
- 456/456 rowed functions across all17 affected units match.
- 18/18 exception graphs EXACT, no missing objects or baseline exceptions.
- Six emitted tables (constructors and destructors) have exactly the native
  four relocations. Every target owner passes complete-byte/relocation proof;
  deleting-destructor weak defaults are checked by the normal build helper.
- All definitions declared. No new link blockers; 14/17 units link cleanly
  versus13/17 before. Same-census prediction increases by213 bytes relative
  to the immediately preceding local run (8310 to8523).
- Remaining blockers belong to other classes in SnapshotXfersBfme and the
  two mixed deleting-destructor units; none were hidden or reclassified.

Reproduce with tools/build.py, tools/eh_verify.py and tools/link_check.py
on the changed C++ units. Canonical contracts record the native slot owners.
