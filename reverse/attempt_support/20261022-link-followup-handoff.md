LineGroupClassRender.cpp handoff
-------------------------------
Its sole current blocker is DX8Wrapper::Set_Transform(Matrix4)'s emitted
non-retail COMDAT; 4516 own bytes are held out. The other Get_Transform
codegen note is not a blocker under the current census rules.
Two trials kept 6/7 rows but failed Render (4371 bytes, RVA 0x1B38A0):
(1) dllimport forceinline (as matched siblings use) also inlines the final
view restore which retail calls out of line;
(2) a separate forceinline helper for the two initial identity transforms,
leaving the final row-name call external, changes frame 0x10C to 0x118 and
caller code. Original restored, 7/7 pass; claims released, attempt logged.
The compiler-visible summary and selective inline boundary remain unresolved.
Scratch trials and full logs: build/link-seat-20261022e/ (not durable).

Reference freshness prerequisite
--------------------------------
Official BFME1 master fetched: 4500af95a; verified checkout retained at
37c3022de1ab944c7ffe536440d637dc8199091c, clean. Reviewed intervening linking
changes: only census refresh among link/header/shim-labelled commits; no new
shared-header or linking repair was available to inherit. The paired old-input
full gate waited for the compiler without output and was interrupted; another
worker holds file:reference/open-bfme-1. No pointer or success stamp changed.
Freshness verification remains due; do not treat fetch as verified update.

RenderObj copy caller
--------------------
At08160bc2c9 the Rva001684D6 Copy/Ctor units fail solely on their inline
RenderObjClass destructor from bfme2renderobj/rendobj.h. The dtor unit also
has an independent Rva001683A7 destruction blocker. A TU-local imported
forceinline redeclaration after the header is rejected by MSVC7.1 C2761.
Original source restored, 2/2 rows pass; all claims released. A coherent
header visibility change is needed; no global include macro workaround.

Read-only queues
----------------
rehome_rows.py --limit12 tested103 candidate units and found three exact
home copies; all three source/home cohorts already link, so no gain.
name_globals.py --dry-run reports0files/0edits. Current-object checks of
45near-two-blocker units found7alreadyclean, including this seat's narrow
and wide scanner repairs; no upstream improvement is credited to this seat.
The published census is08160bc2c9 (2026-10-22 17:08).

Session close and integrated batch
---------------------------------
At dd5807dd58, upstream had independently isolated Pod900 and freed 2,174 B.
Rebased the earlier complete helper repair by rehoming its four rows to their
original unit and removing the temporary split unit. The 2,662 -> 2,838 B
three-unit current-object cohort proves only +176 B additional legacy gain;
the upstream isolation gain is excluded from our final total.

Seven pending repair commits now add 3,505 B relative to this upstream tree:
Pod900 176; StructureTopple 266; wide scanners 563; narrow scanners 1,181;
vector180 destruction 221; build-queue destruction 929; notice frame 169.
The last four are this session's new repairs (+2,500 B). All seven units
pass the integrated gate, 119/119 rows, and current-object link_check reports
7/7 clean (5,679 B in the units, including upstream's 2,174 B). These remain
legacy predictions; no self-strict or closed-strict gain is claimed.

progress.py origin/master after integration reports exact coverage unchanged,
with 46 B moving from authored to generated classification because the five
existing build-queue EH labels now have their proven gen-funclet parents.
Published linking counters remain unchanged until a fresh census measures the
tree. The unrelated read-only four-unit refresh was interrupted before it
returned predictions; it is not evidence that any queue is exhausted.

Narrow append's reopened visible-body trial is restored, logged and released;
resume only after the allocator ABI and deallocation visibility prerequisites
in 20261022-narrow-append-visible/readme.md change. Other unresolved work is
listed above. End this long session after publication/runner handoff at the
context limit; no unfinished source reconstruction remains in Code/.
