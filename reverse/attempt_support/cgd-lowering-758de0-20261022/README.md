# 0x758DE0: grouped arguments and late virtual-call lowering

The retained bank is unchanged: `reverse/attempts/0x00758de0.cpp`, 333 bytes,
zero relocations, 41 positional differences, first at +0x94. Complete
instruction-pair alignment still matches 302/333 bytes (bank score 0.9069).
Only the three virtual-call sequences remain. No reconstruction was installed
in Code and no ledger row, pin or verifier was changed.

Continue this assigned body. This session did not identify a missing callee
or another prerequisite, so there is no justified `blocked-on` RVA.

## Inputs and checks

- Started from the existing bank and read its history with
  `/opt/runner/pick-hard --rva 0x758DE0`, plus the vcall, source-shape and
  local-register packets. The existing negative flag/LTCG, declaration-padding,
  permute and real-vector-header searches were not repeated.
- Ordinary `/O2 /MD /EHsc /I.` RTM compiler, private objects via
  `compiler_command`; never `compile_source` or the shared match cache.
- BFME 1 pointer: `42bba2ddbd5cb895d99293583891d3b7315fa49e`. A fresh
  runner update lock belonged to `claudec2`; this seat skipped the update under
  the runner's serialization rule and did not record its own freshness success.
- Initial `check_csv.py` passed: 98,064 functions, 15,855 symbols, 2,128 data.
  The published link index was fetched/reused, without running a census.
- `tools/variant.py <bank-copy> bfmeTwoCGD 0x758DE0 333` independently
  reproduced the 333-byte/41-difference result. This is a diagnostic mismatch,
  not an acceptance-gate failure.
- `trace-checks.json` verifies that every retained read-only debugger run
  completed compilation and emitted its untraced control's bytes. No compiler
  state or instructions were changed by the debugger.

The body name and Contact* types in these diagnostics are inherited structural
models. Target bytes establish accesses, ABI and slot offsets, not those type
names. No new donor identity or layout claim is made.

## Source families ruled out as tested

`trials-summary.json` records 13,184 corrected variants, 13,056 successful
compiles. The 128 failures are MSVC C2719 refusals of aligned-by-value argument
models. Initial malformed generators were corrected and their earlier results
are excluded. Region scores use complete `(mnemonic, operands)` alignment;
the search helper's faster mnemonic-first score is a different metric.

| Family | Variants / compiled | Distinct bodies | Finding |
| --- | ---: | ---: | --- |
| compound2 | 384 / 256 | 20 | One 8-byte argument containing both vector addresses, as struct/reference fields or 64-bit scalar; copy/align, wrapper/direct at each site, pointer/integer result. No overall improvement. |
| callconv | 1024 / 1024 | 1 | Virtual fastcall/default forms with 4-byte argument carriers, copy constructors, constructor calling convention and const prepare. All emit the same worse 361-byte body. |
| podparam | 1024 / 1024 | 24 | POD 4-/8-byte argument packs, aggregate/field initialization, direct/adapter calls, outer argument carrier and fastcall variants. No improvement. |
| visible | 256 / 256 | 1 | Pure/declaration/visible-inline/visible-noinline callbacks, novtable and base-slot context. All reproduce the bank. |
| exprlife | 4096 / 4096 | 203 | Assign each point/normal pointer and inner/outer receiver within its actual argument expression, independently at all three sites. No improvement. |
| wrapalias | 2048 / 2048 | 61 | Recombine the known 330-byte inline-prepare wrapper with field volatility, four wrapper bodies, declaration placement, throw/fastcall and per-site direct calls. No improvement. |
| pairshape | 4096 / 4096 | 35 | Recombine the grouped-argument region winner: field types, constructor parameter order, body/initializer list, copy, forwarding scope, pair constness and per-site direct calls. No improvement. |
| bytereturn | 128 / 128 | 1 | Test AL-sized return types, unused response return metadata, prepare/info word types. All reproduce the bank. |
| refresult | 128 / 128 | 1 | Prepare returns an opaque object reference or pointer reference, consumed by matching outer references; cv, const callbacks and throw. All reproduce the bank. |

The grouped-argument candidate `compound-v0199.cpp.txt` matches the reverse
response's final +0x136..+0x140 sequence completely and scores 285/333 overall,
but loses 26 bytes of the bank's prefix. Its inner-target ordering is still
wrong. The 4,096 pairshape recombinations did not recover the prefix. This is
a local diagnostic, not a replacement bank or a legal byte splice.

The 330-byte wrapper `wrapper-v0256.cpp.txt` matches the first test's
post-prepare push/reload tail, but caches its inner receiver from the guard and
does not fix the inner-vtable ordering. Do not describe it as matching the
whole test call. Other apparent region gains likewise did not produce a
stronger body when recombined.

## Compiler trace and a useful small probe

The read-only trace uses RTM c2.dll 13.10.3077 at base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Addresses below are RVAs in that image, not target RVAs.

1. In the early optimization driver, the call at +0x5fa6f to +0x73108 lowers
   high-level nodes. Between snapshots +0x5fa5a and +0x5fa74, virtual target
   loads become explicit MOVs, ahead of the normal/point address operations.
   This is a general lowering pass, not a virtual-call-only routine.
2. The main driver's call to +0x70532, before +0xb0029, lowers argument nodes
   to PUSH and the call nodes to the later call representation.
3. Local allocation is invoked from +0xb0039 through +0x74f92 / +0x75782.
   The earlier local-register packet describes its rotating cursor and
   forbidden sets. +0xb003e is immediately after this call.
4. Later checkpoints +0xb0065, +0xb0079 and +0xb0087 bracket final lowering
   through +0x75efd, which calls +0x7641f. The linked diagnostic IR still
   places the inner-target load before the argument addresses in the probe.

`probe-p01.cpp.txt` reduces the function to one guarded test and state store.
Its untraced and opt/early/late-traced builds all emit the same 69 bytes,
zero relocations. In the final machine code its relevant sequence is:

```
01d push edi
01e mov  edi,[eax]       ; outer target table
020 lea  eax,[esi+20h]
023 push eax            ; normal address
024 mov  ecx,edx        ; inner receiver cached from the guard
026 mov  edx,[ecx]      ; inner target table AFTER the first push
028 lea  eax,[esi+14h]
02b push eax
02c call [edx+0ch]
```

This establishes that early linked-IR ordering does not by itself prove the
eventual machine ordering. **Do not require a source edit to move the vtable
node before local allocation as a prerequisite to success.** The exact later
selection/forwarding/peephole mechanism has not yet been located. That is an
inference to investigate, not a proven pass identity.

The probe does not match retail's scratch allocations, nor solve the complete
body: retail uses EDX for the normal address before reusing it for the vtable,
and the bank's state read destroys the guarded inner receiver's earlier home.
The probe gives a compact way to trace that difference without the loop and
reverse-normal work.

Decoder cautions: snapshot `fw[2]` is the flow-graph root; its identity changes
temporarily during local allocation. Following `fw[8]` is wrong (assembly
offset +8 means word 2). Late nodes and symbol homes mutate, so the diagnostic
formatter's names are not an independent final physical-operand oracle. Do
not infer a byte schedule solely from them. No useful result came from the
discarded fw[8] experiment.

## Resume without repeating these searches

Trace final instruction selection through c2+0x7641f on the 69-byte probe and
the bank, retaining actual selected operands alongside the linked IR. Locate
where the cached receiver becomes `mov ecx,edx` and permits the vtable load
after the first push. Then test an evidence-backed source/dependency change
in the full body. The bank already matches the loop, guards, x87 reverse,
extent and important saved registers; avoid regrinding those solved regions.

Materialize the archived `.py.txt` helpers into a fresh `build/<directory>/`
as `.py`, copy the current bank there as `base.cpp`, and use a `probes/`
subdirectory for `probe-p01.cpp.txt` as `p01.cpp`. From the repository root:

```
python3 build/<directory>/early.py opt
python3 build/<directory>/early.py late
python3 build/<directory>/early.py opt-probe probes/p01.cpp
python3 build/<directory>/early.py late-probe probes/p01.cpp
python3 build/<directory>/show_ir.py build/<directory>/late-probe.json
```

All helpers stay exploratory evidence; none belongs in tools or changes a
gate. The source generators and scorer reproduce the tested families with
eight isolated compiler workers. Existing raw logs and full snapshots remain
ignored under `build/cgd-order-20261022/`; only compact evidence needed to
resume is tracked here.
