# Direct record typedefs in naming header admission

Tooling follow-up to attempts 83200-83202, on BFME 2 `1575882a8de8`.
This fixes type-name admission only. No inferred name, canonical name,
target layout, C++ recovery or linking gain is landed by this change.

## Reproduced false rejection

`reference/shims/sweep/GameClient/Gadget.h:352-392` explicitly declares:

```
typedef struct _ListboxData { /* members */ } ListboxData;
```

The naming lane nevertheless returned `header_type("ListboxData") == False`
and rejected it as another file's stand-in. Its local header check read only
named class/struct body declarations, and its Zero Hour check also searched
only the word immediately after `class` or `struct`. Neither recognized the
public alias after the closing brace.

The real-tree before/after comparison is recorded in
`name-lane-typedef-header-proof-20261024.json`: old admission false/new true,
and the exact rejection becomes absent. The same header contains ten direct
record aliases recognized by the reader. Source/header/naming-ledger hashes
are identical before and after the read-only comparison.

The historical locator is the already matched 468-byte window-border drawer
at RVA 0x00105AF3. That locator does not prove the private data view's layout.
The offset claims withdrawn by attempt 83202 remain withdrawn. Header spelling
permits a proposal to enter the inferred lane; it supplies no canonical naming
basis and still requires blind agreement and the ordinary rename gates.

## Scope and refusals

`record_typedef_names` recognizes direct by-value struct/class aliases from
tagged or anonymous definitions and explicit forward typedef declarations.
It balances nested bodies, accepts simple comma-separated bare aliases, and
ignores comments, literals and preprocessor definitions. Pointer, reference,
array, function, primitive and indirect-alias forms are not inferred.
Unterminated bodies do not supply an alias.

Macro text is removed using the existing conservative MSVC continuation
reader as well as ordinary directive removal. A backslash followed by blanks
may continue a macro under MSVC; both LF and CRLF controls demonstrate why the
longer interpretation must be excluded from positive header evidence. The
first implementation admitted those two cases; the final reader refuses both.

Local evidence remains restricted to tracked headers under the existing
`Code/` and `reference/shims/` roots and existing header suffixes. A typedef
in a C++ source or an untracked local header does not qualify. The Zero Hour
fallback retains its existing `.h`-only scope, including untracked donor
fixtures/submodule contents. Ordinary named-class admission is unchanged.

The shared Git search gains explicit tracked-file and NUL-terminated filename
modes. Filename quoting, spaces and non-ASCII characters therefore cannot
corrupt the subsequent header read. Search errors stop with the existing
diagnostic rather than granting admission. Existing parameter/spelling search
defaults, votes, agreement filters, source rewriting, byte checks and baselines
are unchanged.

## Validation

36 new cases: with the committed old lane, **15 fail and 21 pass**; all 36
pass with the repair. They cover definition/forward aliases, nested braces,
comments and line breaks, supported roots and header suffixes, unsupported
declarators, macro continuations, missing bodies, tracked-file boundaries,
quoted filenames, search failures and the actual Gadget.h rejection.

Related suite:

```
pytest tools/tests/test_name_lane_header_types.py tools/tests/test_name_lane_donors.py \
  tools/tests/test_name_lane.py tools/tests/test_name_metric.py tools/tests/test_name_tiers.py \
  tools/tests/test_rename_overload_scope.py tools/tests/test_gate_exploits.py \
  tools/tests/test_pin_admission_renames.py -q
```

**230 passed, 1 skipped**, no deselections. The skip is the existing empty
audit-fixture parameter set. Existing blind voting, agreement/filter, landing,
dispute, overload, reference-search and exploit tests pass together.
`check_csv`, `find_declared_unmatched tools/name_lane.py`, and
`git diff --check` pass too.

Selection refreshed BFME 1 scan/ranked/near and the lift listing, and Zero Hour
match/packets against the unchanged verified reference inputs. Both transfer
queues have no candidates. Prior evidence shows the generic money-get lead
already links, so no unchanged native trial or inherited gain was claimed.
