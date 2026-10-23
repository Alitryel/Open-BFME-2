# Network debug factory and constructor frame repair

BFME2 parent 35861e85dc; published census 08160bc2c9 (2026-10-22 17:08).
The current DebugIONet_Create.cpp and DebugIONetConstructorThunk.cpp both fail legacy linking solely on DebugIOInterface's scalar deleting destructor. Its native 31-byte frameless owner is rowed at 0x0003F340 in Rva0088FAA0DebugIOInterfaceDestructor.cpp. These consumers compiled that base under /Oy-, producing a wrong copy.

Apply the established DebugIONetPipeDestructorThunk.cpp and DebugIOOds_Create.cpp compiler boundary: remove unit-wide /Oy- and place optimize(y, off) immediately before the derived class. The visible base compiles frameless; derived constructor/factory keep EBP. This is an evidence-backed compiler setting repair with unchanged class declarations, semantics, calling conventions, vtable contracts and row ranges. No new names, pins or aliases. BFME1 linking donor review remains at37c3022de1 (111671186/cae821575); this change is proven from BFME2 helpers and matched siblings.

Same frozen-index, current-object legacy previews:

| Unit | Before | After |
|---|---:|---:|
| DebugIONet_Create.cpp |0|106|
| DebugIONetConstructorThunk.cpp |0|70|
| Total |0|176|

The gain is176 legacy linked bytes. Self-strict receipts cover6/6 rows in these units plus the unchanged native base provider. Closed-strict link closure was not measured. Both parent rows, their generated funclets and handler retain exact retail bytes; EH2/2 EXACT, string/float/import gates pass. Class and declared-definition checks pass, enforced converged data check finds0 duplicate names, and new-variants passes. No full link/census/boot runner started. C++ coverage does not grow.

Diagnostics: build/link-seat-debug-before.txt, after.txt, trial.txt and receipts.txt. The attempted unrelated narrow-cstr ownership sweep is banked separately in narrow-cstr-extern-link-20261022.md; all five source trials were reverted and byte-verified before continuing.
