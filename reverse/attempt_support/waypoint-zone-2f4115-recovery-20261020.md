# Pathfinder waypoint-zone recovery, 2026-10-20

Recovered `?rva002F4115@Pathfinder@@QAE_NPAVObject@@HHPAVLocomotorSet@@@Z`
in its existing `Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`
home. Native interval: **0x002F4115..0x002F436F, 602 bytes, RET 16, EH**.
Input master: `4d59997174`; BFME 1 reference pointer remains
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`.

## Evidence and retained uncertainty

The Ghidra boundary, next entry at 2F436F, native return cleanup, matched
Pathfinder callers, and WorldBuilder D5F260 establish the method boundary,
Pathfinder receiver and four arguments. Native accesses independently support
Object AI +258, template +56C/+634, locomotor surfaces +10 / AI +1DC,
waypoint position +0C, next +1C and link count +4C, and effective-zone query
through Pathfinder +460. Its observed waypoint filtering and zone breadth-first
walk agree with the existing bank's interpretation. The address-derived name
is retained: no original member spelling is asserted.

The algorithm and STLport storage adapters come from the previously banked
reconstruction, including the corrected single AI surfaces read and real deque
destruction documented in `0x002f4115-20261019.md`,
`0x002f4115-20261019-w3.md` and `0x002f4115-20261020-w2.md`. Folded container
element spellings remain inherited provider adapters, not newly established
original container types. No new pin, alias, address-named global, naked body,
assembly, volatile access or compiler override was introduced.

## What closed the bank

The 601-byte bank selected a LocomotorSet pointer and loaded the surfaces once.
Retail loads the surfaces value in each arm. Earlier standalone value-in-arms
trials emitted 602 bytes but assigned different registers. Reapplying that
source form to the **current whole home unit**, reusing its existing Object,
LocomotorSet, Waypoint, terrain and cell views, yields the exact 602-byte native
body, with every call resolved and no differing patched byte. This does not
attribute the allocation change to any single declaration: whole-unit context
is the demonstrated control. A trial using the existing HSO query constructor
also matches; the landed source retains the bank's explicit query stores.

Both whole-unit trials keep all **108 prior matched function rows** exact.
The production `add_match` verification passes **109/109 functions**, its
data row, 122 literals plus three empty-string references, 92 float literals
and 18 named imports. Existing EH labels are resolved through their parent
unwind data after compiler renumbering. Frozen-file declaration checks pass.

Transient trial sources, complete-byte comparisons and prior-row checks are
in `build/waypoint-zone-oct20/`. `add_match` removes the superseded partial
bank and records the landed result through the ordinary ledger machinery.
Normal commit/push hooks remain enabled. This recovery supplies one previously
missing provider; it does not claim that the entire Pathfinder unit links or
that its unrelated pre-existing link debt is repaired.
