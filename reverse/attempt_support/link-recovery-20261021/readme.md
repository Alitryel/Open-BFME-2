Preparation recovery, 2026-10-21

The retained preparation ref is refs/runner/preparation/1792580970912982727
(06ea378298); the preparation record names no stash or resyncStash. The runner
already completed the rebase onto 144da2dec5 before this recovery started.
There was no conflict index, active rebase, staged/unstaged edit, or untracked
file to restore. The three saved commits survived as 6fb692ca33, cdd3a45a81
and 5de53003fc. The backup ref is retained.

The recorded push gate failure reproduces: data_rows verification cannot
compile Rva00427157Ctor.cpp. Upstream 1dabd10323 independently added the
same inline-only allocator specialization as the first preserved commit,
leaving two definitions after rebase. Remove only the preserved duplicate;
the reconciled source is byte-for-byte identical to origin/master at
144da2dec5. The original +691 legacy linked bytes already landed upstream
and are not a new gain from recovery. The superseded commit is retained in
history with this corrective commit rather than discarding preserved work.

The decimal-fold and import-binding commits remain intact. Their original
paired legacy gains are +266 and +147 bytes respectively; their tracked
handoffs preserve the before/after evidence and limitations. Recovery adds
zero authored C++ coverage or additional linked bytes. Removing the duplicate
is required to publish those repairs under the current byte gate.

Recovery checks: build.sh over all six outgoing code units passes 19/19
function rows, the armor FieldParse data row, three strings and four named
imports. The armor unit alone passes 12/12 function rows and its data row.
prepare-current also passes all 21/21 rows in the eight providers and
consumers with self-strict reusable receipts. Current-object link_check
reports 8/8 units linking and 1,888 legacy linked bytes against the frozen
2b4d1fb42a census's 784 bytes; its +1,104 includes the 691 bytes already
in upstream. No closed-strict gain is claimed. The final outgoing push-hook
dry run is recorded in runner finish metadata; local raw outputs remain
under build/recovery-*. No census or maintainer-only runner was used.
