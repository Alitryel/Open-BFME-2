# TileData declaration prerequisite, 2026-10-26 (codexb)

Allocated destination: Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp,
family B shard 0/2. Runner --check-tu exits zero. The parent-scoped naming
planner records the exact original TileData.cpp path, ZH/BFME1 donor hints,
and macro/pragma and path-register prerequisites. The current routing plan
approves 11 ordinary rows in three clean and three mixed files. Neither a
merge nor a split is applied here; no TU map is regenerated into the index.

Before repair the ordinary --merge --dry-run accepts no pair. The setter
file's private TileData lacks the destination's base/destructor and uses a
companion field that the destination does not declare. Use identical class
declarations in the two files: the seed's existing RefCountClass, TileData
layout and reference field, plus the already-rowed setter declaration.
The setter retains the incoming reference before releasing the previous
one, as before. Its native body proves count +4, virtual release slot 0 and
receiver reference +0x2AB4; no original method name is inferred.

The ordinary dry run now accepts the seed plus
TileDataReplaceCompanionRef.cpp, six existing rows (including the native EH
handler). This is a demonstrated prerequisite unblock for Luna, not a
confirmed merge. No Common source is edited. Rva00111A05Finish.cpp remains
blocked on its different member/mip declarations; record this for its
assigned owner. The two Common mixed files are also unchanged.

The separately inspected --split TileDataGetRGBDataForWidth.cpp --for
TileData.cpp --dry-run carves constructor and updateMips but cannot spell
the deleting destructor's definition. The residual then loses its matched
0x00111867 row, so the supported tool refuses. No split is attempted or
worked around. Its ordinary getRGBDataForWidth body belongs elsewhere.

## Verification and provider comparison

Before/after ./build.sh on both edited files passes 6/6 rows. The frozen-file
check passes after the change without suppressions. Three stale
present-unmatched markers disappear: the rowed setter and two deleted
private inline helpers. tools/hatch_counters.py --update lowers that hatch
total by three. No other hatch grows and no identity/data debt key is retired.
Scoped code_identity_gate.check returns shadow mode, six rows, zero problems
and zero notes; data_check.py returns zero findings. class_gate.py and case
checks pass. link_check.py --new-variants --staged-peers --shadow on both
sources exits zero. Header adoption queue has no affected row; scoped
ms_header_audit.scan_files/refresh_queue reports no tracked queue change.

Supported allowed_symbols.Obj/body and census COMDAT-selection APIs compare
before snapshots with the current standalone objects and accepted composed
object build/tu_skeleton/90280cfea0266924.obj. Seed providers, bodies,
relocations, section flags, selections and undefined symbols are unchanged.
The setter's 41-byte body and relocation targets are unchanged. Its only
standalone provider changes are removing the unreferenced private retain
and release COMDATs and emitting Release_Ref, exactly equal to the seed's
existing 10-byte provider, including relocations, flags and selection 2.
The removed release is also identical to it; removed retain is ff4104c3.
Neither removed helper is referenced by any pre-edit provider/undefined
symbol in this scope; repository Code references to their private class are
absent. No changed caller binding remains. The composed union has no added,
missing or changed retained external provider and no undefined-set change.
The EH handler local referent is explicit, not generically masked.
eh_verify.verify_row reports EXACT for the destructor, with its associated
funclet location checked. The initial scratch comparison correctly refused
the changed helper set; the final proof explicitly verifies these changes.

Receipts: build/sol-tiledata-declarations-{before,after}-build.txt,
before.json, after-trial.txt, bindings.txt, proof.py and link-check.txt;
build/sol-tiledata-before-{trial,split}.txt records baseline failures.
After rebasing on 78cb0834c7, ./build.sh verifies all five FTP/TileData scope
sources together (22 rows). The FTP Microsoft-header queue conflict was
resolved by preserving upstream and rescanning exactly the two FTP sources.

## Complete pending batch audit

After the rebase, origin/master..HEAD contains the inherited session handoff
(e524323871) and FTP prerequisite (349ba5d456). Together with this staged
prerequisite, the batch makes only in-place source edits; there are no source
moves, additions or deletions. Active tools, hooks, workflows, include paths,
build inputs and registries therefore need no repointing. Historical paths
remain. Function/data owner ledgers, code/data debt registers, fold proofs,
compiler flags and TU routing are unchanged. The three removed hatch keys
are lowered through the hatch tool with the required trailer. The refreshed
planner is checked against the final source/register inputs.

File reduction: zero. Identity/data debt retired: zero. Recovered C++ bytes:
zero. Hatch debt: three fewer present-unmatched markers. Six existing rows
are now composition-compatible. Keep the destination, setter and handoff
file claims until confirmed publication. The runner owns final held batches.
