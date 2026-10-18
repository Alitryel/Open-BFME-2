# Preparation recovery, 2026-10-18

Recovered the five saved commits from preparation head 210a112eff onto
c206b2a7e0. Both rebase stops were in dx8renderer.cpp. Upstream 9338f64595
already owns the shader repair and accessor anchors: keep that declaration-only
implementation and omit duplicate anchors. Its 131 B gain is not counted again.
Retain the saved trial logs. No commit was skipped or rebase aborted here.

The ordinary dry-run push completed 96,642/96,642 function rows, 960/960 data
rows, 30,809 string literals, 2,138 empty strings, 8,081 float literals and
6,182 imports. It failed solely on the pre-existing root vtable identity:
??_7Rva0007DF07@@6B@ resolves to BC6F20 and C7A630. The six witness Common
sources and Rva0007DF07.h are unchanged by this batch. See full-gate.log and
the existing vector-range-destroy-link-20261018 publication evidence. This
is a failed full acceptance result, not a false-reject or permission to
weaken the verifier.

The narrow-string repair requires that full gate because its file lives under
Code/stlport. Restore only that source exactly to upstream in a new commit;
retain its complete replayable change in deferred-narrow-size.patch and its
original proof in ../narrow-size-link-20261018/. Its paired local LEGACY
preview rechecks 207 -> 84 B after deferral (-123 B), and the restored source
passes both byte rows. Resume the patch after the unrelated native vtable
identity prerequisite is resolved. No new pin, baseline or verifier change.

For the remaining six changed units, rerun the same twelve-provider cohort
against the fixed c206b2a7e0 source baseline and the recovered source. Both
source configurations pass 108/108 byte rows, one string and 15 float refs.
Paired LEGACY preview: 3/12 -> 9/12 clean, 1,081 -> 3,277 B (+2,196 B).
The retained gains are the cleanup constructors (953 B), category owner
(878 B) and range destruction family (365 B). The shader's 131 B already
links in the baseline. Renderer, shatter and vector-dtor-family witnesses
retain independent blockers; their unchanged failures make both cohort
commands exit 1. No self-strict/closed-strict LINK gain or census update is
claimed. No new authored C++ coverage.

The preparation record names no stash or resyncStash. The older unrelated
stash@{0} is untouched. refs/runner/preparation/1792343424550161659 remains
intact; upstream source and tooling additions relative to that older backup
were retained. Temporary paired-measurement source backups remain in
build/preparation-recovery-source-backup. All tracked saved changes are
accounted for by the recovered commits, upstream shader repair and deferred
narrow-string patch. The original preparation record is left for the runner.
