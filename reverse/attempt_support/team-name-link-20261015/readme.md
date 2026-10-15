# Team script-name getter link repair, 2026-10-15

Remove three competing, unused getter COMDATs from two existing private views:
Team::getName and TeamPrototype::getName in TeamUpdateState.cpp, and
TeamPrototype::getName in TeamCtor.cpp. Read the existing prototype name field
at the same call sites. Team::updateState retains the original null-prototype
fallback to AsciiString::TheEmptyString at all five script dispatches. Friendship
allows the update member to read the already-declared private prototype field.
No class layout, ledger row, pin, alias, shared header or compiler flag changed.

Target evidence: the complete updateState row at 0039F0E3/1163 directly forms
prototype+0x10 at 0039F165, 0039F400, 0039F416, 0039F4B8 and 0039F548, with
null paths using the existing empty string at VA 00DE0878. The complete Team
constructor row directly forms prototype+0x10 at 003A3B01. target-reads.json
records owner rows, full retail hashes and surrounding instructions. Existing
recovery records and ZH semantics supply the Team/prototype/name identities;
this repair independently verifies the field access and complete behavior.
It does not establish a retail address for either standalone getter.

## Paired local verification

The unchanged runner index measures commit 28269d8e8d, 2026-10-15 09:31 UTC;
SHA256 6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
Baseline sources are at e05e610d0b2837acf7a02ca525f5342628f5a12e. Both original
strictly receipted objects were substituted together into an in-memory copy of
that census, then compared with both repaired strictly receipted objects.

| Consumer | Legacy findings before | After | Retained COMDATs unchanged |
| --- | ---: | ---: | ---: |
| TeamUpdateState.cpp | 2 | 0 | 34 |
| TeamCtor.cpp | 4 | 3 | 61 |

Exactly the getter bodies are removed: 17 and four bytes from the update unit,
and four bytes from the constructor. All 95 retained external COMDAT bodies,
extents and relocation digests are identical. Strong, undefined and weak symbol
sets are identical (symbol table ordering changes). object-proof.json records
source/object hashes, removed bodies, retained digests, paired findings and all
other census getter copies. The on-disk index/status were not rewritten.

Ordinary link_check.py predicts TeamUpdateState becoming clean, **0 -> 1,158
existing authored linked bytes**, excluding padding. The constructor's 471
existing bytes remain blocked by unresolved Team::crc, a non-retail STLport
Rb_tree destructor and the selected non-retail Rva003A393A constructor.
The summed findings improve 6 -> 3 without new findings.

This is a legacy local link preview with strict compiler/byte currency checks.
No self-strict placement, closed-strict linkage, committed census gain or full
link-cycle result is claimed. The changed consumers neither define nor reference
the removed getters and introduce no provider dependency. Authored C++ byte
coverage grows by zero. Maintainer/runner broader linkage measurement remains
outstanding.

## Acceptance

- link_check.py --prepare-current before and after: eight matched rows across
  both explicit claimed sources, strict reusable receipts, no census expansion.
- Independent ./build.sh: 8/8 exact rows, two string literals and one compiler
  float verified; no skipped or baselined literal and no named import.
- EH verification: 2/2 EXACT, no nonexact/baselined/missing objects. Existing
  constructor funclet labels renumber; their parent EH graph proves unchanged
  retail placement without pins or ledger edits.
- Local paired proof and ordinary link_check.py as above; --new-variants accepts.
- Frozen-file, class, whitespace and check_csv checks pass. Shadow data: zero
  findings; converged data: eight addresses, zero second names/unjudged rows.
- Read-only placement rescans of both units find zero additional bodies or pins.

## Donor review, ownership and outstanding work

Reuse the dedicated BFME1 linking review of repair
 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (also inspected this session): suppress
surplus competing COMDAT emission where target bytes permit it. Its constructor
identity, wrapper, pin and alias scaffold are inapplicable; none was imported.
The clean verified BFME1 gitlink/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
1c4d808dd6a0f2bd514f607f40e9e422db3ab91b. The live foreign pointer claim
(codex-6bc6-20261008) and outstanding comparative full-byte verification keep
freshness advancement outside this seat. No donor input or success stamp changed.

Discovery used repair_queue.py link and link_rank.py help/top/near, followed by
current-object checks. The published-index fetch retained the identical local
index and restored available compiled objects. The same-getter blocker sweep
found only these two affected consumers. Both file claims preceded edits;
original sources/objects and the proof script remain under ignored
build/team-name-link-20261015. No full link cycle, census build/measure/history,
nightly, boot or scheduler operation was started.

## Identity shadow limits

The commit hook reports three shadow identity findings. A paired scan in the
same current identity universe (identity-debt.json) confirms the parent's
AsciiString destructor binding at 0x00036410 already existed, and both consumers'
Snapshot destructor bodies are unchanged; the universe still has two divergent
Snapshot variants. The additional raw-label finding is for $L6269 after compiler
label renumbering: the raw identity scan selects an unrelated funclet by its
label. Parent EH verification resolves the actual ledger funclet to retail and
is EXACT. This records the shadow discrepancy without changing the checker,
adding a baseline, or claiming identity debt was repaired.
