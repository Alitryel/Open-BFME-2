# Callback-holder unwind ownership blocker

Whole Common/Rva0044BF40.cpp (78 lines) reviewed with whole
Common/Rva004F6986Dtor.cpp provider. Parent constructors44BF40/44BFB2
are55B each and both install handler78970F / FuncInfo93798C.
The graph places the8B cleanup789707; it inherits EBP and takes the
by-value pair at frame+8. Native bytes are:
  8d 4d 08 e9 3f 23 cc ff
The jump reaches44BA4E, the complete61B two-reference destructor.

The source instead emits a call to Rva004C5DD0's wrapper destructor.
That emitted body is only5B, E9 plus a REL32 relocation to the rowed
Rva0044BA4E destructor. It is not the native61B callee and must not be
admitted as a byte-and-relocation twin or folded alias for it.

Tested one new hypothesis: __forceinline on the existing wrapper destructor.
Both55B parents still match and both EH graphs still report EXACT, but the
generated funclets still reference the same5B wrapper. Explicitly reading
the emitted callee exposed the difference. The source edit was reverted
byte-for-byte and the restored two-row unit passed build.py again.

The existing caller/provider pair verifies11/11 rows and both units predict
link-clean (401 bytes at the same old census), so those aggregate checks
alone do not prove the new cleanup claim. No handler or cleanup row added.

Remaining prerequisite: reconcile the actual owning pair lifetime and its
callers, or prove a compiler shape that emits the native direct61B destructor
call from the inherited-frame cleanup. Do not pin the5B wrapper to44BA4E.
The original source and generated cleanup row remain intact. Native graph
evidence is the starting point; no adjacency-based parent assignment.
