# Line3D renderer full-view trial, 2026-10-26 (codexb)

Allocated family B shard 0/2; runner --check-tu authorizes
Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp. Current WW3D2 planner,
original-path alternatives and prerequisites were reviewed; currency passes.
The destination and renderer were claimed for this trial and released after
restoring the renderer. No production source, row, flag or register changes.

The ordinary merge dry-run still accepts the established seed, derived
destructor and endpoint-constructor subset: eleven rows in three files.
Renderer is rejected because its private Line3DClass lacks the Clone/copy
signatures implemented by the seed. Receipt:
build/sol-line-render-before-trial.txt. This is the existing prerequisite
boundary, not a lost-body regression.

A scratch full-view trial replaced the renderer's opaque RenderObjClass with
the seed's existing bfme2renderobj/rendobj.h view, agreed on W3DMPO ancestry
and added existing copy/assignment/Clone/Class_ID declarations. Before editing,
./build.sh verifies all nineteen seed+renderer rows. Four baseline objects,
source/object SHA256 and the original renderer are preserved under
build/sol-line-render-before* and build/sol-line-render-original.cpp.

The trial preserves twelve of fourteen renderer rows, including Render and
both Scale bodies. Both Reset overloads call the three-axis Scale via 0x170;
retail requires 0x16c (slot 91, table VA 0x00BD3FA8). Reordering the derived
Scale declarations does not fix an inherited slot. The shared header currently
declares three-axis Scale before scalar Scale; its comment describes retail
slot order without accounting for this compiler's overload-group ordering.
Do not infer that swapping a shared header is safe for its other consumers.
Receipts: build/sol-line-render-full-build.txt and
build/sol-line-render-after-build.txt. No shared-header edit was attempted.

The supported Obj/COMDAT reader also finds two helper-identity changes:
Get_Container becomes const and Invalidate_Cached_Bounding_Volumes becomes
protected const. There are no new undefined references; the other two
Reset bodies are the only changed providers besides these helper replacements.
The seed, endpoint constructor and destructor objects stay identical.
These replacements need explicit provider/consumer proof, in addition to a
consumer-scoped shared Scale ABI repair. Byte success alone would not suffice.
The reader is build/sol-line-render-provider-reader.py.

The original renderer was restored byte-for-byte and its frozen-file scan
passes (fourteen rows; three existing unclaimed definitions). The tool-written
blocked verdict at Reset RVA 0x00167B60 records this evidence. No nonmatching
attempt remains in Code; no helper/name/slot guess or hatch was added.
The existing eleven-row subset remains for Luna; this trial demonstrates no
new accepted donor. Mixed Common getters remain outside this seat's scope.

No source path changed. The complete pending range at this commit consists
only of this handoff and the attempt log; tools, hooks, workflows, includes,
build inputs and registries need no repointing. Existing debt and historical
EA paths remain intact. Files reduced, identity keys retired, recovered C++
bytes and linked bytes: all zero. Keep this evidence-file claim while its
commit is pending and release after publication is confirmed.
