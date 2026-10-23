# 0x758DE0: point interference identified; final scheduler windows captured

The bank is unchanged: **333 bytes, zero relocations, 31 positional byte
differences, 308/333 complete instruction-pair bytes aligned** (score
0.924924924924925), SHA256
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed. Continue this assignment from this packet next session.

The test and first-response virtual-call windows still differ. The reverse
window is exact in the bank, but its reverse-only fastcall pair interface is
an **unproven ABI diagnostic**, not a justified landing interface. Contact*
names and types remain structural models. These compiler observations add
no target class, donor identity or original parameter-type proof.

## Inputs and preparation

Input HEAD: `18b87a0f1763856fb57058dbe9ccd34208a2b6bc`. BFME 1 checkout and
pointer: `f890413e75e671748215ba2ef3304aa7953993e9`. The fresh update lock was
owned by codex4, so this seat skipped updating and recorded no freshness
success. Ledger check passed (98,084 functions, 15,851 symbols, 2,138 data).
The published link index was fetched; no maintainer-only runner was started.

Compiler: stock RTM c2.dll 13.10.3077, base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`,
flags `/O2 /MD /EHsc /I.`. `inputs.json` records these inputs. Retail extent
is 333 bytes, RET at 0x758F2C followed by three INT3 bytes.

Read the per-RVA history with pick-hard and the preceding
`cgd-rounds-758de0-20261023/README.md`. That packet links the already tested
control-flow, scope/lifetime, types/layout, callee/header visibility and
compiler/ABI families. Do not repeat them without new evidence. This session
also read recipes and the per-read volatility recovery for sibling 0x7586F0;
that motivated the precise occurrence-level searches below, rather than
repeating the earlier whole-field volatile sweeps.

## The point's EAX exclusion has a concrete cause

The previous packet identified H324 as a saved outer receiver but left its
causal interference unresolved. New read-only selection and allowed-set
watch traces refine that explanation. Candidate IDs, source-symbol field 7
and heap addresses are different namespaces and are pass-specific.

* Candidate word 4 (offset 0x10) receives its physical-register symbol at
  c2+0x834bd. Candidate word 8 (offset 0x20) points to its allowed-register
  set. Selection entry is +0x833f2. Registers 1/2/3/4/6/7/8 mean
  EAX/ECX/EDX/EBX/EBP/ESI/EDI here.
* The first-response point is source-symbol field 7=308, split candidate 8.
  Its allowed mask initially is 0x4E: EAX, ECX, EDX, EBP. In both inputs,
  choosing the inner receiver's ECX home clears ECX, giving 0x4A.
* In the bank, the first-response data-pointer candidate (source 7,
  candidate 9) is selected EAX without an edge to point candidate 8. The
  point subsequently receives EAX too. Their live ranges permit reuse.
* In the integer-boundary control, the corresponding data pointer (source
  8, candidate 9) has point candidate 8 among its neighbors. Selecting it
  EAX causes **0x4A -> 0x48**, clearing EAX from the point's set. The write
  is at +0x832bd; the watch stops at +0x832c0. The point then selects EDX.
* **H324 is assigned later.** It still changes the live ranges and has an
  edge to the point, but it is not the selection that clears EAX in this
  trace. Avoid treating it as the direct cause. Late watch hits after set
  storage is freed/reused are irrelevant and must not be read as exclusions.

`allocation-summary.txt` has selected rows; `*-select.json` and
`*-masks.json` retain raw records. The integer control's IR hoists the point
LEA before the data-pointer value is consumed; see the previous barriers
packet's `early-identity-ir.txt`. This explains the edge structurally.

Retail's first-response point also uses EAX, as the bank already does.
Forcing that point into EDX is therefore the wrong direction for this
window. The needed inner-vtable EAX home requires a shorter, later lifetime
after the point argument is pushed, not an overlapping EAX allocation.

## Final scheduler graph: observed, not just a static lead

The bank was traced through all 14 scheduling windows. Relevant windows 9
(test) and 11 (first response) are retained in `schedule-windows.json`, with
readable IR in `schedule-ir.txt` and graph edges in `schedule-edges.txt`.
The graph is read after +0xb550a computes priorities, before +0xb5338
selects order. Its root is at 0x108a8054; graph-node word 7 points to the IR
instruction, word 13 contains a low-half priority and high-half ordinal.
The window traversal preserves the predecessor's next link, rather than
mistaking 0x108a8050 (the first IR node) for that predecessor.

In window 11, normal/point LEAs precede the outer-source chain before final
scheduling. The inner vtable already goes to EDX. The scheduler moves both
LEAs after that chain and inner vtable load, matching the emitted bank order.
The vtable node's only outgoing edge is to prepare; there is no direct edge
from it to either argument push. Merely adding a scheduling dependency to
those pushes would not supply retail's different register lifetime.

In window 9, the inner vtable is also EDX before scheduling; normal and point
LEAs both use EAX. The scheduler additionally moves the response receiver's
reload ahead of the returned argument push. These physical roles precede
this pass. Next work should investigate their earlier allocation/call
lowering, with these graph windows as controls, rather than rediscovering
the final scheduler or attributing register changes to it.

All five retained debugger outputs completed compilation and reproduced
their untraced controls (`trace-checks.json`); no compiler state was changed.
The integer-boundary control emits 338 bytes, zero relocations, SHA256
`989f954d5365980b83059a426534f0d5310eec83e0bfc6d91cc46ba500e32a87`.

## New searches: do not repeat unchanged

All **11,698 variants compiled successfully with zero relocations**, using
eight private-object workers. None improved a complete instruction-pair
region or the full bank. `summary.json` retains regional winners; use its
pair_sum rather than search.py's different mnemonic-first metric.

| Family | Compiled | Distinct bodies | Choices |
| --- | ---: | ---: | --- |
| reads | 1,458 | 648 | Six callback receiver occurrences independently ordinary, volatile-qualified data-pointer read, or volatile-qualified source-pointer read; bank/ordinary-thiscall controls. |
| checks | 2,048 | 78 | Independent data/source read qualifiers at four null checks, plus two state reads; both controls. |
| recombine | 8,192 | 289 | Twelve bits combining four null-check source reads, two state reads, four test/first-response receiver source reads and two inner data reads; both controls. |

Reads/checks v0000 and recombine v2048 reproduce the best bank. Some other
variants tie 308 aligned bytes but have more positional differences; no
regional winner needs recombining. Existing-read qualification can change
code generation but this tested family does not repair these windows.

The retained generators and scorer are reproducible scratch tools. Copy
their `.py.txt` files to `build/cgd-interference-20261023/*.py`, likewise
bank.cpp.txt and identity.cpp.txt; run generators then `search.py FAMILY`
and `regions.py reads checks recombine`. For compiler traces, use
`select.py bank`, `masks.py bank`, or `schedule.py bank` (identity is valid
for the first two). No shared match-cache objects are written.

Independent `tools/variant.py` compilation reconfirmed 333 bytes / 31
differences, first at +0x94. The ordinary thiscall control remains available
in the preceding rounds packet. No missing-function prerequisite or
justified blocked-on RVA was identified. Keep the bank; investigate the
earlier lifetime and lowering that let retail share EAX between point and
the first-response inner vtable, and EDX between normal and test vtable.
