# Shrub morph/render-header prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2, allocated W3DShrubBuffer.cpp. Current
routing approves the startMorph donor; the GameClient planner supplies path
evidence, not merge approval. No merge is applied in this prerequisite.

The preceding complete normal dry-run accepted five files / 22 rows and
rejected startMorph. Align its private record/count/type/dirty-flag names with
the seed's opaque storage. The record stride remains 0xA0 from +0x1958, count
+0x4FB58, dirty flag +0x4FB5C, and type stride 0x5C from +0x4FB70. Direct casts
to the existing method views preserve every access and avoid extra accessor
COMDATs. The store of true is unchanged. These are storage facts from the
existing byte-exact bodies, not a claim about recovered class/member names.

A storage-only trial still failed composition. Captured upstream normal
verifier diagnostics show Debug class redefinition from the rendering headers
and missing slot60/slot6C in the selected declaration. The texture donor's
private Debug definition conflicted with those headers. Reuse the lookup
donor's existing BfmeAwakenDebug declaration verbatim, retain the real
`extern Debug *theDebug`, and cast that pointer to the existing view for the
virtual calls. Virtual offsets and the BfmeAwakenLog declaration stay fixed.
No second global, header change, pin, alias or compiler flag is introduced.

`./build.sh` over the six affected shrub files passes 23/23 rows, four strings,
seven empty-string references, 12 float literals and four imports. Supported
standalone before/after evidence preserves all 77 bindings (63 owner, nine
alias, three fold, two EH), definitions, undefined names, COMDAT selections and
flags, and code/data facts. Only local EH label spelling is normalized.
`class_gate.py`, shadow/converged `data_check.py`, `ms_header_audit.py check`,
`find_declared_unmatched.py`, `eh_verify.py` (two EXACT) and `git diff --check`
pass. No relevant baseline/queue key is removed or re-keyed.

The before diagnostic filtered the six approved donors through upstream
`_merge` and its normal verifier. It records the Debug/header conflict. The
complete normal routing dry-run, rather than that filtered diagnostic, is
the acceptance test. Detailed before/after and composition receipts are in
the adjacent JSON.

The outgoing tooling audit covers the merge-base range through 4c4255b2d2 and
this prerequisite. No source moves/deletes, ledger repoints or protected
register edits occur. The batch's new waypoint render header has two direct
consumers, verified with its prerequisite and dependent-source hook. Searches
of active tools/hooks/workflows, build input, doxygen source registry and
module registries find no reference requiring repointing. Historical EA paths
remain intact. No maintainer-only measurement, link cycle or smoke runs.

This is prerequisite work: zero recovered bytes, zero file reduction, zero
identity debt retired. No later Luna landing is claimed. Keep claims with the
pending publication batch until publication is confirmed.

The final complete normal routing trial accepts all six files and 23 rows,
one additional existing 880-byte parent over the prior 22-row subset. The
composed object preserves 77/77 bindings, drops no external definition and
adds no undefined symbol. All 52 names retain their global selected
definitions, and data binding/definition sets are equal. The only additional
emitted constructor is the exact three-byte existing-owner Coord3D copy
verified in the movement prerequisite. Both composed EH rows are EXACT.
Other rejected donors and their prerequisites remain in the JSON.

The first planner refresh raced a temporary normal-verifier source file and
reported that vanished path. After the complete trial finished, rerunning
`name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient`
succeeded; no generated temporary source is committed.
