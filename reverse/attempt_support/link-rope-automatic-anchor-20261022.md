# Rope duplicate provider repair, 2026-10-22

BFME 2 parent 256525b16a; published index 08160bc2c9 (2026-10-22 17:08).
BFME 1 remains at verified checkout 37c3022de1ab944c7ffe536440d637dc8199091c.
Donor link repairs reviewed through upstream 024afb28c, including the tracker,
ShareBuffer destructor, INIClass and MeshClass inline-provider fixes. This
repair applies the existing BFME 2 ProductionPrerequisite emission technique.
No donor layout is imported.

Drawable/W3DRopeDraw.cpp still defined ZH's obsolete buildSegments beside
Draw/W3DRopeDraw.cpp's retail-proven definition. Remove that unverified body
and its marker. Keep the independently matched SegInfo _Construct worker by
taking its function address within doDrawModule, where the nested private type
is accessible. The automatic const pointer adds no runtime operation. Earlier
failed work used a static pointer and emitted a guard; the bank at
rope-duplicate-link-20261021 remains the evidence for that distinct failure.

Paired current-source previews of exactly these three units, against the same
index, report:

| Unit suffix | Before | After |
| --- | ---: | ---: |
| Drawable/W3DRopeDraw.cpp | 0 | 0 |
| Drawable/Draw/W3DRopeDraw.cpp | 0 | 762 |
| Drawable/Draw/W3DRopeDrawInitRopeParms.cpp | 0 | 131 |
| Total linked nonpadding retail bytes | 0 | 893 |

These are legacy link previews, not a closed-strict or full-link measurement.
The edited unit has a strict reusable object receipt from --prepare-current;
all five rows, literal/float/import gates pass. Declaration and class gates
pass. The three-unit EH check reports two EXACT rows and zero debt. CSV passes.
Unchanged consumer/source objects are included explicitly in both previews.
Their RVA claims belong to another worker, so neither consumer was edited.

The edited donor unit itself retains DrawModule view/global-pool and drawable
accessor debt. No linked gain is claimed for it. Logs are
build/seat-rope-before.log, seat-rope-after.log, seat-rope-byte.log and
seat-rope-strict.log. No verifier, header, ledger, symbol pin or baseline changed.
