MoveToGroupOrderCtor link handoff,2026-10-20

Strict original17/17. Frozen e7a7769fe5 legacy0/930B: five losing
vector<void*> constructor/cleanup copies. Paired check uses the original
object under its census basename; baseline has no unresolved imports.

Trial1 declaration-only vector/base constructors and dtors changes the
rowed hashtable ctor and dtor (2/17 fail): native inline ctor/cleanup context
is required. Trial2 native constructor/cleanup bodies marked import-forceinline
and plain empty allocator dtor hits C1001 msc1.cpp2701 at base constructor
specialization line108. No emitted body or gain. Its diagnostic dtor also
lacks the native outer null guard; add that before any future compile,
though it cannot explain the earlier compiler ICE. Both patches diagnostic.

Original restored after two failed gates. Need compiler-safe constructor/
cleanup ownership preserving native visible inline context. Do not suppress
addressless unreferenced copies; these five are actual retail-truth losers.
BFME1 donor review4483e88da1c2; vendor _vector.h65..84,198..199,258
establish helper semantics; target original17 rows establish code shape.
No pin, alias, ledger or verifier change. t=8min model=gpt-6.1-sol.
