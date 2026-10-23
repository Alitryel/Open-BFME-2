# canMake: early failure cleanup and shared insufficient-funds block

Continue only `AIBuildableWallSegment::canMake`, `0x00596e15`, retail 218 B.
This session improves the bank from 204 B / fitness 0.913159 / instruction
difference count 8 to **216 B / 0.945980 / count 6**. It is still nonmatching;
no ledger row or authored exact C++ bytes were added. Scores measure diagnostic
similarity, not byte verification or source identity.

Read `canmake-failure-phase-20261022/readme.md` for the preceding ESI finding.
Its 223-byte alternative reaches ESI but retains a redundant value calculation
and puts failure cleanup too late. Recombining that result led to a different
late-folding source shape that places cleanup correctly without that calculation.

## New bank and regional alternative

The improved bank's tail is equivalent to:

```cpp
if (failed) return 9;
if (result.m_20 == 7) return 2;
if (result.m_20 != 0) return 9;
unsigned int money = player->m_money;
if (money < (unsigned int)result.m_pad04) goto insufficient;
m_totalCost = result.m_pad04;
return 0;
insufficient:
do {
    if (!(player->m_money < (unsigned int)result.m_pad04)) break;
    return 2;
} while (0);
return 0;
```

The repeated unsigned comparison is true on entry to `insufficient`; no call
or store intervenes between the Player/cost reads. The unreachable return-zero
arm affects compiler phase ordering, then disappears from emitted code. This
is a semantics-preserving compiler experiment, not a claim about EA's spelling.
The emitted body has separate failure and success destructor calls, the failure
cleanup immediately after the quote-failure test, and the cost store before
the success destructor. The shared `push 2` block follows the funds comparison.

Remaining bank differences: failure cleanup returns through EBX rather than
ESI, and it tests status 7 before status 0. Retail tests 0 first, then has a
conditional jump to the shared `push 2` and an unconditional jump back to the
return-nine block. The bank omits that extra two-byte jump; its success cleanup
and epilogue are therefore two bytes earlier. Its relocation-masked SHA256 is
`21a3f8f3243cb7b71022d189657993f03de236d0f2c6ca0516628a7e138820c9`.

Keep the other regional winner too: retain the original switch and replace
only the funds failure with the same do/break/return-zero shape, leaving the
success path as fallthrough. This is also 216 B (fitness 0.929420, count 7),
hash `24cb4ff2cbbe3c1d3dc377e8267c34b78a28d91af8e6b59f35739ffe0e0af7e2`.
It preserves retail's first status-zero comparison, but places the shared
return-two block before funds loading. Both regional winners are reproduced
without copying a diagnostic source into `Code/`:

```sh
python3 reverse/attempt_support/canmake-early-cleanup-20261022/replay.py.txt early
python3 reverse/attempt_support/canmake-early-cleanup-20261022/replay.py.txt funds_after
```

`baseline`, `regional` and `esi` reproduce the earlier 204/218/223-byte controls.
All five replayed bodies pass the existing EH verifier **EXACT**, with no
unresolved main-body relocations. The portable bank was separately compiled
with its includes resolved relative to the production home; it reproduces the
funds-after hash. `regions.txt` gives both new tails and retail.

The original shared diagnostic scorer now freezes its old 204-byte input at
upstream commit `69526d2ae11afc4582e85371b0ff60dbd293e616`, where it is byte
identical to this session's starting bank. This keeps earlier replay scripts
usable after the bank update. All compilations use private `build/` objects;
none writes the production object cache through `build.compile_source`.

## Completed experiments: do not repeat unchanged

`replay.py.txt --list` lists the eight saved matrix families. There were 14,368
final source trials, zero compile errors, zero unresolved main-body relocations
and zero exact candidates. A generator NameError was corrected before the final
shared-ESI matrix; it is not counted as a completed compiler trial.

| Family | Trials | Result |
| --- | ---: | --- |
| `joint` | 2,592 | Six equivalent conditional return forms at all four failure sites, both old starting bodies. Combining single-site ESI selectors does not improve the bank. |
| `control` | 768 | Twenty-four branch/loop/reference/selection forms at four failure sites, four condition types, two starting bodies. Finds the first new 216-byte early-cleanup candidate. |
| `shared-esi` | 512 | Old ESI funds selector combined with shared return-nine edges, predicates, destinations and declaration orders. Best separate-success ESI body remains 223 B. |
| `recombine` | 3,456 | New early-cleanup funds form with eight status shapes and six return forms at each earlier failure, plus do/goto variants. No improvement. The WB nested status spelling also emits the same early-cleanup body here. |
| `return-weight` | 4,096 | New early-cleanup context, eight return/conditional-local forms at three failures, four alternate values and two funds-selection forms. Only the same 216 B or merged 204 B result; no ESI. |
| `funds-layout` | 1,024 | Eight funds-test/block layouts, eight status shapes, four failure forms and four quote returns. Finds the better 216-byte funds-after bank. |
| `status-integration` | 896 | Fourteen integrated status/success layouts, eight funds layouts, four failure forms, two quote returns. No improvement. |
| `shared-two` | 1,024 | Explicit shared return-two label with a predicate proved true on both status-7 and insufficient-funds entry, eight selection forms, four label orders, four status shapes. Does not combine the desired regions. The final bitwise-OR control reads Player on status failure and is diagnostic only. |

These are new interactions with the saved ESI and early-cleanup findings.
They do not supersede earlier negative results for types/layout, declaration
scope, actual inline Money accessors, destructor/base/lookup visibility or
compiler settings: those concrete trials remain in the preceding handoffs.
The WB twin was read again: original status logic is nested, quote size is
24 bytes, position temporary is 12 bytes, and failure is a byte local. Its
asserts establish Player/start-node preconditions, not a new layout contract.

## Read-only allocation evidence and next angle

`color_trace.py.txt` observes c2 3077 at context +0x83acd, round +0x82978,
pop +0x82a4d, assignment +0x831f7 and split +0xa8f54. It never writes compiler
state. `allocator-observations.json` preserves selected raw records; anonymous
record names and field semantics have not been independently decoded.

In the old ESI 223-byte candidate, after `this` the allocator pops anonymous
index 11 with allowed registers [4,7,8], raw word 3 = 36, word 9 = 8; it chooses
register 7 (ESI). The fixed EBX-zero record is popped next. In the early-cleanup
216-byte candidate, the corresponding later return-related index 10 is popped
in round 2, words 3/9 = 8/6, and chooses register 4 (EBX). The traced objects
reproduce their normal hashes and EH EXACT. This suggests an allocation-weight
or coalescing interaction worth isolating; it does not prove a mapping for
every anonymous record. The return-weight matrix above did not change it.

Next work should combine the early cleanup and shared-two block placement with
that register-lifetime evidence. Preserve both regional winners when testing
deeper source or inline-context changes. No missing callee is established as a
prerequisite; the remaining blocker is exact compiler register/branch shape.

## Inputs and checks

`receipt.json` records revisions, all candidate hashes/EH results and matrix
counts. BFME 1 remains at verified pointer `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
The due freshness update was deferred under the runner's live foreign lock
(`claudec2`); no success timestamp was written. No broad queues were swept:
the standing assignment overrides them.

`check_csv.py` passed (98,064 functions, 15,855 symbols, 2,128 data rows).
`find_declared_unmatched.py` reports all home-unit definitions matched, and
`./build.sh AIBuildableWallSegment.cpp` passes 2/2 existing bodies plus the
string/float/import checks. Published link-index fetch was current. No
maintainer-only verification runner was started. Claim is released after
banking; the next session must reclaim this same unfinished body.
