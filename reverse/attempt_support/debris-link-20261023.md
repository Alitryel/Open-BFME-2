# Debris animation link partition, 2026-10-23

Base e91a2067e0; model gpt-6.1-sol; seat yasinschroeder-codex.
Published index: retail-truth-4, 0fa62a2841, 2026-10-22 23:07 UTC.

## Measured change

Paired current-object command:

    python3 tools/link_check.py Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp

Before: 0/318 authored bytes link; unresolved DrawModule::crc(Xfer*) and
non-retail DrawModule scalar-deleting destructor copy.
After: 318/318 bytes link, no blockers. This is a legacy scoped preview;
there is no self-strict or closed-strict linked-byte claim and no census update.

Keep the 308-byte animation setter, its 10-byte handler and its three
8-byte compiler funclets in the existing indexed unit. Preserve the other
Zero Hour methods, emission anchors and 12-byte gen-alias in
W3DDebrisDrawLegacy.cpp. That unit remains blocked on the unrecovered CRC
provider; no gain is claimed for it. Its existing interface alias was
repointed with add_match and independently verified; no new identity, pin,
layout or alias notes were invented. Neither original method bodies nor
compiler settings changed. Generated aliases/funclets contribute no claimed
C++ growth. Byte gates verify all six original rows across the two units.

## Trials and acceptance limits

Removing only the destructor-emission anchor passed all six rows and removed
one blocker, but left CRC unresolved. Isolating CRC alone passed all six rows
but would create a zero-row source, which is prohibited. Both trial shapes
were superseded by the partition above. A first setter-only split also passed
its five rows, but new objects have no census link position. The final shape
keeps the authored setter at its existing indexed source path and moves only
the already-blocked remainder. add_match recorded the intermediate and final
verified rehomings; temporary SetAnimNames/CRC files are absent.

prepare-current refused both units because the existing donor headers have
uncacheable macro/parent-traversing includes and headers outside inventoried
roots. Ordinary byte verification remains successful. A read-only
--refresh --current-ledger attempt refused three missing unrelated objects:
Rva0016B680DeformedVertices, AptError, AptScriptFunctionBase. No whole-tree
compile, census, full link cycle, nightly or boot runner was started.

## Other lanes checked

check_csv passed (98,096 functions; 15,853 symbols; 2,139 data rows).
link_rank top-30 and near-2, class_views --blockers, repair_queue link,
name_globals --dry-run (zero edits), and read-only rehome_rows were reviewed.
The inherited provider/identity blockers remain documented in
link-seat-20261023b.md and link-seat-20261023/final-triage.md.

Two alias-helper units already linked 296 B before edits. Three particle
writers already linked 1,047 B before edits. These gains are inherited and
are not credited to this repair. The 1,198-byte rotation-writer lead retains
its explicit false-reject data-name blocker from
rotation-table-link-blocked-20261014; it was not retried.

BFME 1 stays at verified f890413e75e671748215ba2ef3304aa7953993e9.
The paired verification receipt from October 22 is under 24 hours old.
Official master was fetched at 0a12ba59d192074592c1e5db0b496be23f623438.
Its new inline StringBase destructor repair was reviewed; no eligible BFME 2
counterpart was established. The gitlink was not advanced without paired gates.

## Final queue audit and handoff

The complete read-only rehome_rows scan found three movable rows, all already
documented without a linked-byte gain: Rva004F6318EntryCtor into
LivingWorldAutoResolveBattle, W3DView_Rva0008BB27 into View, and
RvaTreeInsertUniqueGenP12pod009282C0 into RvaMapIndexGenP12pod00928690.
No rows were moved by this audit. collisionmanager_impl.cpp already links
1,704 B with the inherited provider repair; that gain is not ours.

A concrete next lead is StlSweepR3Rva002FFC74.cpp (115 B): commit
72ddad5cb6 had proved the native list insert/create-node chain exact, while
4efa5fe3e7 subsequently made those specializations declaration-only. The
current preview has insert as its sole unresolved name. Compare the earlier
proof in list-range-provider-link-20261021.md and restore the supported helper
definitions while retaining the range-erase bridge. This is a hypothesis to
verify, not a new repair claim. RVA 0x002FFC74 is held by another worker;
no source was edited and all partially acquired claims for this lead were
released. The native insert/create owners are 0x002FEC97 and 0x002FE8AA.

Other current previews still require independent provider or class work:
SlowDeathBehaviorParseDeathFlags needs 0x0045D859, the ArmySummaryEntry
constructor needs native vtable adjustors, and Rva00243177 needs the native
container destructor/class reconciliation. Earlier evidence for these blockers
was reviewed rather than repeating unchanged build trials.

Commit bdacbabb87 passed the hooks, all six byte rows and the EH check.
Publication is queued by the runner's batch policy. progress.py origin/master
reports +0 authored C++ bytes and +0 census linking bytes; the +318 B result
above is the separate paired scoped preview, pending a future census.
