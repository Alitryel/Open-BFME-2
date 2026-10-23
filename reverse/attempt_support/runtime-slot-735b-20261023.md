# Opaque runtime dispatch cell at RVA 0x0000735B

The complete seven-byte entry at RVA 0x8449 pushes ECX and EAX, then calls
0x7C63. Its return address is 0x8450. The dispatcher computes
0x8450 - 4341 = 0x735B, reads exactly one 32-bit value and jumps through it.
The initial bytes are B4 5A 82 66, value 0x66825AB4. The next byte is zero
but is not read by this load and is not included in the four-byte cell claim.

Prior attempts and runtime-slot-712b-20261023.md correctly leave the runtime
writer, eventual destination, callable ABI and import identity unresolved.
This change does not invent any of those. It owns only the complete observed
mutable 32-bit cell and its file initializer. The minimum storage view is a
packed unsigned-int field, not a function-pointer prototype or a relocation
to a fictitious provider outside the image. Source comments explicitly retain
the unresolved address interpretation of the initialized bits.

The existing zero-initialized cell at 0x712B retains its unchanged declaration
and pointer initializer. Both objects are verified by the normal data gate,
which evaluates sizeof and compares their complete four-byte initial values.
This adds four data bytes to rebuilt-source coverage, not C++ function bytes,
reconstructed dispatcher behavior or a LINK census result.

The fifth bytes of the two formerly served five-byte gaps are represented as
two separate unsigned-char zero-fill objects, at 0x712F and 0x735F. Each is
between the complete four-byte cell and the next 16-byte-aligned function:
locale's copy constructor at 0x7130 and wide num_put::do_put at 0x7360.
The gap starts are independently bounded by the complete ret4 at 0x7128 and
ret18 at 0x7358. Neither fill byte is added to a pointer field or treated as a
runtime flag. Their original ownership is not inferred beyond this observed
zero fill; no claim is made that computed runtime accesses cannot reach them.
The data gate separately proves sizeof=1 and the zero initializer for each.
These two non-CC bytes already belong to the bar's denominator; owning their
fill reproduces them without changing any denominator or function count.
