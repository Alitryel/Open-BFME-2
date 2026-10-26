# AptInput prerequisite repair, 2026-10-26

Seat codexb5, family B shard 1/2; base 87cad06378. Runner allocation lists
Code/Libraries/Source/Apt/AptInput.cpp. No inherited edits or unpublished
commits remained. Earlier allocator/CIH prerequisites landed as 8090b770df,
41292c3a9b and 50b594a2fe; their old claims have expired.

The scoped Apt planner and current in-memory tu_skeleton routing were reviewed.
The seed has eight matched rows. Normal --merge TU --dry-run initially accepts
only seed + BfmeMeshHitTest1290.cpp (nine rows). It rejects coordinate update
Rva006F9EF0Cluster.cpp and AptAnimationPoolBILValidate.cpp with missing method
and operand members. Both are allocated destination dependencies inside Libraries.

The change adds their existing nonvirtual declarations and partial operand view
to the seed: BIL count/list +0x10/+0x14; value +0x44; six floats +0x48..+0x5c;
coordinates +0x74/+0x78. It preserves current +0x6c and adds the existing
AptCIH::factorySetProperty declaration. These offsets are observations from
byte-verified target bodies, not donor layout recovery. No body, virtual slot,
compiler flag, global definition, pin, path, ledger or register changes.

## Acceptance and verification

- Full normal before/after dry-runs: nine -> eleven rows, two newly accepted
  donors, 194 + 224 = 418 existing retail bytes. After accepts seed,
  BfmeMeshHitTest1290.cpp, Rva006F9EF0Cluster.cpp and
  AptAnimationPoolBILValidate.cpp. No merge is applied; leave it to Luna.
- A scoped call of the same tu_skeleton._merge(..., dry_run=True) with seed and
  the two repaired dependencies checks current routing, header queue, every
  row, alternate strategies and normal flag/register checks. Before: neither
  donor accepted, C2039 and missing fields. After: all three sources, ten rows,
  no rejection. Scripts/results: build/sol-b5-input-scope-{before,after}.*.
- ./build.sh on those three sources before and after: 10/10 matched, eighteen
  literals verified, zero float/import failures. Frozen-file and class gates
  pass. One funclet renumbers from $L1115 to $L1136 and still resolves through
  its exact retail parent EH data at 0x007aa180. eh_verify.py: EXACT 1,
  zero missing/nonexact objects.
- build/sol-b5-input-proof.py compares saved objects through allowed_symbols
  and data_check.object_facts. All ten external code definitions retain exact
  normalized digests, sizes, exclusivity, COMDAT selection/flags, undefined
  symbols, data definitions and data bindings. All 79 scanned code references
  retain offset, relocation kind, target and classification (58 owner, one EH,
  sixteen local labels, four aliases). Local $L spellings renumber; comparison
  normalizes only their spelling and retains the resolved retail target.
  This is the only receipt difference. Source paths/link order stay fixed;
  no shared provider variant or external consumer binding changes.
- allowed_symbols.py --source independently reports zero wrong bindings
  (78 references; it omits the relocated funclet's reference, which the proof
  explicitly resolves). data_check.py: zero findings. --converged: ten judged
  addresses, zero second names or unjudged rows. ms_header_audit.py scan:
  no private Microsoft prototypes, conflicting files or failures.
- None of the three sources has code/data identity, header or ms-header queue
  keys. No debt is retired. check_csv.py and git diff --check pass.

## Remaining prerequisites and publication audit

The full after dry-run still rejects FocusTransition for missing rva006FA7E0
and m60, and FB910/InputDispatch for AptCIH declaration ordering. The Common
Rva006F9FC0 donor has a conflicting existing flag override; hand off that
cross-family dependency rather than edit it here. SuffixAdvance remains mixed
and needs the supported split lane. Do not repeat unchanged failed trials.
AptRenderingContext normal dry-run accepts all six rows from three donors;
no prerequisite repair is needed there and that merge is left to Luna.

Audit at base 87cad06378 plus this staged repair: no outgoing source paths
move, no include/build/tool/hook/workflow consumer changes, no register changes.
Only a seed declaration view and this handoff are committed. Historical EA
paths stay intact. Planner regenerated after source edits; currency check passes.
File reduction, debt retirement and recovered/authored C++ bytes are all zero.
The 418 bytes measure newly compatible existing donor rows only, not linked
coverage or a confirmed downstream Luna landing.

BFME 1 freshness: official master verified remotely as 0337dcca9296 on this
session; clean reference checkout remains ff391a5e90aa, matching the committed
gitlink. Full before/after byte verification for an update is not available
in this scoped prerequisite pass; retain verified inputs and no success receipt.
No maintainer-only runners were used.

Claims retained until confirmed publication: file:Code/Libraries/Source/Apt/AptInput.cpp,
file:Code/Libraries/Source/Apt/AptAnimationPoolBILValidate.cpp,
file:Code/Libraries/Source/Apt/Rva006F9EF0Cluster.cpp and this handoff.
