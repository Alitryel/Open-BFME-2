# canMake: a separate, exact success cleanup

Continue only `AIBuildableWallSegment::canMake`, retail RVA `0x00596e15`,
218 bytes including RET4; the next body starts at `0x00596eef`.
Identity, ABI, quote offsets and call slots remain the existing WB/retail
findings, not new deductions from these diagnostic sources. The starting
revisions and unchanged bank digest are in `receipt.json`.

The existing bank remains the better instruction-alignment candidate:
204 bytes, normalized instruction difference count 8, fitness 0.913159.
Its historical 0.886 header used a different measurement. No bank or
production source was overwritten merely to change that score.

## New regional result

`separated-success.patch` keeps the cost store **before** quote destruction
and produces 218 bytes. The normal funds test already proves the repeated
test false; both repeated-test arms have identical stores and return zero:

```cpp
unsigned int money = player->m_money;
if (money < result.m_pad04)
    return 2;
if (!(player->m_money >= (unsigned int)result.m_pad04)) {
    m_totalCost = result.m_pad04;
    return 0;
}
m_totalCost = result.m_pad04;
return 0;
```

There is no intervening call or store between the two money reads. This is
an equivalent source experiment, not a claim about EA's original spelling.
The compiler removes the repeated test, retaining a separate success exit.
All bytes before +0x84 and from +0xb9 through the end now equal retail:

```text
+0b9 or   dword ptr [ebp-4], -1
+0bd lea  ecx, [ebp-0x38]
+0c0 mov  dword ptr [esi+0x54], eax
+0c3 call 0x39205c
+0c8 xor  eax, eax
```

EH verification is EXACT. There are no unresolved relocations. This closes
the store-placement problem in the earlier 216-byte post-scope-cost probe:
the cost does not need a register across destruction. Remaining differences
are within +0x84..+0xb8: failure cleanup is placed after the funds test and
uses EBX; retail puts it immediately after the quote-failure branch and uses
ESI. The first difference is +0x84. The variant has 50 positional differing
bytes versus the bank's 85 when its missing 14 bytes are counted. Its
instruction fitness is lower, 0.900070, difference count 11; retain it as a
regional alternative rather than replacing the better full-body bank.

Reproduce just this candidate from the repository root:

```sh
python3 reverse/attempt_support/canmake-init-context-20261022/replay.py.txt winner
python3 reverse/attempt_support/canmake-init-context-20261022/replay.py.txt baseline
```

These commands rebuild home-relative includes from the unchanged bank and
write private sources/objects under `build/`. The replay resolves observed
relocations explicitly, including FS:[0], the EH stub and the actually called
destructor. Scores are diagnostic, never acceptance gates. `--list` lists
the families; dependent families regenerate their prerequisites. Review
the substitutions if the bank changes. The patch is for the bank's body,
not a production edit; its zero-context hunks require `git apply --unidiff-zero`.

## Trials not to repeat unchanged

All 4,136 matrix variants compiled after correcting two generator mistakes
(export attributes on declarations and a pointer's default-zero initializer).
One additional probe compiled the real ZH Money header. No exact body emerged.
The matrix factors were combined, rather than only tested individually.

| Family | Trials | Result |
| --- | ---: | --- |
| Quote initialization/copy/factory/aggregate context, scope, getters/setters, position temporary, status shape | 256 | 191..204 bytes; no better cleanup |
| Quote/cache ownership in bases, nested structs or arrays; flat and polymorphic Money views; inline access chains | 256 | 204 bytes |
| Nontrivial scalar return wrappers, conversions, copy constructors, success scope and empty guard | 272 | 204..254 bytes; no improved body |
| Constructor reset helper/default argument/initializer list, Oa/Op/Z7, noinline/export | 128 | All identical 204 bytes |
| Success cost store in an inline RAII destructor; references, pointers, values, bases, members, temporary lifetime | 128 | 204 bytes |
| Duplicate equivalent success branches with real predicates and optional duplicate failure exits | 256 | 204..232 bytes; some retain an unwanted predicate |
| Duplicate success branches with conditions proved by the successful path | 128 | Finds the 218-byte regional candidate; other forms 204 bytes |
| Failure values derived from their branch conditions, status/funds expressions and success scope | 512 | 204..208 bytes; changed quote Boolean materialization is worse |
| Regional candidate with eight status shapes, failure joins/helpers, predicate loads and declaration shifts | 1,024 | 202..218 bytes; no better failure exit |
| New 218-byte context: k=0..64 int/const-int locals at four declaration positions | 520 | All same 218 bytes |
| New context: six known-zero returns, real Money headers, getters, position temporary and visible actual destructor | 144 | 204 or 218 bytes; no better exit |
| New context plus the cost-store RAII guards | 256 | 204 or same 218 bytes |
| Equivalent 32/64-bit, double and alias-based predicates, const money reference, Oa/Ow, status shape | 256 | No better failure exit |

The real-header probe used donor Money.h, Snapshot.h, AsciiString.h and
BaseType.h (including its Coord3D), plus the actual VS2003 PlatformSDK.
`/showIncludes` confirmed those paths, and sizeof(Money)==12 was checked.
It emits the identical 204-byte baseline. This is a compiler-context trial,
not proof that the donor's full Player layout applies to BFME2. The Money
view remains at the previously established target +0x90 offset. No missing
header was silently replaced. Diagnostic attributes and compiler flags have
no asserted production contract.

Read-only WineDbg allocator observations are retained in
`allocator-observations.json`; the traced objects' main bytes and relocations
equal their ordinary compilations. Both runs select ESI for `this` and EBX
for the observed anonymous constant-related allocation. The trace does not
identify the anonymous nodes' full meaning or locate the pass that splits
or merges cleanup. Do not infer a proven cause from those observations.

## Checks and continuation

Pull/rebase, ledger validation, published-index fetch and the production
declared-definition check passed. The unchanged home passes
`./build.sh AIBuildableWallSegment.cpp`: 2/2 plus source, string, float and
import checks. Baseline and regional candidate both have EXACT EH data.
No rows, pins, headers, verifier code or production C++ changed. Progress
against origin/master is +0 C++ bytes.

BFME1 freshness was due. The current committed and checked-out pointer are
37c3022de1ab944c7ffe536440d637dc8199091c; the live update lock belonged to
claudec2. Per runner instructions this seat skipped the concurrent update
and wrote no success stamp.

All five reassessment angles have concrete evidence: control flow, local
lifetime, types/layout, callee visibility and compiler settings. The new
continuation is narrower: retain the exact success tail while moving the
failure cleanup to the first failure and allocating its value to ESI.
Ordinary declaration shifts and the listed recombinations are exhausted;
investigate the timing of common-load elimination and return merging, or
another supported source context, rather than repeating these matrices.
No missing-function prerequisite is known. Model gpt-6.1-sol, about 30 minutes.
