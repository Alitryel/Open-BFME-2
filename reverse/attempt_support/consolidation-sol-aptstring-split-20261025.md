# AptString split composition prerequisite, 2026-10-25

Seat codexb, Libraries pool. After member-lookup composition, split's private
m_text names conflicted with the selected value/AptString declarations, and
selected EAStringC/AptValue views omitted existing split methods. Its string
accesses now reuse the existing ScopedStringText +8 view; unused manual prefix
fields are removed from its method-only class views. Add the donor's existing
copy constructor, Find/Append and SetString signatures to the selected views.
No new name, field offset, vtable layout or external identity is inferred.

Acceptance: ./build.sh on AptString.cpp, AptStringObjectMemberLookup.cpp,
AptStringSplit.cpp, AptStringCharCodeAt.cpp and AptStringFindCallback.cpp
preserves 30/30 rows, including split's 685-byte parent and all eight rows it
owns. Nineteen literals verify. All five EH parents are EXACT with no missing
objects; the existing funclet rows remain bound through EH despite compiler
label renumbering. Declared-unmatched passes for all five sources. Data and
code identity report zero new findings (identity remains shadow). The SDK
scan has zero local definitions; owning scoped queue refresh is unchanged.
No canonical or protected data/identity/header key is moved or retired.

The ordinary final dry run accepts all five sources together, 30 rows,
versus the previous 22-row subset. Leave the now-compatible Libraries donors
for Luna. The only ordinary rejected donors are Common's Rva006D74E0Cluster
and Rva006D7D00Cluster, which require additional methods and m_str member
reconciliation outside this pool. Seven protected-register files and the
mixed deferred donor remain untouched. No merge or split was applied here.

Receipts: build/sol-apt-split-{plan,build,after,eh,data,identity,headers,queue}.txt
and planner build/sol-library-planner-split.txt. The preceding lookup dry run
is the before receipt. Files removed, recovered C++ bytes and identity keys
retired are zero. This session removed one separate Microsoft-header ABI queue
entry in the earlier charCodeAt prerequisite, not an identity-register key.

Publication audit against origin/master 97b2c77498 plus these staged changes
finds no source path changes. Tools, hooks, workflows, includes, build inputs,
registries and historical EA paths require no repointing. Earlier mesh/tree/Apt
commits are confirmed published; their finished claims are released. Retain
file claims for AptString.cpp, AptStringObjectMemberLookup.cpp, AptStringSplit.cpp
and this handoff, plus 0x006D77B0, until this final commit is published. If the
runner holds it, the next session should release those scopes after landing.

Other session handoff: tree's normal compatible subset is 22 rows and meshmdl's
is 11 rows. Tree movement remains blocked on byte-exact SSE scheduling; see
consolidation-sol-tree-move-20261025.md rather than repeating unchanged probes.
