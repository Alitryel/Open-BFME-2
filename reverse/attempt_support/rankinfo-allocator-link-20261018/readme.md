# Rank parser allocator linkage, 2026-10-18

The unchanged 269-byte `RankInfoStore::friend_parseRankDefinition` at RVA
0x0020038E now links in a bounded local preview. It previously emitted allocator
DLL imports and a competing optimized placement-new body.

Use the existing game allocator shim and static STLport/CRT declarations, as
neighboring game-allocation units do. The shim is opt-in for this TU; no donor
pointer or shared header changes. The placement operations retain the CRT's
identity/no-op semantics inline, with dllimport preventing unused external
copies. This unit already disables C++ EH, so no placement cleanup import is
referenced. The five changed allocator helpers are listed in proof.json;
there are no added COMDATs. The optimized placement-new copy disappears.

Evidence separates existing donor identity from the repair: the parser's
BFME1 provenance, target offset claims and native boundary are unchanged.
The BFME2 byte gate proves its entire 269-byte body, all calls and two string
literals. The opt-in shim implements the target game allocation ABI documented
in reference/shims/bfmealloc/README.md. The current native parser emits the same
bytes with the repaired helper dependencies.

Acceptance:

- `./build.sh .../RankInfoParse.cpp`: self-strict 1/1, both literals verified.
- `link_check.py --prepare-current` on this source: strict-current receipt.
- `link_check.py --new-variants`: passes.
- `find_declared_unmatched.py`, `check_csv.py`: pass.
- `place_bodies.py`: zero new bodies or pins.
- Same published index c2c5ac8c27, 2026-10-18 11:36, paired local object
  substitution: before two unresolved allocator imports and one losing COMDAT;
  after zero blockers, 0 -> 269 linked bytes. The unused getLoadType copy is
  only a diagnostic under retail-truth-2, preserved without suppression.

This is a legacy/local prediction, not a closed-strict or full-link result.
The index and census status remain unchanged. Nearby RankInfoDtor already
links; RankInfoCtor retains independent Overridable/vtable/vector-assignment
blockers, so it is outside this cause sweep. The other ranked placement-new
consumers have multiple independent blockers; no zero-gain suppression landed.

Scratch reproduction: build/rankinfo-allocator-link-20261018/proof.py, original
source/object snapshots, byte/current/variants/link/siblings/placements logs.
