# Link repair session handoff, 2026-10-23

Started from BFME 2 800e4b6c94; BFME 1 verified at 74ea60ad41ef.
MSVC 7.1 under Wine, gpt-6.1-sol. Closing at the session context limit.

Verified local work and publication reconciliation:

* DieModule ordinary deletion: locally verified 0 -> 240 B, then superseded
  during publication by upstream 4321ed9ff6. Redundant macro header, two include
  edits and duplicate row removed from the outgoing commit. Upstream provider
  retained; no additional gain over current master. The verified BFME 1 pointer
  update to 74ea60ad41ef and historical evidence remain.
  Evidence: diemodule-delete-link-20261023/readme.md.
* Wide-record list: use canonical UnicodeString storage and real typed-list cleanup.
  Unit 0 -> 116 B; providers stay linked. Paired preview 425 -> 541 B.
  Evidence: string-record-list-link-20261023.md.

Before publication, the current-object legacy preview linked all three units,
356 B. After removing the superseded DieModule alternative, the retained repair
is the list unit's 116 B; compare it against the rebased master, not the original
seat baseline. The other 240 B now belongs to the independent upstream repair.
Ordinary byte checks, self-strict reusable receipts, literal/import checks,
declared definitions, class gate, new-variant admission and CSV checks pass.
List parent EH graph is EXACT; the Die units have no EH-bearing rows. Full
freshness verification passed 98,105 rows and 2,140 data rows before the two
real ICF rows were added. No authored unique-byte growth is claimed. No
closed-strict, full-link, runtime, or saved-census gain is claimed.

Failed trials are restored and recorded. MpGameSetupComboRef's native 11-byte
assignment matches, but local definition visibility changes shutdown's loop;
mp-combo-assignment-link-20261023/readme.md preserves three tested variants
and the remaining external-provider hypothesis. The separate Pod88 overflow
owner is hidden by the broad vector TU. A declaration-only specialization
changes native push_back 4E3BA1 from 55 to 58 B: the unused __false_type tag
needs stack storage when the body is hidden. Broad TU restored, 149/149 rows
pass. Needs a body-visible native no-EH implementation or compatible real type;
raising the valid retail extent is not a repair. Both attempts' claims released.

Queues reviewed: link_rank top/near, class_views blockers, repair_queue link,
name_globals dry run (zero edits), and rehome_rows dry run (census.log missing).
Several high-ranked units already link in current objects; no credit taken.
Existing hard class/ABI and compiler-visibility blockers were read before
retrying. A final Defector prerequisite probe, link_check --refresh
--current-ledger, still refuses 11,134 objects lacking current compiler evidence;
no Defector edits or claim. Its older exact patch remains banked, not progress.

The first publication was correctly refused for a duplicate DieModule row
introduced by the rebase; the outgoing commit was rewritten to retain only the
upstream owner. No verification bypass.

progress.py origin/master ran successfully. Origin advanced during the seat,
so its saved census and generated-coverage deltas include other upstream work;
use the session-base comparison and the per-repair paired previews to assess
this seat. Do not infer a fresh census measurement from progress.py.
No maintainer-only verification runner was started.
