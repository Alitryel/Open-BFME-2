# ElvenWoodSpecialPower::addObject

Complete native entry 0x004C397F..0x004C3A9F, 288 bytes including RET8.
WB 0x0125EB20 gives the method name, Matrix3D(true), scalar scale local and
the kind dispatch. Retail independently supplies template+0x108 bit accesses,
scale+0x4E0, owner+8, team+0x304 and the four-argument terrain/factory calls.
The seven-word bitset follows WB's 218-bit reference type; the target accesses
do not establish the rest of ThingTemplate's layout. The address-derived view
and padding retain that uncertainty.

The old primary bank depends on volatile matrix stores and a volatile raw kind
read. Those were never suitable production recovery. Normal Matrix3D(true)
and a real std::bitset<218> reproduce the full native instruction schedule when
the two inner tests use the reference accessor and /d2inlS100 enables inlining
of the constant valid-index STLport tests. No source fences, equal-arm tricks,
inline assembly, new aliases, pins or shared-header edits.

Compiler: ordinary hash-pinned VC7.1 RTM, /O1 /Ob2 /d2inlS100 /G7 /arch:SSE
/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB; repository STLport and the existing
bfme_matrix3d_bool_link view of the real WWMath header. Static-library mode
removes the imported STL helper reference. The verified bool-constructor view
keeps the header body inline without emitting a competing nonretail copy of
the constructor whose native owner is 0x0004C91A. Neither shared header changes.
Standard <new> precedes the WWLib placement-new guard to avoid defining the
same array-placement operator twice. Both intended include directories and
headers exist. BFME1 is the current committed verified pointer
92f6bbe8e1dcdb46b5d27da0674313efc822b790; WWMath did not change from b3cc.

Existing 42-byte constructor independently remains exact in the same object.
Normal explain_mismatch reports all 288 bytes exact with zero unresolved calls;
place_bodies finds exactly this one new body and zero pins. Scalar SSE variants
were rejected: named and unnamed vector expressions force dynamic stack
alignment, growing the body to 317..337 bytes. Checked/unchecked bitset and
standard O2/Os or no-exception settings alone do not solve the inlining barrier.
The successful source uses the checked reference bitset test, ordinary matrix
construction and ordinary scalar scale value. The existing destructor marker
and old vtable alternate-name declaration are unchanged; no hatch repair is
claimed for removing artifacts that existed only in an unlanded bank.

Replay driver: elven-wood-bitset-20261020.py.txt (copy to build/). Its phases
first, inline, kinds, bitset-inline and bitset-flags use the primary bank frozen
at 1e1497c0b9. The successful source is
stlport-bitset-dispatch-Ob2-inline-budget.cpp under build/elven-wood-sse-oct20/.
Full logs, COFF-aware instruction metrics and dependencies remain there.
In-place build and add_match verify both functions (330 bytes including the
constructor's alignment byte); find_declared_unmatched accepts the complete
file. The local testKindInView adapter has its own name: its bounds-checked
reference test must not publish a divergent copy of the original isKindOf
overload. The proper in-place legacy link preview reports LINKS for this unit
and both dependent units at census d5ae1ce9c2: 42 to 826 real source bytes in
that preview. This is a preview, not a new published census.
Normal hooks and rebased publication remain required. The full reference check
before this source edit passed 97373/97373 functions and 1119/1119 data rows at
the current verified pointer. No new pin, alias or compiler escape is added.
