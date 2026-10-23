# Complete the hash-map payload copy

2026-10-23, gpt-6.1-sol. Parent b226462442; published census b711de3634,
2026-10-23 14:28, retail-truth-4. BFME1 remains the verified 96c88c73
input; no donor source or shared header was changed.

StlSweepR3Rva002A3FAF.cpp's 176 existing nonpadding bytes were held out by
its undefined Rva002A3FAFRecord copy constructor. Native operator[] at
0x002A3FAF calls pair construction at 0x0029FB63; that complete 29-byte
provider copies the integer key and calls 0x0029E067 for its payload at +4.
The existing neutral copy provider there establishes two AsciiString handles,
scalar accesses through +0x30, and a 52-byte object. Implement those accesses
in the private record view, retaining its existing constructor/destructor
bindings and compiler settings, with the established AsciiString shim include.
The application-level identity and field meanings remain unknown. These layout
facts come from target accesses, not donor type names.

The entire 127-byte copy and all relocations match the existing owner at
0x0029E067. add_match admitted the gen-alias with that owner's ledger source
as fold-proof. No pin, address alias, or new unique retail coverage is claimed.
A search for the same private record name finds only this source.

Paired current-object legacy previews against the same published index:

- StlSweepR3Rva002A3FAF.cpp: 0 -> 176 B, LINKS.
- Rva0029FB63Init.cpp: 29 -> 29 B, LINKS.
- Rva0029E067Ctor.cpp: 127 -> 127 B, LINKS.
- Total: 156 -> 332 B, **+176 B linked**.

Acceptance: scoped byte gate passes all six rows in the edited source;
link_check --prepare-current passes all eight rows across these three sources
and creates strict reusable compiler receipts. find_declared_unmatched,
check_csv, and link_check --new-variants pass. Renumbered cleanup labels resolve
through their verified parent EH data. The measured gain is a legacy preview;
strict link closure was not checked and no closed-strict gain is claimed.
Census/index/status are unchanged. Diagnostics are in ignored
build/link-seat-record-{before,after,strict,add}.log.
