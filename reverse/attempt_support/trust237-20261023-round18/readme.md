# 0x237D3D: recovered-status switch and result-copy controls

Assignment remains `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, **226 B**.
Continue from [round17](../trust237-20261023-round17/readme.md), which recovered
the two comparisons independently and documents the input provenance limits.
BFME2 input `e63565fff3ea8fcc76faa4bee0d83e2cdbc791de`; BFME1 committed and
checked out at verified `f36a4db066aa61edeee90085a31d628eb829001d`.
The 02:02 UTC successful freshness check is under 24 hours old. The completed
update's old lock belonged to this same seat; its pointer is on origin/master,
so the lock was removed. Unrelated untracked `reverse/zh_sweep/` is preserved.

## Hypotheses and finite results

The scoped history was read with `pick-hard --rva 0x237D3D`. Earlier sessions
already tested control flow, lifetime/scope, layout/types, callee visibility,
compiler versions/settings, return carriers, loops and actual padding emitters.
Do not repeat those matrices, the patch-provenance search, or the two-status
direct-return switch from round17. No missing game callee is identified.

This round asks whether **switch result updates with earlier declarations**
or **explicit success/default copy preferences** reproduce the recovered
pre-patch tail. The latter is informed by the recent unreachable-copy recipe
for 0x596E15; applying that recipe here is only a hypothesis, not shared-cause
proof. Both families use the independently recovered error order and constants.

| Family | Choices | Final valid objects | Raw bodies | Decoded NOPs |
| --- | --- | ---: | ---: | ---: |
| switch-results | Eight result-update/label forms; four result types; four declaration positions; G6/G7; signed/unsigned status; throwing/nothrow cleanup | 1024 | 9 | 0 |
| success-cases | Eight explicit success/default or duplicated-cleanup arrangements; four result types; sixteen optimization/alias/inlining flag combinations | 512 | 127 | 0 |

Neither matches the independent unpatched body, and neither supplies a NOP
producer. The first family's best is 230 B, prefix203, 26 differing bytes;
the second's best is 230 B, prefix194, 36 differences. These are controls
that return **zero for 0x80096010 and 0x800B0100**, so they cannot replace
the always-one bank even if their original-byte comparison improves.

The first success-family scoring pass exposed a real same-unit cleanup call
under /Ob0. The corrected scorer reads that helper from the same object and
assigns an explicit scratch placement; the emulator executes its actual body.
It never invents a retail identity for the helper. A separate template bug
replaced the A in releaseArgs; its 256 C3861 failures were corrected with
word-boundary substitution and retried, retaining the 256 valid objects.
Those setup failures are not source/codegen counterexamples. Counts above
refer to the final complete, independently audited matrices.

## Checks and retained bank

The independent audit rereads all 1536 source/object pairs and checks their
hashes, full instruction decoding, relocations, lengths and differing offsets.
It verifies all 64 emitted cleanup-helper instances against their own objects.
The 136 code/relocation/helper/expected-result groups pass **77,248 emulated
executions**: 142 status values, including the exact errors and neighbors,
four argc/cleanup-return combinations, API arguments/order/count, GUID,
file16/data44 contents, stack and callee-saved registers. External APIs clobber
caller-saved registers and flags. The retained bank always returns one; the
diagnostic controls implement the recovered original predicate.

Independent `tools/variant.py` compilation still reproduces the best bank:
**226 B**, prefix205, **exactly 16 differences at +CD..DC**, score **70/86**
(bank header 0.813953), raw SHA256
`ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`.
The audit checks its actual IAT names and direct-call thunks. The bank is
preserved without source changes and remains a partial, never a landing.

* `python3 tools/check_csv.py`: OK, 98098 functions / 15853 symbols / 2139 data rows.
* `./build.sh Code/GameEngine/Source/Common/VersionDestructor.cpp Code/GameEngine/Source/Common/VersionInitGlobals.cpp`: **39/39** functions, two source claims, one data row, 21 literals plus two empty-string references, four named imports pass.
* `link_check.py --fetch-index`: current published index retained; matching published objects fetched.
* Both units' link prediction: VersionDestructor **LINKS, 1275 B**; VersionInitGlobals' **200 B** still withheld by unresolved `Rva00237D3DCheck`. Combined command exits1 for that known blocker. No new link improvement is claimed.
* Audit, syntax, JSON and diff checks pass. `progress.py origin/master`: **+0 authored C++ bytes**, +0 linking bytes.

The standing assignment's old VersionDestructor link-blocker description is
stale; the predictor result above agrees with round17. No maintainer-only
verification runner was started. No Code, ledger, baseline, pin or verifier
change was made.

## Reproduction and handoff

Retain round17's pinned independent image and original_check.py under its
documented ignored scratch path. Copy these three Python text files without
`.txt` to build/trust237-round18. Then:

```sh
python3 build/trust237-round18/switch_results.py
python3 build/trust237-round18/success_cases.py
cp reverse/attempts/0x00237d3d.cpp build/trust237-round18/r18_bank.cpp
python3 tools/variant.py build/trust237-round18/r18_bank.cpp Rva00237D3DCheck 0x237D3D 226 _memset=0x6291AE _WinVerifyTrust@12=0x655652
python3 build/trust237-round18/audit.py
```

The audit records input/tool hashes and matrix digests; all objects and large
artifacts stay ignored. Fresh runs of success_cases compile all jobs; existing
runs retain valid receipts and retry failed jobs.

**Remaining blocker:** baseline +CD..DC is the known sixteen-byte binary patch
documented in rounds16/17, replacing the independently recovered comparisons.
This round establishes no legal C++ producer for those bytes. A finite search
does not prove universal compiler impossibility, but further unchanged source
matrices do not address the evidenced input patch. Resume on new concrete
compiler evidence or an upstream decision authorizing how to represent that
patch; such a policy/baseline change is outside this seat's authorization.
Do not insert asm/emit padding, substitute the zero-returning original, or
weaken verification. The best bank is recorded and the claim released. The
standing assignment forbids switching to other bodies before this one lands.
