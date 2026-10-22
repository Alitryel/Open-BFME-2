# Link seat: vector erase repair and blocked hash/string work, 2026-10-22

Base checkout: 7f383cb855. Published census: 08160bc2c9, 2026-10-22
17:08 UTC. Compiler: repository Wine/MSVC 7.1 through ./build.sh;
BFME_MODEL=gpt-6.1-sol. One verified repair adds 51 legacy linked bytes;
authored C++ coverage is unchanged. Failed hash/string attempts were restored
and pass the byte gate (5/5). Claims are released after publication/handoff.

## Verified vector erase repair: +51 B legacy linked

stlport_vector_record_2154f3_erase.cpp's private __copy declaration omitted
STLport's third, distance-type template parameter. Consequently its emitted
__copy_ptrs helper referenced an undefined two-parameter template rather
than the existing three-parameter worker pinned at 0x00215696. Correcting
the declaration resolves that name. An uninitialized named category local,
as in the existing Rva0021570DCopy source, also removes the prvalue tag's
extra initialization. The helper then matches all 29 bytes at 0x0021570D;
the 51 B erase caller at 0x002157DB remains byte-exact.

Paired current legacy previews, including the existing allocation/copy
provider: 1/2 units and 649 B before; 2/2 units and 700 B after. Thus the
new gain is 51 B, not the pre-existing provider's 649 B. The touched source
also passes --prepare-current (one strict reusable self receipt and normal
byte/reference gates). This is not closed-strict closure evidence, and no
closed-strict gain is claimed. See vector-erase-verification.txt.

The same two-parameter declaration occurs in Rva005842F7Finish.cpp (38 B),
whose bad __copy_ptrs also blocks stlport_vector_pod28_single_erase.cpp
(47 B). Those were checked as the same-cause sweep, not changed. Native
0x002161A5 is currently rowed as __copy_backward_ptrs<Rva002161A5Record>,
with a previously recorded identity-suspect verdict: native forward-copy
behavior contradicts that name. Its current producer also has a non-retail
__copy_backward callee and unresolved element methods. Binding consumers
to that producer would not establish a correct closure. Resolve the known
owner/callee identity first; no new pin or alias was introduced here.

## DamageFX range erase: a semantic prerequisite, beyond frame pointers

Read prior findings in link-seat-stlport-growth-20261022.md first. Current
Rva0016DEE0Cluster.cpp already contains upstream's owned-destructor-only
instantiation repair (5db0c32f95), so the consumer now reports unresolved
erase, rather than the stale census's selected wrong copy. Paired current
legacy preview: producer links 246 B, DamageFX_hashtableNewNode.cpp links
0 of 368 B. Consumer also has a competing local map destructor.

The existing DamageFX erase locator points at 0x00055612, 153 B. This is
also the rowed int/POD hash-table erase owner; a locator alone does not
establish DamageFX instantiation identity.

Two diagnostic trials, restored afterwards:

1. Instantiate range erase with imported-inline vector<void*>::size and
   global /Oy-. Three of the four cluster byte rows fail.
2. Keep original flags; define the vendor range-erase specialization
   under local #pragma optimize("y",off), with imported-inline size.
   All four cluster byte rows pass, but helper is 165 B versus 153 B and
   the consumer remains unlinked. Patch and instruction diff are retained.

Target evidence establishes the important difference: both retail bucket
computations use the single dword key at node+4 modulo bucket count.
The DamageFX instantiation instead computes (node[+8]<<16)+node[+4]
through rts::hash<NameKeyType>. This is not an equivalent optimization.
The consumer's existing 15 B hash row at 0x00169440 independently verifies
that two-word hash, so changing it to match the generic single-word owner
would invalidate another proven body. Local frame-pointer control closes
only the prologue issue; source/type/caller identity must reconcile the
range-erase locator before another shape-only trial.

The donor/vendor erase structure is reference source. The dword loads,
shift, arithmetic and size differences above come from target/object
bytes. Original meaning of the DamageFX key/type relationship remains
unresolved. No alias, pin or guessed class change was added.

## basic_ios<wchar_t>::imbue: assignment suppression changes inline shape

Current stlport_wide_ios_imbue.cpp has 238 B and one legacy blocker:
its basic_string<char>::operator= copy differs from the kept copy.
The rowed assignment owner is stlport_narrow_string_assign_copy.cpp at
0x000120C0 (41 B); its vendor operation dispatches pointer ranges.

Two careful trials, both reverted:

1. Before <ios>, an explicit dllimport/forceinline assignment
   specialization with the exact vendor condition and assign call.
   The 238 B caller fails: dispatch-tag initialization adds five bytes,
   locale temporary homes move, and allocator free binds differently.
2. dllimport on explicit operator= instantiation retaining the original
   vendor definition. VC7.1 rejects C2375 (different linkage) and C3190
   (not the explicit instantiation of any member function).

Need a supported import/inlining arrangement retaining native temporary
initialization and cleanup visibility. Do not repeat either syntax above.
The restored unit passes 1/1 byte rows. No link gain or strict gain claimed.

## Live queue reconciliation and remaining lanes

The published index substantially predates the working sources. Current
source checks already link OpaqueScalarDeletingDtorsB12 (740 B),
GapForwardersSeat8 (739 B), SlowDeathBehaviorParsers (556 B), both
AptOnlineQuickMatchOptions units (3106+1763 B), the queued-icon unit (929 B),
wide num_get (563 B), rva00260BBF (537 B), fstream constructors (528 B),
Rva004EA420Init (206 B), and SelectionID hash constructors (105 B).
Those are inherited upstream results, not improvements from this seat.
SidesListDataChunks links 6726 B when current BfmeConv932 and
WorldHeightMap providers are checked together. Do not repair its already
resolved static keys or reintroduce the old getter copy.

Rank/class blockers and repair_queue link were reviewed. Other live
candidates retain existing independent prerequisites: sort_rva00204bb8
has a refuted comparator/callee pin at 0x0021D375; VersionInitGlobals waits
for the post-link-patched 0x00237D3D; AIPlayer queue waits for 0x004F37B0;
HordeContainDtor has unresolved secondary-interface slots (see existing
0x0046F901 record). ProductionPrerequisite removal was already refuted by
loss of three owned worker emitters. No unchanged trial was repeated.

name_globals dry-run on the three address-getter units kept zero edits.
The other sole address blocker is VP6 InitLibrary (169 B), outside this
seat's non-decoder repair sweep. No decoder source was read.
No matching link-cycle data-back artifact is available for a measured
ranking; no synthetic or mismatched ranking was used. Full census and
maintainer-only link cycles were not run.

The rehome_rows dry-run found the 29 B Rva004F6318EntryCtor placement in
LivingWorldAutoResolveBattle. Current paired link checks already link both
units (29 + 2441 B), so moving the row would produce no repair gain. The
same probe led to the verified erase repair above instead of a zero-gain
row move. Its full local output is build/link-seat-rehome.txt.

BFME1 linking review reused the tracked 20261021 freshness/link review
and 20261022 farm-binding evidence. The verified donor pointer is
37c3022de1ab944c7ffe536440d637dc8199091c; official master fetched at
aef2f1687742cdc91db274993cd41c3d036860ad. Another seat holds the reference
file claim, so no pointer/freshness stamp was advanced or assumed verified.

Also reviewed the three newest donor repair commits at that fetched tip:
4c4394701 (RefCountClass terrain-track prefix), 0a4cb4954 (shared-string
destructor suppression), and b3c535569 (battle-plan accessor). BFME 2's
terrain-track views already include refcount.h; its remaining blockers are
different. There is no BfmeSharedString class or BattlePlanUpdate_update
unit in this checkout. These commits supplied no new applicable transfer.

Final progress.py origin/master reports +0 authored C++ bytes, as expected
for an existing-row link repair. Published census totals are unchanged;
the +51 B result is the measured legacy per-unit preview above.
