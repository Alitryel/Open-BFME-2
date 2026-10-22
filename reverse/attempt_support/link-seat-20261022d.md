# Link-repair handoff, 2026-10-22

BFME2 base 896b220f7d; verified repair b68575f39f. Published index
08160bc2c9 (2026-10-22 17:08), BFME1 retained at verified gitlink
37c3022de1ab944c7ffe536440d637dc8199091c. Donor mechanism reviewed:
2483354a, canonical row-call binding; no donor layout was imported.

## Verified improvement

Rva000834CERva000834CE.cpp now calls the rowed
RenderableStandingWaterArea::AllocateAndFillBuffers at 0x8304A instead of
the old Rva0008304A view. The complete native caller 834CE..83547 establishes
the same thiscall target and ABI. Paired current-object legacy preview with
W3DWater.cpp changes the caller from 0 to 121 linked bytes. Its byte gate and
commit hooks pass. W3DWater.cpp still has independent duplicate cache helpers;
this is not a closed-strict or full-link placement claim. A preview against
the old index without the explicit provider still reports the new name as
unresolved. No new authored C++ coverage is claimed.

## Restored attempts

The five failed units are unchanged and all their claims released:

- StandingWaterAreaLoadPCA.cpp: constructor/base-destructor visibility changes
  parent stack allocation and EH cleanup identity. See
  pca-link-20261022/readme.md and its diagnostic patch.
- W3DHordeModelDrawSetModelState.cpp: declaration-only and visible imported
  vendor constructor both change stack slots and cleanup grouping. See
  horde-link-20261022/readme.md and its diagnostic patch.
- PeerThreadNickError.cpp, MainMenuUtils_hasWriteAccess.cpp and
  stlport_money_put_long_double.cpp: plain and extern-template constructor
  declarations fail the parent/EH gates. See string-ctor-link-20261022.md.

After restoration the combined byte gate passes 64/64 rows, resolves 49
funclet pins and two STL folds, and passes literal/float/import checks.
Do not repeat the same suppressions without a new compiler-visibility or
provider-selection explanation. Attempt log entries record each boundary.

## Queue audit and prerequisites

link_rank --top 30, --near 2, class_views --blockers and repair_queue link
were reviewed. Live probes of approximately 150 unheld near-link units found
many inherited fixes; none were credited to this session. In particular,
both quick-match option units already link (4869 B combined), as do the
current SlowDeath parser and ocean-water units. The old ranking is a lead,
not a before measurement.

The Rva00204BB8 heap provider lead is still refuted: the pin at 21D375 belongs
to the Rva0021B68D comparator family and calls 21C878, not this family's
206D33 adjust helper. Prior evidence remains valid; no edit or new attempt
was made. The word-vector resize blocker likewise retains the recorded
load-bearing Thai consumer dependency. Unrowed FESL/Miles callees remain
unrowed and their existing banks should be preserved.

name_globals --dry-run finds zero eligible edits. rehome_rows cannot inspect
placements because build/link_census/census.log is absent from the fetched
artifact; no census was rebuilt and this failure is not queue exhaustion.
No matching data-back measurement artifact was available. Large remaining
class contracts and unrowed callees need separate substantive work.

BFME1 freshness remains due: official fetched master was 704af04c, while
file:reference/open-bfme-1 was held by codex-bce2-01a11b23-root. The retained
verified pointer and previous freshness stamp were not advanced. Coordinate
that update through claims and comparative full-byte verification. This
session does not establish that all eligible link work is exhausted.

---

# Link repair and provider audit, 2026-10-22

Inputs: BFME2 b1433f0f92, BFME1 verified pointer
37c3022de1ab944c7ffe536440d637dc8199091c. Published index: 2026-10-22
17:08 at 08160bc2c9. These are local legacy linkage measurements; no full
census/link cycle or closed-strict gain is claimed. Reviewed BFME1's linking
repair history, including d5043e16 (Coord3D inline ownership), as a method lead;
no donor layout/address change was imported.

## 0x0040B61A vector assignment: +186 B linked

The assignment's provisional BfmeRecord0040B61A element view emitted a
non-retail const-pointer __uninitialized_copy copy. Retail's tail REL32 lands
on the existing 38-byte Rva0040AEE3 worker at 0x0040B2FD. The latter's stride
is 16 and its placement helper is 0x0040B14E. Those target relationships,
not equivalence of the provisional source types, justify the pointer adapter.

Specialize assignment from the same STLport implementation, preserving the
allocation/reuse/destruction branches and using the rowed worker in the tail.
Keep that worker's loop visible, with the rowed _Construct declaration, to
preserve MSVC 7.1's empty-tag argument optimization. Suppress the obsolete
const-pointer copy in the unused allocation helper. The inline specialization
emits a COMDAT twin of the native worker, rather than a duplicate strong body.
No new pins, aliases, layout names, ledger extents or escape hatches were added.

Paired explicit checks using assignment and Rva0040B2FDUninitCopy.cpp both
before and after: 38 -> 224 linked bytes, with the provider's 38 unchanged.
All 186 assignment bytes pass the normal gate. prepare-current byte-verifies
both providers and issues strict reusable compile receipts; this is distinct
from closed-strict linkage verification.

Failed variants: a declaration-only native copy changed caller stack/register
allocation and materialized the empty-tag temporary. The ordinary STL template
kept the caller exact but emitted non-retail exception cleanup/destruction for
the opaque view. A non-inline specialization was exact but strong, conflicting
with the native provider. The final inline loop resolves these independent
causes without weakening checks.

## Same-class copy wrapper: +29 B linked

Rva0040AEE3CopyPtrs.cpp had a one-byte empty class view. Its rowed callee
at 0x0040B218 demonstrably computes (last-first)>>4 and advances by 16;
the placeholder made the locally emitted __copy differ from that retail body.
Giving only this opaque view its proven 16-byte size makes its COMDAT copy
retail-exact while preserving the wrapper's complete 29-byte row. No field
types are inferred. Local legacy check with Rva0040AEE3Copy.cpp: 47 -> 76 B,
with the provider's 47 B unchanged. Combined repair gain is 215 B; both
consumers and both native provider witnesses pass prepare-current byte gates
with strict compile receipts. The new-variants and class gates also pass.

## Narrow-string provider sweep

The published census's narrow C-string constructor findings are stale for
money_put_long_double, BfmeNarrowRecord00079C23Ctor, MainMenuUtils_hasWriteAccess,
PeerThreadNickError, VersionBlockParserText and W3DHordeModelDrawSetModelState:
paired current stlport_narrow_string_cstr_ctor.cpp resolves them without edits
(3,574 inherited consumer bytes, not credited). The earlier narrow-constructor
suppression blocker notes from this seat were explicitly voided.

Declaration-only constructor suppression in nine units changed matched caller
allocator temporaries/register allocation. Extern-template suppression in two
simple cases had the same issue. All source trials were restored.

Four consumers remain blocked on _String_base<char,allocator<char>>::~_String_base:
PeerThreadStats_PackStatKey (295 B unit), PingThread_Pinger_getPing (172 B),
StandingWaterAreaLoadPCA (2,362 B) and rva0060D2E9Rva0060D2E9Farm (341 B).
Plain destructor declaration alone changes matched caller bytes. The existing
BuddyThread inline-only destructor idiom (dllimport forceinline body calling
_M_deallocate_block) preserves every matched row in all four but leaves an
unresolved __imp_ base destructor in EH cleanup. All four restored. A future
repair must reconcile EH outline ownership as well as inline code; do not repeat
these two variants unchanged. Constructor findings alone are not blockers now.

Read-only wider base-destructor checks found additional independent blockers in
registry, XferBlockWriter, urlBuilder, setModelStateRva000C4E23Farm,
XferSaveAsText and PingThreadThreadFunction. No edits to those units were made.

## Other current-provider checks

W3DMouse, ChatSendChat, colmathsphere, original/provider W3DRopeDraw pairs,
AptOnlineCustomMatch, Pathfinder, AIBuilder, Rva00031010Insert, W3DWaterOcean,
BuddyThread and quick-match consumers include inherited fixes; no gain from
merely refreshing their old census objects is credited. Rope's native draw
and initialization providers currently link (762 + 131 B); original drawable
unit still needs its six private-class/allocation providers.

LineGroupClassRender still loses the inline Matrix4 DX8Wrapper::Set_Transform
copy. Prior dllimport suppression altered Render's rowed bytes; that experiment
was not repeated. Its 4,371-byte body requires visible inline semantics with
correct outline ownership. Claim released and evidence recorded.

Module destructor consumers already declare explicit canonical base destructors:
SpecialPowerCompletionDie, TransitionDamageFXDtor and ObjectModuleCtor now need
the correct selected provider, rather than another declaration. BridgeBehaviorDtor
needs its private virtual slot set reconciled. VersionInitGlobals still needs the
unrowed patched WinTrust worker (0x237D3D); ArmySummaryEntry's table still needs
an independently proven native adjustor at 0x40C5D3. Existing banks apply.

## Measurement limits and remaining queues

name_globals --dry-run reports zero files/edits. rehome_rows requires the absent
build/link_census/census.log. No matching data-back artifact was available.
Current-ledger closure previously refused 143 missing strict provider receipts;
local prepare-current receipts do not replace the global closure proof. Broad
rankings contain stale providers, so explicit paired current checks are required
before claiming further gains. Never start a full census to fill these gaps in
this seat. Prior unchanged blockers are also recorded in link-seat-20261022c.md.

The initial commit hook's shadow identity check exposed the old BfmeRecord
_Destroy pin as a wrong binding. Before publishing, the assignment's shrink
branch was changed to call the existing Rva0040B52EDestroy row by name using
its opaque pointer type. All 186 bytes still pass; paired current destroy
provider remains linked at 55 B, and assignment gains 186 B as before. Its
provider also passes prepare-current. This removes the new shadow finding
without changing a pin or baseline.
