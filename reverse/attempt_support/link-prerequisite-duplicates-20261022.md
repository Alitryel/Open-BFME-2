# Production prerequisite duplicate repair, 2026-10-22

Parent: 59661c1b1e. BFME 1 donor pointer remains 37c3022de1ab944c7ffe536440d637dc8199091c.

## Result

The current ProductionPrerequisite.cpp retained the ZH definition of
addUnitPrereq(AsciiString, bool), even though the verified BFME 2 definition
already belongs to Common/Thing/ProductionPrerequisiteAddUnitPrereq.cpp.
Both current objects defined the same strong symbol, blocking both units.
Remove the unverified definition and its present-unmatched marker. Keep the
rowed vector<PrereqUnitRec>::push_back instantiation by taking its member
address in init(), where the private nested record is accessible. This
address is unused and adds no runtime operation. No class layout, call pin,
header, ledger row or verification rule changes.

The two explicit current-source previews use the same published index
(2026-10-22 11:05, ae3b3e68e2) and the same pair of units:

| Unit | Before | After |
| --- | ---: | ---: |
| Common/RTS/ProductionPrerequisite.cpp | 0 | 0 |
| Common/Thing/ProductionPrerequisiteAddUnitPrereq.cpp | 0 | 185 |
| Total retail bytes linking | 0 | 185 |

These are legacy preview results with current paired objects, not a new census
or closed-strict gain. The edited provider has a strict reusable object receipt
from link_check.py --prepare-current. ProductionPrerequisite.cpp retains
independent AsciiString/allocator unresolved and COMDAT blockers; no gain is
claimed for its own rows.

## Checks

- ./build.sh on the edited unit: 6/6 rows exact; literal, float and import gates pass.
- link_check.py --prepare-current on the edited unit: 1 strict provider receipt,
  6/6 exact, census/index/status unchanged.
- find_declared_unmatched: all definitions accounted for; only init remains
  honestly marked present-unmatched.
- class_gate.py and check_csv.py pass.
- eh_verify.py: edited unit has no EH-bearing rows.
- The unchanged overload owner passes ./build.sh (5/5 exact) and EH verification
  (one exact EH-bearing row).
- Before/after logs: build/seat-prereq-duplicate-before.log and
  build/seat-prereq-duplicate-after.log; byte/receipt logs:
  build/seat-prereq-removal-build3.log and build/seat-prereq-object-strict.log.

MSVC 7.1 refuses namespace-scope explicit instantiation naming the private
record. A private/public header adaptation changes private member mangling and
was discarded. Taking the member address inside init retains all six original
rows without either issue.

## Other session handoff

The two preceding repairs add 1,744 B (numeric scanner users) and 4,145 B
(selection bucket helpers), for 6,074 B across three paired previews. They also
have strict object receipts, but no closed-strict link claim. Their evidence is
link-num-get-20261022.md and link-selection-buckets-20261022.md.

Current-source pairing shows many census-ranked blockers already repaired on
master (AIBuilder, AAB tree, GameSpy callbacks, CreateAHero duplicate global,
control-bar destructor, allocator insert, PlayerCloneFrom and several STL
providers). Do not count those as new gains or replay their old fixes.

Wide basic_ios::imbue still fails on its nonretail string copy-assignment copy.
Two inline-only trials were reverted: spelling the vendor assign call adds a
five-byte tag initialization; an uninitialized tag removes those bytes but
changes stack slots and argument scheduling. Its original byte-exact source
was restored and its claim released. The attempt log records this blocker.

The selection-adjacent string hashtable helper has a deeper identity error:
its pin names a string bucket helper, but retail's 0x51B89 hashes a pointed-to
field at +8. Suppressing that helper without reconciling the container identity
would hide the problem. Strategic battle-prompt callbacks likewise need ctor/
property ABI identities reconciled. Both are logged; no source edits remain.

BFME 1 upstream was fetched at 42bba2ddbd5cb895d99293583891d3b7315fa49e.
The verified pointer was not advanced: full comparison needs 7,758 stale
objects, and another worker holds the reference file claim. No successful
freshness timestamp was written. Donor link-repair review and prior baseline
attempts are documented in link-num-get-20261022.md.
