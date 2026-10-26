# Sol prerequisite batch, 2026-10-26, codex, second session

Dedicated family A, deterministic shard 0/2. Current AGENTS.md and consolidation
instructions were read before work. The inherited batch was already upstream at
session start (a338c81b13); its 21 file claims were released after confirmation.
Inherited repairs are excluded from the measurements below. No merge or split
was applied in this session. Compatible donors remain for Luna.

## Verified prerequisite improvements

Each result is an ordinary `python3 tools/tu_skeleton.py --merge TU --dry-run`,
with current routing and normal verifier/claims behavior, following the allocated
runner queue and scoped original-path planner. Planner hints alone did not
approve placement. Before and after composition trials were recorded separately.

| Destination | Repair commit | Accepted composition after repair | Newly compatible donors / rows / existing bytes |
| --- | --- | --- | --- |
| GameLogic/Object/Update/HeightDieUpdate.cpp | 7329f8736f | Update, Xfer, PoolKey: 7 rows / 799 bytes | 2 / 3 / 166 |
| GameLogic/Object/Body/InactiveBody.cpp | 0e5ad8a973 | Seed, PoolKey: 5 rows / 225 bytes | 1 / 2 / 79 |
| GameLogic/Object/Update/StealthDetectorUpdate.cpp | 87ed3c05a4 | Bfme, Xfer, PoolKey, Common/Rva004A2D67Init.cpp: 15 rows / 1841 bytes | 2 / 3 / 147 |
| Common/RTS/ResourceGatheringManager.cpp | 947bdbc6d7 | Seed, Xfer: 5 rows / 236 bytes | 1 / 1 / 54 |
| GameLogic/Object/Update/AutoDepositUpdate.cpp | 260f603aa9 | Update, PoolKey: 8 rows / 1094 bytes | 1 / 2 / 79 |
| GameLogic/Object/Collide/CrateCollide/MoneyCrateCollide.cpp | cff7e837d3 | Seed, PoolKey: 4 rows / 333 bytes | 1 / 2 / 79 |

Paths in the table are beneath Code/GameEngine/Source/. Six repairs add eight
compatible donors, thirteen existing rows, 604 existing retail bytes. All accepted
compositions together cover 44 existing rows / 4528 bytes. These are demonstrated
dry-run unblocks, not recovered bytes or confirmed downstream Luna landings.
File reduction 0; authored/recovered C++ bytes 0; identity/data/header debt retired
0. Four scoped receiver headers were added; no source was moved or removed.

Per-target evidence, exact commands, object comparisons and residual donors are
in the adjacent heightdie-receiver, inactivebody-pool-declaration,
stealthdetector-receiver, resourcegathering-stl-receiver, autodeposit-receiver and
moneycrate-pool-declaration handoffs dated 20261026-codex. Scratch evidence is
under build/codex-{heightdie,inactivebody,stealth,resource,autodeposit,moneycrate}.

## Acceptance evidence and limits

All affected body bytes, literals and imports pass `./build.sh`; frozen-file and
class checks pass. Applicable EH graphs are EXACT and compiler-renumbered funclets
are placed through verified parent EH data. Scoped `link_check.py
--prepare-current --paths-from ...` receipts and `--new-variants` checks pass;
these are predictive, not census measurements. Before/after standalone objects
and final ordinary compositions were compared through upstream object/COMDAT,
allowed-symbol and data-fact readers: no code definition lost or changed,
identical COMDAT selection policies, aliases and unresolved bindings after
internal resolution. External data bytes and relocations are preserved.

StealthDetector's one composition-local guard renumbering is separately verified
by unique matched parent/address and identical four-byte STATIC storage; its
debt remains. Its section reorder is verified by owner-normalized section
identities, not ignored. ResourceGathering's first byte-matching composition
changed three STL helpers' free bindings and was rejected. The final repair
spells the seed's existing empty _CRTIMP environment before STL includes; the
three helpers and default-library union now agree. Transfer's added .drectve
libraries were already requested by the seed. No check or protected override
was weakened. Final whitespace cleanup removes one extra EOF blank line in
AutoDepositUpdateView.h; its two consumers were rebuilt 8/8 exact and current
strict receipts refreshed. No compiler/body/layout change accompanies it.

All normal commit hooks completed. A full gate returned a session ID only once
per invocation and was polled to completion. No hand build.compile_source call,
maintainer-only link cycle, nightly runner or smoke test was run. The census
does not yet measure these repairs. No ownership receipt or NOT OURS reduction
is claimed.

## Blocked and reviewed targets

45eb12416e records DataChunk Mapping evidence and a blocked attempt: next/name/id
versus seed m_next/m_name/m_id. `rename.py ... --dry-run` refuses replacing a real
member name from inferred evidence. Its 24 existing rows still build exactly;
no source edit or naming vote was made. Both source claims were released.

Remaining constructor and opaque-vtable models in all six targets need real ABI
reconciliation, not declaration-only admission. ResourceGathering destructor and
EmitVtableTag deleter remain rejected. StealthDetector Rva004A2D49.cpp also has
opposite NONE/FOREVER enum values and lacks setWakeFrame. Mixed sources remain
behind the supported split lane; no foreign rows were moved by hand. Existing
key/guard identity/data debt and future merge transfers remain recorded in the
per-target handoffs, including StealthDetector's guard renumbering.

Read-only reassessment found prior repairs already upstream for DynamicShroud,
QueueProductionExit, SpecialPowerCreate, SupplyWarehouse and GameMemory. Their
remaining constructor/interface/legacy STL prerequisites were not retried
unchanged. HealContain retains the recorded explicit-vtable/real-virtual receiver
boundary. Protected TheMessageStream/MessageStreamSubsystem at 0x00A00950 was
not touched (maintainer issue #116). No work was taken from another shard or a
live foreign claim. Allocation snapshot: build/codex-prerequisite-allocation.json.

## Complete outgoing compatibility audit and publication handoff

Fetched origin/master at cd967b4e02 before this final handoff. Audited all seven
outgoing commits listed above (including 45eb12416e), plus staged EOF cleanup
and this handoff. `git diff --name-status --find-renames origin/master..HEAD`
and outgoing commit path lists distinguish inverse upstream changes from this
batch. Fork base a338c81b1349e4c7297ae5c2f0f0aa1df5bcbd39; the only actual
upstream overlap since that base is the append-only re_attempts.log.

No old-to-new source path mapping exists: no moves, renames or absorbed files.
Combined searches of active tools, hooks, workflows, includes, build.sh/build.ps1,
doxygen source inputs and reverse registries find no path consumer to repair.
The four new headers have exactly ten direct consumers (3 HeightDie, 3 Stealth,
2 ResourceGathering, 2 AutoDeposit), all verified with their providers. No source
list, owner, fold proof, baseline, header queue or TU map was repointed. Historical
EA paths and existing debt keys remain. `check_csv.py` passes; outgoing
`git diff --check` is clean after EOF cleanup. Audit scratch:
build/codex-session2-outgoing-paths.txt and
build/codex-session2-active-path-consumers.txt.

Every repair commit called /opt/runner/publish in the same command. Publication
was deferred by the shared-account slot; at this handoff's preparation all seven
commits remain pending. The final handoff commit retries through the same path.
The runner publishes the remaining batch when the session ends. A normal
pre-push selected-provider/lost-byte/input-freshness report must still be read
when publication runs; no successful pre-push audit is asserted here.

Retain the 29 outstanding file claims listed in
build/codex-session2-own-claims.txt, plus this handoff's file claim, until landing
is confirmed. They cover the six scopes, their verified consumers/headers and
handoffs; DataChunk source claims are already released. After confirmed landing,
release these file claims and run `claims.py release --landed`. Do not count
pending commits as a confirmed downstream merge or discard preserved scratch
evidence while completing publication. No source trial is unfinished.

## Required progress report

`python3 tools/progress.py origin/master` completed at session end; receipt:
build/codex-session2-final-progress.txt. BYTE-MATCHED 7,978,500 / 100.00%; authored
C++ 7,249,397, delta zero. Census 2026-10-26 08:28 at 47e030bafc reports LINKING
7,370,962 / 98.11% and LINKED 7,614,012 / 98.75%, both delta zero. Prerequisite
compatibility is the verified improvement in this batch; future Luna merges,
debt acceptance and the next census remain separate work.
