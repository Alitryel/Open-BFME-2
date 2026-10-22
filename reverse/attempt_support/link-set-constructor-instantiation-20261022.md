# Set constructor instantiation sweep

At parent a3f28ce143, census 08160bc2c9 (retail-truth-4), six
StlSweepW4 units recovered only a 25-byte default set constructor but
explicitly instantiated the entire set class. This emitted unrelated insert,
copy and comparison operations needing undefined opaque-element methods.

For 002F307A, 00463D59, 004FFE96, 00502D48 and 00558D6B, instantiate only
the rowed constructor. MSVC additionally instantiated the unused member-tree
destructor (clear -> erase -> undefined element destructor); declare that
specialization without defining it in these constructor-only units. COFF
inspection confirmed that the set constructor only calls the existing,
pinned comparator/allocator tree constructor, not the tree destructor.
The element declarations, inferred layouts, flags, pins and row names stay
unchanged. No new identity or layout claim is made.

Paired legacy previews used the same explicit five-file list for the first
four repairs plus unchanged 004DA329: 0 -> 100 B. A second paired preview
for 00558D6B is 0 -> 25 B. The combined six-file preview gives 125 B in
five linked units. The six types have distinct names and no cross-unit
references, so these gains are independent. This is **125 B newly linked**,
not new authored C++ coverage.

The 004DA329 unit also emits a required tree constructor that is not retail
at its existing 0x4D9B18 pin. It is unchanged and remains blocked; narrowing
alone would not fix it. A re_log.py record preserves this prerequisite.

Acceptance: ./build.sh passes all five owned rows. --prepare-current verifies
all five providers' self-strict compiler receipts. find_declared_unmatched
passes. Link gains are legacy provider previews; no closed-strict result or
census status change is claimed. A scan of full-class set instantiations in
StlSweep units found no additional constructor-only unit beyond these six.

Local logs: build/link-set-inst-{before,after,after2,final,byte,byte2,strict}.txt,
build/link-set-558d6b-{before,after,byte,strict}.txt. Original source backups
are build/link-set-<RVA>-original.cpp.txt. The first narrow-instantiation trial
removed copy/comparison requirements but still emitted the unused destructor;
the declaration-only specialization removed that last requirement without
changing a rowed body.

## Shadow identity limitation, explicitly compared

The hook reports five wrong/unknown callee bindings. Rebuilding all five
original sources and running allowed_symbols.py reports the same five
wrong/unknown bindings as the repaired sources (identical diagnostic logs).
A COFF digest comparison, including relocations, proves every retained
COMDAT is unchanged: no added or changed body. Only unrelated emissions
are removed. Thus these are existing identity-certification gaps, not a
new runtime binding or proof that the callees are retail. The legacy
predictor admits these unknown copies; closed-strict gains remain unproven.
The comparator/allocator tree constructors and their base constructors
need reconciliation with the address-derived row owners before making
that stronger claim. Logs: build/link-set-{original,repaired}-identity.txt,
build/link-set-{original,repaired}-byte.txt and
build/link-set-coff-comparison.json.
