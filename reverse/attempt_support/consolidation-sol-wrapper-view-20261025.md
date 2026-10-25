# NetCommandWrapperList declaration prerequisite, 2026-10-25

Seat codexb, family B shard 0; allocation check authorizes
Code/GameEngine/Source/GameNetwork/NetCommandWrapperList.cpp. The prior pool-prefix
repair cleared the BfmePoolGlue hoisting failure, but ordinary composition still
rejects its three-row ready-command donor with C2248: class union puts the node
constructor under protected access. The seed's legacy headers also supply the
pooled NetCommandRef, incompatible with the donor's existing de-pooled view.

BfmeNetCommandWrapperView.h shares the seed's existing pool macro, wrapper
members/access, and the donor's existing reference/list/packet declarations.
NetCommandMsg still comes from the seed's existing header, after PreRTS and the
unchanged local pool prefix. The node grants friendship to its list so the
existing global-delete path can reach its protected destructor; its access,
mangled name and pool operators stay unchanged. No class registered in the
canonical register is copied. No address, pin or ledger owner changes.

The four existing wrapper getters move into the shared declaration, and three
stale present-unmatched comments disappear with their former definitions. The
seed's rowed isComplete accessor must remain noinline. Its donor previously
inlined the same comparison, so calling the now-shared noinline accessor loses
bytes. Spell that existing equality directly in getReadyCommands; this restores
retail's inline compare while preserving the seed's twelve-byte accessor and
existing anchor. There is no new anchor or escape hatch.

Acceptance: ./build.sh on both sources preserves 16/16 rows, the existing
funclet and all three compiler float references. find_declared_unmatched and
class_gate pass the two sources and new header. The ordinary --merge TU
--dry-run accepts both sources, sixteen rows, no rejected donors. Three donor
rows are newly compatible; leave the actual merge for Luna. No file is removed,
no C++ bytes are recovered and no code-identity key retires.

The before/after scoped identity check reports sixteen rows, zero new problems
in shadow, and no wrong bindings. data_check reports zero findings. EH has
EXACT 1 and bytes_differ 1, the latter already in the baseline both before and
after. Baseline receipts were regenerated with normal ./build.sh after saving
the trial sources, the two complete baseline objects copied to build/, then
the trial sources restored and rebuilt normally. No direct cache compilation
or copied object was placed in build/match/.

Binding evidence: external undefined-reference sets are exactly unchanged.
Every provider body, size and COMDAT exclusivity survives in the final union,
including the duplicate array helper and rowed isComplete. Compiler-generated
names account for the nonidentical raw digests: the anonymous wrapperPercentMin
name changes its file hash, and the two class-local static initialization flags
renumber from S40/S41 to S38/S39. The scoped proof normalizes only those specific
names, compares every provider's complete bytes and relocation referents, and
checks each renamed flag is a four-byte zero object with the same section flags
and COMDAT selection, referenced by its own getClassMemoryPool body. All other
relocation names stay exact, including the pool pointer, pool-name literal,
factory and findMemoryPool. The composed trial has precisely the same provider
union and external references after these verified private compiler renamings.
link_check.py --new-variants --staged-peers --shadow reports no new variant.
This is scoped binding evidence, not a census or full-link claim.

The owning ms_header_audit scan/refresh removes exactly the donor's queue row:
its hand-written NULL and operator delete declarations are gone, supplied by
its existing standard-header environment instead. One Microsoft-header queue
entry is retired, separately from zero code-identity retirements. Other queue
records remain byte-for-byte; the audit still notes unresolved legacy virtual
include roots and does not certify their contents. The compiler/byte gate uses
the supported mapping. No core baseline, header-adoption key or TU map changes.

Receipts: build/sol-wrapper-current-{plan,before,before-build}.txt,
sol-wrapper-{shared-after,final-build,baseline-receipts,providers,eh,data,
identity-after,headers,link-variants,binding-proof}.txt; complete baseline
objects and objects-{before,after}.json. The scoped planner is
build/consolidation/sol-network, refreshed sequentially after the final trial.
An overlapping earlier refresh refused a changed Code snapshot, as intended.

Publication audit covers all pending commits from origin/master's merge base
through the inherited AptString prerequisite, two debris prerequisites and this
staged repair. There are no existing source path moves or deletions to repoint.
Reviewed active tools, hooks, workflows, includes, build inputs and registries;
new local quoted includes resolve to tracked headers, historical EA paths are
retained, and no active path consumer changes. Protected identity/data/header
registers and tu_map.csv are unchanged; only the supported Microsoft-header
queue refresh removes its proven-fixed entry.

Retain file claims for the seed, ready-command donor, new shared header and this
handoff, plus 0x0058C1A5, 0x0058C2AD and 0x0079CEF3 until publication is confirmed.
The publisher may hold the batch; inherited AptString and debris claims are
listed in their handoffs. Release file claims after push and settle landed RVAs.
