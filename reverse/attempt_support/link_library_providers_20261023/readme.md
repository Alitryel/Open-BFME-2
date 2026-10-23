# BFME 1 freshness and existing-provider link repairs

The freshness comparison keeps BFME 2 at 24aa52a328 and changes only the
reference pointer from 96c88c73a5cd1a58fc2f8db691beea50acd996db to official
master f5140c1cff6a58e16276fd6de6788186286953d4, fetched 2026-10-23. The donor
checkout was clean. The old pointer is preserved at refs/bfme2-verified/96c88c73.

Old full gate: 98,188 function rows and 2,173 data rows, every check green.
New full gate: 98,188 function rows and 2,173 data rows, every check green. All 23,418 TU dependency caches were current.
Both complete EH verdict sets are identical: 11,894 rows, 11,870 exact and
24 pre-existing baselined findings; zero missing objects. The JSON SHA256 is
3e72167eae1f6ba1ea61f24a7dc0e99d6a418214739cd79a4a4c47a8ee3664d1.

The donor diff changes nine game source files and no headers, inputs, flags
or layout. None changes the WW3D math/StringClass or STLport helper families
used here. The existing layout resolver needs no repair: six resolved roots,
97 explicit include directories and the actual vector/matrix/STLport headers
exist. This does not assume that successful compilation proves header choice.

Fresh BFME 1 scan: 38,787 donors, ranked/near zero; lift lane 146 named bodies,
103 servable. ZH cache was absent and was rebuilt: 918 objects, 68 discovery compile
failures out of 986 TUs. The 68 failures equal the documented prior count;
the update changes no ZH input or sweep code. Matching scanned 26,995 functions and packets were zero, rerun
from the populated cache (not inferred from the initial empty-cache result).

The repair moves existing rows to already-emitted exact copies in providers
which currently link. No body, declaration, symbol, ABI, name, pin or alias is
introduced. Original provenance/alias notes are retained. The StringClass
Resize parent and its existing EH handler move together. Each current object
was checked with compile_function: all 19 complete bodies and relocations
match, with no unresolved relocations. Target-byte proof and existing type
identity support the move; it establishes no new donor identity or layout.

Scoped legacy link_check preview against b711de3634 (retail-truth-4):
before 33,454 B, after 35,304 B: +1,850 linked bytes.
The 19 rows cover 1,975 bytes; two existing gen-alias rows (61 and 64 bytes)
are excluded from the authored-byte metric. This is not a self-strict, closed-strict or
full-link measurement. Index SHA256:
1707d876c79d52c4e34a88342706796110595063d75abb3d5ed81bd080c08ad7.

Before code-identity shadow check: nine existing findings over 289 rows,
including the two old Pod28 wrong-call bindings and seven divergent helper
copies. After check: the same nine findings, no growth; no shadow baseline is edited.

Receiving-object EH preflight is exact for both moved EH parents: StringClass
Resize (first batch) and basic_stringbuf constructor (follow-up batch).
Reviewed 13 same-named donor helper rows: their owners and several bodies differ,
so BFME 2 current-object byte and relocation proof controls these moves.

Acceptance: all 289 rows across eight touched units pass the full-byte gate;
23/23 source EH graphs are exact; find_declared_unmatched passes all eight
units, check_csv and git diff --check pass. The link preview exits 1 because
three original owners remain blocked; the same five receivers link before
and after. Those existing blockers are preserved in before.txt/after.txt.
No new authored C++ bytes, self-strict or closed-strict gain is claimed.

Moved rows (RVA, extent, old owner -> receiving owner):

- 0x0011FA40, 122 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00121230, 126 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00122010, 112 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00121E70, 355 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00121450, 105 B, mesh.cpp -> dx8wrapper.cpp
- 0x001220B0, 81 B, mesh.cpp -> dx8wrapper.cpp
- 0x0011F710, 31 B, mixfile.cpp -> dx8wrapper.cpp
- 0x001493F0, 178 B, mesh.cpp -> MeshClassCollision.cpp
- 0x00149310, 157 B, mesh.cpp -> MeshClassCollision.cpp
- 0x00102559, 146 B, mesh.cpp -> W3DCamTransform.cpp
- 0x001212B0, 61 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00121DE0, 64 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00122080, 47 B, mixfile.cpp -> dx8wrapper.cpp
- 0x00419ED4, 156 B, stlport_pod_noexc_bodies.cpp -> stlport_deque_pod16_base.cpp
- 0x00419E3D, 151 B, stlport_pod_noexc_bodies.cpp -> stlport_deque_pod28_base.cpp
- 0x00419DB1, 33 B, stlport_pod_noexc_bodies.cpp -> stlport_deque_pod28_base.cpp
- 0x0041A1A2, 20 B, stlport_pod_noexc_bodies.cpp -> stlport_deque_pod28_base.cpp
- 0x0041A1B6, 20 B, stlport_pod_noexc_bodies.cpp -> stlport_deque_pod16_base.cpp
- 0x0076546C, 10 B, mixfile.cpp -> dx8wrapper.cpp
