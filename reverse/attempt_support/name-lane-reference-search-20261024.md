# Portable naming-lane reference searches

Tooling repair on BFME 2 `14774258a6fa`; BFME 1 remains at the committed,
verified pointer `32774ab03393709a7f14331ba8d98d281a55ffd9`.
No native C++ recovery or naming agreement is part of this change.

## Observed failure

The naming lane invoked a separate `grep` executable for three reference
operations: donor parameter names, Zero Hour header types, and the casing of
an agreed name. Windows without that executable raised `FileNotFoundError`
while listing candidates, checking a type, or preparing an agreed spelling.

Putting this checkout's bundled GNU grep on PATH did not fully repair it:
the existing `test_owned_keeps_donor_spelled_weak_params` still served `a`
from `Dot_Product`, although the donor declaration spells `a` and `b`.
A controlled one-header fixture reproduced an empty result, exit 1 and no
diagnostic from that grep executable with native, forward-slash and relative
paths. Git grep over the same header and regex finds both the declaration
and the call; only the declaration supplies parameter names. This is an
observed backend difference, not a claim that all GNU grep installations
behave identically.

The old code also ignored nonzero search failures and populated negative
parameter-cache entries before running the search. An unavailable/failed
search could therefore be mistaken for evidence that no donor owns a name.

## Repair

All three operations share `Lane.reference_matches`, using the existing Git
dependency with `grep --no-index`. Searches retain their original scope:

- parameter names: BFME 1 `game/` and Zero Hour, `.h`, `.inl`, `.cpp`;
- header type admission and spelling: Zero Hour `.h` files only;
- the existing word boundaries, case handling, declaration-parameter parsing,
  ambiguity fallback and 200-function batches stay in place.

Explicit recursive glob pathspecs work with native paths containing spaces
and non-ASCII characters. Untracked/ignored donor files remain searchable,
including test fixtures and submodule contents. Output disables color,
line/column numbers and headings so user display settings cannot change
the evidence parser's input. Binary files do not supply textual evidence.

Git exit 1 is a valid empty search; process failures and other exit codes
stop with a reference-search diagnostic. New positive and negative parameter
cache entries are published only after every batch succeeds. A later batch
failure leaves all those new entries unpublished, and a retry can search
again. Previously proven cache entries are retained.

Votes, agreement requirements, canonical evidence checks, source rewriting,
byte verification and baselines are unchanged. No name is landed here.

## Validation

The 18 new cases exercise all three search operations without a standalone
grep executable, supported roots/extensions, unrelated paths/extensions,
declarations versus calls, word boundaries, absent roots, cache reuse,
200-function batching, Unicode/space paths, ignored/untracked files, display
configuration, missing Git, error exit codes, failed later batches, header
type boundaries and ambiguous spellings. Loading the committed old lane in
a separate process gives **17 failed, 1 passed**. The working tree is not
overwritten for that comparison.

The initial Git-backed implementation also reproduced a separate display
configuration failure: enabling line/column numbers and forced color made
a valid parameter search empty. Explicit output flags repair it, and that
positive control is included in the final cases.

Completed related suite:

```
pytest tools/tests/test_name_lane_donors.py tools/tests/test_name_lane.py \
  tools/tests/test_name_metric.py tools/tests/test_name_tiers.py \
  tools/tests/test_rename_overload_scope.py tools/tests/test_gate_exploits.py \
  tools/tests/test_pin_admission_renames.py -q
```

**194 passed, 1 skipped** in 69 seconds. The skip is the existing empty
audit-fixture parameter set. No tests are deselected. Both previously failing
naming-lane tests, including the real-tree list-only scan, now pass without
adding GNU grep to PATH. The existing blind voting, agreement/filter, landing,
dispute, overload and exploit cases pass in the same run.

`check_csv`, `find_declared_unmatched tools/name_lane.py`, and
`git diff --check` also pass. No C++ bytes, native linker gains or game
runtime behavior are claimed by this tooling-only repair.
