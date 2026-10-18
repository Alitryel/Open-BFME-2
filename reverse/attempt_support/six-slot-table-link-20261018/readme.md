# Six-slot table ownership repair

At fixed BFME2 HEAD `19b5c683a1` and census `c2c5ac8c27`
(`retail-truth-2`), paired current objects change the legacy preview from
2,304 to 2,531 linked bytes: **+227 B**. BfmeConv1338's three rows (187 B)
and BfmeGo1053A's initializer (40 B) now link. All five provider units keep
their previous results. This is not a self-strict or closed-strict link gain.

Target evidence establishes one table at VA CE33EC, installed by the native
666BC0 initializer and 666E30 allocator and restored by 666DD0's deletion
path. Its six pointers are A66DD0, 587F40, A66CC0, A66C80, A66BF0 and A66C50.
The independent string beginning at CE3404 bounds its complete 24 bytes.
Every pointer is bound to its existing whole-body row owner. In particular,
587F40 keeps the established `fpos<int>::state` name; no new function identity,
pin or alias is inferred from its presence in the table.

The original three table spellings are consolidated on the existing
`bfmeVft1053A` name, whose definition lives with its initializer. Pointer
members become const-correct. This introduces one data owner and removes
the two undefined spellings, without adding an alternate-name directive.

Donor provenance: the existing bodies came from BFME1. The checked-in donor
64d369b90170b7e9ec917d646f020b11f13eb0d5 still has the undefined declarations
in game/GameEngine/Source/Common/BfmeConv1053.cpp and BfmeConv1338.cpp, so this
is a local target-backed repair rather than an inherited donor linking fix.
The neutral donor class names and their uncertainty are retained.

Acceptance: strict preparation and the normal byte gate verify all 44 code
rows, the complete data row, one string plus one empty-string reference and
two imports across the seven current units. Frozen-file and class checks
pass; enforced converged-data checking reports two sources, nine addresses
and zero second names or unjudged rows. Ledger integrity and whitespace
checks pass. No full link cycle or census was run.

Shadow-check limitation: data_check's older derived data_ledger still selects
the undefined `g_bfmeVftAUNA` spelling at this address. It reports the chosen
`bfmeVft1053A` owner in BfmeConv1338 as one new wrong-name finding (the same
spelling in BfmeGo1053A was already baselined). This is a stale canonical-name
record, not a second definition: the two old declarations were removed, both
consumers bind the one byte-verified data row, and all six relocations verify.
The derived ledger and baseline were not changed in this repair. The separate
code-identity shadow check reports four rows and zero new findings.
