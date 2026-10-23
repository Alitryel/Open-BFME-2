# Recovery disposition

While recovery waited for the shared publication slot, upstream commit
fe5d4a4cdc landed a broader Vector3 repair (+951 B legacy local preview),
including layer.cpp. It forward-declares imported Vector3 before including
vector3.h, preserving the inline arithmetic without a conflicting COMDAT.
Recovery retains that current implementation instead of replaying the saved
link-view include. No additional 199-byte gain is credited to this recovery.
The original trial remains in refs/runner/preparation/1792331358981882686.

The independent earlier report follows as historical evidence.

# Layer Vector3 emitter repair

The existing BFME 2 Vector3 link view keeps the donor component assignments
inline without emitting a competing out-of-line constructor. Included before
layer.h; no class layout, compiler flags, pins, ledger or shared header changed.
The retained retail bodies are the same five GenericNode/Node bodies (199 B).

Before and after: `python3 tools/link_check.py
Code/Libraries/Source/WWVegas/WW3D2/layer.cpp`, index c2c5ac8c27,
2026-10-18 11:36: sole active constructor COMDAT finding -> LINKS, 0 -> 199 B.
This is the legacy same-index projection, with a strict-current receipt for
the edited source, not a closed-strict gain. `--refresh --current-ledger`
refuses 46 missing current-ledger objects (first Rva002A4A68); no census run.
`./build.sh` and `link_check.py --prepare-current` both pass all 5/5 rows,
with zero string, float or import references. Unclaimed-definition check passes.

Same-cause probes: ringobj, distlod and coltest also emit this constructor,
but have numerous independent blockers; no change made to those units.
W3DShrubBuffer remains deferred after its recorded two failed byte trials.

Donor linking precedents reviewed at fetched BFME 1 master
933ed3632ea9cefe401b53336118918f8c0f4db4: d003077f declaration-only
forwarding and 51b97cd79 helper suppression. This repair reuses BFME 2's
existing target-specific link header, without transplanting donor addresses.
BFME 1 checkout stays at committed 64d369b90170: the existing freshness
comparison is blocked on the incomplete old/new full gate (see preparation
recovery evidence); no successful freshness stamp or pointer advance claimed.
