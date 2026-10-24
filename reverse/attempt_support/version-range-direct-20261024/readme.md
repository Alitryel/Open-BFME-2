# Use the native version-record destruction chain

The unchanged 51-byte range erase at 004286AF calls 002385E6. That complete
25-byte loop advances 24-byte records and calls the complete native destructor
at 00238580. Existing VersionDestructor.cpp implements both bodies: its two
owned buffers are released in reverse order. Target call relationships and
complete bytes establish this provider independently of a same-size type guess.

The old generic _Destroy<BfmeNarrowRecord00427F75*> name has another emitted
25-byte copy in StlportVectorGrowthFootprints.cpp. It advances the same stride
but calls the 59-byte destructor at 0022CCEF. That is a different record and
callee, rather than a relocation twin. Equal body shape and record size do not
justify the template pin as this caller's runtime binding. The code-identity
checker correctly reported this pre-existing wrong binding when the file was
verified for the preceding holder-copy repair.

A TU-local forced-inline overload now calls the existing real
destroyVersionRecords(void*,void*) provider directly. The opaque record type
remains incomplete here; no new field layout or original identity is claimed.
The native caller's complete instruction bytes remain unchanged. Its second
relocation now names the actual owner at 002385E6. All other existing emitted
code bodies and relocations are unchanged against a fresh isolated compilation
of the saved original source using its normal compiler settings.

The extra compiler copy of the local overload has static COFF storage, a
COMDAT section and no code or data references (only debug information refers to it). Its absent-from-retail marker
records this unused copy. No public adapter, alias, pin, ledger row, class view,
header, tool, baseline or compiler setting is added or changed. The existing
template pin and competing copy in other providers remain separate debt; this
repair does not claim that family is globally reconciled.

Verification: normal paired caller/provider gate passes 95/95 function rows,
one data row, 18 literals and two empty-string references. All nine EH rows
are EXACT with no baseline or missing object. Both explicit providers have
strict current receipts. Frozen-file checks pass. The caller file's staged
code-identity check reports 59 rows and zero new findings, removing its former
single wrong-binding finding. The complete local-helper and body evidence is
included here.

This corrects one existing code binding. It adds zero recovered bytes and no
additional predicted linking bytes beyond the preceding 2550-byte repair.
No census, placed-link or closed strict result is claimed.
