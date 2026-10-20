# Standing-water byte-vector escape analysis

Target: `RenderableStandingWaterArea::AllocateAndFillBuffers`,
`0x0008304A..0x000834CE`, **1156 bytes**. Still unmatched. The stronger
existing `reverse/attempts/0x0008304a.cpp` is unchanged:1163 bytes,
fitness0.9197485, frame0x88, complete parent EH EXACT.

BFME2 input: `3d009a9247912b1251d375f2f9e57a19d4703aea`.
BFME1 pointer: `92f6bbe8e1dcdb46b5d27da0674313efc822b790`.
Model: GPT-6 Astra. Parent/root executed the ordinary compiler commands
after the sandbox could not launch cl.exe. No production source, ledger,
pin, gate, baseline, or full verification runner changed in this work.

## New evidence

Complete genuine byte-vector visibility **does** hoist the mask base out of
the first pass. The first full-graph control reads `flags.start` once at
parent+1A0, stores the row base at `[ebp-18]`, then increments it by `nx`
after each row. It also removes the extra null-conversion branch and changes
zero initialization toward retail. The baseline instead reloads the vector
header in the inner loop.

Replacing any one of `erase`, `_M_fill_insert`, or `_M_insert_overflow`
with only its declaration restores the original baseline output. All three
real bodies are needed for the compiler to establish that `&flags` does
not escape. Complete containment visibility has no additional parent effect.
The exact file loader at `0x00307EDC` independently established the same
mechanism; its full vector definition supplies this control, not a fabricated
effect summary. See
`reverse/attempt_support/0x00307edc_20261020_visible_members.md`.

This improvement does not finish the function. The complete graph uses EDI
as x and stores through `[rowbase+EDI]`; native uses EDI as the advancing
cell pointer with x on the stack. Frame size grows0x88→0x90 and local
lifetimes change. Explicit row pointers do not repair this. Removing the
loader's special inline/import policies, reducing inline depth to6, and
marking the real resize noinline also fail to reconcile it.

## Measurements

Normal `explain_mismatch.py`, then `align_diff.py`; fitness and EH read the
resulting objects without compiling again. All parent calls resolve.

| ID | Controlled change | Bytes | Fitness | Parent EH |
| --- | --- | ---: | ---: | --- |
| 00 | Current bank | 1163 | .919749 | EXACT |
| 01 | Full vector graph, E12 local retained | 1151 | .828519 | six stack bytes |
| 02 | Same graph, actual char-vector local | 1147 | .825555 | same |
| 03 | 01 plus real containment body | 1151 | .828519 | same |
| 04 | 02 plus real containment body | 1147 | .825555 | same |
| 05 | 04 plus containment's `/Oy-` profile | 1147 | .825555 | same |
| 06 | 01 plus exact loader header preamble | 1151 | .828519 | same |
| 07 | 02 plus exact loader header preamble | 1147 | .825555 | same |
| 08 | 07 with first-pass row/cell pointers | 1147 | .821987 | same |
| 09 | 07 with second-pass row pointer | 1150 | .783992 | same |
| 10 | Both pointer controls | 1150 | .783881 | same |
| 11 | Both pointer controls, E12 local | 1154 | .787434 | same |
| 12 | 06 using ordinary real header policies | 1151 | .828519 | same |
| 13 | 07 using ordinary real header policies | 1147 | .825555 | same |
| 14 | 06 with declaration-only erase | 1163 | .919749 | EXACT |
| 15 | 06 with declaration-only fill_insert | 1163 | .919749 | EXACT |
| 16 | 06 with declaration-only overflow | 1163 | .919749 | EXACT |
| 17 | 12 with TU inline depth6 | 1151 | .828519 | six stack bytes |
| 18 | 12 with noinline resize | 1151 | .828519 | same |

Every control preserves the whole-exact153-byte cache constructor at82A53,
including its EH, and39-byte coordinate addition at7DEC8. Controls01–18 emit
the whole-exact54-byte by-value resize at826E3;00 declares it. Containment
controls03–05 also emit the whole-exact304-byte body at30D111.

The six EH differences are cleanup stack-home operands, with identical
`.xdata$x` bytes and no relocation-graph conflict: guard `-94→-9C`, flags
`-54→-50`, cache `-90→-98`, allocation pointer `-14→-18` twice, and lock
`-34→-5C`. They are not new cleanup actions. The char local additionally
removes one four-byte parent state store.

## Provenance and limits

Native proves the local three-pointer object, constructor7FAEA, by-value
resize826E3, one-byte Boolean mask, signed loop bounds, first-pass invariant
row base, and second-pass `base+y*nx` computed once per row. Containment
receives only shape and `&pos`, never the vector or its payload. Its opaque
virtual/wrapper calls can nevertheless alias a vector whose address escaped
through an earlier helper.

WB73F580 supplies the named builder and indexed mask loops. Its69C090
helper is **reserve**, not native resize: it preserves logical size and
does not initialize new bytes. WB therefore supports purpose and indexing,
not identical vector helper context. The nullable shape adjustment through
vbptr+18/entry+4 is shared; a genuine virtual-base conversion was already
tested in the earlier lifetime handoff and is not a new control here.

The full graph comes from
`Code/GameEngine/Source/Common/Rva00240000Load308050.cpp`, with its
target-supported zero-allocation guard and native by-value resize ABI.
The used headers are the current `vendor/stlport` plus
`reference/shims/bfmealloc`, confirmed by compiler dependency receipts.
The char spelling and E12 layout view do not establish the application's
original element type. The loader's imported-forceinline specializations
are link repairs; controls12/13 use ordinary genuine header definitions.

Parent flags remain the bank's `/O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG`,
`_STLP_NO_EXCEPTIONS`, `_CRTIMP=`, `_STLP_USE_STATIC_LIB`, and existing
BFME allocator/ASCII/moduledata include shims. Control05 changes only the
containment frame-pointer policy;17 changes inline depth;18 changes resize's
inline eligibility. Nothing forces stack padding, stores, or alias effects.

## Reproduce and resume

Run:

```
python3 reverse/attempt_support/water-vector-escape-20261020/replay.py.txt
```

`--prepare-only` creates all19 sources without compiling. Numeric arguments
select controls, for example `00 12 16`. Input hashes are checked against
`results.json`; review changed inputs before regenerating old measurements.
All scratch outputs go to `build/water-vector-escape-replay/`.
`BFME_OBJSTORE=off` avoids shared object-store writes while retaining the
normal byte-check entry points.

Read already compiled helper bodies without compiling:

```
python3 reverse/attempt_support/water-vector-escape-20261020/audit.py.txt
```

Use `--directory build/loop2-water-audit` to inspect this run's existing
objects. `full-vector.patch` preserves the ordinary complete-graph control12;
`alignment.txt` records its precise remaining differences. `results.json`
contains all measured parent/helper results and source-input hashes.

No new candidate supersedes the old bank. Resume only with evidence that
reconciles complete vector non-escape with native cell-pointer induction
and the0x88 stack lifetimes, or with new source/compiler context. Replaying
the graph cuts, individual containment visibility, row-pointer forms, or
the tested inline policies is not a new hypothesis.
