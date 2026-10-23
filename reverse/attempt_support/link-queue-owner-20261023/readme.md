# Queue virtual-owner link repair: resolved

Follow-up at 4cf1695b67 after upstream released B10. The original blocker
below is resolved. Scalar deleting destructor41A7DB now lives with the
complete constructor in GameResultsQueueStartup_Unresolved.cpp; all28 bytes
and relocations are exact. Remove B10's synthetic one-slot view and
emission-only constructor. Reconcile worker-status419D2A with Rva0041A644
in both views using the preserved patch's target evidence. The third
createGameResults view already agrees and remains63/63 B linked.

Current before: B10 572 B and startup633 B link; constructor/dtor0/285 B.
VslotSmallBodiesM is unchanged from the published index (blob equality
checked), where its117 B link. Total1322 B. After:544+673+313+77=1607 B,
all four link. **+285 B newly linkable**, accounting for both moved rows
(40 B and28 B). No coverage, self-strict or closed-strict gain claimed.
Before/after previews: before-current.txt and after-current.txt.

Validation: build.sh40/40; four-provider strict preparation40/40 with reusable
receipts; eight EH graphs EXACT; check_csv, find_declared_unmatched and
diff --check pass. The initial scalar-row placement in startup was rejected
because that unit emits no scalar destructor; corrected to the constructor
unit, then the full gate passed. No pins, aliases, shared headers or verifier
changes. B10 loses one emission-only constructor and private class view.

Other current-object audits: registry1907 B links with its already-fixed
narrow-string provider; colour ctor514 B links with V3InlineTemplateDtor;
AptError572 B and phase destructor482 B already link. No inherited gains
credited. Narrow-string compare/insert/range initialization, CreateAHeroData,
event and word-vector blockers retain their previous evidence. Camera
transform needs unlanded102F83 and AI queue needs4F37B0. Particle namespace
reconciliation needs scalar destructor1F4B47 in B03, held by another worker;
no edit attempted. Larger class repairs need whole class contracts.
name_globals dry-run yields zero edits; rehome probes yield an already-linked
pair. No measurement-matched data-back artifact was available. BFME1
freshness remains blocked as recorded in link-ww3d-fog-20261023.md.

## Original blocked investigation

Baseline HEAD 27dd681fd2, published census 456ce161c5 (retail-truth-4).
BFME 1 verified donor 96c88c73; compiler flags remain the units' original flags.

Native C3AD70 slot 16 (C3ADB0) targets 419D2A. The constructor 41A754
and startThreads 419F88 establish the same receiver+74 single worker.
The patch reconciles the standalone Rva00419D2A method with the existing
Rva0041A644 virtual slot, preserving the exact 40-byte body. All 18 rows
in the three touched units passed the full byte gate and strict preparation.

This does not yet link additional bytes: legacy link_check remains 750/1035
bytes. The first-selected vtable is a one-slot synthetic constructor view
in OpaqueScalarDeletingDtorsB10.cpp (hash 9ae473802ebd), whereas the complete
queue view emits the real full table (hash beba7cddb56f).

Next prerequisite: check the 28-byte scalar deleting destructor 41A7DB in
the complete queue object. If exact, move its row there and remove the old
synthetic queue view/emission constructor from B10, or reconcile that view.
B10 is claimed by swift-wt2, so this seat did not edit it. All source/ledger
experiments were reverted and claims released. No closed-strict gain claimed.
Preserved patch is diagnostic only, not an approved identity rename or landing.

## Independent lane checks

- link_rank --top 30 and --near 2, then --top 100 --near 1: reviewed
  current blockers by bytes. Several large census blockers already have
  upstream fixes; no inherited gain is counted as this seat's work.
- class_views --blockers: highest entries need whole class contracts
  (MilesAudioManager, AIUpdateInterface, GameLogic and RenderObjClass).
- repair_queue link: same 456ce161c5 measurement; no newer measurement invented.
- name_globals --dry-run on the 162/120-byte ConstIntGetters address units:
  zero rewrites. Earlier targeted current-global probes likewise found no
  standalone accepted repair; native parser tables and shader registries
  remain dependent on unresolved owners/providers.
- Current-object probes: AptError572B, Rva00576C4B482B, Rva001ECF6696B
  and list assignment2FFC74115B already link without edits.
- SidesListCtor1035B and BuildListInfoCopyCtor253B still report getter
  dependencies absent from the old index although those rows now exist;
  preparing providers would be inherited work rather than a new repair.
- ParticleEmitter ctor888B/copy494B now fail on the emitter table and
  Set_LOD_Bias, beyond their old RenderObjClass blockers.
- Event destructors3FD4DA123B and3FD3EF126B: current first-selected
  LivingWorldLogicDelayedEventXfer views and other constructors disagree
  on their full tables. Native getters/slot4/base ownership need a coherent
  contract; copying the old first-selected view would not prove retail.
- Debug destructor99B: current first view has35 stream virtuals and a
  nonvirtual destructor; isolated view has a virtual destructor. Existing
  ctor/member layout is proven, but deleting-callback ownership must be
  reconciled before simply copying declarations. No source trial retained.
- FXShader namespace ctor139B needs the existing nested SourceNamespace_Fog
  owner reconciled with Rva0018BEC7_Member across three function rows and
  table BD5BD4. rename.py only supports an unoccupied simple identifier;
  nested-owner reconciliation is a coordinated identity task, not a blind
  token rename. Existing upstream blocker remains unchanged.

No new authored or linked bytes. All claims taken by this seat were released.
