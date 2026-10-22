# Link-repair handoff, 2026-10-22

Inputs: BFME 2 parent 501a13ca82, published link index 08160bc2c9
(2026-10-22 17:08), BFME 1 verified donor 37c3022de1. No source changes
from the attempts below are retained. Existing banks remain authoritative.

## Static narrow-string returners: data verifier disagreement

`static-string-owner.patch` changes only the three returners in
`stlport_narrow_string_range_ctors.cpp` to reference their existing owners,
`g_Va00DDEEFC`, `g_Va00DDEF08` and `g_Va00DDEF38`, through a local string view.
Normal byte verification passes all eight rows (367 authored bytes).
`Rva007AB8D0StringInits.cpp` defines these globals and initializes them to
"false", "true" and "" respectively, with the teardown calls in
`Rva007B6880Thunks.cpp`. These facts refute the original consumer comments
that they are permanently empty 16-byte strings.

`reverse/data_rows.csv` already records the g_Va owners at RVAs 9DEEFC,
9DEF08 and 9DEF38 (currently as four-byte storage). However,
`reverse/data_ledger.csv` selects the consumer's old `StaticEmpty` names and
marks those names unowned, listing the real owners as aliases.
`data_check.py --enforce` rejects all three real owner references as
wrong-name outside the baseline. A tooling seat should reconcile this
ownership discrepancy before the patch is resumed; do not add another
storage definition or whitelist it. An initial trial defining three zeroed
string objects was abandoned when `data_rows.py --verify` correctly caught
those duplicate addresses. The existing owner storage extent is a separate
issue for a future provider repair.

## Helper imports must preserve parent inlining

`stlport_wide_ios_imbue.cpp` (238 bytes at 16200) and
`DamageFX_hashtableResize.cpp` (252 bytes at 16DD70): declaring the conflicting
helpers out of line changes the matched parents. Imported forceinline
helper variants also fail byte verification. Two byte-failing variants were
restored; original 2/2 rows pass. Scratch diagnostics and rejected changes
are under `build/link-seat-helpers/` in this checkout. The shared prerequisite
is preserving the native helper inlining/optimization while binding the
correct retail provider.

## RenderObj destructor optimization

The three Rva001684D6 SimpleStreak units (309 authored bytes) emit a 60-byte
RenderObj destructor with EH-prolog/EBP shape, whereas retail's rowed
13BE20 destructor is 79 bytes with FS/ESP shape. `/O2` and `/Ot` source
flags tested here are normalized back to `/O1` by the region defaults;
those trials preserved four rows but did not test the intended speed
optimization and gained no linking. The shim resets optimization before
its empty destructor. Reconcile provider/optimization rather than repeating
those ineffective flag trials. Scratch: `build/link-seat-renderdtor/`.

## W3DScriptedModelDraw::setModelState

Unit Rva000C4E23Farm.cpp has 3581 legacy authored bytes, including its 3553-byte
parent. Conflicting string cstr ctor and string-base destructor copies
block it. Declaration-only helpers change parent bytes and leave the base
dtor unresolved; imported nothrow forceinline base body still changes the
parent. Two failing builds restored; original 27/27 rows pass. The terrain
track system pointer is also incorrectly declared locally: data RVA 9E2014
names TerrainTracksRenderObjClassSystem. Its real declaration plus a local
view cast is supported, but that alone cannot unblock this unit. Scratch:
`build/link-seat-model/`. Preserve helper inlining/IPRA before retrying.
