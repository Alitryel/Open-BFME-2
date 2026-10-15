# Banner singleton ownership repair, 2026-10-15

Ten consumers now reference one `BannerUI *TheBannerUI` owner at RVA
0x009FE32C, replacing two undefined address-based names with different pointee
types. BannerUI.cpp defines the four-byte zero-initialized pointer. The parser
casts that canonical pointer to its existing table view; layouts and function
bodies are otherwise preserved. This does not reconcile private BannerUI class
views or claim recovery of the original retail variable spelling.

Target evidence in native.json establishes the singleton's role independently
of donor source: within the proven InGameUI::init boundary 0x0029E2DE..0x0029E656,
call 0x0029E613 constructs BannerUI at 0x00217211; store 0x0029E620 places its
result in VA 0x00DFE32C before virtual initialization. The constructor pushes the
retail string `TheBannerUI` at 0x00217277. The slot is four loader-zero bytes.
The descriptive name follows that target subsystem string. Existing parser
accesses establish the +0x0C table view; no new layout is inferred here.

## Controlled local link evidence

Base commit 861c21b790558ba81dad2b4004128260ed475936. Both phases use copies of
one frozen runner index, refreshed in memory with only these ten strictly
prepared objects. context.json records its SHA256 and proof.json records the
measurement: index update 19a2565407, 2026-10-15 09:33, census 5986a99448 at
04:52. The committed link-status queue (28269d8e8d) served selection only.
No index, census or link-status artifact was rewritten.

| Consumer | Legacy findings before -> after |
| --- | ---: |
| Rva0052A295BannerSteps.cpp | 3 -> 2 |
| InGameUIDtor.cpp | 17 -> 16 |
| StrategicInGameUIDynamicAutoResolvePlayerPanel.cpp | 3 -> 2 |
| InGameUIMessages.cpp | 4 -> 3 |
| InGameUIUpdate.cpp | 3 -> 2 |
| InGameUIReset.cpp | 4 -> 3 |
| ControlBarVisibility.cpp | 3 -> 2 |
| AptInGameSpellBookInterface.cpp | 1 -> 0 |
| BannerUI.cpp | 6 -> 5 |
| Rva0052A470Dtor.cpp | 2 -> 1 |

Exactly ten unresolved bindings disappear, with every other finding identical.
The spell-book unit changes from zero to 2,143 existing authored LINKED bytes
under the legacy local preview. New authored C++ bytes are zero. No self-strict,
closed-strict, full census or executable-link gain is claimed. Strict receipts
prove current objects; the provider's remaining dependencies prevent a claim of
provider closure.

proof.py compares every nondebug section, relocation, external binding and linker
directive. After mapping the two old names to the canonical name, all consumers
are identical. The provider adds only one four-byte .bss allocation and changes
that symbol from undefined to defined. Local labels are compared by actual
section and offset. Original sources/objects/receipts and after objects remain in
ignored build/banner-ui-owner-link-20261015; replay needs these snapshots and the
recorded frozen index. These scripts record evidence, not alternative gates.

## Acceptance and limits

- Strict preparation: before 148/148 code rows and seven data rows; after
  148/148 and eight data rows, ten reusable strict receipts. Explicit build.sh
  verifies the same affected sources. Literal checks: 36 strings, 11 empty
  references, 24 floating literals, 12 imports; zero baselined/skipped.
- EH verification: 29 rows EXACT, zero baseline or missing-object cases. The
  normal byte gate resolves 67 pre-existing renumbered funclet labels through
  proven parent EH data and verifies one complete STLport constructor fold.
- New-variant admission, class and declared-definition checks pass.
  Converged-data enforcement passes eight protected addresses without second
  names or unjudged rows. Placement resweep finds zero bodies and zero pins.
- Local link_check exits 1 because nine units retain independent findings.
  Explicit preparation and the bounded preview refresh only the ten relevant
  objects; no global refresh/census was run.
- Shadow identity diagnostics remain 31 -> 31. Paired data diagnostics improve
  5 -> 4: only the obsolete parser-view name disappears. data_check --enforce
  still reports four pre-existing wrong-name findings: _g_pRva00224BC9 at
  0x009FE4CC; military-subtitle guard/click at 0x009FEEA8/0x009FEE20; update guard
  at 0x009FEEDC. No baseline or checker was changed.
- data_ledger.py generated a scratch ledger; only its exact row at 0x009FE32C
  was selected into the tracked ledger. ledger-generation.json records the
  command, hashes and discovery warning (130 unrelated missing objects). All
  ten relevant objects are strictly current. The row now has one owner,
  one definition and 17 references. No unrelated generated drift was adopted.
- check_csv passes: 91,234 functions, 15,500 pins, 437 data rows. Source line
  endings are preserved; whitespace checking with CR-at-EOL awareness passes.
  Normal commit/publication hooks are required.

## Remaining blockers and reference review

The provider still needs vector-base and Rva00056F61 constructors, FieldParse
0x00BE5A50 and the region-manager battle getter; its vector constructor also
conflicts with the first copy. Other consumers retain unrelated lifecycle/global
and COMDAT/selected-definition debt. Full names are in proof.json/link-final.txt.
No maintainer-only full link cycle, nightly or boot runner was started.

repair_queue.py link and link_rank.py selected this live shared binding issue.
BFME1 donor commits 92a8d854746f059994f8ab370c133f3ba71eec24 (declare the
verified owner and cast to a view) and 3d83042a6cabae08e002a9f5a88c1c60f55a51d3
(IME singleton identity) were reviewed. Their dependency repair method is
applicable; BFME2 target stores, relocations and object comparisons prove this
adaptation. No donor address, layout or original-name claim was imported.

Official BFME1 master was fetched to 7a8811f5d62de60f920d817a0017c88170f69410.
The verified clean checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d
is retained. Another worker holds the submodule update claim; the prior full
old/new-input comparison remains blocked on dependency inputs/stalled old-input
compilation. No successful freshness stamp or pointer update was recorded.
