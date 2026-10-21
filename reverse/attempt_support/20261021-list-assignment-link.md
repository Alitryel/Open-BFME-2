# Opaque-record list assignment link repair

Target: `0x000BDBFA`, 115 B,
`Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva000BDBFA.cpp`.
The existing row identifies an STLport list assignment; element spelling and
layout remain donor inference. No application identity or additional layout is
claimed. The target call displacement reaches the existing range-erase owner
at `0x002FECD3`, `list<AsciiString>::erase(iterator, iterator)`.

The unit previously instantiated its own opaque-record erase and referenced an
undefined record destructor. An inline typed adapter now calls the existing
canonical erase provider. It transfers only iterator node pointers, preserving
the native call and avoiding invented cleanup for the opaque record. No pin or
alias was added.

Paired current-object legacy predictions against census `d08db10acb`
(2026-10-21 18:42, retail-truth-2): 0/1, 0/115 B before; 1/1, 115/115 B after.
The byte gate passed the complete 115-byte body and its call relocations.
`find_declared_unmatched.py` passed. Self-strict reusable provider preparation
is recorded separately from this legacy prediction; no closed-strict closure
gain is claimed.

Cause sweep: the indexed second candidate `0x002FFC74` also has a private
destructor reference, but a current check finds three additional COMDAT losers
and a wrong selected assignment definition. An erase-only repair cannot link
that unit. No source edit was made there; its evidence is logged and both
claims released. It needs coordinated provider/layout reconciliation.

Local before/after, byte and preparation logs:
`build/link-seat-20261021d/listassign-*`.

Pre-existing shadow identity debt: the commit hook reports the existing private
record insert binding to `0x000BD24A` as wrong. The insert helper's 30-byte COFF
byte-and-relocation digest is `936283378db2` both in the published census object
and after this repair; this change does not modify that helper or pin. The
shadow finding remains unresolved and is another reason not to claim closed
strict linking. Diagnostic receipt: local
`listassign-insert-shadow-comparison.json` and `listassign-identity-detail.json`.
