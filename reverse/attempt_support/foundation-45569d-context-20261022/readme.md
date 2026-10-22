# FoundationAIUpdate::construct, 0x0045569D (1174 bytes)

The faithful bank is unchanged at the function-source level: 1175 bytes, three structural regions, 31 memory operand differences (21 relocation sites), six register differences. No body was landed. The bank's stale comments and broken four-level relative includes were repaired; the repaired candidate emits identical main-body bytes and relocations to the starting bank.

## New finding: the exception graph is already exact

`eh_verify.verify_row(Image(), Obj(baseline.obj), symbol, 0x45569d)` returns `('EXACT', '')`, as does the repaired bank. All three unwind states, their actions, the two local-static initialization guards, and the Lua list at `[ebp-0x84]` agree. This is a verified EH result, **not** a main-body match. The native extent is still 0x45569D..0x455B33, ending in `ret 0x18`.

The unresolved choice is still the receiver web documented on October 21:

- Native +0x345 loads interface `this` from `[ebp-0x10]` into EDI for `onStructureCreated(getObject(), obj)`, retaining it through the rebuild/pathfind work and module lookups. **newMember** is EBX; the second lookup's **oldMember** result is EAX.
- The bank uses EAX at +0x345, reloads `this` into EBX at +0x3bf, and keeps newMember in EDI. The cost block then loads the player earlier; final self is EBX instead of EDI.
- IDs must copy under `newMember && oldMember`; cost must additionally require `!isRebuild`. WB 0x11715D0 confirms the nesting. Moving cost out of that guard, or looking up oldMember through obj, remains invalid even when it gives the desired allocation.

## Hypothesis and trials

Before editing, I read the served history and the October 19/20/21 handoffs. Those had already disproved ordinary equivalent guards, isolated declaration scans, direct field/getter spellings, visible findModule, local cost/player temporaries, and the usual compiler switches. This session tested interactions and missing source context: whether incomplete class views, a missing callee summary, or the last EH alias set prevents the +0x345 receiver from joining the later web.

The scripts preserve the exact generated families. Counts are **generated combinations**, not distinct compiled bodies or progress. There were 19,649 combinations, 144 compilation failures from duplicated goto labels, and no improvement. Most combinations optimized to exactly the same body. The scratch scorer's baseline is `(1175 bytes, 19 heuristic bad instructions, 3 regions)`; it masks relocation instructions and branch displacements, so it is only a search score.

| Family | Combinations | Evidence tested / result |
|---|---:|---|
| refweb | 225 | Object field const references, module references, reference-return getter and pointer-to-field at three declaration sites; baseline or 1174 bytes with worse scheduling/4 regions. |
| context / before | 128 / 384 | Visible matched cost/onStructureCreated bodies, real const getter overloads, ID mutators, math.h float overload, event hierarchy and player locals; definitions both before/after caller. All baseline. |
| merges | 768 | Twelve equivalent tail/return forms crossed with duplicated rebuild/pathfind branches and accessor contexts. 144 duplicate-label failures; valid variants baseline or much worse. |
| wrappers | 480 | Typed member/template/static findModule wrappers, receiver/key argument orders and four lookup sites. All baseline. |
| ehcontext | 256 | Snapshot/EventParameter hierarchy, 24-byte event elements with AsciiString, visible list/event constructors and destructors. All baseline. |
| tailapi | 512 | Cost wrapper, build-cost setter, charge/stat helpers, value/upgrades accessors, ID/getObject accessors. Baseline or outlined helpers with worse shape. |
| types | 4096 | Module/ObjectModule inheritance and boundary types, pointer constness, cost/withdraw signedness, typed Lua/stats/builder arguments. All baseline. Changed manglings were diagnostic only. |
| namescope / scopes | 1024 / 1152 | WB-inspired local spellings and declaration/block scope interactions, including early setup and orientation/member scopes. All baseline. |
| temporary-eh | 3072 | Empty temporary destructors, visible matched 44/66-byte bitset helpers, constructor/leaf nothrow contracts. All baseline. |
| complete-views | 1536 | Full 48-byte Matrix3D, actual WWMath matrix3d.h, polymorphic Thing/template/stats/AI prefixes, correct 12-byte Money layout and seven-word kind mask. All baseline. |
| home-context | 384 | Current home unit's complete secondary interfaces, extra Foundation fields/virtuals, five existing neighboring bodies before/after construct, Object-owned physical prefix, accessor contexts. All baseline. This was not a complete home-unit integration. |
| tail-exceptions | 4096 | All combinations of throw() on twelve post-Lua/helper declarations, including findModule, cost, money/stats, list destructor, model notifier, upgrade OR/update and final cleanup. All baseline. Diagnostic contracts, not established declarations. |
| inline-visibility | 1536 | Plain/inline/noinline matched cost/onCreation/pathfind/notifier/cleanup and 32-word OR bodies, before/after caller, getter/ID contexts. 1280 baseline; 256 inlined OR variants were worse (1196 bytes). |

This covers concrete trials of control flow, local lifetime/scope, types/layout, and callee visibility/exception contracts. Compiler settings were covered by the October 21 evidence and were not blindly rerun. No missing function prerequisite has been identified. No semantically wrong diagnostic was promoted to the bank.

## Inputs, verification, and replay

- BFME 2 input revision: `3e7fd99380fcf15f1a44d1780c71ecc38ba83679`.
- BFME 1 committed/checked-out revision: `37c3022de1ab944c7ffe536440d637dc8199091c`; freshness stamp was under 24 hours, so no reference pointer update was attempted.
- Compiler: repository MSVC 7.1 under Wine; `/O1 /G7 /arch:SSE /DNDEBUG /MD /GX`. Scratch compiles used unique objects via `build.compiler_command`, never `build.compile_source` or the shared production object path.
- Target evidence: native bytes and WB 0x11715D0 via `wb_show.py rva:0x45569D --gd --max-lines 1200`. Reference headers/providers supplied source-shape leads, not new target identity claims.
- `check_csv.py` passed at session start. `link_check.py --fetch-index` succeeded. `find_declared_unmatched.py` passed for FoundationAIUpdateSlots.cpp. `align_diff.py` reconfirmed the bank's residue; the repaired bank's body source, emitted bytes and relocations equal the starting bank. See `baseline-align.txt` and `bank-verification.txt`.

Copy the `*.py.txt` files to `build/foundation-oct22/` without the trailing `.txt`. Run the desired driver from the repository root (for example `python3 build/foundation-oct22/home_context.py`). `search.py` loads the current bank and fixes its includes for scratch use. It compiles at most eight variants concurrently, caches by source hash, and writes per-variant JSON and an aggregate. `results.json` here preserves distributions only; generated objects, full result arrays and duplicated candidate sources stay ignored under build/.

To recheck EH after compiling baseline:

```python
import sys
from pathlib import Path
sys.path.insert(0, 'tools')
import eh_verify
symbol = '?construct@FoundationAIUpdate@@UAEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@H_N@Z'
print(eh_verify.verify_row(eh_verify.Image(), eh_verify.Obj(Path('build/foundation-oct22/baseline.obj')), symbol, 0x45569d))
```

## Continue the same target

The current faithful bank remains the starting point, score 0.95. Do not repeat these inert families or the October 21 wrong-guard diagnostics. The remaining task is a faithful source form that joins the receiver webs. Complete real BFME1/ZH ObjectModule/BehaviorModule/Player header integration (rather than equivalent private views) and the full home-unit context remain broader untested avenues; this session only tested the specific prefixes/providers listed above. Keep the native guard nesting and use the normal full byte/relocation/identity gates for any winner.

Model: gpt-6.1-sol. Session duration recorded in the attempt log.
