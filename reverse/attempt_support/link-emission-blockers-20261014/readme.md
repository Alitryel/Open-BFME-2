# Link emission trials and current-provider handoff

At checkout 35cf9be768, inspect the dedicated link-repair queue and local
index measured at cb660e4d97 (2026-10-13 04:02). The committed discovery
status is newer, at 67e1365aa9. measurement.txt identifies the exact inputs.
No source, ledger row, pin, baseline or census change is retained. Both
trial file claims were released. Three blocked verdicts were recorded through
re_log.py. This commit preserves the evidence; it claims no repair gain.

## StringOwner unwind regression

Rva0048C200StringOwnerDtor.cpp has two native 54-byte destructors, at
2019E1 and 23DBC3. Following the previously accepted narrow cleanup pattern,
replace its forwarding alias with a dllimport forceinline specialization that
calls StringBase<char>::releaseBuffer. The four main rows still pass, but
both exception graphs regress from EXACT to bytes_differ: unwind code at
76C54F and 770F15 calls the imported destructor instead of retail's cleanup.
The entire source trial is reverted. This needs an emission strategy that
preserves unwind code; the main byte result alone is insufficient.

The before preview with the same current StringBaseWideReleaseBuffer provider
already links both consumer destructors (108 bytes). The provider has a
pre-existing duplicate narrow destructor. Alias removal would not fix that
closure. See owner-before-link.txt and the before/trial EH transcripts.

## MaterialPass first-copy regression

MaterialPassClassCtorThunk.cpp owns constructor 13EDD0/104 bytes and two EH
rows. Remove its two optimization pragmas and use the established imported
forceinline RefCount constructor, while retaining its native RefCount layout.
All three rows and its EH graph remain exact. Bounded strict preparation
with GapBodiesGE31 verifies 29/29 rows, and new-variants accepts the emitted
set. The standalone RefCount constructor disappears, but its protected scalar
deleting destructor changes from 29 to 31 bytes and loses first-copy selection.
With the same current provider, the consumer's legacy local preview regresses
from LINKS 114 bytes to zero. Revert source and hatch baseline in full.

GapBodiesGE31 retains six unrelated unresolved globals in both previews.
The trial needs consistent destructor emission without disturbing the native
constructor or unwind data; no failed code or optimization removal is retained.
An initial preparation receipt was invalidated by a comment edit during the
check; material-trial-prepare.txt is the repeated successful final check with
stable inputs. No invalid receipt is used as acceptance evidence.

## Restored acceptance and other checked lanes

restored-prepare.txt verifies 40/40 matched rows across both restored consumers
and their unchanged RefCount/string providers, including strict dependency
receipts, four floats and six imports. restored-eh.txt independently verifies
all three affected parent exception graphs EXACT. check_csv, case-collision
and diff-whitespace checks pass. Strict preparation certifies object inputs;
no self-strict executable placement or closed-strict link gain is claimed.

repair_queue.py link and link_rank.py top/near/S/A/U queries identified the
existing ranked blockers. A global name_globals.py --dry-run scan completes
with zero supported rewrites. A bounded read-only rehome_rows.py --limit 3
scan is stopped after several rejected homes and the already recorded exact
4F6318 entry-constructor lead; it is not declared exhausted. That lead remains
blocked by its LivingWorld owner (previous entry-ctor-rehome-link-20261014
receipt), so no unchanged retry is made. FireWeapon's secondary vtable lacks
an independently established provider; unchanged WinMain SRCCOPY false-reject
and folded Vector4 blockers are not retried. Broader linking work remains.

BFME 1 donor cleanup/provider repairs 5fa9bfd662c427a198176b0b727c4c11d0965733,
d3f9000fe08615a100e844adfff57fa4a39cd615 and
5093777e8373a843f1f1ccfc648601ae78351aaa were reviewed at the clean verified
pointer. These are emission leads, not target layout/ABI facts. Official
master fetch succeeds and discovers fea964f85433012ec0c95a44a8d88f77b4c29af5.
The overdue comparative full verification remains outstanding; no submodule
pointer or success stamp is advanced. No census rebuild, full link cycle,
nightly or boot runner was started.

## Listener current-provider confirmation

Rva004FA738ListenerWalks.cpp alone still fails its legacy preview with missing
SpawnArmy constructor/destructor names. Both methods are already matched in
LivingWorldCampaignObjects.cpp (4E30D5/175 and 4E3184/201); the older census
contains their prior names. Bounded preparation of both current units passes
41/41 rows, nine string literals and one float, with strict reusable receipts.
Refresh both explicitly in memory against the same census: listener and
provider both link, as listener-provider-link.txt records. This is confirmation
of existing source and resolution of a stale-provider queue lead, not a new
source repair. The CLI aggregate delta against old census objects is not
attributable to this session. Census/status remain unchanged. No closed-strict
placement or executable link result is inferred.
