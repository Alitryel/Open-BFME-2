# 0x758DE0: asymmetric vector types and aggregate layouts were inert

The best bank remains **333 bytes, zero relocations, 31 positional byte
differences, 308/333 complete instruction-pair bytes aligned**, score
0.924924924924925. Its emitted SHA256 is
`01e69aef7e003a734f1bc04dc4faf28fd44f3c0d6757d8db6f5fb935382ab90e`.
No body landed. This packet adds negative evidence, not recovered C++ bytes.

Continue the same assignment next session. Read the preceding
[`cgd-interference-758de0-20261023/README.md`](../cgd-interference-758de0-20261023/README.md)
for the allocator watches, final scheduler graph and earlier ruled-out
families. The point already has retail's EAX home in the first-response
window; forcing it to EDX is the wrong direction. The inner-vtable load
needs a later lifetime and different register. That mismatch exists before
the final scheduler.

The reverse-only fastcall pair in the best bank remains an **unproven ABI
diagnostic**. The uniform thiscall control is retained separately. Contact*
names, storage models and callback signatures are structural experiments;
these results establish no target type, class identity or original ABI.

## Inputs and preparation

Input HEAD: `5485a303c7` (full revision in `inputs.json`). BFME 1 pointer and
checkout: `f890413e75e671748215ba2ef3304aa7953993e9`. A fresh update lock
owned by codex4 was present, so this seat skipped the update and recorded no
freshness success. Ledger check passed: 98,087 functions, 15,851 symbols,
2,138 data. The published link index was fetched; no maintainer-only runner
was started. AGENTS.md, the per-RVA history and relevant recipes were read.

Compiler: stock RTM c2.dll 13.10.3077, base 0x10700000, SHA256
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Flags: `/O2 /MD /EHsc /I.`. Retail extent: 333 bytes, RET at 0x758F2C and
three following INT3 bytes. All experiments used private scratch objects,
not the shared match cache. Nothing under Code/ or in the ledger changed.

## New hypotheses tested

All **6,468 variants compiled successfully with zero relocations**. Each
family emitted exactly the same four control bodies. No full-body or
complete instruction-pair region improved. These observations rule out the
listed source changes for these inputs; they do not prove which compiler
pass erased their distinctions.

| Family | Variants | Independent choices |
| --- | ---: | --- |
| vectors | 1,024 | Point and normal each independently use one of eight storage/type models; declaration order, typed callback-info return, reverse ABI control and first-response bridge. |
| selfstores | 2,916 | Six callback receiver occurrences independently use an ordinary read, an identity store to the source pointer, or an identity store to the data pointer; both ABI and bridge controls. |
| assumptions | 2,048 | Nine independently enabled facts already established at their original program points; both ABI and bridge controls. |
| layouts | 480 | Four data-pointer arrangements, five geometry arrangements, three state arrangements, optional header base, both ABI and bridge controls. |

Vector models were: the original common typedef, a distinct class with the
same fields, a base containing the fields, an xyz/array union, per-component
float/integer unions, an empty tag base, a role-template base, and an empty
destructor. Copy and negation stayed field-wise. Point and normal models
were varied independently and propagated through prepare, bridge and the
diagnostic pair, rather than changing both vectors together. The typed
callback-info return was also propagated through test/respond. A preliminary
generator with incomplete alternate-prepare type propagation was corrected;
only the final 1,024 successful cases are counted here.

Identity stores preserve the pointer values at the six call occurrences.
For the inner first-response bridge, its data argument carries the selected
identity store before the unchanged helper. These are diagnostic source
forms, not proposed production writes.

The nine assumptions concern: the current node after the nonnull loop;
the saved node after its guard; each source after the initial null guard;
state being neither zero nor two after the state-two filter; the point and
normal member addresses; and both sources after the reverse null guard.
They add no new facts about callback side effects.

Aggregate layouts used named members, arrays, nested structs and an
anonymous named/array union for the data pointers; named, array or nested
state words; named vectors, a vector array, nested geometry, separate
header/geometry bases, or position/direction bases inside geometry. Each
node had a compile-time 52-byte extent check. All emitted bodies reproduced
the control access offsets. The separate geometry-base case necessarily
uses a header base, so two header-bit settings duplicate that case.

## Results and independent checks

`summary.json` records the four outputs per family, hashes and regional
scores. Regions use retail offsets `[0,148,170,190,225,310,320,333]`.
`regions.py` aligns complete `(mnemonic, operand)` pairs; use its `pair_sum`,
not search.py's separate mnemonic-first diagnostic metric.

The four controls are:

| Reverse interface | First response | Size | Positional differences | Pair bytes aligned |
| --- | --- | ---: | ---: | ---: |
| Uniform thiscall | Direct | 333 | 41 | 302 |
| Uniform thiscall | Data bridge | 335 | 76 | 256 |
| Diagnostic fastcall pair | Direct | 333 | 34 | 308 |
| Diagnostic fastcall pair | Data bridge (bank) | 333 | 31 | 308 |

All families' regional maxima equal the bank's
`[148,13,20,19,85,10,13]`. There is no region winner to recombine.
Independent `tools/variant.py` compiles confirmed the bank and uniform
control; `independent-checks.json` records full object-body hashes. Cleaning
duplicate bank metadata comments also reproduced the bank. Neither output
is exact, so no add_match or production build claim was made.

## Reproduction and next work

Copy the retained `.txt` files to a new directory immediately under build/,
dropping only the final `.txt`. Name the bank copy `bank.cpp`. Run each of
`vectors.py`, `selfstores.py`, `assumptions.py`, `layouts.py`, followed by
`search.py <family>`, then:

```sh
python3 build/<scratch>/regions.py vectors selfstores assumptions layouts
python3 tools/variant.py build/<scratch>/bank.cpp bfmeTwoCGD 0x758de0 333
python3 tools/variant.py build/<scratch>/uniform-control.cpp bfmeTwoCGD 0x758de0 333
```

The search driver uses eight private-object workers. Bulk generated sources
and objects are scratch only; the generators and compact results suffice
to resume. The bank's duplicate metadata comments were removed, with no
body change.

Do not repeat these four families without a new causal finding. The next
useful question remains the earlier call representation or lowering rule
that can postpone the inner-vtable load until the argument's EAX lifetime
ends. Use the prior packet's allocator and scheduler controls to distinguish
that from another inert type or pointer spelling. The saved pre-lowering IR
decoder needs care: high-level operands can be linked lists, and its fields
do not all have their post-lowering meanings. This session obtained no new
causal result from those dumps. No missing-callee prerequisite was found.
