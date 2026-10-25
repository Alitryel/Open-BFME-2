# Tree vertex-buffer view prerequisite, 2026-10-25

Seat codexb, Device pool. The normal tree dry run rejected the existing
Rva000EBFD1UpdateVertexBuffer.cpp donor because the selected Rva000EDA94Ref
view lacked Release_Ref, used by the destination destructor.

The donor's existing model-at-C4 view now also carries the seed's existing
virtual Delete_This slot 0 and reference count at +4. Padding keeps the model
pointer at C4. No body or external-reference layout is substituted, and no
canonical class is registered for this private view.

Acceptance: seed plus donor build preserves 20/20 rows, including 1710-byte
update, 2326-byte load, and handler. Three EH parents across those files are
EXACT, zero objects missing. Declared-unmatched and data checks pass. SDK scan
finds zero local definitions; scoped queue refresh is unchanged. No source-
keyed identity/data/header register entry is moved or retired.

The ordinary final dry run accepts seed, removal, toppling, vertex-buffer and
lookup donors together, 22 rows, up from the previously accepted 19. Composed
C++ is emitted with the seed's flags. Leave that subset for Luna's normal merge.

The donor identity scan reports the same four pre-existing divergent COMDATs
with HEAD's unchanged source rebuilt and with this edit: Vector3 copy ctor,
PtrVector<int> and PtrVector<VertexBufferClass*> operator[], and Matrix3D
const operator[]. Its provider-binding reports are byte-identical before and
after: nine owner, one gap-filler, one alias; zero wrong bindings. The edit
introduces no identity improvement claim and does not retire those findings.
The modified donor was restored and freshly built after the comparison.

Receipts: build/sol-tree-vertex-{plan,build,after,data,eh,headers}.txt,
identity.txt, identity-before.txt, bindings-{before,after}.txt, and
{before,final}-build.txt under the same sol-tree-vertex prefix.

No source path or row owner changes. The entire pending batch contains no path
moves; tools, hooks, workflows, includes, build inputs, source registries and
historical EA paths need no repointing. File reduction, recovered C++ bytes and
identity debt retired are all zero. Keep destination/donor/handoff file claims
and RVAs 0x000EB6BB/0x000EBFD1 until publication is confirmed.
