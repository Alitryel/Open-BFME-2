# Naming check false reject: overloaded famgenDelete parameters

On BFME 2 base `605cde0e4a`, the naming lane independently agreed on
`FamilyDeletingDtors9.cpp|param|famgenDelete#8|p -> palantir` and
`FamilyDeletingDtors9.cpp|param|famgenDelete#9|p -> selectionDetails`.
The source is `Code/GameEngine/Source/Common/FamilyDeletingDtors9.cpp`.
The matching deleting destructors are respectively `0x0042D4CF` (28 bytes)
and `0x0042D53F` (28 bytes); these RVAs identify the emitted bodies, not
separate retail addresses for the C++ forcing wrappers.

Target evidence: the existing byte-verified destructor relationships and
the file's recorded target-proven destructor aliases distinguish Palantir
and SelectionDetailsUIImpl. The variable spellings are inferred, supported
by blind agreement between gpt-6.1-sol and gpt-6-astra, not recovered debug names.

`python3 tools/name_lane.py apply --min-models 2` made these exact edits:

```diff
-void famgenDelete(Rva00578C43 *p) { delete p; }
+void famgenDelete(Rva00578C43 *palantir) { delete palantir; }
-void famgenDelete(Rva0057BD01 *p) { delete p; }
+void famgenDelete(Rva0057BD01 *selectionDetails) { delete selectionDetails; }
```

Both rename operations passed their source, identity and ledger checks and
`./build.sh Code/GameEngine/Source/Common/FamilyDeletingDtors9.cpp`.
The pre-commit hook subsequently verified all 18 matched rows, strings,
floats, imports, EH and converged data. It reported no new identity or data
findings; existing `/alternatename` shadow findings were already in HEAD.

The mandatory post-rebase `python3 tools/rename.py check --range
origin/master..HEAD` then refused the commit with 30 findings. It reported
that each unrelated overload still declared parameter `p`, for example:

```text
param famgenDelete::p -> famgenDelete::palantir: ...: famgenDelete#3 still declares param p
param famgenDelete::p -> famgenDelete::selectionDetails: ...: famgenDelete#18 still declares param p
```

The generated name_basis records use `famgenDelete::p` for both operations,
losing the `#8` and `#9` selectors retained in the agreement keys. The check
therefore treats the correctly unchanged overloads as stale-name users.
This is an overload-scope serialization/check prerequisite, not a byte mismatch.

The unpublished rename commit was removed, its source and generated landing
records restored, and the two agreements marked blocked. No verifier was
changed or bypassed, and the file claim was released. A tooling seat should
preserve/recover overload identity in rename records and add a regression
test before reopening these agreements with `--retry-blocked`. Existing
gate-exploit tests must remain refused. Source/compiler inputs were unchanged;
the normal source-declared flags and dependency-current build cache were used.

Investigation: approximately 10 minutes including the lane scan;
model=gpt-6-astra. The complete transient patch and diagnostic output are
also retained locally under `build/name_lane/false-reject-famgendelete*`.
