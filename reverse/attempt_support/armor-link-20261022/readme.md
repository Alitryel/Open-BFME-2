ArmorStoreParse link repair, 2026-10-22

The existing strict-current object lost on the referenced const vector<void *>
subscript helper: its body differed from the first unpinned library copy. Keep
STLport's subscript expression available for inlining, using the established
import/forceinline specialization to avoid an incompatible out-of-line copy.
This also folds that expression into the unrowed hashtable _M_find helper.
The seven ledger bodies and their EH graphs remain byte-exact.

Paired preview against the same frozen published index (ae3b3e68e2,
2026-10-22 11:05): 0 -> 407 nonpadding matched bytes linked. Both objects were
prepared through --prepare-current and ordinary byte gates. The after object
has a strict reusable receipt at measurement. This is a **legacy preview gain**;
closed-strict closure and a new census were not measured. The index and status
were not edited. proof.json includes hashes and all before/after blocker lists;
proof.py.txt reproduces the bounded measurement with the saved scratch object.

Sweep: FXListStoreParse, SelectionIDMap and Rva0002C7FD already link with their
current sources; changing them would earn no gain. SelectionXlatTranslateGameMessage
has the same const-subscript blocker but is held by another worker. The 33
census copies of this helper all agree, so they are not a supported repair sweep.

BFME 1 review: current verified donor 37c3022de1; fetched upstream 42bba2ddbd.
No changed donor headers/inputs/tools. MemoryPool/Contain/EAStringC repairs were
reviewed; no supported instance of their old pattern in these units. A full
baseline byte gate waited on the host compiler flock and was interrupted before
compiling; donor checkout/pointer and freshness success stamp were left unchanged.

Preparation recovery: upstream 78a9580cf33bd5e5741384e72d287bce29203b64
independently landed the same const-subscript specialization. Replaying our
commit duplicated that definition and failed C2995. Remove our earlier copy
and retain upstream's equivalent definition. The historical paired +407 B
measurement above remains evidence of the original repair, but those bytes
already link upstream and contribute no additional gain from this recovery.
The preparation record names no stash or resyncStash; its retained backup
04566185323271011722ca39cc1811abe30994c8 contains the same five repair commits
now rebased onto current upstream. No saved edit needs separate restoration.
