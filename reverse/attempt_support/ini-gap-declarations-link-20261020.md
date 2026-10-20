# INI gap parser declaration repair

Base c274d41623; census 3f413ed3ff, 2026-10-20 18:52. Current-object
legacy preview of GapBodiesS3E_Rva003F9CD2.cpp links 0/393 bytes before
and 393/393 after. All four current rows verify (394 retail bytes): the
factory, formation parser and two nested-block callbacks. The twelve
literal references, float/import checks and undeclared-definition check
pass. link_check --prepare-current verifies all four rows with a strict
reusable receipt; this is self-strict evidence, not closed-strict closure.

The factory calls the recovered Rva003F9D08 constructor at 0x003F9C11.
Its target-proven 0x74 allocation and existing nonthrowing caller contract
stay the same; the static parse table retains its existing owner name.
The nested callbacks now declare the C61830/C61884 tables as three-entry
arrays, matching their data_rows providers Rva004E1BFCParse.cpp and
Rva004E1C7BParse.cpp, rather than unresolved scalar FieldParse spellings.
No new pin, alias, marker or data definition is needed. The other occurrence
of the old table declarations is unused in GapBodiesS3E.cpp and emits no
reference, so changing it would not repair additional linked bytes.

Provider preview: constructor and Rva004E1C7BParse link; Rva004E1BFCParse
still has separate TracerFXNugget vtable/constructor blockers. No provider
closure or full link-cycle gain is claimed. BFME 1 pointer reviewed this
session: 4483e88da1c2f3b9a273f779baac7458bd8bb891; this repair is based
on the already verified BFME 2 constructor, table definitions and calls.

Recovery reconciliation: c3a5a6851b already landed the same constructor
and array-name repairs. Preserve upstream source (including its compatible
unsized array declarations); this saved report records historical evidence
and adds no new linked bytes relative to the synchronized upstream.
