# Table destructor 003EF22B: native vector cleanup prerequisite

The whole 19-line source and its existing two rows (57-byte destructor and 5-byte cleanup forwarder) were reviewed. Its parent and associative EH graph pass the existing tools, and the original unit links, but those checks do not establish the unbound cleanup callee.

Native cleanup 00783909 adjusts the saved receiver by 4 and jumps to 00027370. That address owns the complete 131-byte STLport vector<void *> destructor in stlport_vector_voidptr_alloc.cpp. The current source instead emits the distinct 14-byte S3RegionBucketStorage destructor. It cannot be admitted as a fold or substituted for the native owner. Handler00783914 and cleanup00783909 remain unclaimed recovery work.

A reference trial replaced the three-pointer storage surrogate with the actual STLport vector<void *> from committed BFME1 f52d3a5cb41976aafa760e8db12c4bfdb2be91e8. With the existing bfmealloc headers, the free call and EH state transition differed. A local allocator<void *>::deallocate specialization calling the already verified throwing Rva00030830GameFree provider restored both complete parent rows exactly. This is native-supported allocator behavior, not evidence of a new payload identity.

The resulting unit did not link: it emitted competing allocator, allocation-proxy, vector-base and vector destructor COMDATs; the latter two differ from retail's kept bodies. The full native vector owner uses /Od /Ob1 and is already independently rowed. Do not pin the 14-byte surrogate onto its 131-byte address or accept only the parent-byte result.

The source was restored byte-for-byte. Ignored local receipts: build/resume-oct19-table3ef22b-preflight.log; table3ef22b-eh.json; vector-trial2.log; vector-trial3.log; reference-trial.cpp (each prefixed resume-oct19-). Continue after a supported reference configuration preserves parent inlining while binding EH calls to the actual kept vector destructor without competing definitions.
