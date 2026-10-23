# Waypoint and storage-base lifetime review

Inputs: BFME2 ea9c37350e, BFME1 a18d9ed50607e9175de4d6568798d7d73119de09,
MSVC 13.10.3077; /O1 /G7 /Ob1 /MD /EHsc, static STLport and bfmealloc shim.

Target facts: waypoint selector 001F21E8..001F22A3 is 187 bytes, RET4.
WB B082D0 corroborates prefix matching, waypoint links/name/position and the
ObjectCreationList.cpp line 1973 diagnostic. Native unwind parents are
[-1, 0, -1]: an allocator temporary, then the vector storage. The existing
NuggetCreated destructor at 001F22A3 transfers to storage cleanup 001F1609.
The latter is 43 bytes through 001F1634; its sole unwind state cleans the
allocator proxy at this+8, with an empty callback at 000B3FD0.

The existing Object-pointer storage view is supported by creator/copy/consumer
ABIs; this is not independent proof of EA's original container spelling.
No new names, pins or rows were admitted.

This pass reproduced both complete bodies and their EH graphs in diagnostic
builds by specializing the allocator destructor with
`if (enum_constant_zero) ::free(this);`. This is **rejected**: the operation
has no donor or target provenance. It repeats the rejected dead-deallocation
probe in crack-d-allocator-eh.md. Exact bytes alone do not repair that flaw.
Clean BF2 vendor, bfmealloc and BF1 vendor headers all have inline-empty
allocator destructors and implicit proxy destruction. Original ZH allocator
configuration supplies no such destruction operation. BF1's monetary barrier
reconstruction is not independent original-source evidence.

A default allocator argument on an inline NuggetCreated constructor, with
the real base destructor declared out of line, resolves the wrapper call
without an alias. Removing the dead branch gives an honest 183-byte parent:
first difference +0xF, with the native allocator-temporary state and its
store still absent. It is not a better bank than the existing saved candidate;
that bank is preserved. A pre-header C++ free declaration reproduces the
free ABI but does not by itself retain empty allocator cleanup. Explicit
class instantiation legitimately emits the diagnostic base specialization;
it does not justify the rejected destructor body.

Further progress requires a supported allocator/proxy lifetime or compiler
context, rather than more variations of the already disproven empty-dtor
and dead-operation levers. No nonmatching production source remains.
