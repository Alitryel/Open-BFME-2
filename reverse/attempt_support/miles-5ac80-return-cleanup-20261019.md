# Miles 0x0005AC80 return lifetime and cleanup recovery

Input: BFME2 d8961f14c218725a3dc0890fe1dcc313d533d469 with verified BFME1
f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. This is target-led repair, not a
reference-source transfer. Existing manager identity comes from vtable
007C55B0 slot 73; original handle and metadata class names remain unresolved.

The newly matched 291-byte parent has an exact native EH graph. Its return-slot
cleanup at 0075DBAF tests state bit 0 at EBP-18, clears that bit, and tail-calls
0010F149 with the return pointer from EBP+8. Its 25th byte is RET at 0075DBC7;
that interior RET is not a separately recoverable byte. The next independent
cleanup starts at 0075DBC8: PUSH [EBP-10], CALL scalar delete 0002FD60, POP ECX,
RET (10 bytes). The graph binds it to failed allocation of the 0xC4 metadata.

The former return view Rva0036CA00Str naturally emitted a 7-byte unchecked
release, although its existing pin resolved to native 0010F149, a 12-byte
null-checked release. Masked parent/funclet bytes alone concealed that mismatch.
Use the existing Rva0010F149Handle view for this return instead. Its same-object
copy is the complete 31-byte native A8C7C body; its destructor is the complete
12-byte native10F149 body including the Release_Ref50ED3 relocation. Its raw
construction uses the existing AudioEventInfoRef constructor51914. No new pin,
private class or inferred original type is required. The vector keeps its
existing element/provider ABI.

Verified after integration: all238 Miles rows,19 strings,32 float constants and
100 imports; full291-byte repaired parent and exact EH graph; full31-byte copy
and12-byte checked destructor with all relocations resolved. The return-type
spelling changes the provisional mangled method name; a Code search found no
other declaration or caller using that spelling. Existing unchecked uses of
the old view are outside this repair.

The whole-unit EH audit also checked apparently unclaimed labels at75DC55,
75D912,75D9AC and75D7E2: each is inside an existing25-byte cleanup extent.
They must not be added as new rows. The25-byte75DBAF MASM row can yield to its
actual parent-emitted cleanup after this callee repair. Scalar delete2FD60 is
already a real21-byte C++ provider in mem_ops.cpp.
