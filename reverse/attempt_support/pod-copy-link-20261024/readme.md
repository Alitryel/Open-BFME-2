# POD vector configuration and typed-copy link repair

At BFME2 49304d5015, the no-exception and malloc POD units had 2,451 matched
bytes between them but linked none with their current objects in the same
preview. Published census: 268f876e3b, 2026-10-24 02:54, retail-truth-4.

The malloc unit provided the first vector<BfmePod44>::_M_insert_overflow,
but its EH-enabled 240-byte body displaced retail's 189-byte no-EH body
at 0x00081AF2. Restore the existing STLport 4.5.3 _vector.h algorithm for
this specialization without the exception wrapper, and bind its allocator
to the existing retail provider. Keep the implementation compiler-visible:
a declaration alone initializes the unused empty tag and changes the rowed
0x00082819 fill-insert caller's stack frame. The resulting overflow has
retail's bytes and relocations in link_check; all twelve rowed malloc bodies
also remain byte-exact. This is a prerequisite of the no-EH unit's gain,
not a claim that the malloc unit itself now links.

The no-EH unit also emitted generic copies for records of the same size
but different copy identity. The 0x00541434 constructor needs the 28-byte
Rva00541021 uninitialized-copy family at 0x005411C8, not the generic
0x00215F38 helper. The 0x0052C823 constructor needs the 32-byte
Rva003A6F70 family at 0x0052C27E, not 0x00421D28. The 28-byte reserve
at 0x00541BDF and insert at 0x005849EF reach the corresponding unresolved
copy/fill families. Record size alone is not an identity proof.

Two binding trials were rejected and restored. Explicit typed helper calls
first introduced exception handling into the constructors; adding throw()
and preserving default-initialized empty tags removed that difference but
still loaded the three pointer arguments into registers before pushing,
where retail pushes the fields directly from memory. Both constructors
therefore exceed their 71/68-byte bodies. The failed candidate patch and
exact gate diagnostics are preserved here, not compiled as game source.
Do not retry this wrapper approach without new code-generation evidence.

Move those four unchanged explicit instantiations (269 bytes) with their
original declarations and compiler configuration to
stlport_pod_noexc_deferred_copies.cpp. The remaining thirteen rowed bodies
(1,162 bytes) are independent. No row identity, ABI, compiler flag or pin
changes. Original placeholder provenance remains in each source. The donor
review used verified Open-BFME-1 pointer
32774ab03393709a7f14331ba8d98d281a55ffd9; no donor update was needed.

Paired command on the same two indexed sources:
`python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/stlport_pod_noexc_bodies.cpp Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_malloc_bodies.cpp`
changed from 0/2 linking (0 bytes) to 1/2 linking (1,162 bytes). The deferred
source is absent from that census and contributes no claimed gain. This is
a legacy scoped provider preview, not closed-strict closure or a new census.
Scoped strict input receipts and normal full byte gates cover all 29 rows
(retained 13, deferred 4, malloc 12); declaration and CSV checks pass.

Remaining malloc conflicts: the 40-byte __copy, 8/16-byte const
uninitialized copies and allocate-and-copy helpers, and 8-byte overflow /
fill-insert. They need their own target-supported copy contracts; do not
rename by stride or suppress copies that a kept caller actually needs.
