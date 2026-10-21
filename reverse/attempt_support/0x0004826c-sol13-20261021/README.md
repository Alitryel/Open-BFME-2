# gatherDebugStats: prove null-edge definition creation and selection

Continue only `?gatherDebugStats@W3DDisplay@@UAEXXZ`, RVA `0x4826C`,
retail boundary `0x4826C..0x49271`, 4101 B. **Not exact.** Preserve the
canonical bank, score 0.9968: 4101 B / 1237 instructions / zero structural
regions / 13 nonrelocation stack-displacement bytes. The source is unchanged.
The slot-correct sol10 alternate remains 4101 B / 1239 instructions / 11
masked diagnostic bytes / one structural region. No Code, ledger, pin,
header, compiler or verifier edits; no padding.

## Inputs and checks

Started 2026-10-21 00:22:56 UTC after the sol12 continuation. AGENTS.md,
served RVA history, prior handoff and recipes read; claim acquired. Initial
ledger validation: 97651 functions / 15928 symbols / 1136 data rows.
Published link index fetched, 23147 objects. BFME 1 clean verified pointer
`68c5ce2789e974f36b6c742d57437d157bc159e9`; successful receipt 2026-10-20
15:49 UTC remained within 24 hours. No update due. Final pull rebased the
preceding evidence commit to `a5edf75fd8` atop upstream `3eee2106d6`.
AGENTS.md, tools/build.py, hooks and reference inputs did not change across
that pull. Final ledger validation passed: 97800 / 15929 / 1136.

Original c2 13.10.3077 SHA256:
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Frozen bank input SHA256:
`543c60098a558083c8e25ac900f5643eea7c1b5e42eb3e4b4bf286b26aa3454c`.
Flags `/O1 /arch:SSE /G7 /MD /EHsc`; model gpt-6.1-sol. Scratch
`build/gather-sol13-20261021/`. Eight isolated outputs; no experimental
compile_source/shared-cache writes. Official explain_mismatch and align_diff
reproduce the 4101 B body, unresolved MemoryPool REL32 classification,
first stack difference +0x64, 1237 instructions and zero structural regions.
Those diagnostics are not a successful byte gate. Completed control compiles
independently reproduce bank 13 bytes, throwing base 44, unsigned alternate
11/one region, plain-pointer control 4104 B/two regions.

## Native evidence: synthetic definition, not a source copy

Read-only debugger captures now prove the path from predicate to replacement,
with source/destination fields checked against c2 constructors:

1. Watch the original p record's +0x40 linked-definition head after early
   flow construction. It begins zero, is reset during initialization, then
   gets the ordinary lookup-result definition and, for the plain pointer
   comparison, a second definition with a literal-zero source.
2. Both insertions stop after `0x1076196D: mov [ebp+0x40],eax`, at
   `0x10761970`. This is inside `0x107617B5`, which registers an assignment
   expression. At the zero insertion, its argument is synthetic tuple
   `0x00C5C9FC`, opcode 0x263, literal-zero source, p destination, and
   byte +0x17 equal to 1. Its next tuple is the null-arm draw=p copy.
   The ordinary lookup assignment is tuple `0x00C35460`.
3. The zero tuple is created by the call at `0x1076285C` to TupCreate;
   `0x10762864` marks byte +0x17, then `0x10762868` calls the assignment
   registrar. Caller `0x107626A8` admits branch condition nibble 1 or 2
   (`0x1076272D..38`) and requires the second compare operand's type 7
   (`0x10762764`). These are observed numeric tests; their equality roles
   follow from the pointer comparison input, not from compiler symbol names.
   Compare tuple `0x00C35540` contains p and literal zero.
4. On the null-arm draw copy, `0x10761E41` follows the p record's +0x40
   list and `0x107622A5` checks definition availability. At `0x1076A9B3`
   the pointer control selects the zero definition, record `0x00D3C6EC`,
   availability index 0x919. Its expression is opcode 0x263 and literal
   zero. Return to `0x10761F3A` yields nonzero EAX, an operand of type 7,
   value zero. The source-root hardware watch independently confirms the
   later actual replacement at `0x1075AC02` (sol12 finding).
5. The unsigned control's head contains only the original lookup definition.
   It considers that definition (record `0x00D35338`, index 0x8cc), but
   returns EAX=0 at `0x10761F3A`: **no accepted replacement**. Selecting
   an available candidate at 0x1076A9B3 alone does not prove substitution.

The definition expression structure is `[hash-link, opcode, type,
operand-list, result-record]`; its first pointer is not an originating tuple.
Raw captures are in native-evidence.json. Static caller sites above were
checked in the original binary. Other raw stack words are clues, not an
unwind. Snapshots deliberately quit before full compilation; separate
completed controls establish emitted results. No compiler writes or patches.

`windowdefs.py` first breaks on the containing block at 0x10763847, then
on the selected tuple at 0x10761F35. This is much faster than a conditional
breakpoint on every source operand from the start of the pass. The original
wide-window probe needed about four minutes; its initial 30-second timeouts
were diagnostic-driver failures, not evidence about the source.

## New source hypothesis and 4096 checked trials

Hypothesis: compare against a computed zero whose literal form appears after
edge-fact admission, preserving p through packing while eventually emitting
retail's direct null branch. This differs from sol12's inverse copy lowering:
the computed zero is a comparison operand, not a copy of p.

The factorial grid crosses 32 zero expressions (variable rotations, duplicated
intrinsics, division/remainder identities, narrowing and bit identities,
conditional zeros), inline helper/direct expression, local/direct zero,
comparison orientation, assignment order, char releaseBuffer contract,
null obj=p/zero, and equality/unsigned ordering: 4096 cases. Every final
source and its runtime string-literal set was regenerated and checked against
its compiled input; all compiles succeeded. No zero-region candidate; best
remains the previous 11-byte/one-region alternate. Full histograms and source
stream hash are in validated-results.json. Counts include duplicate outputs.
Relocation masking is diagnostic only.

A precedence error in four initially unparenthesized XOR comparison expressions
was corrected; all 128 affected cases were recompiled and replaced before
validation. The final generator includes the correction. Preliminary results
and the old diagnostic capture for that malformed predicate are excluded.
A standalone MSVC/Wine unsigned-arithmetic harness checks all 32 corrected
zero expressions on 100000 inputs (3.2 million checks); this is a finite
semantic check, not exhaustive proof or retail-byte acceptance.

A fresh native probe of the corrected variable-rotate-XOR case
`zc040000010` returns literal zero at 0x10761F3A and emits 4104 B. Thus this
concrete computed-zero expression folds early enough to admit the same null
fact; it does not preserve the required third reference. This replaces the
pre-correction capture, which had actually tested a different predicate.

## Resume

The task remains unfinished; retain both the canonical bank and sol10 patch.
Earlier control-flow, lifetime/scope, types/layout, real-header/callee,
compiler-profile, copy and predicate grids remain ruled out by their handoffs.
This continuation adds the exact synthetic null-edge definition and its
selection/rejection path, and rules out this computed-zero comparison grid.
Do not rerun these expressions without a new timing distinction.

The concrete next investigation is the later branch/join simplifier: find
when the unsigned control's initial predicate becomes a machine branch and
why its obj=p null arm survives while ordinary pointer facts eliminate
copies too early. A new source hypothesis must explain both a third draw
reference before packing and direct `je TERRAIN; load` after packing. The
existing two unresolved MemoryPool calls still require the 3-byte folded
wrapper identity/admission repair; no pin workaround was retried.

Reproduce by copying sibling *.py.txt into a fresh directory directly under
build and removing .txt. Run prepare.py (asserts frozen bank), zerocompare.py,
validate.py, controls.py and semantics.py. Then windowdefs.py carrypointer,
windowdefs.py carry081200, windowdefs.py zc040000010, and factbuild.py
carrypointer; summarize.py combines those captures and existing official
diagnostic text outputs. It intentionally does not run acceptance or
maintainer-only verification runners.
