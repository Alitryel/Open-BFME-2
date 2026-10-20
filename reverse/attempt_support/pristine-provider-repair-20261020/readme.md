# PristineBone map provider prerequisite repair

Base: `7a5635339195863a474e3d15a48254eb7f5590ad`.
Reference: BFME1 `92f6bbe8e1dcdb46b5d27da0674313efc822b790`, unchanged.
Model: `Codex(runtime-model-not-exposed)`.

This is a provider-ownership prerequisite repair, with **zero new unique
recovered bytes and zero additional linked bytes**. Existing matched owners
and their extents are unchanged. No shared header, compiler flag or layout
changes. Only three existing sources change: W3DModelDraw,
W3DModelDrawO1Inlines and stlport_map_namekey_pristinebone.

## Native evidence and resulting source

The PristineBone map's existing 25-byte default constructor at `0x004260FD`
calls its 42-byte tree constructor at `0x00425FEC`. Main W3DModelDraw's
26-byte incidental default constructor loses to that provider through an
early declaration, before its header instantiates the map.

Native map destructor `0x000BBF4B` is a five-byte tail jump to the 56-byte
tree destructor at `0x000BB65C`. The latter calls 41-byte clear `0x000B92FB`
and allocator `0x00030830`; its EH state transition before allocator cleanup
is present in the standalone home, but absent from the incidental O1
52-byte destructor. Both consumers declare the explicit tree destructor.
Main consequently emits the natural five-byte map wrapper and stops
emitting its differing tree/base/deallocator copies. No implicit-map
destructor declaration is retained.

The 41-byte clear is already owned by RvaTreeEraseClearFamily.cpp; it is
not new coverage. Its typed name previously called an unbound typed erase.
Removing the standalone home's old declaration-only suppression emits the
genuine STLport 45-byte `_M_erase`: all bytes match neutral owner
`0x000B646B`, recursive REL32 at +19 targets itself and REL32 at +28 targets
allocator `0x00030830`. All 134 prior home COMDAT definitions remain
unchanged. Ordinary `pin_admission --add` admits this actual template fold
with the home as proof source. The neutral owner remains; no duplicate row
or renamed body is added. The rowed map assignment and Pod248+A0 map
teardown chains independently support the clear/erase family relation.

The admitted fold makes the existing typed clear fully provable, including
its sole erase relocation. Main declares clear instead of emitting its
50-byte incidental copy. The previously incorrect main node deallocator
also disappears naturally after declaring the tree destructor; the
remaining O1 20-byte copy calls the real game allocator wrapper.

## Verification and accounting

Normal build: 47/47 matched functions across six sources, including all
13 O1 consumer rows. Exception-data verification: 8/8 EXACT, no baseline
and no missing object. String/float/import checks pass. The three changed
sources' placement scan proposes zero bodies and zero pins. Frozen-source
checks pass. No function-ledger rows change.

Immutable before and final objects/receipts use published index `144ed0ccab`
on both sides. Both states are 1/6 clean and 115 linked bytes. The original
pre-edit report versus final report removes 18 blocker instances and adds
none. Replaying both frozen object sets with the final identity pin also
finds no additions and removes seven COMDAT and sixteen selected-provider
findings. Those extra five findings are the old incorrect erase copy newly
classifiable under its now-proven identity, not additional byte progress.

Independent object audit: main removes 14 definitions and preserves 1,216
normalized definitions; its unrowed ModelConditionInfo constructor changes
322 to 310 bytes because it calls the real map constructor, and the unrowed
adjustAnimation body's only change is diagnostic __LINE__ constants. O1
removes its tree destructor and unused clear, preserving 642 definitions.
Home adds only the exact erase; the other three objects are identical.
The prior matched bodies remain exact throughout the final cohort.

The outside indexed GameSpyInfoCtor consumer was also checked with its current
object and all 74 dependency hashes: 63 to 60 blocker instances, none added.
Its existing 52-byte tree-destructor debt is unchanged; only the selected
map-constructor, clear and deallocator findings disappear. No outside linked
byte gain is credited.

## Failed controls and remaining prerequisites

Late constructor/tree-destructor declarations fail VC7.1 C2908 after header
instantiation. The declarations must precede the W3D header, after Common/CRC
has established the project's memory-header ordering. A declaration of the
implicit map destructor is accepted but does not suppress its emission;
the explicit tree destructor is the effective, ordinary ownership control.
A separate node-deallocator declaration was discarded after it changed the
base destructor. It is unnecessary in the final tree-destructor repair.

The main ordinary PristineBoneInfo default constructor still emits three
bytes rather than the established 22-byte Matrix3D constructor twin. Fixing
that requires a separate class/header contract and is intentionally deferred.
Other preexisting subscript, pair-copy, lookup and unrelated donor blockers
remain. The existing typed-base-destructor pin at `0x00142D70` also predates
this work; native EH cleanup uses equivalent 14-byte body `0x0007FAB3`.
Both call allocator30830. That historical duplicate-body identity is not
changed or used to justify a new alias here.

The hatch-baseline diff is exactly normal pin_admission output: its checked
B646B allowance plus removal of eight stale allow annotations at 41360E,
413727,603A2D,603AA8,603E50,604251,60426C and6044A0. No manual exemptions or
new protected debt-baseline entries were added.

Reproduce ordinary build, eh_verify and link_check using the six sources:
W3DModelDraw, W3DModelDrawO1Inlines, stlport_map_namekey_pristinebone,
stlport_map_namekey_pristinebone_subscript,
stlport_map_namekey_pristinebone_copy and StlportPod248Assign.
Local logs and immutable objects are in `build/pristine-batch3/`; the final
snapshot is `final-v2-manifest.json`/`final-v2`, not the earlier diagnostic
`final` snapshot. Independent reports are under fleet reports/zh-scout/batch3,
reports/review/batch3 and reports/near-audit/batch3.
