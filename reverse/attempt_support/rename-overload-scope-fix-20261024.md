# Retain overload scope through naming records

Tooling follow-up to `naming-famgendelete-overload-scope-20261024.md`
and attempts 83429/83430. Investigated on BFME 2 `a04ac1ede826`.
The target is the rename verifier's recorded scope, not a C++ recovery.

## Reproduction

`plan_scoped` selected `famgenDelete#8` and `famgenDelete#9` correctly,
but stripped `#N` when writing `old` and `new` in `name_basis.csv`.
`check_row` then compared every overload against the unselected scope.
The unchanged sibling parameters therefore made the mandatory post-rebase
check reject the two agreed edits. The record also could not tell `revert`
which overload to restore without a caller-supplied hint.

The actual two agreements remain blocked and their C++ source is unchanged
in this tooling commit. Read-only plans recompute their existing blind votes
through the normal agreement check. Applying those plans in an in-memory
view reproduces **30 findings with the old unselected records and zero
with selected records**. The complete comparison is in
`rename-overload-scope-proof-20261024.json`. The historical retail locators
are the 28-byte deleting destructors at RVA 0x0042D4CF and 0x0042D53F;
the C++ forcing wrappers do not have independently claimed retail addresses.

## Repair and retained refusals

- Parameter/local records retain their selected `#N` scope. Explicit `#1`
  selects and records the first overload; an unselected overloaded scope
  remains ambiguous.
- The post-rebase check examines that selection. An old name restored there,
  a missing selected function or a missing source still fails. An unchanged
  sibling's parameter/local does not fail another overload's record.
- `revert` uses a recorded selection automatically and rejects a conflicting
  caller-supplied selector. Historical records without selectors retain their
  exact inverse and the manual selector fallback.
- Legacy canonical records remain protected. Old unselected records retain
  their conservative all-overloads check; this change does not reinterpret
  or rewrite historical ledgers.
- Scope carry preserves selectors through class/function renames. Checks and
  inverses follow those carry records and recorded file moves, so legitimate
  later renames do not become missing-scope errors. An inverse after a scope
  carry is recognized as restoring that landing.

The only existing test adjustment makes an overload-specific agreement's
qualified name include its selector. Byte verification, agreement vote
requirements, collision rules, baselines and hook invocation stay unchanged.

## Validation

The 21 new regression cases cover parameters and locals, unchanged siblings,
resurrected names, lost functions/files, first-overload selection, automatic
and conflicting inverses, legacy records/protection, class/function carry,
recorded file moves, and the actual post-rebase CLI. With the committed old
verifier loaded in a separate process, **18 fail and 3 pass**; with the repair,
**all 21 pass**. The old-verifier comparison does not overwrite project files.

The real-tree dry runs retain `famgenDelete#8::p` and `famgenDelete#9::p` in
their plans. No source rename, name agreement, name-basis landing, native
byte credit or link-census credit is included here.

The broader test run was stopped when C: ran out of space. Only that run's
temporary directory, identified by its lock PID, was removed. Focused naming
tests and the mandatory gate-exploit cases are checked separately below;
the interrupted broad run is not reported as a successful suite.

Completed focused suite: `test_rename*.py`, `test_name_lane.py`,
`test_name_metric.py` and `test_name_tiers.py`: **814 passed, 12 failed,
4 deselected**. All 12 failures reproduce with the committed old verifier
loaded in a separate process under the same environment:

- `test_rename_carry`: killed-process recovery requires `fork`; two carry
  CLI fixtures lack the Windows-selected `tools/build.py`.
- `test_rename_files`: three fixtures write CRLF data rows which the existing
  LF-only ledger guard refuses; the cancellation fixture requires
  `signal.pthread_kill`.
- `test_rename`: the CLI fixture lacks the Windows build entry point; two
  alias fixtures append CRLF to LF-only symbol ledgers.
- `test_name_lane`: two donor scans lack `grep` on PATH. With Git's existing
  `usr/bin` added for a diagnostic rerun, the real-tree list-only case passes;
  the weak-donor-parameter fixture still fails its expected-name assertion,
  also with the old verifier. No unrelated test or production tool is changed.

The four deselections are the existing `test_killed_run_is_recovered`,
`test_sigterm_rolls_back`,
`test_a_signal_while_waiting_for_the_hook_tools_cancels_them` and
`test_cancelling_kills_the_name_dependents_build`, which require Unix process
or shell behavior. No new regression test is deselected.

Mandatory exploit and pin-rename suite:
`pytest tools/tests/test_gate_exploits.py tools/tests/test_pin_admission_renames.py -q`:
**42 passed, 1 skipped** (the existing empty audit-fixture parameter set).
The complete native scope checks and the existing byte-verification path are
not weakened. `check_csv` and `git diff --check` also pass.
