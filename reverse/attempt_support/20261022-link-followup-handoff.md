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
