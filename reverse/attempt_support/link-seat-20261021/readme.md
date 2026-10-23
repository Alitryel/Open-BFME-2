# Link repair, 2026-10-21

BFME2 baseline d814c66f36, published census 2b4d1fb42a (2026-10-21
06:00). The index SHA256 and allocator object comparison are in
allocator-proof.json. Measurements below are bounded legacy link previews,
with self-strict byte receipts on the touched providers. No closed-strict
closure measurement or full link cycle is claimed.

## Armor constructor allocator binding

Rva00427157Ctor.cpp changes from 0 to 691 non-padding matched bytes linked.
Its private generic node allocator loses against the shared provider. Make
the allocator's original native-size branch visible and force-inlined, using
the recipe already present in AnimateWindowManager.cpp. Out-of-line calls
bind to the shared provider; the unit no longer emits its own allocate or
unused __stl_new COMDAT. The original deallocate recipe remains intact.

The allocator semantics come from the STLport header, not an inferred target
layout. The target proof is the unchanged complete bytes and relocations of
all 11 ledger rows, including EH handlers. The three changed unrowed helpers
are listed in allocator-proof.json; no replacement function identity, pin,
alias or layout is asserted. No new external COMDAT variant is introduced.

## Full-gate prerequisite

AudioManagerFocusVolume.cpp had a pre-existing compile error after the
focus-volume parameter rename: the body still read v->m_factor. Restore
the parameter reference as focusVolume->m_factor. All three existing ledger
rows byte-verify, including the 166-byte parent. The legacy preview remains
166 -> 166 bytes; this is a prerequisite of the full byte gate, not a new
link gain.

## Unverified update virtuals

Preserve seven unverified ZH destructor/CRC definitions in the four adjacent
*.cpp.txt artifacts and remove their definitions from the active TUs. These
definitions were explicitly present-unmatched; they have no verified retail
identity or bytes. Their original include context, flags, license and readable
bodies remain available for recovery. No empty Code source or whitelist entry
is added. Existing matched bodies and provenance remain in their home units.

The original collapse, hijacker and default-exit objects emitted unclaimed
vtables/base helper copies referencing DISABLEDMASK_NONE<13>; all four emitted
a CRC body referring to undefined UpdateModule::crc. The helpers are not
needed by the matched bodies. The queue-exit destructor already lives in its
own matched unit, so only its unverified CRC definition moves.

Before: all four units fail their legacy preview (406 + 98 + 34 + 76 bytes).
The 32 related class units are also measured together to check for displaced
dependencies; before, 28 link and 6,513 matched bytes are linked. Acceptance
requires unchanged target bytes plus a positive net result across that group.

After: all 32 related units link in the bounded preview, 6,513 -> 7,127 bytes
(+614); no previously linked unit loses its status. update-proof.json records
the exact unit list, object hashes and the 16 unchanged row extents. Alongside
the 691-byte allocator repair the measured gain is 1,305 bytes. Strict receipts
cover all 30 rows across the six changed TUs, including the audio prerequisite.

The default-exit getter/setter were emitted through the unverified destructor's
vtable. After removing that destructor their symbols vanished. Disabling
inlining globally retains them but also emits wrong Matrix3D/Vector3 helpers,
so that trial is discarded. A qualified-call emission anchor with
inline_depth(0) confined to the anchor retains both original 21/13-byte bodies
without those helpers or the unverified vtable. The anchor is explicitly
absent-from-retail; it is not a new matched body. Both rows pass the complete
byte gate and the unit's legacy preview changes 0 -> 34 bytes.

## Deferred consumers

The attempt log records the rejected special-power visibility trial (caller
stack layout changes), the TeamFactory map-node ownership prerequisite, the
PersistentStorageThread float-tree ownership prerequisite, and the additional
missing command provider in AssistedTargetingUpdate. Sources are restored and
claims released for those units. The special-power diagnostic remains in
build/link-seat/special-power-after-gate.log locally; there is no promising
banked reconstruction or new C++ body in that trial.

## Donor review

Reviewed BFME1's new STLUnsignedShortIntTreeInsertUnique.cpp at
5987fd1b859e86801d093256eadc6fb63d87785f: the explicit specialization
declaration binds to an established shared tree helper. This supports the
ownership approach, but supplies no float-tree destructor identity or
BFME2-specific layout. StatsCollector's zeroOutStats transfer is unrelated.
The allocator recipe itself is already established in BFME2. layout.json
records actual game/ and inputs/reference include resolution.

## Donor freshness and complete acceptance

The previous verified submodule pointer was
68c5ce2789e974f36b6c742d57437d157bc159e9; the clean checkout was updated to
5987fd1b859e86801d093256eadc6fb63d87785f from official master. The update
changes no headers, toolchain or inputs/reference files. The already-migrated
layout resolver finds all six recorded logical roots and the allocator unit's
four include directories; every resolved directory exists (layout.json).

The initial old-pointer full gate exposed the pre-existing audio parameter
error, with three unverifiable rows. After that repair the old-pointer full
gate passed 97,915 function rows and 1,139 data rows plus all reference checks.
That run began before the virtual-isolation edits; their 16 rows additionally
passed scoped complete-byte and self-strict checks at the old pointer. The new
pointer is checked against the final complete source set. No verification was
weakened and no header was substituted.

Refreshed BFME1 scan: 38,752 donors, 5,524 unique placements, all on claimed
ground, with 5,515 exact independently matched boundary controls. Ranked and
near queues both serve zero candidates. The lift lane was run with limit 1000:
150 lifted bodies, 104 servable; these are reference leads, not C++ recovery.
Four changed clean donor units (AsciiStringVectorCopyConstructor,
STLUnsignedShortIntTreeInsertUnique, RvaHashInsertAsciiString, icoord) were
compiled and searched read-only, yielding zero new placements or pins. These
results are tied to the new donor revision above.

Final combined legacy preview: all 34 affected/related units link,
6,679 -> 7,984 bytes (+1,305). All six touched units pass the new-COMDAT-variant
check. check_csv and find_declared_unmatched pass. The full gate also removes
one obsolete reloc-derived name (dup_00223168); no pin or matched-row extent
changes. Authored matched C++ growth is zero; the improvement is existing
verified bytes newly linking. No closed-strict or runtime result is claimed.

The final new-pointer full gate passes all 97,915 function rows, 1,139 data
rows, string/float/import references, DIR32 and pin consistency, module
registry, source claims and the no-op patch. The ignored freshness stamp is
written only after this success. Both full-gate logs are preserved here.
