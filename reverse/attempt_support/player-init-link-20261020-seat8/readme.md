# Player initializer binding attempt, 2026-10-20 seat8

Base 9aa13ba247. Paired ordinary preview has 11 unresolved private
Rva00148F5ECache key globals and zero linked bytes (4,707 useful bytes).
The retained frozen index is 144ed0ccab, 2026-10-20 15:34.

Tried binding those keys to existing const StaticNameKey names and casting
addresses into the existing cache view, following the verified 20261015
player-key-cache-link repair. An incomplete StaticNameKey declaration changes
the first branch displacement at parent offset 544 from 0x336 to 0x338.
The complete established mutable key/pointer view improves this: its first
change is offset 1376, branch displacement 0x2D0 to 0x2D2. Both native and
compiled comparison extents are 2762 bytes, but later instructions differ and
EH allocation-cleanup labels become ambiguous. These are two failed builds;
no nonmatching source remains in Code. The better second candidate is retained
as candidate.patch. It is diagnostic evidence, not recovery or a verified repair.

Eight canonical names have an indexed provider in WorldHeightMap.cpp. Three
(livingWorldPlayerID, playerFactionIcon, playerHandicap) do not; do not assume
those providers exist merely because other keys do. No new provider, alias,
pin, data row or class contract was added. A future attempt needs supported
ownership proof for these three and a declaration/access pattern that preserves
native scheduling and the exact EH graph. Existing donor names/contracts are
leads only; no donor layout/address/body was imported. Source and ledger rows
were restored; all 32 claims released. t=9 model=gpt-6.1-sol.

Restoration acceptance: ./build.sh PlayerInitFromDict.cpp passes 31/31 rows,
six literals plus one empty-string reference, and import/float checks. Three
legacy funclet labels are independently resolved through the verified parent
EH graph. The source is identical to HEAD. No failed objects are treated as
current receipts.

## Session queue reassessment

link_rank.py --top 30 and --near 2, class_views.py --blockers and
repair_queue.py link were refreshed. The census remains 144ed0ccab. Several
high ranks are stale: repair_queue's live preview reports mapper,
InGameUIHandleBuildPlacements, StringRecordCopyBFME2 and PathfinderBridgeUpdate
already link, so these are not new repairs for this seat. No index was rebuilt.
The direct default preview still finds both AptStrategicPlayerStatus STL
copies losing; the existing 35-minute blocked attempt already exhausts ctor
suppression and explains why decl-only overflow changes frame size. No edit
or repeated build trial was made. Its 27 claims were released. DX8Wrapper's
Matrix3D owner still has wrong Vector4 assignment and a wrong earlier selected
Set_Transform provider; its existing tracked bank already fixes the first and
requires provider reconciliation. No unchanged trial was repeated.

name_globals.py --dry-run on the constant getters/Rva59675ACtor and four
additional address-global-only units found zero rewrites. The apparent
Rva59675ACtor address is a COLOR literal, not a missing global. Other scoped
leaders need an unrowed callee or broader class/provider contract; onExit
consumer repair claims belong to jacob-codex-20261020-near. Rehome discovery is
unavailable without the matching census.log; that missing artifact is not
proof of an empty queue. Reference pointer advancement remains blocked on the
comparative full byte verification; verified old inputs were retained.

Final paired ordinary check over the three repaired sources reports all three
LINKS, 0 -> 4,545 useful matched bytes (3,766 + 209 + 570). Strict self receipts
and byte gates passed per the repairs' individual readmes; no closed-strict,
fresh census or real link.exe gain is claimed. StructurePhaseListParsers has
three inherited code-identity shadow findings on existing ObjectCreationList
vector::push_back bindings; these were not changed by defining its tables.
No maintainer-only runner was started. All own claims released.
