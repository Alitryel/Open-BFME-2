# canMake: failure selection and cleanup phase

Continue only `AIBuildableWallSegment::canMake`, RVA `0x00596e15`, 218 bytes.
No exact body landed in this continuation. The existing 204-byte bank stays
unchanged: instruction difference count 8, diagnostic fitness 0.913159. Its
digest and the actual starting revisions are in `receipt.json` (BFME2
`f23dc69293`, BFME1 `42bba2ddbd`). These scores are not acceptance checks.

Read the preceding `canmake-init-context-20261022/readme.md` first. Its
218-byte regional candidate already retains separate success destruction,
with the cost store before destruction and an exact suffix from +0xb9.
The bank, that regional candidate and this session's alternative all pass
the existing EH verifier exactly. None is a whole-body match.

## New regional finding: ESI is reachable without a new ABI

Starting with that 218-byte regional candidate, change only the funds failure:

```cpp
unsigned int money = player->m_money;
if (money < result.m_pad04)
    return (player->m_money < (unsigned int)result.m_pad04) ? 2 : 0;
```

The second comparison is true on this path. There is no intervening call or
store between the reads, and the explicit unsigned cast retains the original
comparison's conversion. This is an equivalent compiler experiment, not an
assertion about EA's spelling. Both quote/status failures now use ESI, as in
retail, while the separate success cleanup remains. The price is a remaining
`sbb esi,esi; and esi,2` on insufficient funds: five extra bytes. The failure
cleanup is still after the status/funds checks; retail places it immediately
after the first quote-failure branch. Moving that block remains necessary too.

This candidate is 223 bytes, instruction difference count 12, fitness
0.878807, with no unresolved relocations. Its relocation-masked body SHA256 is
`cee9ad3381596a8b9ccaf90853784474f08e8fba700151736cb48a163c332648`.
It is a regional alternative, not an improvement to the whole-body bank.
`regions.txt` compares all three candidates with retail from +0x83 onward.

Reproduce the small candidates from the repository root:

```sh
python3 reverse/attempt_support/canmake-failure-phase-20261022/replay.py.txt baseline
python3 reverse/attempt_support/canmake-failure-phase-20261022/replay.py.txt regional
python3 reverse/attempt_support/canmake-failure-phase-20261022/replay.py.txt esi
```

The saved replay reproduced all three sizes and masked hashes; their EH
results are recorded in `receipt.json`. It imports the earlier tracked
`canmake-00596e15-20261022/replay.py.txt`, reconstructs home-relative includes
from the unchanged bank, and uses private source/object paths in `build/`.
It does not write the shared production object cache. `--list` lists the
individual matrix replays. Recheck substitutions if the bank changes. An exact
diagnostic candidate would still need the normal identity and full-byte gates.

## Matrices and ruled-out explanations

There were 7,336 final source trials, zero compiler errors in the recorded
matrices, and zero exact candidates. Early generator declaration errors were
corrected before those runs. Some diagnostic controls change contracts or
contain unproven accesses; neither compilation nor a score validates them.
`receipt.json` counts unresolved relocations separately.

| Replay family | Trials | Finding |
| --- | ---: | --- |
| `duplicate_failure` | 512 | Eight predicates/shapes at quote, status and funds exits, both starting bodies. 34 distinct bodies; no ESI failure return. Some predicates read Player on quote failure without a proven nonnull precondition: diagnostic only. |
| `return_enum` | 256 | Enum ranges, casts, scope and Oa/Ow; two bodies, no ESI. This overlaps an earlier enum trial and adds no new conclusion. Every variant changes the base-call mangling and leaves it unresolved; no ABI or pin claim. |
| `return_alias` | 312 | Constant/reference/local return codes, declaration order and sites; two bodies, inert. |
| `dead_scope` | 352 | Provably false success branches containing nontrivial locals or opaque calls; 26 bodies, no ESI. Alias-sensitive repeated Player reads were not placed after the cache write. |
| `callee_context` | 48 | Actual qualified base fallback and GameLogic lookup bodies visible before/after the target, including noinline/diagnostic exception declarations; only the two starting bodies. |
| `raw_quote` | 192 | Placement construction in array/union storage, references/pointers/getters and RAII ownership; only the two starting bodies. Plain char storage is an alignment diagnostic, not a production proposal. |
| `late_value` | 544 | Known-zero memory/CSE return expressions and local types; 18 bodies. The two ESI controls mix unsigned locals with signed-to-double expressions and are not equivalent for negative costs: exclude them. |
| `shared_failure` | 1,024 | Re-entry into the first failure's duplicated assignment/return, including status/default/funds edges; six bodies, no ESI. Scalar declarations were moved so no initialization is bypassed. The shared-completion recipe did not close this residue. |
| `outer_return` | 512 | Quote and fallback share one outer result, eight shapes/types/scopes/polarities; four bodies, no improvement. Some 233-byte bodies use ESI. |
| `unreachable_failure` | 512 | Conditions proved at each failure site, alternate returns and four shapes; 54 bodies. Finds the valid 223-byte ESI candidate above. |
| `selected_failure` | 3,072 | Recombine twelve conditions, sixteen equivalent return forms, four temporary shapes, outer-test polarity and both starting bodies; 314 bodies. No exact candidate. The best separate-success ESI body remains the same 223 bytes; removing the redundant value calculation restores EBX or worsens the body. |

These cover control flow, variable lifetime/scope, boundary types/storage,
callee visibility and compiler context. They do not prove those broad axes
exhausted. Do not repeat these unchanged matrices. The diagnostic enum,
exception declarations and storage controls establish no new target contract.

## Read-only compiler observation

`merge_trace.py.txt` records the range-removal breakpoint at c2+0x9724c, gated
on this function using the existing c2+0x83acd context observation. It uses
VS2003 c2 build 3077. No compiler data or source instruction was patched.
The traced baseline and 218-byte regional objects reproduce their normal
masked hashes and both verify EH EXACT. `merge-observations.json` retains raw
tuple/operand words and relative callers, without unreliable name decoding
or debugger backtraces.

The baseline's four observed removals are called from c2+0x9f871. The regional
body's first two have that caller and its last two come from c2+0x513ef.
At removal, opcode-591 operands with immediate failure values 9/2 already
carry register record 0x108a9984; the emitted failures use EBX. Thus the
register choice is already present when the final tails are removed. This
does not identify the complete compiler phase or prove which earlier
transformation caused it. A late block-layout-only explanation is insufficient
for the register mismatch. Earlier register selection/coalescing and the
redundant funds-selection expression are the next concrete leads.

To retrace, pass an isolated candidate source and a fresh private object path:

```sh
python3 reverse/attempt_support/canmake-failure-phase-20261022/merge_trace.py.txt build/canmake-failure-phase-replay-20261022/regional.cpp build/canmake-failure-phase-replay-20261022/regional-traced.obj
```

## Target evidence and checks

Retail and the reread 619-byte WorldBuilder twin at `0x015386c0` continue to
support the existing identity, 24-byte quote, cost/status at +4/+0x10, owner
cache at +0x54 and Player funds at +0x94. The WB frame shows its five return
temporaries, quote, position and failed Boolean; it supplies no evidence for
new original locals. The visible fallback source is the existing target
`AIBuildableStructure.cpp` provider. The compiler trials establish codegen
effects only. No new layout, symbol pin or callee identity is asserted.

The initial pull was clean. `check_csv.py` passed (98064 functions, 15855
symbols, 2128 data); the production home reports all definitions matched;
`./build.sh AIBuildableWallSegment.cpp` passed both existing rows, including
source/string/float/import checks. The published link index was fetched.
Saved replay/tracer syntax checks passed. No maintainer-only runner was used.

BFME1 freshness was due, but another seat's live update lock named `claudec2`.
The runner rule requires skipping the update in this case; no success stamp
was written. The donor pointer was not edited. Production C++, the ledger,
pins and the best bank are unchanged. `progress.py origin/master` reports
C++ exact +0, game-code C++ +0 and linking +0. The unfinished target still
needs its failure cleanup ordering and register/value-selection residue solved;
no missing-function prerequisite is known. Resume this same assignment.
