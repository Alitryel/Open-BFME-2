# debug_except clipboard-report prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2; runner --check-tu authorizes
Code/Libraries/Source/debug/debug_except.cpp. No merge or path move applied.

The shared local Debug ABI view ends at SetPrefixAndRadix (slot 0x50).
DebugCopyDialogReport.cpp already declares GetVersion/GetInternalVersion/
GetBuildDate at 0xA0/0xA4/0xA8. Composition selects the header view and fails
C2039 GetVersion. Extend the header with the donor's existing pad21..pad39
and three named virtual declarations. Existing fields, vptr, old slots,
method bodies and flags do not change. The names and slots are existing
BFME 2 reconstruction facts, not an upstream donor identity claim.

## Demonstrated unblock

Reviewed the scoped fresh name_lane planner, original-path evidence,
alternatives and blockers; its same-name leads do not approve moves.
Current in-memory routing approves the whole clipboard-report donor.

    python3 /opt/runner/consolidation_queue.py --check-tu Code/Libraries/Source/debug/debug_except.cpp
    python3 tools/name_lane.py consolidate --under Code/Libraries/Source/debug/
    python3 tools/tu_skeleton.py --plan Code/Libraries/Source/debug/debug_except.cpp
    python3 tools/tu_skeleton.py --merge Code/Libraries/Source/debug/debug_except.cpp --dry-run

Before: seed, DialogWatchdog and ShowAssertCrashDialog, 12 rows. After:
same set plus DebugCopyDialogReport, 13 rows, one existing 767-byte body
at 0x0003D3A0. Receipts: build/sol-b5-except-{before,after}-trial.log.
This is an accepted dry run, not a confirmed Luna landing. Leave the merge
for Luna. ExceptionFilter still lacks Signature::Size in the seed's
DebugStackwalk view; Common RecordInitialize still fails composed bytes and
belongs to the other family. Mixed donors remain separate; no manual split.

## Verification and bindings

Before/after ./build.sh on debug_except.cpp and DebugCopyDialogReport.cpp:
10/10 exact, 109 literal references plus 10 empty strings, 11 named imports,
no string/float/import failures. find_declared_unmatched.py reports all
bodies matched. eh_verify.py reports no EH data or missing objects.
class_gate.py passes; allowed_symbols.py reports no wrong binding.
data_check.py: zero findings; --converged: 10 addresses, zero second names
or unjudged rows. The header has one active includer, debug_except.cpp.

build/sol-b5-except-proof.py uses upstream allowed_symbols load/scan,
_object_defs, Obj, link_census._comdat_selections and data_check.object_facts.
Before/after receipts are exactly equal: 17 external code definitions and
their hashes/extents, COMDAT selection and section flags, undefined sets,
data definitions/references, and all 27 relocation bindings (18 local label,
7 owner, 2 alias). No changed shared provider or consumer binding requires
a replacement witness. The dry run separately verifies the new composition,
including virtual-call offsets. No maintainer-only link runner was used.

Existing header/MS-header/data/code-identity debt remains at its owners.
MS-header audit still classifies the exception structs as existing local
Microsoft-header conflicts; this change introduces no such definitions.
No source ledger, queue, protected baseline or hatch count changes. A later
merge must carry its data keys and hatches through the supported tool.

## Publication audit

Audited the pending browser prerequisite (0ad490306b) and this staged change.
The outgoing merge-base diff and index contain no source path moves or
deletions; origin/master..HEAD also contains incoming remote changes, which
are not authored moves in this batch. No tools, hooks, workflows, includes,
build inputs or registries need repointing. Existing include consumers were
searched and verified together. Historical EA paths and tu_map.csv remain
untouched. File reduction, retired identity debt and recovered bytes: zero.
Claims on the header, TU, clipboard donor and this handoff remain held until
publication is confirmed. The publication hook supplies the final batch audit.
