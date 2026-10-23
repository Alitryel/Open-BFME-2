Notice display generated destructor, 2026-10-22
==============================================

Current object at published census08160bc2c9 links0/169 authored bytes.
Its sole blocker is selected ??_GIngameNoticeDisplay@@UAEPAXI@Z: the
unit flag /Oy- emits a31-byte EBP-framed copy while retail004E6231
and FamilyDeletingDtors_Rva004E61C8.cpp prove the complete28-byte body
without EBP. Remove the explicit flag. Both authored methods already need
EH frames; all6 ledger rows remain exact, including native-parent-resolved
funclets. EH2/2 EXACT; strict reusable receipt prepared.

After:169/169B legacy predicted linked, net+169B; no new C++ recovery.
The read-only deleting-dtor provider remains0/28B because its one-slot
vtable differs from the first owner; no closed-strict gain claimed.

Cause sweep: the other ranked /Oy- deleting-dtor emitters are DebugIONet
(known missing native seventh virtual slot), TerrainResourceModuleData
(private base destructor/vtable identity), FXParticleSystemTemplateWriteINI
(multiple independent STL blockers), and CallHelpOnDamageModuleData
(UpdateModuleData hierarchy). Their evidence does not support the same
flag-only repair, so no zero-gain speculative edits.

Local gate, EH, current legacy and strict-receipt logs: build/link-seat-20261022e/notice-*.
