# wwstring lock include prerequisite, 2026-10-26 (codexb)

Allocated destination: Code/Libraries/Source/WWVegas/WWLib/wwstring.cpp,
family B shard 0/2. The parent-scoped naming planner records the original
WWLib path and ZH/BFME1 donor hints. Current routing approves 11 ordinary
rows in two clean files and one mixed file. No merge or split is applied.

The baseline ordinary merge dry run accepts no pair: mutex.h redefines
FastCriticalSectionClass after the seed's wwstring.h view. Get_String uses
BFMEPoolCriticalSection, not a FastCriticalSection guard. Remove its unused
mutex.h include and use the lock-word declaration already supplied by
wwstring.h. Shared headers, class definitions, flags and runtime data are
unchanged. This does not reconcile the existing private lock-view identity.

The ordinary dry run now accepts wwstring.cpp and wwstring_get_string.cpp,
12 existing ledger rows including the EH handler/funclet. Leave the actual
merge for Luna. wwstring_free_string.cpp remains mixed and is unchanged.
This is a demonstrated composition unblock, not a confirmed Luna landing.

## Verification and bindings

Before and after ./build.sh on both sources passes 12/12 rows, two data rows,
the funclet pin and three imports. find_declared_unmatched.py passes; the
seed's existing absent-from-retail definition note is unchanged. class_gate,
data_check (zero findings) and case checks pass. code_identity_gate.check is
shadow, 12 rows, zero problems and notes. link_check.py --new-variants
--staged-peers --shadow exits zero. The scoped Microsoft-header scan preserves
the seed's existing WideCharToMultiByte finding; its identical queue row is
left in place. No debt key is retired and no header adoption is claimed.

The supported allowed_symbols.Obj/body and census COMDAT-selection APIs
compare before snapshots against both current standalone objects and the
accepted composed object build/tu_skeleton/ed096bb08bdb08a3.obj. Every external
code/data provider, body, relocation target, section flag, COMDAT selection
and standalone undefined set is identical. The composition has no added,
missing or changed provider and no new undefined reference. Its four removed
undefined references (StringClass::ReservedMask, m_EmptyString, m_Mutex and
m_TempStrings) are supplied by identical existing seed data providers.
There are no multiple provider variants in the compared scope. Local code
labels are compared by containing provider and byte offset; the Get_String
EH handler is an explicit local referent. eh_verify reports EXACT and checks
the associated funclet at 0x007A6E90. No changed consumer binding remains.

Receipts: build/sol-wwstring-lock-{before,after}-build.txt, before.json,
after-trial.txt, bindings.txt, proof.py and link-check.txt. The baseline
refusal is build/sol-wwstring-current-trial.txt. The refreshed parent planner
is build/consolidation/wwlib-current.

## Complete pending batch audit

The inherited handoff, FTP prerequisite and TileData prerequisite plus this
change contain only in-place source edits. There are no source additions,
deletions or moves, so active tools, hooks, workflows, includes, build inputs
and path-keyed registries need no repointing. Historical paths are retained.
Function/data ledgers, code/data identity debt, fold proofs and flags are
unchanged; TileData's three hatch removals remain tool-recorded separately.
The final planner currency check covers current source and register inputs.

File reduction: zero. Identity/data debt retired: zero. Recovered C++ bytes:
zero. Twelve existing rows become composition-compatible. Keep the seed,
donor and handoff file claims until publication is confirmed; the runner
publishes a held final batch.
