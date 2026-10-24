# Bind four record consumers to their existing placement-copy provider

Four current files share the same undefined _STL::_Construct specialization:
the 186-byte assignment, 180-byte overflow, 38-byte uninitialized copy and
55-byte append. The actual 45-byte Rva0040B14EConstruct provider already exists
in Common/Thing/Rva0040AEE3Construct.cpp, with its verified copy constructor
and exception graph. Its type is the same existing Rva0040AEE3 view.

Expose a TU-local forced-inline overload before the reference loops are
parsed. It directly calls that real typed provider without any cast.
Remove the obsolete declaration-only specializations. The loops and their
visibility remain, unlike earlier attempt 81807's unsuccessful helper
suppression. No header, flag, pin, alias, owner row or class name changes.

Target evidence supplies the 16-byte stride and native constructor edges:
40B14E calls the copy constructor at 40AEE3; native copy38 at 40B2FD,
fill37 at 40B1A8, overflow180 at 40B834 and append55 at 40BA33 call the
placement-copy chain. The source's application record name is not recovered.
The assignment's separate BfmeRecord0040B61A view still has uncertain fields;
this patch changes none of those fields or their operations and makes no
new claim about their meanings. Existing vector<int> identity debt discussed
in attempt 83536 is separate and is not concealed with a pin or alias.

Reference STLport 4.5.3 supplies the algorithms. The existing target provider,
its measured receiver and native calls supply binding and ABI evidence.
BFME1 remains at the already verified 0bf534ea7ccde110c456edb9cd2dd5dae823c953.
Only the typed construction call is adapted; the target's semantics and
relationships stay intact.

Fresh before/after and production compiles preserve all four complete owned
bodies. The assignment's raw bytes and every relocation are identical; the
other three change only one constructor relocation name each. Its visible
38-byte helper is independently exact at 40B2FD with its actual constructor
call. Every changed unit keeps the same external defined names. Each local
forwarding copy has static COMDAT storage and zero runtime references; its
sole reference is discardable debug metadata.

Normal gates pass all 6 rows across four consumers and the provider.
All four changed units have strict current receipts and pass frozen-file
checks. The provider's full EH graph is EXACT, with no baseline or missing
object. The placement follow-up serves zero bodies and zero pins.
Paired previews keep the provider at 55 linked bytes and change all four
consumers from zero to 459. An existing unreferenced assignment-deallocation
diagnostic remains. These are existing bytes predicted linkable, zero new
C++ recovery, and no claim of a new census or executable smoke test.
