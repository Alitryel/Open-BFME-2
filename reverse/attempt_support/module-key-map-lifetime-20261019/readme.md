# Independent module key-map lifetime

The old dup_004ABCFE row owns56 bytes through an object-symbol annotation
to a different tree destructor at286852. Its own notes explicitly preserve
unresolved identity. The legacy annotation is not a gen-alias token, so
normal admission requires a separately reviewable retraction before a real
name can own this address. retired-row.json preserves that exact record.
No OpenContain source or canonical tree owner is changed.

Native4ABCFE destroys the tree through clear4ABC5C and then frees the
owning header pointer at offset0. clear4ABC5C independently proves the
node count at+4 and the header's parent/left/right links. The receiver's
remaining four bytes at+8 are opaque. The native8-byte EH action78E2B4
reaches the existing14-byte conditional-free body7FAB3. These establish
the lifetime and layout without establishing original key/value types.

The native registry cleanup4ABE53 passes its member at+4 to4ABCFE.
Its vtable C549F0 names the already owned119-byte key-list method4ABDDC,
whose target evidence establishes the module-key registry role. The old
constructor view's set<AsciiString> spelling is inherited uncertainty,
not independent element-type proof. In particular slot0 is that business
method, not a virtual destructor; recovering4ABE53 must preserve the real
table rather than create a new virtual-destructor view. That caller is
left unchanged here.

The real implementation uses a simple owning-header base which frees its
pointer, a count and four opaque bytes, and a destructor which calls the
already owned clear operation. The library's existing int/void-pointer
spelling is an implementation view for that helper; no original target
template identity is asserted. A dedicated Common/ModuleDataKeyMapDestructor
unit gives this registry lifetime a coherent home. Its clear specialization
is declaration-only, using the existing provider instead of another COMDAT.

Scratch tests initially lacked the original source's regional flags; those
results do not diagnose the native body. With the actual/O1 SSE G7 inputs,
both the stock-storage view and the simpler owning-header view match the
whole56-byte parent and complete EH graph. The final small unit also matches
the complete14-byte storage cleanup. A derived whole-container destructor
only emitted a five-byte forwarding thunk and was not adopted. No forcing
pragma, artificial cleanup, assembly or new pin is involved.

This retirement and the following recovery form one publication batch.
The existing56 parent bytes and folded14 storage bytes receive no new
unique-byte credit. Pinned BFME1 cf0a80c228; target-led reconstruction.
