# Wide-string assignment COMDAT repair

The existing wide-string instantiation unit emits non-retail private
_M_assign_dispatch<unsigned short*> and append<unsigned short*> COMDATs.
The native assignment worker at 0x000130A0 is 102 bytes: copy 16-bit
characters until either range ends, call erase at 0x00013110 if the input
ends, otherwise call append at 0x00013160. The independently matched
stlport_wide_string_assign_dispatch.cpp already establishes this algorithm
and its read-only append call.

Replace only the wide type's member-template implementation in the
instantiation TU. Preserve the iterator template parameter: specializing
both levels for a concrete pointer triggers VC7.1 C1001 in _string.h:629
(and in the concrete append trial). A single template<> spelling either
with explicit inner arguments or with deduction is rejected with C2768 /
C2244. Specializing the outer string type while retaining the iterator
parameter compiles normally.

The retained implementation uses a default-initialized iterator tag and
const input pointers for the established read-only append provider. The
header's visible erase was initially inlined, producing a 121-byte
assignment copy. A noinline specialization with the original STLport
erase body preserves its owned 65 bytes and makes the assignment worker
exactly 102 bytes, including every native call destination. Explicitly
instantiate the already-rowed allocator function, which was previously
emitted only through the removed competing append instantiation.

Verification: normal focused build passes all 19 owned rows and both named
imports. explain_mismatch verifies the complete private assignment worker
at 0x000130A0 as exact. Placement resweep finds no new bodies or pins;
find_declared_unmatched and diff whitespace checks pass. Paired local
link_check with the public assignment and const append providers changes
343 -> 842 nonpadding linked bytes (+499), with all three units linking.
Measurement index: 491a8b3d87, 2026-10-23 03:12 UTC. This is a local preview,
not a new census, closed-strict link or runtime test. No ledger rows,
pins, aliases, shared headers, or compiler flags were changed; the extra
exact private spelling does not claim another 102 bytes of recovery.

Sources of evidence: target instructions and current byte-verified BFME2
providers; STLport 4.5.3 vendor erase semantics. This is not a BFME1 donor
transfer. The seat's reference remains pinned at
138757e9b74645fbcbb7724a7af2764e34931e11; the user-designated s1 donor is
unpopulated. No donor identity claim rests on a masked placement.

model=gpt-6-astra seat=s4
