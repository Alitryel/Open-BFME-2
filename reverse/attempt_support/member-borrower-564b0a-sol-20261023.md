# Native member-reference borrower at 00564B0A

Inputs: BFME2 ac8df80501; MSVC 13.10.3077; the existing
GapBodiesSeat10O1.cpp compiler settings and verified callee pins.

## Target evidence and bounded interpretation

The complete eight-byte body is `83 c1 0c e9 97 5b f1 ff`:
add 0C to the receiver and tail-jump to the existing rowed receiver borrower
at 0047A6A9. The preceding native getter at 00564B06 ends with RET at
00564B09; the next row starts at 00564B12. No interior tail is claimed.

The existing Rva005045DBTree::self() provider in BfmeRectVNI_ctor.cpp
returns its receiver, with the complete MOV EAX,ECX; RET body. The new
ordinary C++ member method returns m_0c.self(), preserving the target call
relationship rather than treating the jump as a compiler adjustor.

The holder remains address-derived and opaque. Its original class, member
identity, and relationship to the adjacent Rva00564B12 holder are unproven.
The tree view is the existing provider's view, not a newly established
original retail type. No new pin, alias, dummy constructor, or assembly is used.

## Verification

- explain_mismatch: complete eight bytes exact, existing callee resolved.
- Normal add_match admission: entire source file 89/89 matches; supporting
  source, string, float and import gates passed.
- Scoped link_check preview: whole TU clean, 658 to 666 bytes, against the
  published 456ce161c5 retail-truth-4 census index. This is not a new census.
- place_bodies: zero additional bodies or pins; file drained to fixpoint.
- progress.py origin/master before publication: C++ exact +8 bytes and
  handwritten game C++ +8 bytes. The ArmySummaryEntry post-load override
  prerequisite closure contributes zero unique recovery bytes.

Publication race: upstream d3058cd9a5 landed the same body before this seat's
push. Rebase combined the independent definitions and rows; this seat removed
its duplicates, retaining upstream's implementation. The measured pre-race
+8 is therefore not an additional recovery over current origin/master.

The interrupted full old-input gate and reference-cache refresh are recorded
in river-vtordisp-30c4c6-sol-20261023.md; neither is claimed as a pass.
