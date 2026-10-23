# Selection translator helper binding, 2026-10-22

At BFME2 4680dc89b1 against census ae3b3e68e2 (2026-10-22 11:05), the
current SelectionXlatTranslateGameMessage.cpp object failed on the const
vector<void*>::operator[], hashtable<pair<const int,bool>>::_M_bkt_num_key,
and the selected alloc_proxy<void**> copy constructor. The first two copies
have no retail address and differ from the referenced first-kept copies.
The constructor has retail-proven providers in the census, but another
provider is selected wrong. This unit's reference comes from its unrowed
swap<alloc_proxy<void**>> body.

Use declaration-only specializations for the two accessors and that swap.
The translator does not need private emitted copies of these operations.
All three existing rows byte-verify, including the 4,054-byte translator,
its 86-byte local helper, and 10-byte EH handler. The current-object legacy
preview changes from does-not-link/0 B to LINKS/4,145 B. No strict link
measurement was performed or claimed. No names, pins, flags or globals change.
A preliminary copy-constructor declaration byte-verified but left the swap's
reference to the wrong selected definition; it was replaced with the swap
declaration in the final source.

Cause sweep: FXListStoreParse and SelectionIDMap already link in current
source, as do Rva0002C7FD, StlSweepW4Rva0060CBAC, ArmyDefinitionManager and
Armor. Their stale census failures receive no credit here. ArmorStoreParse
has claims held by another seat and was not edited. GameLogicDoXfer and
MeshGeometryGetEdges have multiple independent blockers; they are not part
of this repair. The current selection hash specialization is also used in
SelectionIDMap, which already links.

Inputs: BFME1 checkout 37c3022de1ab944c7ffe536440d637dc8199091c retained.
Donor repairs b870d563 / 6906e0cd / 6ffd3f49 and 5b1e9f1b were reviewed
as emission/name-binding leads for this pass, without importing donor layouts.
The source's established flags, dependencies, native identities and ABI stay
unchanged. Evidence is from paired current objects against the fixed index,
not the stale ranking alone.

## Preparation recovery

The rebase onto 681beffaaa found the same 4145-byte selection repair already
landed upstream in b589abb5fa. Retain upstream's inline-visible helper
implementation in full; the declaration-only patch above is historical
evidence, not an additional linked-byte gain. No selection source change
is carried by this recovered commit.
