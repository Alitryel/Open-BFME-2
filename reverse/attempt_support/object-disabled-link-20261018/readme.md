# Separate donor Object disabled queries from the native copy

Published index: 2d2ca9cd35, 2026-10-18 18:45, retail-truth-2. The paired
12-source local predictions go from 0 to 6,290 non-padding linked bytes:
ObjectStatusQueries 16; ControlBarRappellerCount 4,725; AreaSpecialPowersAtLocation
780; PlayerUpgradeSpecialPowerDoSpecialPower 197; SplitHordeSpecialPowerRva004C861E
133; CashHackSpecialPowerAction 439. The other six units retain unrelated blockers.
These are legacy local predictions, with strict reusable receipts prepared for
the eight affected providers, not a closed-strict census or full link result.
No authored C++ coverage is added and no census/status file is changed.

Target evidence: rowed Object::isDisabled at 0x0023D394 is the complete 11-byte
`add ecx,0x1C8; jmp BitFlags<11>::any` body. ControlBarRappellerCount already emits
that exact inline copy and its native getCommandAvailability caller uses it.
Its byte gate verifies both the row and call relationship. ObjectStatusQueries
emitted a conflicting strong copy. Rehome this row to the existing inline copy
and remove the strong definition, retaining the two other status-query bodies.
Trying an unused inline definition in ObjectStatusQueries first removed the
symbol; that failed trial is not retained.

Donor evidence: five ZH-view units emit an incompatible +0x130 word test
(digest 1284fd3df7b2), and OCLSpecialPower uses the BFME1 +0x1A4 test
(c888951d6e6b). Their private donor layouts are not target layout facts. Give each
unit's donor query a separate member name, including its unrecovered callers,
rather than allow those bodies to own the native symbol. helper-bytes.txt proves
the renamed bodies have precisely the original census digests. All matched
bodies remain exact. No header/layout, pin, alias, import or verifier change.

Acceptance: normal gate 30/30 across seven changed sources, native row rehome
9/9, strict receipt preparation 39/39 across eight providers; 5 string literals,
3 floats and import checks exact. EH 1 EXACT; data enforcement zero findings;
converged data 9 addresses, zero second names/unjudged; declared-unmatched check
passes. The first converged probe overlapped strict object preparation and found
one temporarily absent receipt; the final sequential probe passes.

BFME1 linking repair review: official origin/master a18d9ed5; checked donor
67f4eab2 (getTemplateBfme) and 5aace43d (Shell immediate-pop donor removal).
Separating an incompatible donor member follows that supported repair pattern,
while offsets, identity and full bytes above are independently BFME2 evidence.
The verified gitlink stays 64d369b9: the existing PrimaryBase DIR32 update blocker
is documented in ../bfme1-freshness-20261018/readme.md.
