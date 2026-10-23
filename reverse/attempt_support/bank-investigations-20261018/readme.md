# Four bank investigation handoffs, 2026-10-18

These are failed reconstruction trials, not recovered functions. The existing
`reverse/attempts/*.cpp` banks are retained unchanged. No production source,
header, compiler profile, symbol pin or function-ledger change is proposed.
The shared verdicts are recorded with `tools/re_log.py` in `reverse/re_attempts.log`.

Inputs: BFME 2 `b1fa8ac4dd4475d713df9d632f90c4bb0140829e`, BFME 1
`64d369b90170b7e9ec917d646f020b11f13eb0d5`, local MSVC 13.10.3077.
`inputs.json` records source hashes and the selected artifacts. Boundaries below
are half-open native game.dat RVA ranges. Trial times exclude this handoff.
The model recorded during the trials was `gpt-6`.

## 0x006C26F0: allocator debug metrics, 934 bytes, 15 minutes

Boundary: `0x006C26F0..0x006C2A96`, RET 8. Bank:
`reverse/attempts/0x006c26f0.cpp`; home:
`Code/GameEngine/Source/Common/Rva006C1F60Finish.cpp`.

The newly rowed query at `0x006C2510` resolves the former missing callee. The
remaining instruction difference is native `sub eax,8` versus compiled
`add eax,-8` (see `metrics-baseline.diff`). Header-pointer subtraction, signed
and wider intermediates, and inline reference/output helpers do not close it.
A reference-owning size view removes the equal-arm ternary but still emits ADD;
`metrics-reference-view.patch` records that trial relative to the bank.

The existing bank still contains volatile argument-home forcing and compiler
barriers. It must not be landed as clean recovery on the strength of this
near match. A supported source explanation for both the native subtraction and
the argument home is still missing; repeating the listed arithmetic spellings
without new evidence is unlikely to help.

## 0x00032B00: allocator core allocation, 343 bytes, 12 minutes

Boundary: `0x00032B00..0x00032C57`. Bank:
`reverse/attempts/0x00032b00.cpp`; home:
`Code/GameEngine/Source/Common/System/Rva00031010Insert.cpp`.

The typed CoreBlock bank emits 341 bytes. Its prefix is exact through
`0x00032C0F`; native then copies EAX to EDX, ORs flags in EDX and copies back,
where the compiler ORs EAX directly and omits one MOV. Footer stores and POPs
also have a different schedule (`core-baseline.diff`).

Natural chunk/fencepost setters, helper return types, flag types, lifetime
boundaries, definition order and supported sibling settings did not fix it.
A two-chunk footer view changes only the epilogue schedule
(`core-footer.patch`, `core-footer.diff`). A bounded permutation run made 1,250
trials with no gain (`core-bounded-search.txt`); this is not a reason to rerun the
same search. The missing copy/lifetime constraint needs independent evidence.

## 0x002A9476: addNewAIForPlayer, 323 bytes, 10 minutes

Boundary: `0x002A9476..0x002A95B9`, RET 4. Bank:
`reverse/attempts/0x002a9476.cpp`; home:
`Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAIManager.cpp`.

The stale bank calls `Rva004E9823::rva004E9823`; the proven current provider is
`AIGameTeam::addPlayer(const ModuleData*)`, 137 bytes at `0x004E9823`.
Repairing the spelling in scratch resolves all calls. The earlier proposed
same-TU visibility lead is now tested: the actual 49-byte ally check at
`0x004E94CA` and that addPlayer body, separately and together, do not change
the caller's output (`skirmish-visible.patch`). This is a disproven lead for
these inputs, rather than an untried dependency fix.

The current manager's reconciled multiple-inheritance bases produce the same
bank output. Native and WorldBuilder evidence support an integer key; correcting
the table type and removing the equal-arm loop-end expression gives a cleaner
loop but allocates EBX to the vector base instead of Player, leaving an extra
stack home (`skirmish-owner-clean.patch`, `skirmish-owner-clean.diff`). Actual
Player index/side getters, raw vector ranges, typed iterators and WorldBuilder
loop forms do not close it. WB parent: `0x00E8E370`.

## 0x0028F326: vision-angle test, 294 bytes, 36 minutes

Boundary: `0x0028F326..0x0028F44C`, RET 8. Bank:
`reverse/attempts/0x0028f326.cpp`. WB parent `0x00CE75F0` and dot helper
`0x0041FB90` (`MathCoord3D.h:580..581`) independently support the vector math
and angle expression. See `vision-findings.json` and `vision-wb.txt`.

The unchanged bank emits 294 bytes with all calls resolved. Under
`tools.permute.fitness` its score is 0.9720859130168922, with five x87
operand/order differences (`vision-baseline.diff`). That metric differs from
the score in the historical bank comments; the numbers are not comparable.

`vision-planar-diagnostic.cpp.txt` adds the known-zero planar facing.z to the delta
operands. This diagnostic gets the x87 operations/operands right, but moves
three independent SSE theta instructions. Its fitness is lower,
0.9698081479782924, so it is neither an improvement nor a replacement bank.
It is preserved only to isolate operand folding from instruction scheduling.

New visibility observation: both GetLength and Normalize definitions must be
visible to retain this x87 caller shape. Hiding either produces SSE XY math and
a different extent. `vision-opaque.cpp.txt`/`vision-opaque.diff` preserve an opaque-provider
example. This is consistent with delta escape analysis, but the compiler's
internal cause is unproven. Reordering definitions, faithful normalization/body
spellings and authentic visible Sin/Cos bodies do not close the mismatch.

Precision/casts, canonical Coord3D views/operators, aggregate construction/copy,
scalar helpers, ABI alternatives, angle/comparison shapes, local lifetimes,
supported CPU/optimization/debug settings and scoped fence/read diagnostics
also failed. None of the synthetic diagnostic forms belongs in production.
A new source/visibility or compiler-scheduling explanation is needed.

## Reading and reproducing the artifacts

The `.patch` files transform the corresponding bank at the input revision into
one selected diagnostic; complete vision diagnostic sources are also included
as `.cpp.txt` evidence attachments, outside the compiled source tree.
Use a scratch worktree and keep trials under ignored `build/`. Their inherited
`partial score=` comments describe the old bank, not the selected diagnostic.
Compile settings are in each source's `// cl:` header. The recorded instruction
diffs are native versus compiled output from `tools.permute.Scorer`; absolute
addresses in relocation slots can be temporary masking values, not new pins.
They are diagnostic output, not full byte-verification receipts.

From the repository root, use the installed Python interpreter and the existing
scorer, for example (no new tool or profile is required):

```python
from pathlib import Path
import sys
sys.path.insert(0, str(Path('tools').resolve()))
from permute import Scorer
packet = Path('reverse/attempt_support/bank-investigations-20261018')
out = Path('build/recheck-vision-handoff').resolve()
out.mkdir(parents=True, exist_ok=True)
scorer = Scorer('0x0028F326', '?rva0028F326@Rva0028F326Owner@@QAEEIM@Z', 294, out)
print(scorer.score((packet / 'vision-planar-diagnostic.cpp.txt').read_text()))
print('unresolved:', scorer.unresolved)
```

The existing banks remain the starting points. Revisit these failures when
independent evidence changes their stated constraints, rather than repeating
the same trial families.
