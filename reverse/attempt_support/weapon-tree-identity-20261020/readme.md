# Weapon tree identity repair

Inputs: BFME2 413ecd9e74b1c122e930f26a1f9d3099f4ad6d20; pinned BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790. Model Codex (runtime model not exposed).

## Native evidence and source provenance

The established weapon map operator[] at 0x0033D19B calls the 29-byte map
insert wrapper at 0x0033CBAD, which calls hinted tree insertion 0x0033C646.
The tree's worker 0x0033C0E1 and unhinted insertion 0x0033C176 call the
73-byte bitwise comparator 0x0033AD5C. Zero Hour GeneralsMD's
Common/SparseMatchFinder.h defines map<const BITSET, const MATCHABLE*,
MapHelper>; the repository's STLport 4.5.3 supplies its insertion algorithms.

The worker's node creator 0x002CF86F allocates 0x18 bytes and constructs
an 8-byte value at +0x10 through 0x002CF36E -> 0x002CF13B. That copy constructs
the first four bytes through 0x002CF0F0, then copies the dword at +4. This
independently supports the established flag-key/pointer pair. BitFlags<17>
is the existing ledger spelling; the native comparator checks 21 bits. This
change does not establish the original template argument count.

The previous float-key view was 12 bytes and compared floats; the wrapper
used an unrelated int-keyed map and the operator[] cast between member
function pointer types. All are replaced by the same actual map type.
The stale Weapon creator pin at 0x004CA19C was also false: that separately
owned AnimationSound factory allocates 0xB8 bytes and calls 0x004CA048.
Its real 37-byte source and identity are preserved.

## Provider and ABI

The real WeaponTree17 member creator is emitted in the existing creator TU,
with 8-byte value/24-byte node compile-time checks, established nontrivial
key copying, and the same allocator/copy helpers. All 34 bytes and both
relocations match the existing opaque creator. pin_admission independently
proves this fold; callers see an out-of-line member declaration, retaining
retail's ECX setup. No free-function/member-pointer cast is used.

Official cached-object name_dependents found only ThingTemplate.cpp and
STLWeaponTemplateSetBitFlagsHintedInsertUnique.cpp beyond the edited provider
for removal of the false creator pin. Independent COFF review found their
28 matched rows contain no direct references to it; incidental insertion
COMDATs do. The provider, both consumer TUs, and real AnimationSound provider
passed 41/41 matched rows after the pin correction.

## Reviewable sequence

First commit renames the three existing owners in place (149 + 449 + 29 =
627 bytes), retaining addresses and extents, updates the 88-byte caller,
retracts the false comparator/create/worker/unhinted/int-wrapper bindings,
and admits the proven creator fold and real pending unhinted insertion.
This is a zero-coverage identity repair. Atomic owner renaming keeps every
caller resolvable and follows the repository's owner-rename guidance.
A separate ordinary add_match commit records the verified 166-byte body at
0x0033C176; it supplies the only newly recovered unique bytes.

All six scratch bodies (34/149/166/449/29/88 bytes) matched fully with
native-supported relocation targets before production edits. The production
group passed 48/48 matched rows across the four edited units, the established
lower-bound/comparator units, both stale-pin consumers and AnimationSound.
check_csv and find_declared_unmatched also passed. Final normal hooks remain
the acceptance authority; no gate/baseline debt is added. pin_admission updated
the hatch register, retaining unrelated existing allow annotations that its
rewrite otherwise dropped.

## Narrow placement check

The ordinary add_match path independently verified the new 166-byte unhinted
insertion and all three rows in its source. Its temporary callee pin was then
removed because the body now owns that name.

The nine-source link_check prediction used the published index from
2026-10-20 12:21 at 5366c4f808. Four sources link cleanly: the 34-byte creator,
76-byte lower-bound, 73-byte comparator, and 593-byte AnimationSound unit.
The scoped linked count remains 776 -> 776 bytes. The repaired insertion,
wrapper and existing index still encounter wrong-selected Weapon template
copies elsewhere; ThingTemplate and the old STLWeapon unit additionally
retain unresolved/COMDAT debt. This work claims no linked-byte gain and does
not add baseline allowances. The normal identity hook also reports divergent
creator/pair/index copies in shadow mode; byte equality of the repaired
owners does not resolve those other emitted copies.

## Provider reconciliation

Independent cached-object review identified four incorrect incidental
definitions in ThingTemplate.cpp: creator, both insertions and map operator[].
STLWeaponTemplateSetBitFlagsHintedInsertUnique.cpp emitted a different creator.
Each is now a declaration of the verified provider; no class or function was
renamed to avoid a conflict. All 28 existing rows in those two units still
byte-match. VC7.1 rejects the private MapHelper name in explicit member
specializations, so ThingTemplate uses the existing sparse_public include
profile. That shim changes only the helper's access labels, with no field,
body or layout change; no shared header was edited.

The combined nine-source prediction now reports seven clean units and
LINKED 776 -> 1656 bytes (+880 unique linked bytes relative to the published
index). The creator, insertion, wrapper, index, lower-bound and comparator
closure is clean, as is the unchanged AnimationSound unit. ThingTemplate
and the older STLWeapon unit retain unrelated preexisting link debt.
The pair constructor's 22/31-byte divergence predates this change and has no
owned native address. Removing the incidental ThingTemplate map instantiation
also removes its pair copy, so that divergence disappears without inventing
a provider or native address.

The raw repaired insertion/wrapper/index extents total 881 bytes. The progress
rule merges source intervals and excludes 0xCC bytes; the sole excluded byte
is at 0x0033C720 inside the hinted insertion, yielding 880. The intervals do
not overlap. The required place_bodies scan over all six edited sources found
zero additional bodies and zero pins.
