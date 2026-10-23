32-byte geometry-record vector linking repair

Parent 0b9dc10694. Two source units, six existing rows, all exact before
and after strict current-object preparation. No coverage or row is added.

The setGeometryName consumer treats the opaque 32-byte record as trivial,
so it emitted incorrect _Construct, growth, push_back and _M_clear copies.
Bind its construction, growth and push_back to their existing rowed names.
The cleanup name then has no provider: its former copy freed memory without
running the record destructor. Define that specialization after the growth
instantiation, preserving its existing out-of-line call and compiler context.
It destroys the Rva004E2382 range through 4E377E and frees through 30830.
The full 30-byte body at 4E3C71, including both resolved REL32 calls, equals
retail exactly (no DIR32 operands, no masked or unresolved relocation).
The address-derived row in Rva004E3C71DestroyFree.cpp independently proves
that destruction identity and algorithm. Keep it and its existing name.
The existing folded pin retains its address; its proof path now names the
actual compiling specialization provider instead of the retired wrong copy.

Donor review: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790,
inputs/vendor/stlport/stl/_vector.h:493, destroys [start,finish) before
deallocation. Target bodies independently establish the opaque element's
32-byte stride, nontrivial lifetime, cleanup range identity and free entry.
No original geometry-record class identity or payload layout is inferred.
An rg sweep finds only the two changed units emitting this bad cleanup;
StlportVectorPushBackFamily already binds cleanup and growth externally,
and StlportConstructFamily already owns the proper nontrivial constructor.

Trial 1 fixed cleanup but left the consumer's wrong construction/growth.
Trial 2 declarations removed those copies, exposing a wrong push_back copy
and dropping unused inline cleanup. Final push_back declaration and cleanup
in its referencing growth unit remove all remaining blockers. All trial byte
gates passed. No generated body, import alias, pragma or new pin was added.

Acceptance: strict self verification 6/6, normal literal/import gates clean,
EH 1 EXACT, declared-definition checks clean, converged data 0 second names.
Paired legacy closure preview against unchanged published census 5366c4f808
(2026-10-20 12:21): 0 -> 343 nonpadding bytes (88 + 255), both units clean.
This is self-strict and legacy closure evidence, not closed-strict measurement.
