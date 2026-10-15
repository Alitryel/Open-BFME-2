# Preserved link-repair recovery

Recovered the preparation rebase onto `384cb143adcfeab2a92f5995f6b2a627069a85b8`.
The original two key-cache repair commits remain separate. GameLogicInit keeps
upstream's multiplayerIsLocal binding and the incoming team/player cache
bindings together. No source reconstruction, new identity or compiler setting
was introduced during recovery.

Upstream `1ff2c94b14474aeeef34933c6684a120bb802723` moved PlayerList::newGame
from the deleted PlayerListRva002A8008.cpp to PlayerList_getNthPlayer.cpp. The
new home already contains the incoming multiplayerIsLocal fix, so the deleted
file stays deleted. Upstream also already owns multiplayerIsLocal's data row;
the duplicate incoming row was removed, leaving seven additional data rows
(56 bytes) from the preserved repair.

Skipped `c97d06464cedb8dfd023ab8e0516927512bbc29a`: upstream
`e6908df8b3aca60c002fedd08c8328e8c154e767` already repairs the same unused
DrawableXfer max COMDAT and retains its paired verification evidence. Its
verified dllimport/forceinline specialization is preserved. The skipped local
overload and its evidence remain in the backup ref, rather than replacing the
upstream repair or its evidence files.

Applied stash `e25361ef013322e556e9c253700424c743d86424` with --index. Its
tracked and staged diffs are empty. All 31 untracked dumps/sweep files restored
with their original blob hashes; saved-work.json accounts for each. They remain
untracked and are not submitted as new source. The stash and preparation backup
ref are retained. No saved change remains unresolved.

## Verification against the recovered tree

- check_csv: 96,517 function rows, 16,000 symbol rows, 895 data rows, no errors.
- Normal byte gate and bounded --prepare-current over GameLogicInit,
  PlayerList_getNthPlayer and WorldHeightMap: 115/115 function rows, 13 data
  rows, 70 literals, ten empty-string references, six floats and ten imports
  pass. All three objects have strict reusable receipts (current-objects.json).
- EH: 29 EXACT, zero exceptions or missing objects. Frozen-definition, class,
  pin consistency and whitespace checks pass.
- Enforced converged data: nine protected addresses, zero second names or
  unjudged rows. General data_check --enforce returns 1 for five pre-existing
  wrong-name findings; all five occur verbatim in the preserved player-key
  repair's final-data.txt. No baseline or checker was changed to excuse them.
- New-variant admission passes for the edited GameLogicInit unit. Including
  the unchanged provider reports its existing setFlipState/vftable differences
  against the old index; provider-new-variants.txt preserves both findings.
- Local link_check refreshes the explicit objects in memory, without a global
  refresh or census run. It returns 1 for retained unresolved/duplicate/COMDAT/
  selected-provider debt; all three sources remain locally unlinked. The index
  is measurement ac77c85054 (2026-10-15 14:25) and predates retail-truth-2's
  reference graph. Its hash and metadata are in saved-work.json. This is a
  legacy projection, with self-strict current objects, not closed-strict proof.

The original paired before/after key-binding proofs remain historical evidence
at their documented revisions. Recovery claims no additional authored C++ or
linked bytes. BFME1's current committed pointer and clean checkout both remain
64d369b90170b7e9ec917d646f020b11f13eb0d5; no reference update or successful
freshness check is claimed. No maintainer-only runner was started.

Publication is subject to the normal outgoing hook dry run and runner
publisher; final command results are recorded in the session handoff. Ignored
build/preparation-recovery-20261018 holds the gate and publisher logs.
