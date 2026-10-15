# Team-name cache link repair

At BFME 2 base `99650b403219a0d8030f5a8aa8a3b49d987b24b9`, bind
GameLogicInit.cpp's teamName and teamOwner accesses to their existing
`const StaticNameKey` owners, instantiated by WorldHeightMap.cpp through
Common/WellKnownKeys.h. The old Rva00148F5ECache declarations produced different,
unresolved C++ data names. Keep the established accessor view and its direct
calls at all six sites so argument evaluation and code generation stay intact.
The provider, headers, compiler flags, pins, aliases, function/data rows,
baselines and census files are unchanged. The sibling consumer sweep finds
these two keys already declared as const StaticNameKey in every other Code TU.

## Evidence and provenance

Target retail data at RVAs `0x009BD9F4` and `0x009BD9FC` each contains a zero
key followed by a pointer to the complete `teamName` or `teamOwner` string.
Their string VAs are `0x00C08A54` and `0x00C08A60`. The unique canonical
provider has the same eight-byte initializer and DIR32 string relocation at +4.
`proof.json` records the full initializer/string checks, unique indexed owner,
and six native DIR32 operands: two each in rva0023E0C7, CreateMPPlayers and
CreateWOTRMPPlayers. All three complete function bodies remain exact.

The key spellings and StaticNameKey contract are donor-derived rather than
asserted BFME 2 debug symbols. Reviewed BFME 1's existing-provider binding repair
`d003077f0b7ce97622adb7a53f1fe76653433c5c`, the retained verified pointer
`a7c38d3b2597121f178ab5190b3062478823257d`, and its WellKnownKeys.h and
NameKeyGenerator.h declarations. This supplies an ownership pattern; BFME 2's
addresses, initializers and consumer operands are verified independently here.
No BFME 1 code, address or layout change is imported. The already-landed
playerName repair in this checkout uses the same provider and accessor pattern.

## Acceptance and measured improvement

- Before and after: bounded `link_check.py --prepare-current` accepts both
  sources with strict reusable compiler receipts and normal byte gates.
  **87/87 function rows**, four existing data rows, 69 string literals plus
  ten empty-string references, five float references and nine named imports
  pass. The edited GameLogic unit independently passes 80/80 rows.
- All nondebug sections, instructions, EH bytes, data and symbolic relocations
  remain identical after normalizing only the two changed external data names.
  Normalized external bindings are identical; provider object is byte-for-byte
  unchanged. EH verification is **28/28 EXACT**, no baseline exceptions or
  missing objects. New COMDAT variants check passes.
- Shadow data identity findings decrease **10 -> 8**, removing both team-key
  wrong-name findings. The eight unrelated findings remain in after-data_check.
  Enforced converged-data audit: two sources, eight protected addresses,
  zero second names and zero unjudged rows.
- Paired legacy local link projection uses the same census index measurement
  `ac77c85054`, dated 2026-10-15 14:25, with strictly current touched objects.
  GameLogic unresolved names decrease **60 -> 58**; its duplicate (2), COMDAT
  (19) and selected-provider (9) findings are unchanged. Every provider finding
  is unchanged. The index SHA256 and complete paired results are in proof.json.
  Both units still do not link: existing local linked bytes remain **0 -> 0**.
- Placement rescan reports zero bodies and zero pins. Frozen-file,
  class, pin-consistency, CSV and whitespace checks pass.

Verified improvement: two unresolved data names and two wrong-name findings
removed. **Zero new authored C++ bytes and zero incremental legacy linked
bytes.** Strict self receipts do not prove closed-strict closure. No
closed-strict gain, new data ownership, actual data-back placement or executable
link result is claimed. No maintainer-only verification runner was started.

## Handoff

GameLogic retains unresolved constructors, virtual members, other key-cache
spellings, two duplicate definitions, COMDAT conflicts and wrong selected
providers listed in proof.json. Other key-cache bindings may admit a similar
repair after their own retail operands and providers are checked; this result
does not establish their identities. No failed conversion was retried.

The BFME 1 freshness update remains inherited work owned by another worker's
`file:reference/open-bfme-1` claim. Official master was fetched and is now
`9f335a9ec9ff012c5103195540fa82ccc3e7877e`, ahead of the clean retained
verified pointer above. The earlier old-input comparison gate had 2,982 stale
TUs and stopped after 21 minutes with 2,806 remaining (attempt 53899).
Preserve the verified checkout/gitlink and success stamp; do not claim the
update complete or repeat the unchanged multi-hour baseline. This bounded
repair is verified against the retained inputs.
