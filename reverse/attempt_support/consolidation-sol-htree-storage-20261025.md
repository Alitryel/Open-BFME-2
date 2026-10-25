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
