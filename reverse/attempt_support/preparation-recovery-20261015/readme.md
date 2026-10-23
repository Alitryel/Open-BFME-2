# Preserved link-repair preparation recovery

Recovered backup ref `refs/runner/preparation/1792062870286305952`
(original tip `af519d7df83f40bd0ea1272d98b163a74f4cef71`) onto the
runner-recorded upstream `e6bcefafac37e833ca4fe47368b17d9ef18e12e1`.
The record has no stash or resync stash. No saved ref or stash was dropped.
No new task was selected.

Skipped redundant commit `0770789e54`: upstream `c1121983ec` already owns
the identical skirmish-matrix repair, with only a comment wording difference.
Upstream evidence and source remain intact; the local version and evidence
remain in the backup ref. All other five commits replayed successfully.
The prior horde-upgrade cleanup leaves that source equal to upstream.

Upstream `d568dd7d2a` also already owns the horde-damage construction repair.
Replaying `7b526ba715` duplicated its static `_Construct(int*, const int&)`
helper after the STL header. Remove only the replayed seven-line block,
leaving the upstream pre-header helper and complete source byte-identical
to upstream. The retained independent proof remains historical evidence;
no additional authored or linked-byte gain is credited to recovery.

Acceptance at recovered tip `58ae3926be`, before this cleanup commit:

- `./build.sh` horde-damage: 1/1 exact, one float literal, no skipped refs.
- `link_check.py --prepare-current --paths-from
  build/preparation-recovery-paths.txt`: all ten bounded units strict-current,
  49/49 function rows, one data row, one string plus one empty reference,
  30 float literals, complete STLport folded constructor, no skipped refs.
- `eh_verify.py --sources-from` that list: 4/4 EXACT, no missing objects.
- `data_check.py --converged` those units: eight protected addresses,
  zero second names and zero unjudged rows.
- `check_csv.py`: OK; frozen horde-damage definitions: all matched;
  `git diff --check`: clean.
- Local legacy preview against retained index `19a2565407` (2026-10-15
  09:33, census `5986a99448`): constructor LINKS 752, heading LINKS 155,
  horde-damage LINKS 538, horde-upgrade LINKS 411, unchanged owner LINKS 511.
  This is a current acceptance preview, not a newly measured recovery gain.
  W3DModelDraw still lacks addEdgeToTrack; renderer still has seven findings
  (FogEnable, W3DShroud, four COMDAT choices, Set_Output_Ambient).
  DynamicPortal, HordeMeleeSwarm and ScriptEngine consumers are absent from
  this index and correctly refused as not previewable. Those limitations
  agree with the retained proofs. Self-current byte receipts do not establish
  closed-strict link placement. No maintainer-only verification was run.

Outgoing dry-run hook and actual publication are recorded in runner session
metadata. The preparation record is left for the runner to archive after
verified publication; all original backup refs and unrelated stashes survive.
