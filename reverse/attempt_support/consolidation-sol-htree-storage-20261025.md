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
