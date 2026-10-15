# Production and AI list-comparison ownership, 2026-10-15

ProductionUpdateQueue and AIPlayerTeamBuild now compare typed STLport list
iterators through TU-local overloads, following GameClientXfer. Each stops
emitting one unused, incompatible external base-iterator comparison. Existing
game bodies, data bindings, compiler flags, ledger rows and pins are unchanged.

## Controlled evidence

Base checkout 92d374989bdc33c4918a7a7c194cc4463ad50cbd. Both preview phases
use deep copies of the same runner index, updated in memory with only the two
strictly prepared consumer objects. context.json records the index hash and
its update commit 19a2565407 (2026-10-15 09:33), whose underlying census is
5986a99448 (04:52). The committed status queue measures 28269d8e8d and served
selection only; it is not paired with these results. No census/index/status
was rewritten. The published object store was fetched; the newer runner index
was retained.

| Consumer | Existing authored bytes | Legacy findings | Identical retained COMDATs |
| --- | ---: | ---: | ---: |
| ProductionUpdateQueue.cpp | 7,749 | 9 -> 8 | 692 |
| AIPlayerTeamBuild.cpp | 9,097 | 22 -> 21 | 187 |

The only removed finding in each is
`??9_List_iterator_base@_STL@@QBE_NABU01@@Z`. Legacy LINKED remains 0 -> 0
across 16,846 existing authored bytes (link_check excludes 0xCC). New authored
C++ bytes are zero. No self-strict, closed-strict, census or executable-link
gain is claimed. Strict receipts establish consumer currency, not provider
closure. No maintainer-only runner was used.

object-proof.json establishes that all 879 retained COMDATs have identical
bytes and normalized relocation digests. All other nondebug sections,
external bindings and directives are identical. Each original comparison is
18 bytes; Production emits one private 12-byte comparison and AI emits two.
Neither the removed helpers nor their replacements has a nondebug caller
relocation. Thus this repair removes conflicting incidental emissions while
preserving existing code and data. Saved source/object/receipt snapshots stay
in ignored build/production-iterator-link-20261015; proof scripts expect them
and the recorded runner index. Scripts are evidence, not gate replacements.

## Acceptance and diagnostic limits

- Strict preparation before and after, plus explicit ./build.sh: 65/65 rows
  match. 41 strings, seven empty-string references and 12 float literals pass;
  no baselined/skipped strings. Both objects have strict reusable receipts.
- EH: all 16 EH-bearing rows EXACT; zero baseline or missing-object cases.
- New-variant admission, converged-data (eight addresses, no second names or
  unjudged rows), class and declared-definition checks pass.
- Local link_check exits 1 for remaining findings. Paired link-proof proves
  exactly the two removals above, with all other local results identical.
- Data --enforce reports one pre-existing wrong-name diagnostic for the
  compiler-owned static guard `?$S1@?7??rva0049DEC8@ProductionUpdate@@UAEXXZ@4IA`
  at 0x00A03B58. diagnostic-proof.json proves identical original/current
  findings from the saved object. This check is not reported as passing.
  No baseline or global declaration was changed.
- The unmodified shadow identity gate has 17 original diagnostics and 15
  current ones; two stale literal funclet-label findings disappear after
  renumbering. There is no diagnostic growth. This is not credited as an
  identity repair; exact EH and object evidence establishes preservation.
- Placement resweeps serve zero new bodies or pins. check_csv and whitespace
  checks pass. Normal commit/push hooks remain required.

## Remaining blockers and donor review

Production still needs UpgradeTemplate::rva0026EF50, Rva0037EE4C::rva0037E815,
Object::setDisabledUntil and Rva000BB710::xfer providers, plus Drawable-list
construction/destruction/insertion reconciliation. AI still needs TeamInQueue
lifecycle/query providers, queueSupplyTruck, ScriptEngine helpers, TeamPrototype
and BuildListInfo providers; its other getters and TeamPrototype-list helpers
remain competing definitions. These need separate target evidence.

The dedicated pass started with repair_queue.py link and link_rank.py.
BFME1 de59a7e9f891b3ed2d4221d151ca881f4b75a583 was reviewed: its Apt helper
unification supports consistent incidental helper ownership, while its Apt
implementation and layouts are inapplicable here. Target STLport node access,
existing BFME2 sibling repairs and controlled target-object/retail checks
support this adaptation; no donor layout or address is imported.

Official BFME1 master was fetched to 9bbab7963c3dac0ef8da8c46860e972ecbafe29d.
The clean verified checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d is
retained: another worker owns its update and the preceding full old/new input
comparison remains blocked on dependency inputs/stalled old-input compilation.
No pointer advancement or freshness success stamp; no unchanged full retry.
