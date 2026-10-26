# surfaceclass split prerequisite refusal, 2026-10-26

Seat codexb5, allocated family B shard 1/2. No source or routing edits applied.
Destination Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.cpp was unheld in
the allocated runner queue. File claims for the destination and SurfaceByteSize
were acquired for this investigation and released after recording the refusal.

The scoped Code/Libraries/Source/ planner packet identifies SurfaceByteSize.cpp
as mixed/incomplete and surfaceclass_constructor.cpp as a whole donor. Original
surfaceclass placement is supported by planner evidence but only the current
in-memory TU map's approvals were passed to the trial. No map was committed.

Commands:

    python3 tools/tu_skeleton.py --plan Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.cpp
    python3 tools/tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.cpp --dry-run
    python3 tools/tu_skeleton.py --split Code/Libraries/Source/WWVegas/WW3D2/SurfaceByteSize.cpp
    python3 tools/tu_skeleton.py --split Code/Libraries/Source/WWVegas/WW3D2/SurfaceByteSize.cpp --for Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.cpp --dry-run
    python3 tools/find_declared_unmatched.py Code/Libraries/Source/WWVegas/WW3D2/SurfaceByteSize.cpp

Merge trial accepts the constructor and Common/BfmeOneHundredEightySix.cpp:
2 rows, no rejected whole donors. Leave these for their consolidation owner;
no new prerequisite on that whole-donor set was demonstrated.

Split inspection: eight SurfaceByteSize rows approved for surfaceclass.cpp,
one row with no approved TU. The dry-run can carve all eight approved rows
at 0x00116620, 0x00116680, 0x001166E0, 0x00116C30, 0x00116910, 0x00116990,
0x00116780 and 0x00116D10; refused_rows empty. However, residual_keeps=0 and
residual_loses=[0x00116560]. It refuses with 'the residual loses matched rows
(flag region or a shared helper)' and exits 2. The leftover 105-byte
Rva008FC4F0_PixelSize body is a static noinline helper used by the routed
surface callers; removing those callers prevents its emission. Its declaration
is not evidence approving a new TU assignment. Do not hand-move it, add an
emission anchor, or claim that a refused split made progress.

find_declared_unmatched: all definitions matched before the trial. The existing
MS-header queue finding (HRESULT local definition, drop-in windows.h candidate)
is preserved; no header acceptance or debt retirement was attempted. The
Common mixed donor is outside this seat's destination prefix and was not edited.

Recorded blocked evidence with tools/re_log.py on the helper row, t=5, current
BFME_MODEL. No banked C++ attempt exists because no reconstruction was authored.
Required next evidence: an approved placement for the residual helper or an
upstream supported split dependency solution that keeps every existing row.
The repeatable refusal is the boundary; do not repeat the unchanged trial.

Outgoing batch audit: no source paths changed in this attempt or the preceding
three prerequisite commits; no tools/hooks/workflows/build inputs/includes,
active registries or fold proofs require repointing. Preserve original EA paths.
File reduction 0, recovered C++ bytes 0, identity/data debt retired 0. Keep only
the handoff file claim until publication; destination and donor are released.
