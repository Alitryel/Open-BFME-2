# Strlen-shaped tail helper, RVA 0x007B9CCA — astra-s3, 2026-10-23

No match landed. The best candidate emits **24 bytes, with five differing bytes**:
one independent TEST/LEA instruction-order swap. All branch displacements,
loop instructions and return instructions now match. This improves the earlier
unbanked 22/23-byte forms and the first 24-byte / six-difference candidates.

## Inputs and identity limits

BFME2 revision: `7aae99cc67cf966798925fe6a5479b84e35d16c9`.
Verified BFME1 input pointer: `138757e9b74645fbcbb7724a7af2764e34931e11`.
The source uses no donor headers or donor implementation. Default compiler:
MSVC 7.1 RTM, with `// cl: /O1 /G6 /MD`. The build driver also supplies its
normal initial `-O2 -GR- -EHsc-`; the later source `-O1` wins.
SP1 and DDK4035 were additional declared-profile controls, not new toolchains.

The baseline bytes at 0x007B9CCA through RET at 0x007B9CE1 form a cdecl,
strlen-shaped helper at the end of .text. The immediately preceding body ends
in a tail jump and does not fall through. An all-section scan found no E8/E9
target or literal VA/RVA reference to this address. Ghidra's function list had
no entry here. These observations support the body boundary and behavior but
**do not identify its original name, owner TU, or callers**. The candidate name
is descriptive evidence only. An exact byte match would still need an honest
identity/provenance decision before admission.

The BFME1 upstream freshness fetch advanced its remote master, but the shared
submodule initialization initially attempted a very large history transfer.
The pinned input was restored using an object alternate to another seat's
already-fetched identical commit, followed by `submodule update --no-fetch`.
No BFME1 source or pointer was changed; no successful freshness stamp was
written. Updating beyond the pinned inputs still requires the prescribed
same-revision comparison/full verification. This attempt does not claim that
update was completed.

## Exact comparison

Retail:
```
8b4c2404 8a11 8d4101 84d2 7407 8a10 40 84d2 75f9 2bc1 48 c3
```
Candidate:
```
8b4c2404 8a11 84d2 8d4101 7407 8a10 40 84d2 75f9 2bc1 48 c3
```

Retail loads DL, initializes EAX with LEA, then tests DL.
The candidate loads DL, tests DL, then initializes EAX with LEA.
There are no relocations. The raw byte-agreement bank score is 19/24
(0.7916666667), not an instruction-normalized similarity score.

`best.cpp.txt` is the simplest independently recompiled candidate. The
parent's round7 and the delegated GLM-5.3 helper independently reached these
same bytes. The helper's clearer goto-arm spelling was adopted only after
`tools/variant.py` independently reported 24B / five differences, first +0x6.
This is ordinary C++ with no asm, emitted bytes, or compiler modification.

## What was tested

`results.json` summarizes 4,323 trial records, including repeated controls.
**Twenty round6 cases are invalid semantic controls and are excluded**:
tags starting `type6_guard4_` or `type8_guard4_` compare an unsigned word
against -1 in a way that makes the guard always true. They provide no evidence
about equivalent-source code generation. There are zero exact results among
the remaining trials. Counts describe attempted cases, not unique bodies.

The reproducible generators are preserved as `*.py.txt` in the two scratch
directory mirrors. They use the ordinary `build.compiler_command` and
private objects, with two compiler workers; no shared match-cache objects.

- matrix / round2: C/C++, loop spelling, pointer lifetime, return expression,
  optimization/processor flags and supported compiler profiles.
- rounds3–6: guard/latch predicates, volatile loads, split variables and
  promotions. Non-unified unsigned predicates give 24B / six differences,
  but their JA/JBE branch differs from the baseline.
- round7: peeled loops and explicit exit/goto arms; first 24B / five-difference
  result, with both JE/JNE bytes exact.
- rounds8–9: component optimization flags and initial pointer/guard forms.
  D4002-ignored switches (including tested /GB and /Gy- combinations) are
  diagnostics, not evidence that those settings were effective.
- rounds10–11: pointer-delta dependencies, ABI-equivalent argument/return
  spellings and attributes; no improvement.
- round12: local/global optimization controls. Disabling /Og also loses
  register allocation and produces large stack-based code; /GL- controls
  retain the same five-difference result.
- helper hh families: goto-arm control flow, separate first-load/loop-entry,
  compound guards, aggregates and inline helper ownership. The goto-arm
  spelling preserves the explicit guard load and bottom-tested loop together.

Observed output families: plain postincrement loops rotate; explicit
split-entry while loops often use a memory CMP guard (23B); shared-header
loops can reproduce the load/LEA/TEST prefix but use a JMP back edge; the best
goto-arm forms have the correct loop and branches but swap TEST and LEA.
The proposed loop-normalization/rematerialization explanation is an inference
from emitted code, not a proven compiler-internal mechanism.

A read-only Wine debugger experiment adapted the camera scheduling scripts.
It captured one intermediate seven-node graph when tracing from process
startup, but produced no comparable output object even in a no-breakpoint
control. Therefore **no scheduling conclusion is drawn from that trace**.
Those incomplete trace artifacts remain scratch, not verification evidence.

## Semantic check and reproduction

`semantic_check.py.txt` implements only the explicit opcodes in the baseline
and candidate. It compared 1,791 NUL-terminated inputs (every nonzero byte at
several lengths, random lengths 0..1024, empty string), 3,582 executions:
equal return lengths, exactly one sequential byte read through the terminator,
preserved callee-saved registers and cdecl stack behavior. The receipt states
its limits: this is not a general x86 emulator or a proof for all machine states.

Restore the `s3-strlen/*.py.txt` files as `build/s3-strlen/*.py`, and the
helper files similarly under `build/s3-strlen-helper/`. Restore
`best.cpp.txt` as `build/s3-strlen/best.cpp`. From the repository root:
```sh
python3 tools/variant.py build/s3-strlen/best.cpp rva007B9CCAStrLen 0x007B9CCA 24
```
To run the semantic checker, create `build/s3-strlen/retail.bin` from the exact
retail hex above, then copy/run the checker there. Generators write fresh
private objects; the `results.json` summary preserves the tested byte forms.

## Resume

The remaining concrete source problem is an entry-block boundary or dependency
that places LEA before TEST while preserving the explicit guard load and
bottom JNE. Repeating generic while/for spelling, signedness, flag matrices or
aggregate wrappers on the same inputs is unlikely to add evidence.
A compiler trace must first reproduce the ordinary object before its internal
observations can be relied on. The helper's original owner/name remains an
independent admission prerequisite. No Code/, ledger row, pin, gate, baseline
or compiler binary was modified.
