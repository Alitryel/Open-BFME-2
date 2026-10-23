# 0x0043003C SelectionTranslator::translateGameMessage, /EHs round (2026-10-19)

Base: banked `reverse/attempts/0x0043003c.cpp` (score 0.9). The new bank differs from it only in the active
`// cl:` line: `/EHsc` -> `/EHs`.

## New evidence

- Under `/EHs`, the `hash_map<int,bool>`/`hashtable<pair<int const,bool>>` destructor the unit emits is now
  57 B and byte-identical to retail 0x42FD1C, including the `or [ebp-4],-1` state store before the
  extern "C" free. Under /EHsc cl drops that store. The parent is unchanged by the switch: 4 structural
  regions, -6 B. The earlier note "broad exception-mode change did not fix the dtor" referred to other
  modes; /EHs specifically does.

## Remaining residue (register allocation only)

1. retail +0x439..0x453 (containedBy/template): retail loads containedBy into EAX and the template into
   ECX, then `mov esi,eax; mov ecx,esi; call getDrawable`. Ours swaps EAX and ECX and emits `mov esi,ecx`,
   2 B short.
2. Select-team case (t-62), retail +0xc62/+0xc6a/+0xcf9: retail reloads `group` ([ebp-0x10]) per arm
   (EAX after the FPS compare in the double-tap arm, ESI at cf9 after deselectAll in the else arm). Ours
   hoists `mov esi,[ebp-0x10]` above the FPS compare and keeps it in ESI across both arms, and then uses
   EAX instead of ECX for ThePlayerList.

## Disproven this round (no change: 4 regions, -6 B)

- An inline member for the 0x10E template test (NativeTmplFlags43003C::testByte).
- `draw = containedBy->getDrawable(); obj = containedBy;`: worse, 5 regions.
- Passing group by const& to an empty inline helper; taking group's address.
- A `Bool doubleTap = ...; if (doubleTap)` local.
- Comparing as `m_lastGroupSelGroup == group`.
- One function-scope `Int group;` shared by cases 52/62/72/82 (assigned per case): still 4 regions,
  memory-operand diffs grow 106 -> 123. The per-case block locals stay.

## Landing prerequisites (unchanged from the w8/compact handoffs)

- The parent belongs in `Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp`
  (it already holds the exact areAllSelected row, which must stay exact under /EHs).
- Owner renames or fold-proof pins for the callees: deselectAll 0x42F9DA (owner row
  `?Rva0042F9DAEmit@ScriptActions@@QAEXXZ`), hash_map ctor 0x43001D, operator[] 0x42FE40, dtor 0x42FD1C
  (gen-alias `?dup_0042fd1c@@YAXXZ`), `_M_find` 0x2888D4.
