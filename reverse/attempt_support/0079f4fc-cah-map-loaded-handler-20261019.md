# AptCreateAHero OnMapLoaded EH handler

Proof input revision: `b5004c8a12c4928e8018849e8a8c40ed68bcbe67`.
Admitted through normal `add_match.py` after `cd45f84993` on 2026-10-19;
source inputs are unchanged.
RVA `0x0079F4FC` is the complete ten-byte compiler-emitted
`__ehhandler$?OnMapLoaded@Class@AptCreateAHero@@QAEXXZ` from
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptCreateAHeroClassConstructor.cpp`.
No source, pin, alias or verifier change is needed.

## Native parent and EH ownership

The existing real parent
`?OnMapLoaded@Class@AptCreateAHero@@QAEXXZ` occupies RVA
`0x005B59FD..0x005B5AAF` (178 bytes, final `RET` at `0x005B5AAE`).
Its established identity comes from WorldBuilder `0x0157BFF0` and the native
Exit and OnMapClick command bindings. This handler recovery inherits that
identity and introduces no additional target layout claims.

The whole 178-byte parent reproduces native bytes with no unresolved REL32
or alias masking. The entry loads VA `0x00B9F4FC` and calls the existing
EH prologue at RVA `0x00629188`. Its native relocation graph places the
associative `.text$x` section at `0x0079F4EC`, and the actual handler symbol
starts 16 bytes into that section.

The complete parent EH graph is `EXACT`, without a baseline exception.
The handler loads FuncInfo RVA `0x009560FC` (VA `0x00D560FC`); its unwind
map at RVA `0x009560EC` has states 0 and 1, both unwinding to -1 through
cleanup RVAs `0x0079F4EC` and `0x0079F4F4` respectively. These are the real
temporary string lifetimes around the two command registrations. The native
prologue, associative section and full EH graph establish ownership.

## Complete body and relocations

Raw COFF: `b800000000e900000000`.
Native: `b8fc60d500e97c9ce8ff`.
The actual object symbol's complete extent is ten bytes.

| Offset | Relocation | Object symbol | Native resolution |
| --- | --- | --- | --- |
| +1 | DIR32 | `$T1854` | FuncInfo VA `0x00D560FC`, independently placed by the exact parent EH graph |
| +6 | REL32 | `___CxxFrameHandler` | Existing named target RVA `0x00629182` |

All ten bytes match after both relocations, with no unresolved sites or
alias/library masking.

## Inputs and normal checks

Source SHA256:
`4b992c73a655add756ff78f5ba217956b94927d450db75e55bba7a2c57c40291`.
Current dependency-receipted object
`build/match/^code_^game^engine_^source_^game^client_^g^u^i_^g^u^i^callbacks_^apt_^apt^create^a^hero^class^constructor.obj`
SHA256: `632c2eb90d06b8e9ac32cc21c228a8254826ee4efff56876d0db563cd48fcc4a`.
Repository MSVC 7.1 flags:
`-nologo -c -O2 -GR- -EHsc- -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc`.

The native handler claim was acquired under `VikoHofer-codex-eh-reference`
before target verification; no live parent, source-file or class-scope claim
covered this source. The normal targeted build passed all existing rows of
this and the separately checked SimpleSiege source (7/7, nine string literals,
one float literal). `explain_mismatch.py` reports a complete ten-byte exact
match, and `eh_verify.py` for those sources reports `EXACT 3` with no baseline
exceptions.
Normal admission then passed this source's four matched rows, nine string
literals and every scoped reference check; `add_match.py` recorded the landed
row and retained its claim until publication on origin/master.

```text
./build.sh Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptCreateAHeroClassConstructor.cpp
python3 tools/explain_mismatch.py '__ehhandler$?OnMapLoaded@Class@AptCreateAHero@@QAEXXZ' --rva 0x0079F4FC --size 10 --source Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptCreateAHeroClassConstructor.cpp
python3 tools/eh_verify.py Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptCreateAHeroClassConstructor.cpp
```
