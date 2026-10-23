# Armor helper link repair, 2026-10-23

Base: 35a3505af5; published census index 456ce161c5 (2026-10-23 06:28).
Same six current sources before/after: ArmorHashMapErase.cpp,
Rva003ED2A3ManagerRemove.cpp, Common/RTS/Rva002AD19EArmor.cpp,
ArmorRva003A28ED.cpp, ArmorRva003A2897.cpp and Rva002AD13F.cpp.
Scoped legacy preview before: 4/6, 358 B; after: 6/6, 511 B (+153 B).
The 123 B threat-manager unit and 30 B erase wrapper newly link; the four
other units already linked with their current sources and are not credited.

Threat-manager callers retain their standard find wrapper but declare its
member-template lookup and hash-map erase out of line, using the existing
providers. The member-template declaration must specialize the containing
class while retaining the member template (`template <> template <class Key>`).
An attempted full member specialization caused MSVC 7.1 C1001 at _hashtable.h:488.
Changing the equality type is unnecessary; the final change preserves it.

ArmorHashMapErase keeps its table-erase definition. Declaring that whole
operation out of line removes the only current definition and regresses two
peers. Declaring only the bucket helper, including extern-template form,
leaves an unresolved call. An import-inline specialization of the normal
STLport identity-hash/modulo calculation retains the native inline behavior
without emitting the incompatible external bucket copy or an IAT reference.
The specialization has no standalone retail body and is annotated accordingly.
No new symbols, pins or ledger rows are introduced. The legacy bucket pin
53EA8 names a pointer-keyed helper whose provider explicitly distinguishes it
from the Armor calculation; it is not evidence for a second Armor body.

Acceptance: all 3/3 owned rows byte-exact; string, float and import checks
pass; declaration checks pass. Both sources prepared with strict reusable
byte receipts. No owned row has EH data. These are self-strict byte checks
and a scoped legacy linking prediction, not closed-strict or placed gains.
No full census, link cycle or boot runner was started.
