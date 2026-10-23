Adapter table link repair, 2026-10-23

Base 11cc55139e; published retail-truth-4 census 0fa62a2841,
2026-10-22 23:07 UTC. Scoped current-object legacy previews, paired at this
base, change three units from zero to 196 linked bytes:

- Rva003FCD04Finish.cpp: 84 B, four unresolved WrapA/WrapB methods removed.
- Rva00317C68Concat.cpp: 56 B, three unresolved CharSourceSuffix methods removed.
- Rva00222C93Concat.cpp: 56 B, three unresolved narrow-source methods removed.

These partial adapter views already install external retail tables. Marking
the views novtable avoids emitting their unrelated synthetic tables. Explicit
restoration of the same external table in each destructor preserves native
lifetime/EH behavior. Novtable alone removes necessary EH code in the compare
unit and was rejected; the explicit destructor stores retain the complete
byte-exact bodies and handlers. There are no new aliases, pins or addresses.

Acceptance: build.sh 6/6 exact across the three units; prepare-current produces
strict reusable compile receipts; find_declared_unmatched, check_csv and scoped
new-variants pass. Final current-object link_check: 3/3 clean, 0 -> 196 B.
This is a legacy preview gain with self-strict compile receipts, not measured
closed-strict closure or an updated census. A current-ledger refresh refuses
four absent/stale providers unrelated to this repair; no closure gain is claimed.

Two independent investigations are logged blocked: StrategicInGameUI Impl has
real secondary-table RET4 entries, so abstract placeholders cannot be inferred;
DamageFilteredCreateObjectDie needs its real secondary-interface contract.
Its initially byte-safe pure-placeholder trial was reverted after native-table
review. Neither contributes gain; both claims were released.

Reviewed BFME1 linking donor changes through 138757e9b (checkout remains verified
f36a4db): 0a12ba59d/138757e9b inline StringBase cleanup, c5880f3ba compiler
visibility/flags. Their analogous BFME2 units either already link or have recorded
layout/visibility blockers; no unsupported donor ABI was imported. Current
particle-output numeric-worker repairs already link and earn no session credit.
