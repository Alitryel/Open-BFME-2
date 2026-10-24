# Existing STLport POD helper providers, 2026-10-24

Eight existing rows (907 B of row extents, including the existing ICF twin) moved from `stlport_pod_noexc_bodies.cpp` to six existing providers that already compile their complete retail-exact bodies. No C++ source, identity, layout claim, pin or compiler flag changed. Existing provisional element names and donor provenance remain as recorded in source and ledger.

Paired `link_check.py --refresh --paths-from build/link-pod-rehome-paths.txt` at the same tree/index: 10,692 -> 11,599 available matched bytes, **+907 B legacy linked availability**, six of seven units linked both before and after. The frozen index is 11b3872700 (2026-10-23 23:06); its 10,671 baseline is not the before measurement. The inherited 21 B difference is excluded. No self-strict, closed-strict or unique authored-byte increase is asserted.

Preflight: each receiving object reproduces every complete body byte and relocation with no unresolved relocation or wrong allowed-symbol finding. Preserve the existing ICF owner at 0x421DC8. Scoped byte gate: 241/241; EH 12/12 exact; frozen-source checks and check_csv pass. Code-identity shadow findings remain the same eight (see paired logs). Rejected ninth row, _Destroy deque<BfmePod16> at 0x54FEC8: receiving 41B copy has a wrong/unknown __destroy target at +0x1F (0x54FE7A). Recorded blocked and released its claim; no source/row change for it.

The no-exception source still does not link: POD28 allocate/copy, constructor and fill, POD32 constructor and selected POD44 overflow remain separate existing blockers. The rejected destructor and those blockers are not repaired by this ownership change.

Acceptance commands: ./build.sh on all seven paths in before/after logs; tools/link_check.py --refresh on those paths before and after; tools/eh_verify.py --sources-from; code_identity_gate.check (unchanged findings); tools/find_declared_unmatched.py for each unit; tools/check_csv.py; git diff --check. Donor linking scan at reference f5140c1cff6a58e16276fd6de6788186286953d4 remains unchanged; this uses BFME2's already-verified providers.
