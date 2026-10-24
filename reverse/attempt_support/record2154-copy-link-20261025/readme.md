# Use the existing native record-construction provider

stlport_vector_record_2154f3_allocate_copy.cpp uses a 16-byte record containing
an AsciiString followed by vector<AsciiString>. Its declaration-only
_Construct specialization has no linker definition. The real native
placement-copy provider at 21559C already lives in
StringVectorRecordCopyBFME2.cpp under the BfmeVectorRecord002154F3 view.

Target evidence establishes the relationship: the four complete callers at
2155C9, 2155EF, 215895 and 215A51 all call 21559C. That matched 45-byte
provider calls the matched 61-byte record copy constructor at 2154F3, whose
members copy the string at offset zero and the string vector at offset four.
Both existing views agree on this 16-byte structure and purpose. The original
application identity is still unknown; similar spelling alone is not proof.

The STLport 4.5.3 vector algorithms remain unchanged. A TU-local forced-inline
overload forwards the old view to the actual typed placement-copy provider,
declared before the vector templates are parsed. Remove the now-unused
declaration-only specialization. There is no new pin, alias, owner row, shared
header, compiler flag or renamed class. Existing candidate pins are unchanged.

This follows the already verified local forwarding pattern from
stl-fill-owner-repair-20261023. BFME1 revision
0bf534ea7ccde110c456edb9cd2dd5dae823c953 and the earlier reference review
supply string semantics; the target's complete caller/provider bodies supply
the ABI, offsets, stride and addresses. Prior link-seat-hash-string-20261022
repaired a separate erase declaration; its provider was linked at that older
index. The current unresolved construction name is independently reproduced.

Fresh isolated original/after compiles and the production object agree on
every complete existing non-EH body. Exactly four relocation names change,
each from the undefined view's _Construct to the existing provider at 21559C;
their native REL32 destinations are independently decoded. External defined
symbol sets are identical. The compiler's discardable local forwarding copy
has static COFF storage and no runtime reference; its only reference is debug
metadata. Its absent-from-retail annotation describes that local glue.

Normal verification passes 41/41 bodies across consumer and provider. The
consumer has a strict current receipt, the frozen-file check passes, and all
14 combined exception graphs are EXACT without baseline debt or missing
objects. The placement scan serves zero bodies and zero pins. Paired current
previews hold the provider at 1044 linked bytes and change the consumer from
zero to 676. This is 676 existing bytes predicted linkable, zero new C++
coverage, and no claim of a fresh census or executable smoke test.
