# 0x758DE0: final scheduler located; reverse-call tail improved

Continue the assigned `BfmeThingCGD::bfmeTwoCGD`, 333 bytes. The replacement
bank is a **diagnostic ABI model**: 333 bytes, zero relocations, 34 positional
differences, first at +0x94, 308/333 bytes in aligned identical complete
instructions (score 0.9249249249). The earlier uniform virtual-interface model
is preserved as `control.cpp.txt`: 333 bytes, 41 differences, 302/333 aligned.
Neither is an exact recovery. Nothing was installed in Code; no ledger row,
pin, compiler flag or gate changed.

## What improved and what is still uncertain

The new bank changes only the reverse prepare call to a virtual fastcall view
whose single eight-byte argument contains the point and normal pointers. In
this emitted call, `this` is ECX, the two pointers occupy the same stack words,
and the callee pops eight bytes, as in the ordinary two-reference thiscall
model. This reproduces the reverse response's final push/reload sequence:

```
136 push eax
137 mov  eax,[esi+4]
13a mov  ecx,[eax+4]
13d call [edi+24h]
```

The rest of the body is byte-identical to the old bank, including the solved
loop, guards, saved registers and x87 reverse normal. Only the first test and
first response now differ. `candidate-diff.txt` shows all three call regions.

This does **not** establish that the original source used an eight-byte
parameter, fastcall, or two interface views. The per-call cast is an experiment
with a stack-compatible ABI, not a proven target class relationship. Contact*
names remain inherited structural labels. Keep the original uniform model as
a semantic control and seek a consistent source/interface explanation before
landing. No missing callee or justified `blocked-on` RVA was identified.

`raw-pair.cpp.txt` obtains exactly the same body through an explicit function
pointer table. The bank instead uses an ordinary virtual call through the
alternate view. Both emit SHA256
`4eed5f454059874abc8ac4979f6a229dee0035889915d71493dc7d1972a3bada`.
In both, the reverse CALL node's word 14 is 0x10040000; the ordinary model has
0x10140000. Do not call this a virtual/nonvirtual discriminator: the virtual
fastcall experiment has the same value as the raw fastcall one. The improved
post-call register/order choices already exist at c2+0xb0087, before the newly
located final forwarding and scheduling passes.

## New evidence: exact late passes

All addresses here are **compiler RVAs**, RTM c2.dll 13.10.3077, base
0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
The previous packet stopped at main-driver +0xb0087. Read-only traces now
continue beyond that point:

1. +0xb48c0 calls +0xb211d with mode 2, +0xb4b22, +0xafe57 and +0xb496a.
   Checkpoints +0xb48e7, +0xb4915, +0xb492f and +0xb493c retain the probe's
   pre-final linked instruction order.
2. In +0xb2969, the call at +0xb2996 to **+0xb5aa6 forwards cached loads**.
   In the 69-byte probe, node 0xbeda64 changes from loading ECX from [ECX+4]
   to `mov ecx,edx`; the source operand changes from 0xbeda08 to 0xbf5c60.
   Checkpoint: +0xb299b.
3. The call at +0xb29d4 to **+0x8734c schedules instructions**. At +0xb29e0
   the probe's outer-source reload has moved before `push edi`, and the inner
   receiver move and vtable load move after the first normal-address push.
   These are linked-order changes; relevant physical register operands stay
   fixed in this trace. The completed object confirms the actual order.
4. Conditional +0xb5d82 and +0xb5dbb follow; checkpoints +0xb2a0b,
   +0xb2a1d and +0xb2a3a do not change these call sequences.

The pass descriptions above are observations, not recovered internal symbol
names. `selected-ir.txt` retains the relevant probe, control and improved
candidate snapshots. `c2-final-passes.txt` preserves the driver disassembly.
All six retained debugger runs completed compilation and reproduced their
untraced control bytes, with no relocations (`trace-checks.json`). The debugger
only read state. The focused `trace.py.txt` removes the old invalid fw[8]
experiment entirely; the flow-graph root is fw[2].

Static scheduler leads, not yet dynamically traced: +0xb4dc3 chooses a window
through +0xb4e2f; +0xb4e11 calls +0xb3e88 to build its dependency graph,
whose pointer is at 0x108a8054; +0xb4e1b calls +0xb550a and +0xb4e25 calls
+0xb5338. The latter two appear to compute priorities and select order.

The control's state read overwrites the guarded inner receiver's ECX home,
so it cannot use the probe's cached-receiver forwarding. Its inner vtable
already occupies EDX while the normal address uses EAX. Scheduling alone did
not change those roles in the traced runs. Distinguish that allocation issue
from merely moving an already allocated load after a push.

## Tested families: do not repeat

`trials-summary.json` records **6,148 variants, 6,147 successful compiles**,
using eight private-object workers. The one rejection is C4234: this compiler
reserves `__thiscall` for member declarations and refuses the raw function
pointer declaration. These are new experiments informed by the traced call
metadata and the earlier grouped-argument local winner, not a rerun of old
flag, padding, lifetime or permutation sweeps.

| Family | Variants / compiled | Distinct bodies | Result |
| --- | ---: | ---: | --- |
| fasttable | 256 / 256 | 24 | All callbacks through fastcall table views, 4-/8-byte packs, reference/pointer fields, copies, constructors, direct/wrapped and word/pointer types. No improvement. |
| hybrid | 512 / 512 | 39 | Change prepare independently at each site; packed/reference/copy/constructor, return and alias choices. v0260 improves the reverse tail and preserves the entire prefix: 308/333 aligned, 34 differences. |
| packhelper | 1024 / 1024 | 27 | Ordinary inline packed-argument helper calls the original virtual prepare; field/reference, copy, value/reference parameter, alias, four conventions, return and sites. Best remains the old bank. |
| thiscall | 4 / 3 | 3 | Raw two-reference function-pointer conventions. Raw thiscall is refused; fastcall/stdcall/cdecl do not preserve the bank. |
| altvirtual | 256 / 256 | 15 | Virtual eight-byte fastcall view at independently selected sites; flat/nested fields, references, copy, constructor and alias. v0001 reproduces hybrid v0260 exactly without explicit table access. This is the new bank. |
| fastpair | 4096 / 4096 | 35 | One consistent virtual fastcall packed-argument interface, with four field types, result, constructor order/body/copy, pointer/reference input, alias, constness and per-site wrapper/direct choices. Best 285/333 aligned, 43 differences; loses solved prefix bytes. |

`coherent-fastpair.cpp.txt` preserves the last family's strongest body, not a
bank replacement. Complete `(mnemonic, operands)` alignment is the reported
score. The search helper's faster mnemonic-first alignment is a different
metric; fixed-offset equality is different again. Region gains cannot be
spliced together into a source recovery.

## Checks and next work

- Pulled master without recursive submodule updates and passed `check_csv.py`
  (98,068 functions, 15,856 symbols, 2,128 data at session start).
- BFME 1 stayed at verified pointer
  `42bba2ddbd5cb895d99293583891d3b7315fa49e`. The fresh update lock belonged
  to claudec2, so this seat skipped the update per runner serialization and did
  not create a freshness-success record.
- `tools/variant.py` independently reproduced the new 333-byte/34-difference
  result. Private objects only; no shared compile cache was written. This is
  still a diagnostic mismatch, not a gate refusal.
- Prior history and the vcall, source-shape, local-register and lowering
  packets were read before experimenting. The 333-byte retail extent remains
  independently established; the dump tool's longer default boundary is wrong.

Continue this body. Compare local allocation/lowering inputs for the first
test and first response with their final scheduler windows. A useful next
probe includes the state read that kills the guarded receiver, unlike p01.
Seek an evidence-backed source or type change that permits the normal-address
and inner-vtable scratch lifetimes retail shows, while preserving the solved
prefix. Use the new reverse-tail candidate and the old uniform interface as
controls; no reason was found to repeat global flag/context searches.

To reproduce, materialize the `.py.txt` helpers in a fresh `build/<directory>/`
as `.py`, `control.cpp.txt` as `base.cpp`, and `probe-p01.cpp.txt` in `probes/`
as `p01.cpp`. Generate and score each family with its named script followed
by `search.py FAMILY`; `summarize_new.py` computes complete-pair scores.
`trace.py end-probe probes/p01.cpp` traces the final passes;
`trace.py post-probe probes/p01.cpp` brackets the intermediate cleanup passes.
`trace.py end-bank` uses `base.cpp`. Each run must reach compiler termination;
verify its object's bytes against an untraced compile before interpreting it.
