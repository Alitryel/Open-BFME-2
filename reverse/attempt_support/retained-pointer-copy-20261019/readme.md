# Native retained-pointer copy at 001494F0

The clean BFME1 library compile sweep found this 22-byte body in two donor
units. Earlier repair evidence correctly warned that its donor names are
already pinned in BFME2 to the distinct 21-byte body 000424BB. Neither pin is
changed. No additional original class or TextureClass identity is claimed.

The native body is independently bounded by eight INT3 bytes before its
16-byte-aligned start and ten after its RET4 at 00149503. It receives a
destination in ECX and one source-reference stack argument, copies one pointer,
increments the nonnull pointee's unsigned WORD at +4, and returns the destination
in EAX. It has no calls, data accesses through image addresses, surviving direct
callers, or address references. The address-derived class records exactly that
four-byte copy representation; constructor interpretation is structural inference
from its copy/retain and return-this ABI. The original name and pointee type are
unknown. This is a direct ordinary-C++ reconstruction of the complete native
effect, not adoption of the donor's unresolved type identity.

It lives in the existing MaterialRemapTexture.cpp unit whose O2/G7 settings
produced the donor lead and whose owning-handle operations share this retain
behavior. Both complete rows pass the normal byte gate. The new row has zero
relocations, zero masked bytes, no assembly, pins, aliases or scheduling devices.
An independent execution comparison covers null/non-null pointers, separate and
overlapping source/destination, WORD wraparound and ordinary counts (32 cases).
It compares the full 4KiB data area, return pointer, RET4 stack cleanup and all
callee-saved registers; an explicit semantic check confirms only the selected
pointer and counter effects. This does not infer callers or a complete pointee
layout. proof.json records the exact body hash and boundary evidence.

Normal strict-current link admission passes. The whole unit links in the local preview against published index 8eecc93d07: 199 to 221 bytes (+22); this is a bounded prediction, not a new census. Placement resweep reaches a fixpoint with zero additional bodies or pins.
