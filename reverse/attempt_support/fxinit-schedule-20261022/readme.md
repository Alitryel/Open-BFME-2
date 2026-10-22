# FXShaderGeometry::Init: allocation precedes the remap scheduling difference

2026-10-22, codexb2, gpt-6-astra. Target `0x0018C84E..0x0018D16B`,
2333 bytes. Input BFME 2 `83daf8c0ba`; verified BFME 1 inputs
`37c3022de1ab944c7ffe536440d637dc8199091c`. The incoming bank's SHA256 was
`afb8743380047129007ce60809b7282a4b44d45bae54278ff045df357be60005`.

## Result and current best

The bank remains the best body: **2333 bytes, nine differing bytes in seven
instructions, EH EXACT, zero unresolved calls**, score `0.9961423060437206`.
This session changes its introductory comments only. A fresh private compile
of that cleaned bank reproduced the same result. No body was landed and no
new pin, gate change, inline assembly or compiler modification was used.

The previous signed-short vector/proxy constructor dependency is resolved by
the providers now on master. Do not repeat the old missing-callee investigation
or add the previously proposed fold pin. Eventual source placement and the
select-any helper preparation remain in
`../fxinit-wbinline-20261020/readme.md`.

Native identity/boundary evidence is unchanged: WorldBuilder `A39110`, its
FXShaderGeometry::Init assertions, and the retail whole body through `RET 4`.
The narrow views in the bank still have the provenance limits documented in
earlier notes; byte agreement does not independently establish their names.

The only native mismatch is at `+0x707..+0x721` (first differing byte `+0x708`):

```text
retail                         bank
mov ecx,[ebp-8c]               mov eax,[ebp-8c]       link1-link0 delta
mov eax,[ebp-2c]               mov ecx,[ebp-2c]       link0 induction pointer
movzx edx,[ecx+eax]            movzx edx,[eax+ecx]    link1
movzx eax,[eax]               movzx ecx,[ecx]        link0
mov ecx,[ebp-58]               mov eax,[ebp-58]       remap base
movsx eax,[ecx+eax*2]          movsx edx,[eax+edx*2]  retail remap0, bank remap1
movsx edx,[ecx+edx*2]          movsx eax,[eax+ecx*2]  retail remap1, bank remap0
```

## New finding: the registers already differ before final scheduling

Earlier notes suggested that scheduling remap0 before remap1 causes the
EAX/ECX role swap. Read-only observations of stock c2 do not support that causal
direction. Both the bank and diagnostic `pn_300000` enter `SchSchedGraph`
(c2 RVA `0xB5338`, graph 57) with the same first nine tuple operations:

1. Load the link-array delta and link0 induction pointer.
2. Load link1, load the remap base, load remap1, shift remap1 by eight.
3. Load link0, load remap0, add the packed values.

Both therefore still have **remap1 before remap0** at scheduler entry. However,
the physical registers are already assigned: the bank has base=EAX/pointer=ECX;
the diagnostic has base=ECX/pointer=EAX. Final scheduling produces the observed
different load order from these inputs.

A hardware watch on the bank's remap-base operand register field
`0xD3849C` (`operand + 0x1C`) fires at c2 RVA **`0x85F15`** in global allocation,
binding it to EAX (`0x108A9804`). This is before final scheduling. The watch and
all breakpoints only observe compiler state.

The allocator trace identifies the competing split ranges in round 14:

| Input | Range | Candidate | Observed priority at +0xC | Available when observed | Assigned |
|---|---|---:|---:|---|---|
| Bank | remap base | 51 | 60 | EAX, ECX, EDX | EAX |
| Bank | link0 pointer, final split | 175 | 36 | ECX, EDX | ECX |
| Diagnostic | link0 pointer, final split | 174 | 54 | already colored when captured | EAX |
| Diagnostic | remap base | 51 | 48 | ECX, EDX | ECX |

In the bank, pointer candidate 130 (priority 50) is popped between the two
listed final candidates, before its later split. In the diagnostic, pointer
174 is colored before base 51. These observations establish the order and
register availability; the exact formula for the priority field is **not yet
established**. Do not infer that changing one scalar cost alone will suffice.

`pn_300000` moves unguarded P/N copies to the common successor of all arms.
It is a **diagnostic only**, not an equivalent/bankable solution: 2326 bytes,
wrong scope for the copies, and moved position-test layout. `once_31200` inserts
a single-iteration pass-count loop around R/W; it also gets the desired remap
registers but emits an extra load/test/branch and moves the position test
(2339 bytes). These show that control-flow/liveness changes can produce the
desired assignment, while neither preserves retail's complete body.

**Next concrete angle:** trace the origins of the split-range priorities and
interference for base 51 versus the link0 pointer. Find a supported source shape
that changes their allocation order while retaining the existing two-bone arm
and its early position comparison. This is upstream of `SchSchedGraph`;
parentheses aimed only at the final scheduler are not supported by this trace.
Investigate whole-function uses/loop splitting or real accessor context rather
than repeating local remap algebra. Compiler helpers around Color/Spillcosts
(`0x82978`, `0x83C65`, `0x83D3C`, `0x85EB0`) are further leads, not decoded facts.

## WorldBuilder correction

The old interpretation of `A3A22C/A3A251` as the skinning P/N copies was wrong:
those instructions copy **tangent/binormal under `if (basis)`**. The actual
skinning position/normal copies are at **`A3A3D6..A3A431`**, after weights inside
the two-bone arm. The bank's source order agrees with that evidence. Moving P/N
before the pass/bone arm is a useful allocator diagnostic, not the source order
established by this twin. Reproduced with:

```sh
python3 tools/wb_show.py 0x0018C84E --max-lines 2000
```

## Trials excluded this session

The history was read with `/opt/runner/pick-hard --rva 0x18C84E` before editing.
Previously disproved families included simple pack commutations, staged scalar
locals, inert-local scans, raw pointer/cast changes, earlier P/N and Vector3
copy forms, flag sweeps, and the 1634 declaration permutations. This session
tested new combinations/boundaries and traced the compiler instead of rerunning
those exact trials. The 6632 generated trials below produced no improvement
over the nine-byte bank residue:

| Family | Trials | Concrete scope |
|---|---:|---|
| pnflow | 192 | Copy placement/guards/order/helper crossed with R/W order |
| pnjoin | 768 | Twelve predicates, eight successor-edge forms, four scopes, P/N selection |
| pnflag | 102 | Deferred-copy flag types, declaration scopes and assignments |
| packboundary | 450 | Scalar/pair/pointer helper boundaries, argument order, types, barriers |
| pnduplicate | 288 | Duplicate R/W across P/N predicates and nesting |
| stagedbarrier | 384 | Link staging/order, map pointer, scalar/reference, barrier positions |
| fpboundary | 512 | Floating-expression boundaries, casts, locals, setters and helpers |
| volatileload | 384 | Individual remap-read order/types/staging (diagnostic) |
| onceboundary | 432 | Loop/entry forms over R, RW, RWP and RWPN |
| inlineboundary | 1536 | Three inline boundaries with 512 argument permutations each |
| mappedpair | 864 | Mapped-pair layout, constructors, references, packing and evaluation |
| armblocks | 720 | All 120 arm/block source orders, three guards, two fallthrough forms |

Independent explanations addressed here were control flow/entry, local lifetime
and scopes, types/layout, inline callee boundaries, floating expression codegen,
and the twin's source shape. Prior compiler-setting experiments were reviewed;
the same established flags were retained. No new missing callee blocks the bank.

`measurements.json` records best results and exclusions. Some generated sources
did not compile (64 duplicate-family trials); `_ReadBarrier` is not an intrinsic
in this compiler (90 pack-family unresolved results); other unresolved/extent
exceptions are grouped separately. These are failed experiments, not evidence
of gate false rejects. The volatile family best full-byte difference is 42.
Old alignment scores in early families include FS-normalization noise; the
actual relocated differing-byte count (`nd`) was unaffected. The final fresh
bank score has seven operand differences and zero structural differences.
Alignment scores ignore some branch/call details and are never byte proof.

## Reproduction and preserved evidence

Stock MSVC 13.10.3077 under Wine, bank flags
`/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`, with the usual build-driver defaults
preceding them. Private object paths only; no `build.compile_source` calls.

Copy the five `*.py.txt` files to ignored `build/fxinit-seat22/`, removing `.txt`.
Run from repository root. `search.py FAMILY` regenerates a family in eight
threads, using the current bank as input, `compiler_command` and ordinary
`compile_function` relocation resolution. The scripts are diagnostic evidence,
not gate code. `bank-verification.json` contains the fresh result, EH verdict and
confirmation that the completed read-only color-trace objects have exactly the
same function bytes **and relocations** as the ordinary compiled inputs.

To regenerate the two diagnostic sources, copy the bank to the corresponding
`build/fxinit-seat22/trials/NAME.cpp` and apply `NAME.patch` to that explicit
scratch path. Never apply these patches to the bank or a `Code/` source.

```sh
python3 build/fxinit-seat22/schedule_trace.py build/fxinit-seat22/trials/baseline.cpp baseline-schedule
python3 build/fxinit-seat22/color_trace.py build/fxinit-seat22/trials/baseline.cpp build/fxinit-seat22/baseline-color.obj
python3 build/fxinit-seat22/register_watch.py build/fxinit-seat22/trials/baseline.cpp baseline-register 0xd3849c
```

First create `baseline.cpp` by copying the bank. For the diagnostic use
`pn_300000.cpp` instead and different output names. `observations.json` preserves
the first nine pre-scheduling tuples/operand words, the relevant allocator
records and the watch event. Full traces and generated objects remain ignored.
The hardcoded compiler/IR addresses refer to these inputs; rediscover them after
compiler or source changes. The color filter includes the original pointer
symbol `0xDB41C4`; its diagnostic counterpart is `0xDB51CC` (the saved trace
captured that candidate through its base-range neighbor).

Freshness housekeeping: official BFME 1 upstream was fetched at
`3cef00d2dd96f598ee0addc171da550f568ee7eb`, but
`file:reference/open-bfme-1` was held by `codex-bce2-01a11b23-root`. The verified
pointer was retained, no freshness success was recorded, and this seat removed
its update lock. This did not block the private Init experiments.
