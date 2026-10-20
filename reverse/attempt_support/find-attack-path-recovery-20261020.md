# FindAttackPath: original scope and exact native helper visibility

Native 0x002FAD13..0x002FB558, 2117 bytes, RET32. WB D4A100 names
Pathfinder::FindAttackPath, pathfinder.cpp lines5908..6062. EA GeneralsMD and
BFME1 attack search are semantic guides; the Object-aware checks and target
field layouts come from the earlier bank's retail/WB evidence. The verified
BFME1 pointer used is92f6bbe8e1dcdb46b5d27da0674313efc822b790.

The committed bank and w2/w7 handoffs were read. The bank had a 0x7C frame,
correct2117 size and24 differing stack-displacement bytes. Its braces around
goal were a compiler-shape stand-in: WB's EH states place goal at function
scope. A current whole-owner replay with the real prependNode name still
needs the holder-release body visible for the native pointer-test sequence.
That restores2117 and the bank's old slot residue, preserving100 old rows.

The important combination was not covered by the old bank-scope probes:
original function-level goal plus BOTH the actual77-byte Path::prependNode
body and its PathNode position/layer constructor. With only prepend visible,
the original goal scope still gives2123 bytes and frame88. With the node
constructor visible, curPos no longer escapes through the opaque call: the
frame becomes7C, all three coordinate slot permutations disappear, and the
parent is2117 byte/relocation exact. No inert reads or lifetime padding are
needed, and the bank's scope stand-in is removed.

Every required emitted helper was then checked at its own native extent:

- PathNode constructor26212A:55 bytes. POD bulk assignment gave46 bytes;
  the existing copyCoord3D scalar-copy helper gives the complete native55.
  Direct field stores gave55 but differed in encoding, so were rejected.
- Path::prependNode265596:77 bytes, existing pool global and set helper.
- Movement constructor2E8BCF:41 bytes, existing source fields and ABI.
- Holder release2EAD62:23 bytes, rowed destructor and operator delete.
- Lowercase Coord3D::normalize:86 bytes; existing length:69 bytes.

All100 old owner rows and five explicit helper checks pass together. The
four non-math helper rows move into the home; their old duplicate definitions
leave the source set. Three now-unowned files are removed. The holder source
still owns its41-byte reset method and keeps that source unchanged. Inline
normalize remains an exact COMDAT copy of its existing math owner. No new
pin, alias, asm, pragma, private Coord3D definition or shared header is added.

The retained pointer/deleting-type declarations are evidence-scoped views.
Promoting the donor helper unit's inferred throw() destructor declaration
into this whole owner changes the attack parent and breaks the already exact
FindClosestPath. That control was rejected. The bank's potentially-throwing
view preserves the target's code and actual EH tables; this is not a claim
that the private deleting type has a fully reconciled class contract.

Actual Code acceptance:105/105 home rows, then106/106 across the home and the
retained reset provider. One data row,122 string literals plus three empty
references,92 float literals and18 named imports verify. All12 home EH rows,
including the attack parent, are EXACT with no baseline exception. All frozen
definition checks pass. Unrelated old bytes/line endings are preserved.

The current-provider link preview removes the three staged-deleted units and
the previously deleted hierarchical-cell unit from an in-memory copy of the
published index, after proving there are no function/data rows left for them.
The unchanged line-walk family is refreshed too: its census-era duplicate
must not stand in for the source already repaired in24bc709a16. No index,
status, census or link-cycle output is written. The home still has existing
link debt: two unrowed Pathfinder/Path calls, sin/cos and the old F83F5 copy,
plus the older index's unresolved GameStateInit datum. The retained reset and
line-walk providers link. This credits2117 unique C++ bytes, not whole-home
or closed-call-graph linking.

Rejected controls were isolated: separate pointer getters do not fix the
holder test, a prepend body without its constructor does not fix the original
scope, and the holder's nothrow declaration changes native code. Initial
duplicate class/declaration compiler refusals were corrected before their
code-generation controls; they are not counted as matching trials.

Transient replay: build/attack-current-owner-oct20/ and the attack-*.py drivers
under build/. All objects came from normal explain_mismatch/build entry points;
read-only compile_function checks never rewrote them. No census, link cycle,
nightly runner or publisher was started.
