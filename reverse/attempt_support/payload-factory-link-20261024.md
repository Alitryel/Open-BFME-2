# Payload factory link repair

Inputs: BFME2 c509a593c8; unchanged verified BFME1 32774ab03393; published
retail-truth-4 index 268f876e3b (2026-10-24 02:54 UTC). Existing donor linking
review remains applicable; no new donor or identity claim.

RvaPayloadValueReturns.cpp contained three 50-byte factories and three
68-byte clones. The clones inline payload copies and emit vtables that need
the missing complete destructors of Rva005FAAA1, Rva005FAB16 and Rva005FAB9E.
The factories call the already matched constructors and need no such tables.
Move only the three existing clone rows to RvaPayloadValueReturnsUnresolved.cpp;
retain their declarations, compiler flags, class sizes and full bodies.
The original indexed unit now contains just the factories.

Paired current-object legacy previews: before 0/354 bytes with three undefined
complete destructors and four competing vtable/deleting-wrapper copies; after
LINKS 150/150 bytes. The unresolved unit is not claimed to link. The two units
pass 6/6 whole-body byte/relocation and string/float/import checks with strict
reusable compiler receipts. Staged peer COMDAT admission and frozen-definition
checks pass. No new pin, alias, marker, function identity or authored coverage.
Closed-strict closure remains unmeasured; no census or full link runner used.

The remaining three clones require complete-destructor and vtable identity
reconciliation. Keep their existing target-derived names and documented ABI.
Other payload factory sources already separate allocation from inline cloning;
there is no further supported split in this family.
