# GameAudio data-debt prerequisite, 2026-10-26, codex4

Allocated family A repair shard 1/2 destination:
`Code/GameEngine/Source/Common/Audio/GameAudio.cpp`. The runner queue listed
two rows and two clean donors: `Main/AudioManagerRegainFocus.cpp` and
`Main/AudioManagerRegainFocusThunk.cpp`. Normal current-map planning approves
0x0035D2F7 (47 bytes) and 0x0035D326 (5 bytes); the merge tool rebuilds the
stale map in memory. No regenerated map or source move is committed here.

The data register retained a wrong-name key for `?g_audioMixer@@3PAVAudioMixer@@A`
at RVA 0x009FE6E8 under the first donor. Its current source instead declares
the real `AudioManager *TheAudio` and casts its existing reference to the mixer
view. This is already the committed source; no new global, alias or layout
is introduced. Current data_check reports zero findings for both donors.
`python3 tools/repair_queue.py retire data
Code/GameEngine/Source/Main/AudioManagerRegainFocus.cpp` retires exactly that
one key, with zero remaining keys for the source. This clears existing debt
before Luna absorbs the donor; it does not claim a new byte or a new accepted
donor. The register's own verdict, rather than a hand deletion, authorizes it.

Verification receipts are `build/codex4-audio-*`: before-build verifies 2/2
rows and all literal checks; find_declared_unmatched passes both sources.
The before snapshot has exactly the two rowed external definitions, their
existing COMDAT selections, and the existing TheAudio binding at 10479336.
allowed_symbols reports two owner references and zero wrong bindings.
Converged data verifies ten protected addresses with no second names or
unjudged rows. EH verifies zero applicable rows and zero missing objects.
There are no Code edits, so code/data providers, selected COMDATs, and external
consumers are unchanged by this debt-only commit.

Before/after normal GameAudio trials both accept exactly two rows / 52 bytes.
The after trial has no carried-register entry. The actual composed object is
`build/tu_skeleton/c32aece75e0de7b4.obj`: its two definition fingerprints,
sizes and COMDAT selections equal the standalone donor union, its three
undefined symbols equal that union after internal resolution, and the per-row
data facts preserve exactly TheAudio at RVA 0x009FE6E8. Thus this cleanup does
not move a wrong provider into the future TU. Both composition receipts are
retained under the before/after `codex4-audio-*composition-evidence.txt` names.

The Audio planner surveyed 13 sources and retained its original-path,
alternative and compile-environment warnings. It is evidence, not routing
approval. Its currency check and the first Contain planner scan encountered
temporary tu_skeleton source paths from concurrent dry-runs; those scans must
be regenerated after the trials finish before anyone reuses the snapshot.
No failed currency check is treated as permission to merge. Independent normal
TU planning and the GameAudio compiler trial accept both donors. The trial's
protected-register transfer is no longer necessary after this retirement.
Leave the compatible pair for Luna; no merge or later Luna landing is claimed.

The complete pending batch also retains inherited RadiusDecalUpdate and
RandomSoundSelectorClientBehavior prerequisites, freshly verified as 9/9 rows
across four sources in `build/codex4-recovery-build.txt`. Their earlier
composition/provider receipts and scoped handoffs remain applicable; this
session adds no change to their code. The inherited publication attempt amended
the SoundSelector commit to 04c1b51a81 and the publisher deferred the two commits
under its batching policy. Claims remain held until publication is confirmed.

The pending path audit reviews origin/master..HEAD, isolates this seat's actual
outgoing commits through merge-base..HEAD when upstream advances, and includes
this register change. There are no moved or deleted sources in this seat's
batch. The two inherited private headers still have exactly their expected
four consumers across Code, tools, hooks, workflows and documentation searches;
those consumers verify together. No active path consumer, header/MS-header
queue, identity register, hatch or flag override needs updating. EA path
literals and historical evidence remain intact.

Also investigated allocated RiderChangeContain using its current plan and
earlier Luna handoff. The seed independently verifies 1/1 and RemoveFirst
verifies 4/4. A proposed broad-include reduction was rejected before editing:
the seed also emits a 34-byte compiler helper and four data definitions, while
its Zero Hour getContainCount()/getContainedItemsList() interfaces differ from
the BFME 2 donor's argument and list-return contracts. A private-access edit
alone would not reconcile those interfaces or prove shared-provider safety.
No source attempt, split or merge was applied; its source/RVA claims were
released. Do not repeat unchanged trials without an ABI/header prerequisite.

Measurements: one data-debt key retired; zero code-identity keys retired;
zero source files removed; zero recovered C++ bytes; no census or ownership gain
claimed. The inherited Radius pair accepts six rows / 342 bytes and SoundSelector
pair accepts three rows / 186 bytes, as recorded in their original handoffs.
