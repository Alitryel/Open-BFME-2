# playerName cache provider repair

At BFME 2 base `4ae467f3a392e542b6a425899e045923721ac97f`, remove the
second eight-byte cache `g_00DBDE24` from Bfme5DictStringPresence.cpp. Six
consumer units now declare the existing `const StaticNameKey TheKey_playerName`
instantiated by WorldHeightMap.cpp through Common/WellKnownKeys.h. Consumers
cast only the accessor view to their established Rva00148F5ECache type, retaining
the same accessor calls, ABI and behavior. Four other consumer units already
declare the exact owner and remain unchanged. The original Player.cpp's donor
uses also inherit the canonical declaration from WellKnownKeys.h.

Add the existing owner's verified eight-byte data row. WorldHeightMap.cpp,
headers, compiler settings, pins, aliases, function rows, baselines and census
files remain unchanged. An initial rename-only trial passed the byte gate but
was discarded after inspection found the macro-instantiated existing provider;
the final repair removes that duplication instead of introducing another name.

## Target proof and donor distinction

Retail RVA `0x009BDE24` contains `00000000 5895c000`. VA `0x00C09558`
points to the complete `playerName` string including its terminator. The
canonical provider's initializer has a zero key and a DIR32 string relocation
at +4. The normal data gate verifies sizeof eight, allocation extent, the
complete initializer and string relocation. `proof.json` records 17 native
DIR32 operands in the matched consumers, their owning rows, extents and operand
RVAs, independently verifying that each operand contains VA `0x00DBDE24`.

The spelling and StaticNameKey contract are donor-derived, not asserted to be
BFME 2 debug symbols. Reviewed verified BFME 1 pointer
`a7c38d3b2597121f178ab5190b3062478823257d`, its
`targets/game/reverse/identity_evidence/012a77a8-012ac510-data-identities.md`,
data ledger and Bfme5DictStringPresence.cpp. Its ownership repair binds the
playerName cache to one const StaticNameKey provider, with mutable key +0 and
name pointer +4. That is a supported repair pattern; no BFME 1 address or code
body is imported. BFME 2 initializer, consumers and provider are verified here.
The already-landed BFME 2 GenericAIObjectType ownership repair uses this same
WorldHeightMap provider and accessor-view pattern.

## Acceptance and measured improvement

- Before: strict preparation and normal byte gates pass 146/146 rows across
  ten consumer units, plus 7/7 rows in the unchanged canonical provider.
- After: bounded `link_check.py --prepare-current --paths-from sources.txt`
  accepts all eleven sources with strict reusable compiler receipts. Normal
  byte gate passes 153/153 function rows, nine data rows, 90 string literals
  plus 15 empty-string refs, seven float refs and nine named imports.
- All nondebug object sections and relocations are identical after normalizing
  only the old data symbol spellings, except the removed duplicate's eight-byte
  data section and eleven-byte string literal. No machine instructions or EH
  sections change. Exactly two key definitions become one canonical provider.
- EH verification: 50/50 EXACT, zero baseline exceptions or missing objects.
- Ten-consumer shadow data identity findings: **18 -> 11**, removing the one
  duplicate-def and all six playerName wrong-name findings. Eleven unrelated
  findings remain: the neutral display name and ten GameLogicInit data names.
  Enforced audit on the five otherwise-clean edited units has zero findings.
- Enforced converged-data audit: eleven sources, eight protected addresses,
  zero second names and zero unjudged rows. CSV, frozen-file and pin-consistency
  checks pass. Diff check passes with `core.whitespace=cr-at-eol` to respect the
  existing provider-consumer file's CRLF format.
- Paired legacy local projection of the same index measurement
  `ac77c85054`, 2026-10-15 14:25: five of eleven units link and existing authored
  linked bytes remain **2,280 -> 2,280**. PlayerListRva002A8008 unresolved names
  decrease 2 -> 1; PlayerSkirmishNameFind unresolved names decrease 1 -> 0.
  Every other link finding is unchanged, including the canonical provider's
  existing debt. Index SHA256 and complete paired results are in proof.json.

Verified improvement: two unresolved references removed, seven data identity
findings removed, one duplicate cache eliminated and eight retail data bytes
owned. **Zero new authored C++ bytes and zero incremental legacy linked bytes.**
Strict self receipts do not establish closed-strict closure. No closed-strict
gain, actual data-back placement or link.exe result is claimed. No maintainer-only
census build, full link cycle, nightly, boot or scheduler runner was started.

## Remaining blockers

PlayerList's newGame still needs multiplayerIsLocal ownership, duplicate
getNthPlayer/getSideInfo reconciliation and the correct initFromDict provider.
PlayerSkirmishNameFind still selects the wrong getSkirmishSideInfo body. Larger
SidesList, GameLogicInit, PlayerCloneFrom and WorldHeightMap units retain the
unresolved/COMDAT/selected-provider findings recorded in proof.json. Deferred
compiler-shape repairs were reviewed without repeating unchanged attempts.

BFME 1 official master was fetched at
`7afa50f4cfe2205fab66de58312bc722dccf8cbe`, beyond the clean verified pointer.
The inherited comparative-update blocker persists: the old-input full gate had
2,982 stale TUs and was interrupted after 21 minutes with 2,806 remaining
(re_attempts record 53899); reference-scope work also had another worker's claim
when inspected. Preserve the verified checkout/gitlink and stale success stamp;
do not claim freshness completion. This bounded repair is independently verified
against the retained inputs. No unchanged multi-hour baseline gate was repeated.
