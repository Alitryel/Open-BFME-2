# PointGroup UV helper link repair

Inputs: BFME2 7ad3d331552911e57fcb8d561a2be304cce399cf; committed BFME1 a80da2e3be84ebdb3b6bc280faca3f99a44788af. Model GPT-6, lane R, approximately four minutes on the selected unit.

The native 1,583-byte UV-fill helper at 0x0017D770 already matched. Its only blocker in the published 2026-10-21 18:42 census (d08db10acb) was the non-retail copy of `??_H@YGXPAXIHP6EPAX0@Z@Z` emitted by this unit's VectorClass helpers.

The existing SceneSpatialCollectBFME2/PointGroupClassRender pattern establishes the iterator's first use under size optimization in an unemitted static anchor. Applying that same pattern before this unit's headers preserves its UV body and makes its complete iterator copy match the 34-byte retail owner at 0x00001423. A COFF audit found no emitted anchor function, no unresolved iterator relocation and no extent overrun. No new pin, data owner, ABI or function-name claim.

Validation, serial with BUILD_POOL=1:

- Control `./build.sh Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRva0017D770.cpp`: 1/1 exact. `link_check.py` on that source: 0 bytes, sole non-retail iterator COMDAT.
- Same scoped build after the edit: 1/1 exact, string/float/import checks pass.
- `link_check.py --prepare-current` on this explicit source: normal byte gates pass using the same strict reusable receipt; census/index/status unchanged.
- `link_check.py` after strict preparation: LINKS, 0 -> 1,583 bytes against the same published index.
- Direct relocation-resolved comparison of this object's iterator with retail: all 34 bytes exact, no unresolved references; see helper-audit.json.
- `find_declared_unmatched.py`: all definitions accounted for.

This is a per-file link-check prediction against a frozen published index, not a newly run link_cycle measurement or a whole-tree closed-strict result. New matched coverage is zero. The published census was not rewritten.

Reference repair review: BFME1's corresponding PointGroupClassUVFill is the semantic donor but has a different 1,453-byte body and no iterator repair. The BFME2 sibling pattern is applicable; no BFME1 layout or byte result was imported. Review of the other 28 iterator-losing units found additional blockers in all of them; prior evidence records caller-byte regressions in several. This was the sole one-blocker unit, so no unrelated anchors were added.

The normal commit gates also reported shadow-only findings: two new optimization pragmas for the compiler helper and existing `_VertexUV` data identity/duplicate-name findings. The data definition and every UV reference are untouched by this repair. Those data findings remain a limitation for whole-image placement; the 1,583-byte figure above is only the link-check result. No admission baseline was expanded and no check was bypassed.
