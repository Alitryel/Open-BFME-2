# AptString find composition prerequisite, 2026-10-25

Seat codexb, Libraries pool. After the charCodeAt prerequisite the ordinary
dry run still rejected the find donor because the selected EAStringC view
lacked its two existing methods. The fuller charCodeAt value view also lacked
the find donor's existing isInteger/isFloat declarations. Add those method
declarations to the selected views, preserving signatures and all data fields.
No callback body changes, private-name recovery or layout inference is needed.

Acceptance: ./build.sh on AptString.cpp, AptStringCharCodeAt.cpp and
AptStringFindCallback.cpp preserves 7/7 rows, three literals, and all three EH
parents EXACT with no missing objects. Declared-unmatched passes for all three.
Data and code identity report zero new findings (identity remains shadow).
The Microsoft-header scan reports zero local definitions. No protected
identity/data/header key is moved or retired, and the existing find breakpoint
is unchanged.

The ordinary final dry run accepts all three sources together, seven rows,
versus the prior three-row seed/charCodeAt subset. Leave the verified merge
for Luna. Split still needs nested StringDataC declaration-order repair, member
lookup needs compatible method/class declarations, and Common donors remain
outside this repair pool. Mixed and protected-register donors stay untouched.

Receipts: build/sol-apt-find-{plan,build,after,eh,data,identity,headers}.txt;
fresh planner build/sol-library-planner-find.txt with a passing snapshot check
before editing. The preceding charCodeAt dry run is the before receipt.

Publication audit across the own outgoing range from 1cd28a3a88 plus this
staged edit finds no source path changes. Active tools, hooks, workflows,
includes, build inputs and registries need no repointing; historical EA paths
remain intact. No merge, removed file, recovered C++ byte or retired identity
key is claimed. Keep the find file/handoff claims and 0x006D6EF0, along with
the earlier destination/charCodeAt scopes, until publication is confirmed.
