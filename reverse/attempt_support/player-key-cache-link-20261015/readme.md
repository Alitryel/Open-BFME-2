# Player cache ownership repair

Base: e2f48db900d235820bb360c8db1df95bb2dc7de9. GameLogicInit and
PlayerListRva002A8008 now declare eight existing const StaticNameKey globals
instantiated by WorldHeightMap.cpp through WellKnownKeys.h. Each consumer casts
the address to its established Rva00148F5ECache accessor view. There are no new
globals, aliases, pins, instructions, class layouts or compiler settings.
WorldHeightMap.cpp is unchanged. Eight matched data rows own 64 retail bytes.

## Target evidence and donor provenance

proof.json records all 17 native DIR32 operands, across GameLogic's
rva0023E0C7, CreateMPPlayers and CreateWOTRMPPlayers and PlayerList::newGame.
Their own row extents and operand bytes independently identify the eight retail
addresses. At each address retail contains a zero key followed by a pointer to
the complete corresponding name string, including its terminator. The existing
provider emits the same eight-byte initializer with its string relocation at
+4. The normal data gate verifies sizeof, extent, initializer and string.
The index has one provider for each canonical symbol.

The names and StaticNameKey contract come from the retained verified BFME 1
pointer a7c38d3b2597121f178ab5190b3062478823257d, WellKnownKeys.h and
NameKeyGenerator.h; these are not claimed to be BFME 2 debug names. BFME 1's
reviewed ownership repairs d003077f0b7 and 92a8d854, and BFME 2's existing
playerName/teamName/teamOwner repairs, support this provider-binding pattern.
No donor address or code body is imported. BFME 2 identity, initializer and
consumer operands are checked independently above.

## Acceptance and measured improvement

- Strict self preparation: 89/89 function rows across both consumers and the
  unchanged provider, with current reusable compiler/dependency receipts.
- Final ./build.sh over those three files: 89/89 functions, 12 data rows,
  69 string literals plus ten empty-string references, five floats and nine
  imports pass. EH verification: 29 EXACT, zero nonexact or missing rows.
- Every nondebug COFF section and symbolic relocation is identical after
  normalizing only the eight renamed data references. External bindings match
  under that normalization; the provider object is byte-for-byte unchanged.
- Paired local legacy projections refresh exactly the same three objects in
  separate copies of index measurement ac77c85054 (2026-10-15 14:25). GameLogic
  unresolved names decrease 58 -> 50; PlayerList decreases 1 -> 0. All other
  findings remain identical. The index hash and results are in proof.json.
- Nine wrong-name findings disappear against the final canonical data index
  (17 -> 8); all eight remaining findings are inherited GameLogic debt. Against
  the original index the old objects also had eight findings: that index still
  named the undefined old declarations. data_ledger.py generated the new
  records; only these eight addresses were refreshed, with no unrelated churn.
  The generator reported 699 other sources without objects, so no global index
  completeness is claimed. Two slots retain unrelated address-named aliases;
  their generated status correctly remains provisional.
- Enforced converged-data audit: three sources, eight protected addresses,
  zero second names and zero unjudged rows. CSV integrity, frozen-source,
  class, pin-consistency, new-variant and diff checks pass. Placement rescan
  finds zero incidental bodies or pins.

Verified improvement: nine unresolved references removed and 64 existing retail
data bytes owned. New authored C++ bytes: zero. Incremental legacy linked bytes:
zero (both consumers and provider still have blockers). Strict self receipts do
not prove closed-strict closure; no closed-strict gain or real data-back/link.exe
result is claimed. No full census, link cycle, nightly or boot runner was run.

## Remaining blockers and reference freshness

GameLogic retains 50 unresolved names, two strong duplicates, 19 COMDAT and nine
selected-provider findings. PlayerList retains duplicate getNthPlayer/getSideInfo
and selected initFromDict findings. The provider retains its existing debt;
proof.json contains the complete paired results. Eight unrelated GameLogic data
identity findings remain. Further repair needs independent supported evidence.

Official BFME 1 master was fetched at 003e59cd87341220c88867837d03ac55e39f8ee1.
The verified checkout and gitlink remain a7c38d3. Another worker holds the
reference scope. The inherited comparative-update blocker remains: old-input
verification had 2,982 stale TUs and was interrupted after 21 minutes with 2,806
remaining (attempt 53899). Preserve the old success stamp; freshness completion
is not claimed. This bounded repair passes against the retained verified inputs.

proof.py is the paired audit used with the retained build/player-key-cache-link-
20261015 snapshots; proof.json retains its full findings, hashes and native proof.
