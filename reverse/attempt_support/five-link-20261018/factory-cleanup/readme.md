Factory result cleanup: MASM to natural C++

The existing 82-byte C++ factory at5FEAAF returns a counted one-word handle. Its complete native EH graph is EXACT and binds compiler-local $L1225 at7A64A9 to cleanup of the caller result home at EBP+8. The cleanup tests/clears result-state bit0 at EBP-16 and tail-jumps the already verified12-byte TreeHintRef destructor at5F8F96. That destructor identity already has a row in Rva002833A3C5.cpp and releases through7DEEF. Original concrete factory/handle types remain unknown.

Register this complete naturally emitted25-byte cleanup under its proven parent, retract the address-named MASM row with ledger_io, record its tombstone with gen_small.write_tombstones, and remove only that old PROC. No new source algorithm, emitter, pin, alias or verifier change; the existing real C++ lifetime already emits the whole native body. Normal source/remaining-MASM gate preserves130/130 rows, and the full parent EH graph remains EXACT.

A canonical-member refactor was tested and fully restored because it changed the parent's register homes and conditional release sequence. No failed trial remains in Code. This conversion changes the C++/ASM partition by25 bytes, adding no physical-byte coverage. It is incidental recovery and does not count as one of the five requested linker repairs.
