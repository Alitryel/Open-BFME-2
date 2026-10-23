# FESL field replacement 0x00655B90: exact 549-byte recovery

The owner unit now compiles the complete 549-byte body with all relocations
resolved. Its escaped-field caller uses the typed three-argument function
directly. The unused void/void placeholder pin is removed. The function keeps
the bank's inherited address-derived spelling; no original EA identifier is
claimed. The bank is removed by verified `add_match`.

Identity and semantics come from the independently matched DirtySock
`Code/Libraries/Source/DirtySock/Y4TextToValue.c::Rva007EC780` at 0x006596B0,
its substantial matching control flow, retail's three-argument cdecl ABI,
the escaped-field caller and both target-owned tables. Local names are carried
from that donor, not independently recovered target facts. This optimized
FESL copy uses its own tables and unsigned field-class index. Prior evidence:
`fesl-field-replacer-655b90-20261019.md`, the volatile-tail patch and the
`local-vm-probes-20261022` handoff. Their excluded variations were reviewed
before changing source.

## Closing source graph

Start from the ordinary zero-based donor length loop with trailing increment
and the already-proven volatile separator read in the final else arm. That
control emits 549 bytes with the known EBX/EBP exchange. Instead of rotating
the length loop as the old bank did, duplicate only the final zero store:

```
if (i > 0) goto clearPositive;
pValue[i - 1] = 0;
goto clearDone;
clearPositive:
pValue[i - 1] = 0;
clearDone:;
```

This graph has identical behavior for either predicate result. C2 merges the
stores and removes the added test, but its allocation changes to retail's
value pointer in EBX, length in EBP and late EBP save. It preserves the native
undisplaced loop, padding, tail and epilogue. This is matching C++ source,
not a claim about the original spelling. Keep the labels and duplicate store.

Read-only C2 tracing confirms a real cost change. The donor control has
`pValue` priority 33 / 12 references and `i` 67 / 13. The exact graph has
37 / 13 and 77 / 15 respectively. The old rotated-loop bank with the proven
tail has 33 / 12 and 55 / 11. Allocation depends on their interactions, not
just ranking these two scalar priorities. No compiler binary, instruction,
register or data memory was patched. `priorities.json` preserves the initial
insertion records; later allocation returns are excluded.

## New trials and reproduction

| Family | Valid trials | Result |
| --- | ---: | --- |
| Eight merged regions, if/switch factorial | 513 | Control plus 512 combinations; unchanged role exchange or worse. |
| Four pointer-definition sites | 540 | Per-site masks, six predicates, if/goto/ternary and equivalent source values; no improvement. |
| Final zero/separator stores | 208 | Predicate, control form, depth and store mask; tail-0204 is exact. |
| Length-loop and declaration interactions | 384 | Sixteen loop/exit shapes, three separator forms, four declarations and two head forms; no improvement. |

The first merge generator had 128 malformed nested-marker variants, corrected
before the canonical run. The first broad final-store generator had 80
duplicate-label errors; those invalid combinations are explicitly excluded.
These were scratch generation errors, not verifier false rejects. The table
and `results.json` count only canonical, successful compiles.

Copy `search.py.txt` and `trace.py.txt` to ignored `build/655b90-mergeweights/`
without `.txt`. Recover the bank from bd584d76a3, restore the ordinary donor
loop and apply the existing volatile-else patch to create `control.cpp`.
`python3 build/655b90-mergeweights/search.py tail` reproduces the exact variant.
The trace driver imports the preceding 4404ac mergeweb `wdbg.py`. Hashes and
revisions are in `inputs.json`. Flags are the owner's `/O2 /GR- /EHsc- /GS`,
MSVC 13.10.3077 under Wine. Scratch compiles use isolated objects through
`build.compiler_command`, eight workers, whole-extent relocation-aware
comparison and explicit emitted-size checks.

## Acceptance

The normal byte gate verifies all four owner-unit function rows and all four
data rows, with no literal, float or import failures. Frozen-file and pin
consistency checks pass. This parent has no compiler-emitted EH handlers.
`link_check.py` reports LINKS, 0 -> 940 bytes against the published
2026-10-22 17:08 census: the new 549-byte body also unblocks 391 existing
matched bytes. A fresh `place_bodies.py` scan finds no additional bodies or
callee pins in this unit.
No maintained verification runner was started. BFME1 remained the clean
verified committed pointer while the other seat's fresh updater lock was held.
