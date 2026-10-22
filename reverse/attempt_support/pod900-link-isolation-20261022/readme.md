# Large-POD link isolation, 2026-10-22

At BFME2 9f39d6f2ee, published census ae3b3e68e2 (2026-10-22 11:05),
`link_check.py stlport_pod_large_bodies.cpp` failed on unresolved
`_Construct<BfmePod900>` and the wrong selected/emitted
`vector<BfmePod900>::_M_insert_overflow`. The unit contained 2,350 authored
non-CC bytes. These are current-object blockers, not inferred from ranking alone.

Isolate the four existing Pod900 rows (176 non-CC bytes) in
`Code/Libraries/Source/WWVegas/WWLib/stlport_pod900_bodies.cpp`, preserving
flags and template definitions. The original unit then LINKS with 2,174 bytes
in the legacy preview. This is a 0 -> 2,174 B legacy improvement; no
self-strict or closed-strict gain is asserted. The new unit is outside the
published census and cannot receive a plain link preview; its two pre-existing
owner blockers remain. Admission checks cover the moved definitions.
All 44 matched rows across both units pass the byte gate. No recovered C++
bytes, identities, pins, or row extents changed.

The native 0x004CB8DE constructor is rowed as
`_Construct<BfmeRecordOwner900>`; the native 0x004CBA0F overflow is rowed
under that owner too. Size-only Pod900 is not a proven trivial element.
Reconciling those views remains work, not a reason to manufacture an alias.
A trial forwarding `_Construct<Pod900>` inline to the rowed constructor and
using a declaration-only overflow changed the rowed push_back from its
58-byte retail boundary to 67 bytes: the compiler initializes the empty
`__false_type` argument (xor/lea/stosb) when the overflow definition is hidden.
The REL32 at +57 extends beyond the row. Reverted that trial in full. Keep
visible-body/interprocedural compiler knowledge in mind when reconciling it.

Inputs: BFME1 checkout 37c3022de1ab944c7ffe536440d637dc8199091c retained;
reference pointer update is claimed by another seat. Existing source flags:
/EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc,
plus the established per-row compiler selection. No donor decoder sources read.
