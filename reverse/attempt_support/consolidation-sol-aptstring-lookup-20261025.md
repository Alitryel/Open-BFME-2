# AptString member-lookup composition prerequisite, 2026-10-25

Seat codexb, Libraries pool. The ordinary dry run selected the lookup donor's
virtual AptString declaration, which lacked Create; its selected EAStringC
and value views also lacked existing lookup method declarations. Add those
existing signatures to the selected views. The destination's +8 string access
now uses the charCodeAt donor's existing ScopedStringText view instead of
placing manual prefix fields in the AptString class that lookup declares
virtual. No vtable layout, data offset or external identity is inferred.

Acceptance: ./build.sh on the seed, charCodeAt, find and lookup sources keeps
22/22 rows, including lookup's 1856-byte body and complete switch table.
Nineteen string literals verify. Four EH parents are EXACT, no objects missing;
the verifier resolves the existing 13 funclet rows past their renumbered labels.
Declared-unmatched passes for all four sources. Data and code identity report
zero new findings (code identity remains shadow); the SDK scan reports zero
local definitions. Canonical classes and source-keyed data/identity/header
registers own no affected key. No debt key is moved or retired.

The ordinary dry run accepts all four sources, 22 rows, up from seven.
Leave that compatible subset for Luna's normal claimed merge. Split now reaches
its own differing m_text field name and missing Find/Append declarations;
Common donors still need additional methods/member reconciliation outside
this repair pool. Protected and mixed donors remain untouched.

Receipts: build/sol-apt-lookup-{plan,build,after,eh,data,identity,headers}.txt;
planner build/sol-library-planner-lookup.txt. The preceding find dry run is the
before receipt. No merge or row move was applied; files removed, recovered
C++ bytes and identity keys retired are each zero.

Publication audit: all own pending commits since 1cd28a3a88 and this staged
edit keep source paths. Active tools, hooks, workflows, includes, build inputs
and registries require no repointing; original EA paths are preserved. Keep
the lookup file/handoff and 0x006D7D80 claims, and the earlier mesh/tree/Apt
claims, until the batch is confirmed published. Then release them for Luna.
