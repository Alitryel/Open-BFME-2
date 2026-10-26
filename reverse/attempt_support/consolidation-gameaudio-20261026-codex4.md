# GameAudio consolidation and prerequisite handoff — 2026-10-26, codex4

## Applied scope

Allocated destination: `Code/GameEngine/Source/Common/Audio/GameAudio.cpp`.
The runner queue and `--check-tu` authorize this seat; the normal current-map
plan approves only 0x0035D2F7 (47 bytes) and 0x0035D326 (5 bytes).
`tu_skeleton.py --merge TU` accepted both Main/AudioManagerRegainFocus donors,
claimed the complete destination/donor/RVA set, composed the source, removed
both donors and repointed the two rows. Net source-file reduction: one.
Matched bytes preserved: 52. Recovered C++ bytes: zero. Identity/data debt
retired in this change: zero. The earlier GameAudio data-debt retirement is
already upstream and is not counted again.

The Common/Audio planner snapshot (`build/consolidation/audio`) and its
currency check passed before applying the merge. Its original-path and
alternative packets were reviewed; it surveys the selected directory, so
the Main donors are outside that packet's source scan. Routing permission
comes from the upstream plan rebuilt in memory, not the planner. Its normal
dry-run accepts both donors, with no mixed or rejected source, under
`/DNDEBUG /MD /EHsc`. The committed TU-map change repoints exactly two source
cells; it is not a regenerated map.

## Current object and consumer evidence

Official `./build.sh` controls verify both original bodies before composition.
The post-merge build verifies 22/22 rows across GameAudio and these three
caller/helper units together:

- `Code/GameEngine/Source/Common/Rva001DBBAD.cpp`
- `Code/GameEngine/Source/Main/AudioManagerFocusVolume.cpp`
- `Code/GameEngine/Source/GameClient/GUI/TransitionStyleSlotsBfme2.cpp`

`build/codex4-audio/proof.py` uses the supported `allowed_symbols.Obj`,
`_object_defs`, `link_census._comdat_selections` and `data_check.object_facts`
readers on saved official before objects and current official after objects.
The composed object equals the original union: two exclusive NODUPLICATES
code definitions, no external data definition, and the same undefined closure
after resolving the internal thunk call. Definition fingerprints are
`812e2e71b47c` / 47 bytes for regainFocus and `c5336dfd0d64` / 5 bytes for its
thunk. Both retain COMDAT selection 1. Relocation-bearing code digests and
each row's DIR32 data-binding set agree. No new competing template provider
is introduced or selected.

All three caller/helper objects retain identical external code/data
definitions, relocation digests, undefined references, COMDAT selections,
linker directives and per-row data bindings. The existing caller alternate
continues to resolve `?regainFocus@@YAXXZ` to
`?regainFocusThunk@AudioManager@@QAEXXZ`; that thunk calls regainFocus, which
retains its LookupFocusChannelVolume and TheAudio references. This is a
current scoped composition comparison, independent of the historical census.
It establishes no new linked-byte or executable-closure claim.

Other acceptance checks:

- `find_declared_unmatched.py TU`: all definitions rowed.
- `code_identity_gate.py --staged`: two rows, zero new findings (shadow).
- `data_check.py --staged`: zero findings; converged check: zero second names
  and zero unjudged rows at ten protected addresses.
- `allowed_symbols.py --source TU`: two owner references, zero wrong bindings.
- `eh_verify.py TU`: zero applicable/missing/inexact EH rows.
- `check_csv.py`: all 98,273 function rows valid.
- No donor/destination key occurs in the code/data identity or header registers.
  The merge tool refreshes header/MS-header reports; neither register changes.

Local receipts: `build/codex4-gameaudio-{before,merge}.txt`,
`build/codex4-audio-{planner,proof,identity,data,path-audit}.txt`,
`build/codex4-audio-build-{before,after}.txt`, and saved objects under
`build/codex4-audio/`. The fetched census index remains 2026-10-26 08:28 at
`47e030bafc`; it is not a current measurement of this merge. Preserve any
pre-push audit's stale-input findings for the next census (LINK-017).

## Complete pending-path audit

Audited the pending evidence-only recovery commit `df3ab6a199` plus this
staged move, using both `origin/master..HEAD` and the actual outgoing
merge-base (`66a8afdbdc`) range to distinguish concurrent upstream changes.
Only this GameAudio pair moves in this seat's batch. Combined old full paths
and basenames were searched across tools, hooks, workflows, Code, build inputs,
documentation and reverse registries. Remaining old-path mentions are the
historical link-status census, prior attempt evidence and generated provenance
comments; they are intentionally preserved. No active include, tool, workflow
or source registry hard-codes either donor. Current ledger owners, the scoped
build and the merge's two path-cell updates supply the new source inputs.
No historical EA path, hatch, flag override or fold proof changes.

## Other allocated probes

No source edits were made for these probes; unchanged blockers were not retried
after their current failed composition. No additional body claim remains:

- DemoTrapUpdate: dry-run accepts the seed and earlier repaired moduledata
  donor (four rows / 433 bytes). Pool-name, receiver, status-field and Xfer
  interface prerequisites remain. The seed/RVA claim was refused by another
  owner; the two helper claims granted in that attempt were released immediately.
- ProjectileStreamUpdate: final composition fails the seed's STLport allocator
  specialization; constructor INVALID_ID, pool declarations and Coord3D/GameLogic
  view conflicts reject the other donors. No donor accepted.
- OneRingPenaltyUpdate: no donor accepted. Missing pool/Xfer/update declarations,
  conflicting moduledata fields and constructor contract, destructor bytes and
  Coord3D first-header adoption remain. A constructor declaration alone would
  not reconcile the seed's AsciiString field with the donor's raw pointer view.
- FloatUpdate: no donor accepted. Seed/moduledata private fields and pool class
  declarations remain incompatible with the current full-header seed.
- ExperienceScalarUpgrade: existing pool-data identity findings and the prior
  refused retirement remain documented in the earlier large-audio handoff;
  no independent spelling or register deletion was attempted.

Inherited RayEffect repair `eb9580bfc9` and its earlier prerequisites are already
published; recovery evidence `df3ab6a199` was pending when this trial began.
RayEffect still demonstrates six accepted rows / 325 bytes for Luna, with its
opaque destructor remaining separate. No later Luna landing is asserted here.
