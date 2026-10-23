# AsciiString list provider canonical-header repair

Scope: `Code/Libraries/Source/WWVegas/WWLib/stlport_list_asciistring_insert.cpp`.
Seat1 isolated worktree `t3-0c85606f`; BFME1 input remains
`138757e9b74645fbcbb7724a7af2764e34931e11`. No shared headers, compiler flags,
ledger rows, pins, or reference inputs change.

## Evidence and provenance

The existing target identities and call relationships are documented in
`asciilist-erase-link-20261018/readme.md` and
`gamespy-list-map-link-20261018/readme.md` in this directory. In particular,
retail list element construction uses the StringBase copy provider, the list
node has eight link bytes plus the four-byte AsciiString, and retail erase
uses the existing out-of-line destructor provider. This change does not infer
new application identities from matching bytes.

At the pinned BFME1 revision,
`game/libraries/source/wwvegas/wwlib/AsciiStringListAssign.cpp` uses
`ascii_string.h` and STLport's actual list assignment. That is donor guidance
for header reuse, not evidence that BFME1 addresses or layouts transfer.
BFME2's existing `reference/shims/bfme2_ascii/ascii_string.h` supplies the
target-compatible one-pointer view. Its existing `BFME_ASCII_DTOR_DECL` switch
preserves this TU's required out-of-line destructor calls.

Replace the private AsciiString/StringBase views with that canonical header.
Remove the now-unnecessary comparison alias and duplicate operators; retain
the existing declaration-only STLport provider bindings. The direct source
hatch inventory falls from four to zero: one class-gate exception, two
optimization pragmas, and one alternatename. Header-level existing pragmas
remain unchanged. Existing ledger object-symbol debt is not changed.

## Verification

- Normal `./build.sh` passes 9/9 both before and after the change, covering
  346 existing retail bytes: 0x001FD72C/37, 0x001FD868/26, 0x0054D800/88,
  0x005BAB0B/115, 0x002FECD3/52, 0x001FD85E/5, 0x001FD863/5,
  0x0079839F/10, and 0x00798397/8.
- Native parent EH data independently resolves the old `$L4272` funclet to
  `$L4799` at the same retail RVA. The gate accepts that verified renumbering;
  no funclet pin or parent metadata is manually edited.
- Read-only before/after COFF comparison finds identical external names and
  named code-definition sets except that local funclet label. All 39 common
  named code definitions have identical bytes and relocations after normalizing
  the compiler-local EH-info label `$T4328` to `$T4855`. The renumbered funclet's
  full eight retail bytes and destructor relocation also agree.
- `find_declared_unmatched.py` reports all defined functions already matched;
  `git diff --check` passes.
- No scoped link prediction is claimed: this isolated checkout has no
  `build/link_census/link_index.pkl`. Provider names and external references
  do not change, but that comparison is not a measured link gain.

This is four direct source hatches removed with 346 existing bytes preserved,
not new recovered bytes, new authored-C++ coverage, or measured link growth.
