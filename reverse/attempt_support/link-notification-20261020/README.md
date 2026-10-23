# Notification movie-clip class linkage

Native evidence identifies the old address-derived destructor owner at 4E6A9B
as InGameNotificationBoxMovieClip: it installs vtable RVA862440, also installed
by the already named constructor at 4E6C34, before restoring base table8078DC.
The five native entries are 578522 / 4E6B7D / 4E725F / 4E6B9B / 4E6882.
Base8078DC contains five entries to purecall3B810. Constructor fields and the
destructor's four member cleanups and holders at40/44 agree. The named
constructor's existing WorldBuilder provenance is retained; no donor layout
is substituted. Method names rva004E6882 and the other neutral slot names
remain unproven original spellings.

The old destructor view had one undefined b0 slot, and the named constructor
view declared only four pure base slots. Reconcile both to five; rename the
existing destructor, deleting destructor and slot4 predicate owners, updating
their consumers, EH-parent records, sole destructor pin and sole data-table
owner. No second name or pin is added to either address. The other declaration
views only supply direct calls and do not emit tables.

Five explicit current objects before: 4/5 link, 4467 B; after: 5/5 link,
4623 B. Gain **156 B**, from Rva004E6A9BDtor.cpp only. This is a self-strict
local prediction with each touched object prepared under the ordinary byte
gate, not a closed-strict gain or a full link measurement. Census baseline
5366c4f808 (retail-truth-2); other units' existing linked bytes are not credited.

Acceptance: build.sh 144/144 rows across five sources, nine string literals,
four floating literals and three named imports; strict prepare 5/5 before and
after; frozen definitions, check_csv and pin_consistency pass. Detailed local
logs: build/link-notice-{before,after}.log and
build/link-notice-{before,final}-prepare.log. No reference update or shared
header edit. Original preparation copies remain under build/link-notice-original.

Hook observation: code_identity_gate's shadow binding report treats the new
$L3874 / $L3875 labels as the old list cleanups and reports two wrong targets
at4E6A1D. The ordinary funclet gate resolves renumbered labels by the verified
parent graph (79220A / 792215), and the hook's independent EH check passes all
five parent graphs EXACT. Recorded as a false-reject tooling lead; no verifier
edit or source/label workaround. The protected data-owner rename requires a
Verifier-Change trailer even though no verifier behavior changes.
