# 0x000BD6C2 W3DScriptedModelDraw event update: visible STLport erase (2026-10-20, seat w1, second run)

## Result

Banked partial `reverse/attempts/0x000bd6c2.cpp` (symbol `?rva000BD6C2@W3DScriptedModelDraw@@QAEXXZ`, 894 B). It closes the final-loop esp-save residue and is closer than the strong-ctor bank by one memory difference, with no class getting worse:

| body | size | structural regions | memory | register |
|---|---|---|---|---|
| strong-ctor bank (before) | 903 B | 2 | 10 | 1 |
| this bank | 903 B | 2 | 9 | 1 |

One of the nine memory lines is the `TheParticleSystemManager` load (`[0xdfdd04]` against an unresolved `[0]` in the scratch object), which the gate fills. The other eight, the one register line and both structural regions are the destroy-loop role swap described below.

## What changed and why

1. **`_STL::list<BfmeStringRecord000B757D>::erase` (0x000BC133, 42 B) is defined in the unit** as a `__declspec(noinline) inline` copy. Retail's unit saw this body because it is a header template, and retail places the instantiation at 0x000BC133 among this unit's other list instantiations (the list copy at 0x000BC0DB). With the body visible, the final defaults-FX loop saves esp at `[ebp-0x24]`, sharing the slot of erase's return temporary as retail does. A diagnostic without the erase call moves that store to `[ebp-0x1c]`, which shows the slot choice is tied to erase's temporaries.
   - The copy compiles to retail's 42 bytes exactly (`align_diff`: 0 memory, 0 register, 0 structural; 2 relocations). Its call to the record destructor resolves through the rowed `??1BfmeStringRecord000B757D@@QAE@XZ` (0x00577998).
   - Both definitions are select-any: the home `Code/Libraries/Source/WWVegas/WWLib/stlport_list_b757d_insert.cpp` (explicit instantiation) and this unit's copy each emit erase as a COMDAT with selection 2 (checked on the compiled objects), so the copy cannot collide in the link.
2. **WorldBuilder twin's locals (WB 0x945CC0).** The create loop reads `*it` twice and has no nugget local; the destroy loop assigns the nugget (WB `local_80`) after the type test. Byte-identical to the previous spelling, kept because it is the twin's shape.

## Remaining mismatch (unchanged)

Destroy loop roles: retail keeps the list node in EDI and the nugget (then the hoisted particle ID) in EBX; ours has the node in EBX and the nugget in EDI. Because the node takes EBX before the loop, the events-iterator reload lands after the destroy list's destructor and that tail is not shared with the create list's (+12 B against retail's 3-byte reload, +9 B in total).

## New measurements on the roles (on the visible-erase base; byte-identical or equal counts unless noted)

- Find loop replaced by one test, so no hoisted particle ID exists: roles unchanged. The rival of the node is the nugget itself whenever its range spans the particle-system calls; the hoisted particle ID only inherits the nugget's register.
- One extra node use in the nugget loop: no flip, so erase visibility did not narrow the gap. Probe uses of the events iterator inside the destroy loop, or of the nugget after the find loop: no flip.
- Visible non-leaking list copy constructor and `_List_base` destructor (diagnostic bodies): identical.
- Strong in-unit `Rva000B9887Init` (0x000B9887) and `Rva000B9A0E::rva000B9A0E` (0x000B9A0E), copied from their units and compiling to their exact sizes: identical.
- The home unit's exact 171 B `rva000BB3E6` in place of the bank's 167 B copy: identical for 0x000BD6C2.
- Declaration order (particle-system views before the list views, erase defined after the class, `Make001FCBD7` declared before the handle): identical.
- `9 == type`, a plain `inline` handle destructor, the nugget bound as a `const` reference: identical. `event.end <= frame`: worse (3 regions).
- WorldBuilder's seven separate FX calls instead of the `fire` flag: roles unchanged, and the shared call site's `mov ecx,esp` and esp save swap order (2 register lines worse).
- Branch-frequency diagnostics (events-empty guard removed; create condition reduced to `frame == event.start`): roles unchanged.
- `tools/permute.py` on the previous bank: 1685 trials, no gain.

## Landing prerequisite (unchanged from the strong-ctor handoff)

The exact body needs the 0x000B6D26 ctor as a strong definition in the same unit, so 0x000C48DB and its ctor have to move into `W3DScriptedModelDrawEventUpdate.cpp` (or the reverse); see `reverse/attempt_support/0x000bd6c2_20261020_strong_ctor.md`. A landing also carries this erase copy, which is safe beside its select-any home.

## Inputs

Unit flags as the home unit: `/O1 /G7 /arch:SSE /EHsc /MD` with `/Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib`. Measured with `tools/align_diff.py` on fresh objects.
