# HTree storage prerequisite, 2026-10-25

Seat: codexb. Destination: `Code/Libraries/Source/WWVegas/WW3D2/htree.cpp`.

Before: the current merge dry-run accepts no pair. Rva00160FC0Storage.cpp
rejects with C2039 (missing HTreeClass member declaration), then missing
private-view fields. Destructor and CaptureBone reject with `bytes`.

Repair: declare the existing nonvirtual `rva00160FC0(Rva00160FC0Input *)`
member in the seed's shared BFME2 HTree header. Make its donor use that header
and the seed's SDK/matrix/STLport environment instead of a second HTreeClass
definition. Interpret the existing three neutral words at +28/+2C/+30 through
a body-specific storage view. Those offsets, pointer widths, allocation calls
and count semantics come from the already-matched native body; no original
method or input-class name is inferred from the donor. Header layout, ownership
and all existing symbol bindings stay intact.

Acceptance:

* `./build.sh .../Rva00160FC0Storage.cpp`: 1/1, full 142 bytes exact.
* `./build.sh .../htree.cpp`: 11/11 matched rows, six compiler float literals.
* `find_declared_unmatched.py` on both sources and the shared header passes.
* `tu_skeleton.py --merge .../htree.cpp --dry-run` now accepts the seed and
  storage donor, 12 rows, and rejects only Destructor/CaptureBone with `bytes`.
  Local before/after receipts: `build/sol-htree-before.txt` and
  `build/sol-htree-after.txt`. No merge applied; this pair is ready for Luna.
* The normal header-dependent commit gate verifies the wider header users.

There are no source-path moves in this prerequisite or the pending AptValue
prerequisite, so the combined outgoing path-consumer audit requires no
repointing. No protected register changes, hatches, files removed, recovered
retail bytes, or identity debt retirement are claimed. Mixed donors and
protected sources remain in place. Diagnose the two remaining byte failures
by row before trying another unchanged merge.

Claims remain held while the runner queues publication: header, seed, storage
donor and RVA 0x00160FC0. The earlier AptValue prerequisite also retains its
header, seed, donor and 0x006DE870 claims. Release these after the batch is
confirmed on origin/master; a prerequisite does not queue an RVA-row landing.

## Follow-up: destructor's unresolved Free call cleared

Row-level composition diagnosis shows the destructor's only mismatch is its
first CALL operand: actual unresolved `e800000000`, retail `e828fdffff`.
The shared Zero Hour-derived header declares Free private, while the existing
matched provider and pin are public `?Free@HTreeClass@@QAEXXZ`. Align the header
declaration with that existing provider; this preserves the current binding
and does not claim to recover original retail access from machine bytes.
The native call destination is the already-matched Free body at 0x00166510.
No new pin, visibility macro, alias or provider rename is needed.

The destructor now includes the same real header and compilation environment
as the seed, removing its second HTreeClass view. `./build.sh` verifies the
26-byte destructor and seed together (12/12); frozen-file checks pass. The
normal merge dry-run accepts seed, storage and destructor, 13 rows, rejecting
only CaptureBone with `bytes`. Receipts: `build/sol-htree-dtor-probe.txt` and
`build/sol-htree-dtor-after.txt`. The wider header gate remains required.
Keep the destructor file and 0x001667E0 claims until publication as well.
This is another prerequisite commit, with no path moves or file reduction.

## Follow-up: CaptureBone specialization conflict cleared

The CaptureBone body itself matched in every combined probe. Its redundant
explicit insert specialization declaration suppressed the seed's 0x001665B0
insert definition. Removing that declaration emitted insert, but its overflow
specialization declaration then changed insert to 293 bytes (retail 288),
adding a zero store to the empty dispatch tag. Removing both redundant
declarations preserves the existing custom push_back and lets the seed's
primary-template instantiations compile in their original context.

Acceptance: standalone CaptureBone remains 229 bytes exact (1/1), and its
frozen-file check passes. All four composition strategies preserve the seed
and CaptureBone rows (`build/sol-htree-capture-probe-after2.txt`). The normal
full dry-run now accepts seed, storage, destructor and CaptureBone with no
rejected whole donors, preserving all 14 rows
(`build/sol-htree-all-after.txt`). These donors are ready for Luna; mixed and
protected donors remain separate. No path moves, identity retirement, file
reduction or recovered C++ bytes occur. The combined outgoing path-consumer
audit still has no moved paths. Hold the CaptureBone file and 0x00166980
claims with the other queued prerequisite claims until publication.

## Follow-up: mixed Free donor is ready for the split lane

`HTreeClassFree.cpp --split --for htree.cpp --dry-run` initially selected only
Free (0x00166510) and lost the residual Clear row (0x001663C0). Clear was defined
inline and disappeared when its only caller left. Move Clear's definition out
of the class so it is emitted independently. A carved Free then called Clear
instead of retaining retail's inline erase: the probe was 71 bytes against
retail's 90. Spell the same erase operation directly inside Free, preserving
its native __copy call, empty by-reference dispatch tag and null distance.
Clear retains its own independent 33-byte implementation.

The donor now includes the seed's real HTree declaration and matrix header,
with the same SDK/STLport environment; its private HTree copy and private
iterator-tag definition are removed. The three-word member view interprets
only already-proven +1C/+20/+24 storage; no new identity or layout is inferred.
The STLport iterator-base header supplies the existing real tag declaration
without instantiating algorithms over an incomplete record.

Acceptance: `./build.sh .../HTreeClassFree.cpp` verifies both rows, 90+33 bytes,
and one float; frozen-file check passes. Final split dry-run retains the one
residual row, matches the carved row alone under TU flags, and accepts seed
plus carved Free with no rejected donor. Receipts:
`build/sol-htree-free-before.txt`, `build/sol-htree-free-probe.txt`,
`build/sol-htree-free-build-inline.txt`, `build/sol-htree-free-inline-after.txt`.
The split has NOT been applied: leave it for Luna, using the tool with claims.
Free's ready split is independent of the three ready whole-donor merges.
No source paths move in this prerequisite or the complete outgoing range;
the prepublication path audit has no consumers to repoint. File reduction,
identity debt retirement and new recovered bytes remain zero. Keep the donor,
0x00166510 and 0x001663C0 claims until the prerequisite batch is published.


## Follow-up: Free split applied at final paths

The split above was subsequently applied with normal tool claims to verify the
prerequisite at its final paths. `tu_skeleton.py --split HTreeClassFree.cpp
--for htree.cpp` moves only Free (0x00166510, 90 bytes); the residual retains
Clear (0x001663C0, 33 bytes). Both existing files remain: net file change zero.
The ledger and TU map each repoint exactly that one existing row. The map was
not regenerated. No identity baseline keys or protected registers change.

Acceptance: `./build.sh htree.cpp HTreeClassFree.cpp` passes 13/13 rows and seven
float literals; frozen-file checks and `check_csv.py` pass (98,249 rows).
The subsequent whole-donor merge dry-run accepts htree.cpp, storage,
destructor and CaptureBone, preserving 15 rows with no rejected whole donor.
Receipts: `build/sol-htree-free-applied.txt`,
`build/sol-htree-free-final-paths.txt`, `build/sol-htree-post-split-dry.txt`.
Leave the three remaining whole-donor merges for Luna after publication.

The staged code-identity check passes in shadow mode with one unregistered
global divergent COMDAT, Vector3's copy constructor. It has 94 cached copies:
93 share the 25-byte variant, while RTS3DSceneVisibilityCheck has a 28-byte
variant. Neither the residual nor this split introduces that variant. A scratch
Verifier compilation of HEAD's pre-split seed passes all 11 old rows and emits
the exact same 25-byte Vector3 constructor as the split seed. This is existing
global shadow debt; no debt retirement or new identity improvement is claimed.

Prepublication path-consumer audit covers the five prerequisite commits since
7d1555ce5f, plus this staged split (HEAD before split f58a519fc4), and checks
both origin/master..HEAD and the own-branch range to distinguish concurrent
upstream work. No active tool, hook, workflow, include or build input names the
moved Free row by its former source path. Both paths remain valid for residual
rows; historical evidence, the header inventory and census snapshots remain.
The tool updates the Doxygen source registry, function ledger and one TU-map
entry. No other consumers require changes. Existing identity keys remain
accounted for; file reduction, identity debt retired and recovered bytes are
all zero. Keep the outstanding AptValue and HTree claims until the runner
confirms this batch is published, then release the scope and prerequisite RVA
claims (the split settles its moved RVA through the normal landed path).
