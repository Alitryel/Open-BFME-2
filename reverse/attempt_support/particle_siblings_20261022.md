# Particle deleting-destructor ownership and folded-helper admission

BFME2 starting revision: 9a8b752ed. BFME1 reference: 37c3022de1ab944c7ffe536440d637dc8199091c.

## 0x003AC243 ownership

The existing 42-byte constructor 0x003AD19B and 38-byte copy constructor
0x003AF208 both store primary VA C1CF9C at +0, category VA C1C01C at +14,
and Snapshot VA C1C8A8 at +18. The factory and clone allocate 0x28 bytes.
The complete Snapshot table is [3AC243, B3FD0, 1F35BF, 3AC23B] (code RVAs).
The primary prefix is [3AD257, B3FD0, 3AF1D1, 55EA8E]; the primary interface
continues after this four-slot prefix and is not completely recovered.

The new eight-byte body subtracts 0x18 from ECX and jumps to 3AD257. That
28-byte scalar deleting destructor calls the complete five-byte destructor
3AD273, conditionally calls delete at 2FD60, and returns the receiver. The
complete destructor jumps to 3ABA36, which restores Snapshot then jumps to
3A983C. These native relationships support an empty derived destructor and
ICF companions for the established address-derived constructor owner;
they do not establish an original template/class identity.

Canonical Common/Snapshot.h selects the target four-slot interface, including
Xfer&. Both empty hooks, the full 21-byte EmissionVelocityInfo name literal,
the 31-byte transfer body, its eight-byte adjustor, and the clone are exact
folded companions. Clone allocation/copy relocations and EH graph are exact.
All 26 existing constructor rows remain exact. The destructor-only novtable
partial view follows the already recovered 3AD273 teardown; it models only
the cleanup relationship, not the entire primary interface.

An independent worker repeated the whole-body/REL32, table, string and clone
EH checks. Production add_match admitted the eight companion rows, then
refused the new adjustor: its COFF SEARCH_LIBRARY weak reference
??_ERva003AD19BModule@@UAEPAXI@Z defaults to its same-class emitted scalar
??_GRva003AD19BModule@@UAEPAXI@Z. proven_weak_dtor_default intentionally
excludes gen-alias scalar owners, even when their whole native body is
strictly verified. A manual scratch symbol map hid this admission limitation;
it was not a successful normal gate. No weak-only symbol is claimed as an
emitted code body and no global E alias pin is added.

The guard has explicit security regression tests. Any repair must separately
prove the actual object-local fold, preserve rejection of generic/cross-unit
alias owners and malformed weak records, and keep every exploit refused.
Verifier repair is separate from each recovered-body commit.

## Reference refresh

The BFME1 ranked and near queues remain empty. Zero Hour compilation sampled
then exhausted the existing 987-unit sweep: 318 usable object files and 669
compiler/header prerequisite failures. The final match inspected 7,758
functions: 501 unique placements already covered, 455 ambiguous placements,
1,273 near matches, and zero unclaimed conversion packets. Existing source,
headers, compiler flags and gate rules were retained. A Windows extended
path was required for long donor filenames. These counts describe discovery,
not additional recovered C++ bytes.

## Scope isolation before publication

The first production layout exposed three additional COMDAT disagreements in
Ortho/Spherical/Cylindrical info destructors because it changed a shared
primary view across 26 constructors. The final implementation instead rehomes
only the already rowed 42-byte 3AD19B constructor and its emitted companions
into existing Rva003AF208Clone.cpp under that file's /EHsc settings. Its three
original table symbol names are retained. The other 25 constructors preserve
their original views and bytes; the three unwanted info-destructor copies are
absent from the isolated object. Both old and new clone EH graphs remain exact.
The destructor-only five-byte companion remains in TailJumpWrappers5B.cpp.
This does not claim the rest of any partial primary interface is reconstructed.

Normal admission and whole-file build pass 99/99 rows across the isolated
clone file, remaining constructor file and destructor wrapper file. Placement
rescan finds zero further bodies. Link preview: the isolated clone file links
(55 to 105 unique bytes, including the rehomed existing 42-byte constructor
and new eight-byte body); the remaining constructor file links (1,334 to
1,292 bytes due solely to rehome). TailJumpWrappers5B retains its independently
confirmed preexisting unresolved Rva0078D310Host destructor; this patch adds
no such dependency. No fresh census or full link runner was launched.

## 0x003ABCAD alpha sibling

Native constructor 3ABC6E stamps primary C1C508, factory C1C504 and Snapshot
C1CDBC at +1C. The complete Snapshot table is [3ABCAD, B3FD0, 3ABC9F,
3ABCA5]. Its full alpha-name literal and all four entries are exact.
The actual constructor references its emitted Snapshot table; the outer
3ACEFC constructor uses that same provider. No dummy anchor or weak pin is
introduced. Scalar3AD3F7 folds the owner's complete destructor into3ACB6F;
that five-byte body tails to the genuine3AEA42 base cleanup at3ABC0B.
The new base cleanup companion reproduces the existing22-byte body and
canonical Snapshot+1C store plus common-head teardown. Seven folded
companions and the new8-byte adjustor pass normal add_match verification.
Only the supported Snapshot table is newly emitted; primary/factory tables
retain their existing raw native providers. Scratch and published-object
baseline comparisons show no new unresolved dependency: alpha replaces the
old undefined C1CDBC data name with its generated exact table. Existing
constructor-unit duplicate/link debt and TailJump's old Host destructor
remain separate limitations. Existing production flags are preserved.

## 0x003ABCFC color sibling

Native49-byte constructor3ABCB5 stamps primary C1C53C, factory C1C538,
category C1C780 and Snapshot C1CDE0 at+1C. The complete Snapshot table is
[3ABCFC, B3FD0, 3ABCEE, 3ABCF4]; the existing raw primary keeps all seven
native entries. The full DefaultModule<CAT_COLOR> literal at C1C558 is exact.
The eight-byte deleting adjustor shares the same strict scalar/complete-dtor
chain as alpha, with its own22-byte Rva0055BF4B cleanup companion at3ABC0B.
All eight additions pass normal admission; the source retains alpha and
velocity additions. The generated Snapshot provider replaces every C1CDE0
raw reference in this file. Baseline-delta preview removes one more unresolved
data name (six to five), retains the same12 old strong duplicates, and adds
no wrong-selected body. This is not a claim that the preexisting unit debt is
resolved. Both full Snapshot tables and both complete literals were checked.

## 0x003ABD5B physics sibling

Native3ABD20 constructor and3AEB9C copy establish the owner. The existing
four vtable names are retained. Their verified native prefixes are primary
C1C578=[3AD3F7,B3FD0,purecall,55EF39], factory C1C574=[3ACF68], category
C1C780=[purecall], and complete Snapshot C1CE54=[3ABD5B,B3FD0,3ABD55,3ABD63].
The category interface is abstract in native; no fictitious destructor entry
is used. The Snapshot name literal is complete and native. The same-size
separate destructor view uses novtable solely for retail's no-vptr-store
five-byte cleanup fold; its object defines only that function and calls the
already rowed Rva0055F197 cleanup at3ABC0B. It avoids redefining incompatible
private class views in TailJumpWrappers5B. Scalar and callback companions,
including the89-byte factory under the old factory-interface class spelling,
pass whole-byte/REL32 checks. The factory's EH graph is exact.

Normal add_match admits all nine rows with no weak pin; only the new eight
bytes increase coverage. Whole-file placement rescan is empty. A bounded
in-memory overlay of the actual three production objects has no unresolved,
duplicate, COMDAT, address or selected-body blockers. The new destructor
object has one unique definition, so its added overlay position changes no
competing definition. This is a preview, not a published census measurement.

## 0x003ABDC0 update sibling

Native3ABD81 constructor and3AEC5E copy establish the owner and original four
vtable names. Verified prefixes are primary C1C5BC=[3AD3F7,B3FD0,purecall,
55F710], factory C1C5B8=[3AC9AF], category C1C780=[purecall], and complete
Snapshot C1CE88=[3ABDC0,B3FD0,3ABDB2,3ABDB8]. The native info payload is104B
and complete owner132B. An address-derived Snapshot payload view keeps exactly
four slots; the legacy DefaultUpdateModuleInfo pointer-xfer declaration is
used only for the qualified call on this+1C. It is not inherited as a fifth
runtime slot. The full update-name literal is exact. The89-byte factory
companion preserves the old factory-interface spelling and its native EH graph.
The destructor-only novtable unit defines only its intended five-byte cleanup.

All nine rows pass normal admission with no weak pin; the new adjustor adds
exactly eight unique bytes. Whole-file placement rescan is empty. The bounded
three-current-object provider overlay has zero blockers in every category,
with the same new-unique-unit/census limitation described for physics above.

## Final verifier validation

The separate verifier repair passed246 production regression tests, including
all instantiated gate exploit cases, old weak-default refusals, ICF admission
and STLport fold cases. Thirteen existing fixture skips were reported. Two
independent reviewers repeated the proof/test assessment. Every real new
adjustor subsequently passed normal production add_match with no masking or
unresolved calls and without adding global weak-name bindings or exemptions.
