# Ghost-object STL declaration prerequisite: blocked, restored

Seat codexb5, family B shard 1/2, 2026-10-26. Target:
`Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp`.
Runner allocation authorized this TU; the GameLogic planner and current
`tu_skeleton --plan` cover 46 approved rows, four clean donors and eight mixed
sources. No merge or source repair was retained.

The baseline normal merge dry-run accepts no composition: both library donors
`StlSweepW5Rva00063BB2.cpp` and `StlSweepR3Rva0006447D.cpp` include real STLport,
conflicting with destination-private `__false_type`, allocator and vector.
Replacing those private declarations with real STLport vector declarations,
explicit helper specializations and the real field names preserves the four
standalone destination rows exactly. The retail reference-tag helper signatures
require the vendored algobase header, rather than bfmealloc's by-value variant.
A default-initialized local dispatch tag avoids value-initialization stores.

The trial normal dry-run accepts seed plus both library donors: seven rows.
This is a demonstrated compile/byte unblock only, not an accepted prerequisite:
real vector instantiation introduces a 53-byte `_M_allocate_and_copy<FileInfoStruct*>`
provider, whereas its existing retail owner at RVA 0x00064432 is 45 bytes.
The relocation-normalized digests differ (3b1439a4404d versus e88cc41386d2).
It also introduces three allocator helpers and removes the private empty-tag
constructor. The seven rowed bodies retain identical bindings/data, but these
provider changes prevent publication. Declaration-only member specialization,
explicit call template arguments, extern-template suppression, noinline and
import-inline forms all hit MSVC 7.1 C1001 at the allocation call (P2/main.c:148).
An explicitly typed member pointer does not avoid that compiler crash.
Do not publish the byte-exact trial without resolving current provider selection.

The remaining Common donor `S3StrideCopyLoops_Rva00064605.cpp` also privately
defines vector; its declaration reconciliation belongs to family A. It was not
edited or claimed. Existing mixed sources still require supported split-lane
approval and coherent identities; no manual split or row move was attempted.

All destination edits were restored from the exact preparation backup.
`./build.sh DEST W5 R3`: 7/7 exact after restoration.
`find_declared_unmatched.py DEST`: all definitions matched, existing two anchor
notes unchanged. Scoped `allowed_symbols`/`link_census`/`data_check` object facts
before and restored after are identical: 7 rows, 18 references (11 owner, one
alias, four fold, two preexisting wrong), all external provider bytes, COMDAT
selection flags, undefined names and data facts unchanged. Receipts and failed
builds remain under ignored `build/sol-b5-ghost-*`. No identity/data/header/hatch
register or source path changed; no debt or recovered-byte progress is claimed.

HTree read-only trial also accepts no donor: pivot/Base layout, archive max,
early specialization, missing Start/Finish, m_bfme54, LoadW3D C1001 and Elem36
blockers remain. No htree edit/claim. Buffer-manager inherited prerequisite
retains its separately recorded three-row composition improvement and provider
limits. No maintainer-only link cycle, smoke or nightly runner was started.

Batch audit: outgoing inherited buffer repair plus this attempt changes no
source paths, include consumers, build inputs or registries. Historical EA paths
and all protected registers are preserved. BFME1 checked-out inputs were retained;
official upstream fetch was verified, but full cross-repo freshness verification
is incomplete, so no success receipt was written.
