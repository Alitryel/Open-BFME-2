# Allocator report, snapshot and formatter ownership repair

Base `930dcce6263119884147dbe00e342836ff6bcefe`; BFME1 pin
`4483e88da1c2f3b9a273f779baac7458bd8bb891`. Agent attribution:
`Codex(runtime-model-not-exposed)`.

Four source-local ABI corrections bind existing native calls to their real
source owners. No body, flags, shared header, verifier or baseline changes.
The general allocator snapshot member takes block types, bool copy, storage
pointer and unsigned size. The report member uses the same bool/storage/size
contract as its existing memory_pool caller. Debug wrappers forward through
their actual GeneralAllocator base; the trace wrapper returns void because
the trace callee has no defined result. The formatter wrapper forwards
(block−8, destination, length) to the actual 31430 owner, removing the stale
pointer/length overload. Native parameter order and call instructions remain
unchanged.

## Measured result

- Four owner names corrected; five pins retired (three stale placeholders,
  two redundant pins for recovered owners). No new alias or pin.
- Five unresolved symbol edges removed in the paired current-object graph:
  9 before, 4 after. These correspond to six direct native call sites.
- All 56 owned rows across five units preserve all 10,546 fully resolved
  bytes. Four EH graphs are EXACT before and after. The source-only
  declaration control and snapshot provider both remain link-clean.
- Zero new coverage bytes and zero whole-unit linking gain. Remaining
  unresolved references are 33150, the lower freeBlock spelling in two units,
  and 32050. No attempt is made to hide or reclassify this remaining debt.
- Focused placement scan of all five units: zero bodies and zero pins.

| Native call site | Callee | Repaired source binding |
| --- | --- | --- |
| 35485 | 34D10 | Trace uses real GeneralAllocator snapshot member |
| 3556A | 34D10 | Report uses real snapshot member and bool/storage contract |
| 6C3802 | 353F0 | Debug trace wrapper uses real void trace member |
| 6C3832 | 34D10 | Debug snapshot wrapper uses real typed snapshot member |
| 3094F | 35540 | Existing memory_pool caller finds the corrected report owner |
| 32810 | 31430 | Formatter wrapper calls actual destination/length owner |

## Identity and regression evidence

`native-windows.json` preserves independently decoded native call windows,
boolean-byte use and return instructions; `native-contracts.json` records
prior-attempt exclusions and source identities. Snapshot's bool copy is
read as a byte, report callbacks return bool in AL, wrappers preserve ECX
and positional arguments, and the formatter preserves its result and RET12.
The native report and snapshot contracts agree with existing recovered
providers; address-derived method names remain address-derived.

`paired.json` freezes all five actual before/after object hashes, row names,
full relocated native byte hashes, named definition deltas, and provider
choices. Both phases refresh all five objects against the same authenticated
published index (SHA256
`3ea1a1da9f47a4ee9770a85b313d75a682b944cc3c01bf88dbfe3c803e81c80e`).
The index predates this checkout, so its old consumer verdicts are not credited.
Baseline resolution uses the exact base ledgers, including the retired pins;
after resolution uses the edited ledgers. No stale symbol is restored in
production. Frozen COFFs and dependency receipts remain in the writer's
`build/batch4-allocator-ownership/{before,after}` for independent replay.

`caller-audit.json` records repository-wide exact mangled-name searches and
current Code identifier uses. The seven genuinely lost call-target names
are also checked by the normal `name_dependents.py --staged` scan of 23,434
units. Its initial conservative fallback named Rva006C2D20Describe.cpp,
whose source already calls the real formatter. Gating that unchanged unit
passed 3/3 rows and one EXACT EH graph; the subsequent scan reports zero
remaining referencing units. Thus there are no unowned callers relying on
the retired spellings. Redundant canonical pin names still resolve through
their actual owner rows.

`prepare-current.txt` records strict reusable receipts for the five providers.
`before-build.txt`, `after-build.txt`, EH reports and the dependent gate record
normal verification. Source hashes and frozen object hashes are in
`manifest.json`. The only named-definition changes are the four intentional
owner renames; all other retained owner code is exact. No full census or
verification runner was launched by this writer.

The fresh BFME1 reference scan at pin4483 and this ledger found zero free
placements, with empty ranked/near queues. No new donor allocator body is
claimed. 33150 remains excluded: prior exact code required unsupported
assume, and the later fence-free candidate remains 375 bytes with 31 real
differences. This repair closes proven identity prerequisites only.
