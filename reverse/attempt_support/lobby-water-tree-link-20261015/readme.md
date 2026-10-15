# Lobby and ocean tree-iterator emission repair

BFME2 base: f492dd289d41c23ff6983dfe18fef8a2bbdf871c. Two claimed consumers:
`Code/GameEngine/Source/GameNetwork/GUIUtil.cpp` and
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterDrawOceanWater.cpp`.
Each now uses a TU-local typed tree-iterator inequality comparing the existing
node pointers. It replaces the unused external base comparison with an unused
private helper. No identity, layout, flag, header, pin or ledger claim changes.

The paired proof refreshes both old or both new objects into separate copies
of the same frozen index, SHA256
672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c.
Receipt: 825b86983f, 2026-10-15 12:37; underlying census 5986a99448, 04:52.
The committed discovery status is older (28269d8e8d); no status or index is
rewritten. Local current-object findings decrease 11 -> 10 in water and
30 -> 29 in GUIUtil. Exactly one base-comparison finding disappears per unit,
with no other finding changes. Legacy predicted LINKED remains 0 -> 0.
New authored C++ bytes: 0. Strict reusable object receipts are verified;
self-strict or closed-strict placement gains are not measured or claimed.

Full object proof preserves all 191 retained COMDAT bodies, extents and
relocation digests (60 water, 131 GUI). All other normalized nondebug sections,
external bindings and linker directives are unchanged, including EH tables and
funclets; local COFF labels/indices normalize to their actual targets. No
nondebug relocation reaches a removed or added comparison. Data facts are
identical, with zero findings. This verifies the existing behavior and call
relationships without deriving names or layouts from byte identity.

Acceptance: normal byte gates pass all 15 ledger rows and two float literals,
plus GUI's nine string literals and three empty references. Bounded strict
prepare-current checks pass before and after for each unit. EH: water 2/2 and
GUI 5/5 EXACT, no baseline exception. The existing parent EH metadata resolves
the automatically renumbered cleanup labels without a ledger edit. Data
 enforcement and converged checks pass (eight converged addresses, no second
name). New-variant, class, declared-definition, CSV and whitespace checks pass.
Placement rescans of both units return zero bodies and zero pins.

Remaining water findings are the HAnimComboDataClass destructor duplicate,
its conflicting copy and selected provider, Vector4/Matrix4/Matrix3D constructor
copies, DX8Wrapper::Set_Transform copy/provider, and selected LightClass ctor
and WW3D::Flush. GUI retains acceptTrueColor/acceptFalseColor imports and
vector<bool>, string, allocator and tree provider conflicts. Exact names are in
each link-after.txt. These providers and their other consumers are unchanged;
this patch removes only unreferenced consumer emissions. Broader link closure
requires separate repairs. No full census, link cycle, nightly or boot runner
was invoked.

Donor review: BFME1 a7c38d3b2597121f178ab5190b3062478823257d remains the
verified clean gitlink. Official master fetched at
4cdfd6e37 (official origin/master at review);
reviewed repair principles in 66b19a8e95a4add525ef808fcea088e306798e2b,
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and 53d32d6b4b377317a3397971629ca3ad20b870e9.
Their inline/import emission suppression is a lead; the already established
BFME2 typed-comparison pattern is proved independently here. No donor source
or layout is imported. BFME1 freshness remains blocked by the previously
incomplete old-input full verification and another worker's active reference
claim; the pointer and success stamp are unchanged.

Discovery: repair_queue.py link, link_rank.py general/near/L/A/per-file input,
and a published-index fetch (same index, restored compiled objects). Six near
candidates already pass the local check and were not edited. Rva000A7E9E's
unchanged funclet-label false reject and MilesAudioCache's existing blocker
were not retried. Other tree consumers include actively claimed files and
larger ObjectCreationList/CreateAHero/W3DModelDraw work; no queue exhaustion
is asserted. Unrelated reverse/zh_sweep work is preserved.

Evidence scripts are snapshots, not production tools. To reproduce: retain
strict baseline objects under build/lobby-water-tree-link-20261015/{0,1}/before.obj,
apply the two consumer edits and prepare them strictly, then run object-proof,
link-proof and data-proof in that order against the recorded frozen index.
JSON preserves results without committing compiled objects. Per-unit checks.json
records acceptance commands and expected exit status (local link remains 1).
