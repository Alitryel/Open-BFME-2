Hero registry storage and helper repair (2026-10-18)

Target facts: the existing six matched rows in CreateAHeroRegistry.cpp address
the twelve-byte registry at VA 0x00DFE358. The data ledger names its existing
ScriptGlueRva003BE7ED.cpp storage ?g_00DFE358@@3IA. The lookup at
Rva002197A6CreateAHeroLookup.cpp already uses that storage through a vector
view. This repair applies that same binding to registration and removal.

The unsigned max overload retains the standard comparison and reference return
while giving this unit no competing external max instantiation. No pin, alias,
new global or ledger extent was added. No donor layout is newly asserted.

Acceptance: build.sh verifies all 6/6 rows; link_check --prepare-current verifies
6/6 with strict reusable receipts. data_check --enforce has zero findings;
data_check --converged has zero second names and zero unjudged rows.

Same-index current-object link_check, census c2c5ac8c27 (2026-10-18 11:36):
before, unresolved g_CreateAHeroRegistry and wrong unsigned max, 0 B linked;
after, LINKS, 343 B linked. This is +343 B legacy predicted linking. Self-strict
byte verification passed; closed-strict linking was not measured. Authored C++
coverage did not increase. Raw command logs are ignored under
build/seat-link-oct18/hero-{before,after,build,strict}.log.
