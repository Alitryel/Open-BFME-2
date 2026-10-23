# Player science and callback bindings

At BFME2 a34d6be94c, PlayerRva002AE252.cpp fails the scoped current-object
legacy preview on vector<int>::operator= and callback_002AE435. Native
REL32/DIR32 targets already have rowed providers: assignment 0x0021C21B
is vector<Rva0021C21BElement>::operator=, and callback 0x002AE435 is
rva002AE435(const Thing *, list<Drawable *> *). Use those existing names;
retain the science storage, callback cast, public signatures and flags.
The element's application identity remains unknown. No pins or aliases added.

Same-index preview (b711de3634, 2026-10-23 14:28), explicit current objects:
consumer 0 -> 214 authored non-padding bytes; callback 64 -> 64 and
assignment provider 177 -> 177, total 241 -> 455. Both providers link.
This is +214 B legacy prediction; no self-strict or closed-strict gain
claimed. --prepare-current verifies all five rows across the three sources
and creates reusable strict receipts without measuring LINK closure.

Consumer ./build.sh: 3/3 exact. Three-source receipt gate: 5/5 exact.
EH verify: no consumer EH rows. Declared-definition check and diff check pass.
Current sweep peers RankInfoCtor, Rva001DE727Assign, Rva0040AEE3CopyCtor
and ArmySummaryCopyBFME2 already bind the provider; no new gain there.
ProductionPrerequisiteAssign retains independent record identity/destructor
blockers and is not altered. BFME1 verified donor 96c88c73 reviewed for
link fixes; this repair extends BFME2's established six-consumer repair
(vector-assign-link-20261020-codex3), without importing new donor code.
