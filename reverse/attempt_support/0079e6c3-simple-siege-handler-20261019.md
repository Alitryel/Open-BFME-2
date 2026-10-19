# AISimpleSiegeTactic initialization EH handler

Admitted through the normal `add_match.py` gate at input revision
`b5004c8a12c4928e8018849e8a8c40ed68bcbe67` (2026-10-19).
The native body at RVA `0x0079E6C3` is the complete ten-byte compiler-emitted
`__ehhandler$?initializeTeamTemplate@AISimpleSiegeTactic@@UAE_NPAVTeamPrototype@@H@Z`
from `Code/GameEngine/Source/Common/Rva005A9CB3Tactic.cpp`. No source, pin,
alias or verifier change is needed.

## Parent identity and ownership

The existing real parent is
`?initializeTeamTemplate@AISimpleSiegeTactic@@UAE_NPAVTeamPrototype@@H@Z`,
RVA `0x005A9F70`, 214 bytes through `RET 8` at `0x005AA043`.
Its existing identity evidence is WorldBuilder `0x0151A830`
(`AISimpleSiegeTactic.cpp:137`) and native slot 3 of vtable `0x00871E6C`.
This recovery inherits that established identity; exact bytes alone do not
establish an additional class or member layout.

The current parent reproduces all 214 native bytes with no unresolved REL32
or masked alias sites. Its native entry loads VA `0x00B9E6C3` and calls the
existing EH prologue at RVA `0x00629188`. The associative `.text$x` section
is placed at RVA `0x0079E6BB` by the parent's native relocation graph; the
actual handler symbol starts eight bytes into that section.

The handler loads FuncInfo RVA `0x00954BA4` (VA `0x00D54BA4`). Its complete
native EH graph is `EXACT`, without a baseline exception. FuncInfo has one
unwind state: state 0 returns to -1 through cleanup RVA `0x0079E6BB`, matching
the real local order-record lifetime in the parent. Ownership is proved by
the prologue, associative section and complete EH graph, rather than adjacency.

## Complete handler bytes and relocations

Raw COFF: `b800000000e900000000`.
Native: `b8a44bd500e9b5aae8ff`.
The object symbol's complete extent is ten bytes.

| Offset | Relocation | Object symbol | Native resolution |
| --- | --- | --- | --- |
| +1 | DIR32 | `$T1694` | FuncInfo VA `0x00D54BA4`, independently placed by the exact parent EH graph |
| +6 | REL32 | `___CxxFrameHandler` | Existing named target RVA `0x00629182` |

All ten bytes match after these two relocations; there are no unresolved sites
and no alias or library relocation masking.

## Inputs and verification

Source SHA256:
`9ff8abb3cf88cf93a1a898f1febe050c801b7805d086ed9fbacea5174f14dbe9`.
Current dependency-receipted object
`build/match/^code_^game^engine_^source_^common_^rva005^a9^c^b3^tactic.obj`
SHA256: `ac320c2083835d3a10945885b1ec92ef7282f34067034cd4a6b73e4412b0e00a`.
The repository MSVC 7.1 command uses
`-nologo -c -O2 -GR- -EHsc- -O1 -arch:SSE -G7 -MD -GX -DNDEBUG -Ireference/shims/bfme2_ascii`.

The authoritative body claim was acquired under
`VikoHofer-codex-eh-reference` before target verification. No live parent,
source-file or class-scope claim covered this source at the claim check.
Normal targeted verification passed every existing row of this source and
the independently checked Apt source (7/7 rows; nine string literals and one
float literal; no baseline exceptions). `explain_mismatch.py` for this actual
handler reported a ten-byte compiled symbol and an exact ten-byte match.
`eh_verify.py` for those sources reported `EXACT 3`, zero baselined failures.
Normal admission then passed this source's five matched rows, one float
literal and every scoped reference check; `add_match.py` recorded the landed
row and retained its claim until publication on origin/master.

Reproduce with the normal entry points:

```text
./build.sh Code/GameEngine/Source/Common/Rva005A9CB3Tactic.cpp
python3 tools/explain_mismatch.py '__ehhandler$?initializeTeamTemplate@AISimpleSiegeTactic@@UAE_NPAVTeamPrototype@@H@Z' --rva 0x0079E6C3 --size 10 --source Code/GameEngine/Source/Common/Rva005A9CB3Tactic.cpp
python3 tools/eh_verify.py Code/GameEngine/Source/Common/Rva005A9CB3Tactic.cpp
```
