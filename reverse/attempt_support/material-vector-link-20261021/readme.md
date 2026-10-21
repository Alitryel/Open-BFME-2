Material collector shader-vector binding

Inputs: BFME2 eca9a2dbd8; published census c7845fd6e7 (2026-10-21
15:41); BFME1 donor 00c2ffbb23e9154fbe9970954afacb04e4943dd7.

Native evidence: the rowed 170240 constructor calls VectorClass<ShaderClass>
at 16FB40, installs BD46A0 at member +0, and initializes growth/count at
+14/+10. Its state-0 unwind calls 16F960. That address already belongs to
DynamicVectorClass<ShaderClass>'s virtual destructor in matinfo.cpp; the
private nonvirtual ShaderVector declaration had no link provider. The native
BD46A0 table's six entries are 56FFB0, 596920, 56FF00, 56FED0, 5969C0,
554BE0. VectorClass's destructor/equality/Resize/Clear/two ID interface in
BFME1 game/Libraries/Source/WWVegas/WWLib/vector.h supplies the source
contract; target constructor, vtable, unwind and existing providers establish
the BFME2 relationship independently. No new function identity is claimed.

Replace the private shader member with that real template specialization,
declare its native virtual interface and let its C++ constructor install its
vtable. Vector base size 10 and derived size 18 are retained. The explicit
external vtable declaration and store disappear; no new alias or pin is used.
Only this source had the private ShaderVector declaration. The unrelated
TextureVector diagnostic is unreferenced and was left alone.

Acceptance: find_declared_unmatched passes; ./build.sh passes 4/4 whole code
rows; eh_verify reports 1 EXACT; link_check --prepare-current succeeds before
and after with strict reusable receipts. Same-index explicit-unit legacy
link_check moves 0 -> 173 B. This is not a closed-strict measurement. No new
retail C++ bytes or ledger rows; all existing rows remain byte-exact.
