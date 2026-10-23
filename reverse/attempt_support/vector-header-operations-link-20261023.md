# Vector-header operation bindings, 2026-10-23

Inputs: BFME2 cd95b5739e plus the three carried lifetime repairs; published
census b711de3634, retail-truth-4. BFME1 verified pointer96c88c73 remains
unchanged; its linking repairs and prior donor handoffs were already reviewed
at that revision. This repair uses target callback relationships, not a donor
identity transfer.

Rva004CE36Dtor.cpp's current object was 0/170 nonpadding bytes linked, with
only Rva0004CDAFSlot's constructor and destructor undefined. Native constructor
4CDCD passes callback256646 to the EH vector constructor iterator for two
12-byte headers at AC; it passes cleanup4CDAF for exceptional teardown. Native
destructor4CE36 passes the same cleanup to the EH vector destructor iterator.
Both callbacks take ECX and no stack arguments.

The existing row at256646 is the complete13-byte default-vector closure in
ModuleFactory.cpp. The existing row at4CDAF is vector<RvaSmartPtr12>::_M_clear
in StlportVectorInsertOverflowFamily.cpp. Its complete30-byte operation destroys
the element range and deallocates the header's storage; STLport's _M_clear does
not reset the header. These are the constructor's and destructor's actual
callback targets. Bind the private header view to these existing names without
introducing pins, another global, or an application identity for the payload.

Paired current-object legacy previews include both provider units: consumer
0 ->170 B, providers unchanged at0/9375 and0/2421 B. Their unrelated unresolved
and COMDAT blockers remain, so this is not a closed-strict link claim. Normal
byte gate4/4, all literal/import checks and scoped strict receipt preparation
pass. The existing funclet label is renumbered naturally and resolved by its
exact parent EH graph. No census, baseline or verifier changes.

Sweep: SlowDeathBehaviorModuleDataCtor already links467B on current master;
Rva0007517FCtor.cpp already links641B. Neither is new gain. The split7517F
constructor still needs both the vector closure and its separately named
class destructor; its private full vtable contract needs reconciliation before
claiming a complete repair. Rva007AEA2CArrayInits additionally needs three data
providers, a callback-iterator ABI repair and several differently spelled
callbacks. Do not treat either as the same isolated two-operation repair.
