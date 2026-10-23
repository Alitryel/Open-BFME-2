# Prerequisite-vector provider repair and remaining identity conflict

Inputs: BFME 2 `4deb3398967`; committed BFME 1 donor
`138757e9b74645fbcbb7724a7af2764e34931e11`.
Link preview uses census `456ce161c5`, 2026-10-23 06:28, retail-truth-4.

## Landed change

Rehome the existing 52-byte global `vector<PrereqUnitRec>::push_back` row at
`0x002DF89B` from `ProductionPrerequisiteRecVectorCopy.cpp` to
`stlport_vector_prerequnitrec_allocate_copy.cpp`. The destination already emits
the complete exact body, including its retail call targets, and already links.
Neither source nor any symbol/pin/type identity changes. `add_match.py
--replace-existing` performs the verified ledger move.

Both complete units pass `build.sh`: 5/5 rows, no unresolved references or
literal/import failures. Both pass `find_declared_unmatched`. Link preview for
the pair improves **258 -> 310 bytes**: the destination owns 310 linking bytes,
while the old owner retains 106 blocked bytes (96-byte constructor and 10-byte
handler). This is a 52-byte predicted linking repair, not new exact C++ coverage
or a new full census result. See `pushback-exact.txt`, the before reports,
`build-after.txt`, and `link-after.txt`.

## Why the constructor remains separate

The picker served `0x002CFE45` in the old owner. Read its whole file and the prior
`../apt51de3d-recovery-20261023/provider-blocker.md` before retrying. The old
raw-word record emits a 42-byte const-copy helper under a name pinned to retail's
38-byte string-bearing copy worker at `0x004F5097`; the current link preview
independently confirms that wrong selected definition. Declaration-only
suppression on that raw record was already tried and failed previously; it was
not repeated here.

Target evidence: the parent at `0x002CFE45` calls the const-copy worker at
`0x004F5097`, which constructs 12-byte records through `0x002CF99D` and the
string-bearing record copy at `0x002CF5B1`. The separate raw-record push_back
at `0x002DF89B` copies three words and belongs to a different established
provider path. A global replacement of every raw `PrereqUnitRec` view would
therefore be unjustified.

The existing `ProductionPrerequisiteAssign.cpp` uses
`BfmeStringRecord002CF5B1` for this class's first vector. Other ProductionPrerequisite
views use its nested `PrereqUnitRec` with an AsciiString at +8. Zero Hour's
`GameEngine/Include/Common/ProductionPrerequisite.h:109` supplies the nested
record declaration. This donor declaration supports the relationship; it does
not by itself prove an arbitrary BFME 2 name or authorize a rename.

## New isolated experiments

Nine builds: unchanged control plus nested and existing string-record views,
declared or inline element copy constructors, and either constructor-only or
whole-vector explicit instantiation. All retain the production flags explicitly:
`/O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc` and the STLport/bfmealloc settings.
`parent-results.json` and `helper-results.json` contain the measurements.

- The unchanged control reproduces all 96 bytes with zero unresolved names.
- All eight typed variants emit a 96-byte parent. The nested form has three
  unresolved callees; the existing string-record form has two. Its remaining
  seven differing bytes are confined to unresolved REL32 operands, not
  instruction shape. This is not an admitted exact match.
- Both typed forms emit complete exact 7-byte allocator getters at `0x0021983A`
  and exact 60-byte count-taking bases at `0x005C8C37`, with zero unresolved
  relocations. These are existing retail bodies, not newly recovered bytes.
- Under the parent's exception-enabled flags, each typed const-copy helper
  emits **96 bytes**, not retail's 38. Changing the record type alone therefore
  does not close the provider graph. A correct parent must use the established
  no-exception helper provider while retaining its own EH behavior.
- The existing string-record `_Construct` emits the exact 45-byte body at
  `0x002CF99D`. The nested `_Construct` has four differing relocation bytes:
  its existing nested copy-constructor pin names `0x004EE1A9`, whose current
  owner is the distinct 39-byte `Rva004EE1A9` record copy, whereas this retail
  chain requires the 35-byte string-bearing copy at `0x002CF5B1`.

No pin was added or changed, no alias was forced for scoring, and no typed
experiment was installed under Code/. The source change needed for a complete
constructor repair must reconcile the owner, EH handler, callers, and conflicting
type-specific bindings together. Read `docs/naming.md` and follow the identity
correction rules; do not rename the global raw record wholesale or add a
second name to an already owned address without the required fold proof.

## Replay

Copy the two `turn69-*.py.txt` scripts to their names without `.txt` under
`build/resume-eh-local/`. Run `turn69-prereq-trials.py` first, then
`turn69-prereq-helper-proof.py`, from the root with the normal tool environment.
The first invokes `tools/explain_mismatch.py` on distinct scratch sources. The
second reads the resulting objects and compares their helper bodies using the
unchanged symbol map. The two representative `.cpp.txt` files and parent diffs
are retained for a focused continuation.

The user requested publication of the next commit and then a stop. The safe
row move is complete; the larger identity/provider repair is explicitly deferred.
