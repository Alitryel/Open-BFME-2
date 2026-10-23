# Standing-water caller linkage, 2026-10-22

At ec344462c8, the 121-byte caller at 0x000834CE retained the old
`Rva0008304A::rva0008304A` placeholder callee. The provider has now landed as
`RenderableStandingWaterArea::AllocateAndFillBuffers` at 0x0008304A in W3DWater.cpp
(1156 bytes). The target REL32 and ledger row establish the binding; no owner
rename, pin, alternate name or layout change is introduced.

Before/after `python3 tools/link_check.py` with W3DWater.cpp and the caller as
explicit current objects: caller 0 -> 121 bytes linked. Provider remains 0 due
to existing duplicate Rva00082A53 constructor/rva00082E33 definitions, unchanged
by this repair. This is a legacy caller-level improvement, not closed-strict.
The published index predates the provider name: include its current object to
measure this binding. No provider source was edited or claimed.

`./build.sh Code/GameEngine/Source/Common/Rva000834CERva000834CE.cpp` passes 1/1;
`link_check.py --prepare-current` passes and writes a self-strict reusable
receipt. Receipt preparation does not assert LINK closure. Whole-Code search
found no other old rva0008304A callers to sweep.

Also triaged LineGroupClassRender.cpp: its sole Matrix4 Set_Transform helper
loses to retail. An imported forced-inline declaration changes Render SSE
ordering (1/7 rows fails), confirming the previously banked negative result in
reverse/attempt_support/dx8mesh-link-20261022/readme.md. Source restored and all
claims released. Do not repeat that emission-control trial.
