# 0x237D3D: barriers, link-time compilation and two-code controls

Continuation of `../trust237-20261022-round4/readme.md`. Assigned target:
`?Rva00237D3DCheck@@YAHXZ`, RVA 0x237D3D, proven extent 226 bytes.
BFME2 input `426782e222`; committed and checked-out BFME1 input
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. Model: GPT-6.1-sol.
No Code source, ledger row, pin, baseline or compiler binary changed.

## Retained bank

The existing bank remains best, score 69/86 = 0.802326. An independent
`variant.py` compile reproduced 219 bytes, 21 diagnostic positional
differences and the first difference at +0xCD. Raw hash remains
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.
`bank.cpp.txt` preserves its current input. The sixteen individual NOPs
at +0xCD..DC and the return-tail ordering remain unresolved. These trials
do not establish an exact match, a universal compiler limitation or an
original post-link patch.

## New hypotheses

Before editing, read the per-RVA history through `pick-hard --rva` and the
four preceding handoffs. Ordinary source lifetime/scope, SDK layouts,
callee declarations, compiler flags/profiles and the normal padding emitter
were already covered. This round tests optimizer-only intrinsics, a
different compilation pipeline, and a gap in the earlier counterfactual
status-check experiments. It does not repeat the earlier matrices.

| Family | Successful | Distinct bodies | Result |
| --- | ---: | ---: | --- |
| barriers | 288 compiles | 37 raw | No NOP; 36 introduce unresolved `_ReadBarrier` calls |
| LTCG | 54 compile/link pairs | 13 after import normalization | No NOP or improvement |
| zero/code controls, G5/G6 | 384 compiles | 18 raw | No NOP or outside-region match |
| two nonzero-code controls | 1,152 compiles | 27 raw | No NOP or outside-region match |

`summary.json` retains counts, representative regional scores and tool
hashes. These are finite experiments, not proof of impossibility.

### Optimizer intrinsics

Eight forms combine `__noop`, 16-argument `__noop`, an always-valid
`__assume`, `_ReadBarrier`, `_WriteBarrier`, `_ReadWriteBarrier` and two
combinations. Factorial choices: 1/16 repetitions, three positions
(before cleanup, after cleanup, forceinline helper after cleanup), three
established return forms, G6/G7. All 288 compile, but `_ReadBarrier` is
**not recognized as an intrinsic by RTM**: C4163 and unresolved
`__ReadBarrier` occur in all 36 of its variants. Those are not functioning
barrier controls or eligible candidates. The other 252 have no unresolved
REL32 and yield 17 distinct raw bodies.

The supported write/read-write barriers change scheduling. For example,
`barrier-region.cpp.txt` (`n0170`) retains the +0xCC prefix and moves `sbb`
before restoration; it still emits 219 bytes, 21 positional differences
and no NOP. It is not an improved bank. `__noop` and `__assume` forms
reproduce existing outputs. `intrinsic-warnings.json` includes independent
representative compiler diagnostics so successful compilation cannot be
mistaken for intrinsic recognition.

### Explicit link-time code generation

RTM `/GL` compilation succeeds, but its isolated `/LTCG` link fails with
C1350/LNK1257 because the committed RTM toolchain lacks `msobj71.dll`.
`gl-prototype-command.json` preserves this setup failure. It is not evidence
against an RTM link-time source shape.

Both already-supported complete profiles, `vc71-sp1` and `vc71-ddk-4035`,
were then tested explicitly. The driver verifies every profile file against
`compiler_profiles.py`, copies that complete set and the unchanged RTM
`link.exe` to a private directory, and uses the selected profile for `/GL`
compilation and link-time code generation. This avoids changing the normal
compiler installation or silently borrowing a DLL for RTM. RTM headers and
import libraries stay fixed. The exact compiler/DLL/linker hashes are in
the summary.

The matrix is two profiles, O1/O2/O1+Og-, G5/G6/G7, and the simple bank,
current range-predicate bank and 64-bit regional alternative. All **54**
compile/link pairs succeed. Export addresses and MAP publics delimit the
function; only trailing INT3 alignment is removed, never NOP bytes. All
extracted bodies end in RET. Candidate import calls are resolved by PE
import names and their actual linker thunks before diagnostic comparison.
The best outputs reproduce the bank's 219-byte shape and +0xCD first
difference. There are no unresolved calls or NOP instructions.

### Counterfactual status checks

Earlier original-check probes predominantly used G7 and paired zero with
one nonzero code. A zero comparison can keep the initial zero live in EBX
and spill status, whereas two full-width immediate comparisons and short
branches can occupy sixteen bytes. This was a concrete new explanation
to test for the unknown region, not evidence about its original contents.

First, eight earlier zero/code shapes were crossed with G5/G6, O1/O2,
int/bool result, flat/nested return scope and no/write/read-write barrier:
384 successful compiles. Next, eight shapes were crossed with three pairs
of nonzero constants, G5/G6/G7, return scope, int/bool result, direct/copied
unsigned status and no/write barrier: 1,152 successful compiles.

No result equals retail outside the fixed sixteen-byte interval. The
closest nonzero-code control is 230 bytes with ten differences outside
that interval: it preserves the first 203 bytes, but lacks the early xor,
adds a jump and retains a separate failure return. The saved
`two-code-control.cpp.txt` (`c0576`) and `regional-comparison.txt` preserve
this finding. **These controls can return zero and cannot be banked as
semantically faithful candidates.** Their constants are hypothetical;
none is established as an original target-source fact. The experiment
does not establish an original patch, even where some instructions align.

## Reproduce and resume

Copy the saved `.py.txt` scripts to `build/trust237-round5/` as `.py`, and
copy `base.cpp.txt` and `bank.cpp.txt` as `.cpp`. From the repository root
run `barriers.py`, `ltcg.py`, `original_g6.py` or `two_codes.py` in that
directory. The matrices use eight isolated compiler workers and distinct
scratch objects. They never use `build.compile_source` or write the shared
match cache. Linked scratch artifacts are diagnostics, not game builds.

Object scores use the existing diagnostic DIR32 masking and REL32 maps
memset=0x6291AE, WinVerifyTrust=0x655652. Shifted DIR32 offsets can make
scores misleading; none is a relocation-admission receipt. The bank's
independent check is:

```
python3 tools/variant.py build/trust237-round5/bank.cpp '=?Rva00237D3DCheck@@YAHXZ' 0x237D3D 226 _memset=0x6291ae _WinVerifyTrust@12=0x655652
```

Continue only this assigned body. The supported barriers and the tested
complete-profile LTCG pipelines do not explain its NOP span. Ordinary
two-status original-check spellings also remain unproven. No missing game
function prerequisite was identified. Preserve the best bank; do not
repeat these finite matrices without a new explanation.

Prework ledger check passed. BFME1 freshness update was skipped under the
live shared lock owned by `claudec2`; no success timestamp was written.
Published link-index fetch succeeded. Current link prediction:
VersionInitGlobals.cpp has 200 bytes held by this unresolved symbol;
VersionDestructor.cpp already links with 1,275 bytes. These are existing
conditions, not a new linking improvement. Preserve unrelated untracked
`reverse/zh_sweep/`.
