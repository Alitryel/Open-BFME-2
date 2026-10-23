# Count-tree destructor provider repair

At checkout `dadc29e144590ad9c883c875a4e648092db913d7`, four units emitted
52-byte copies of the destructor for the existing
`_STL::_Rb_tree<int, pair<const int, Rva00501875Count>, ...>` view.
The first copy displaced the 56-byte, byte-verified provider in
`Code/GameEngine/Source/Common/Rva00501875KeyPresence.cpp`, whose row is
at 0x004FF5F3. A declaration-only specialization binds cleanup calls to that
provider while retaining STLport's class definition and layout.

The repaired units are TerrainLogicCtor.cpp, CreateAHeroDataCtor.cpp,
Rva004FD0DACtor.cpp and Rva0059DA34.cpp. Their original retail identity,
layout qualifications and compiler settings are unchanged. The four-byte
count remains a structural view, not a newly established original type.
No pin, alias, alternate name, pragma or baseline was added.

## Controlled local evidence

The runner census index is dated 2026-10-14 07:27, measurement commit
`147cfae2cb`, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
The comparison replaces all six affected units with current, byte-verified
objects against that same index. No census, index or link-status file changed.

| Unit | Before findings | After findings | After linked bytes |
| --- | ---: | ---: | ---: |
| TerrainLogicCtor | 14 | 14 | 0 |
| Rva00501875KeyPresence | 1 | 0 | 394 |
| CreateAHeroDataCtor | 25 | 25 | 0 |
| Rva004FD0DACtor | 3 | 3 | 0 |
| Rva0059DA34 | 10 | 10 | 0 |
| Rva00598E85Ctor, unchanged | 35 | 36 | 0 |

Clean units improve 0/6 to 1/6 and existing authored linked bytes improve
0 to 394 in the legacy local preview. Total findings remain 88: the count-tree
destructor loser moves from its verified provider to the remaining divergent
AI constructor copy. No previously clean unit becomes blocked. The AI source
has another worker's live file claim and was only read and byte-verified here.
Its declaration-only specialization is the remaining supported sibling repair.

Object comparison removes 32 COMDAT definitions: six from each of the first
three repaired units and fourteen from the tally unit. These include all four
52-byte destructor copies (digest `4a9f2f25c81e`) and unused tree cleanup
helpers. There are no added COMDATs and no changed retained COMDAT body or
relocation digest. Each repaired object adds only the existing destructor
name to its undefined references; no other undefined reference changes.
The provider and AI objects are unchanged.

## Acceptance checks

- Before: bounded `link_check.py --prepare-current` passes 25/25 rows for
  TerrainLogicCtor and the provider, and 7/7 rows for the other four units.
- After: `./build.sh` and `link_check.py --prepare-current` pass all 13/13
  rows in the four edited units, with strict reusable receipts. The four
  renumbered TerrainLogic funclets are verified through their parent EH data.
- String, float and import reference checks pass. The unchanged provider's
  18 rows, including its 56-byte destructor, retain their before receipts.
- The six-source local `link_check.py` comparison gives the table above;
  its exit remains 1 because five units have the documented other blockers.
- New-COMDAT-variant admission, class gate, undeclared-definition checks,
  converged-data check (8 addresses, zero second names) and CSV checks pass.

This is self-strict byte evidence plus a legacy local preview gain, with
zero new authored C++ bytes. It claims no closed-strict or full-link-cycle
gain. Maintainer-only verification runners were not started.

## Donor review and remaining limits

At the verified BFME 1 pointer `23b143233b5a8664a3bdf8572df6d905c310a5a1`,
the declaration-only tree destructor specialization in
`game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0064D320PeerThreadDestructor.cpp`
and `game/GameEngine/Source/GameLogic/ScriptEngine/AttackPriorityInfoSetPriority.cpp`
supports the provider-reuse technique. Their application types and layouts
are not transferred. BFME 2's bytes, relocation checks and local link results
establish applicability here.

Fetched BFME 1 upstream is `a7c38d3b2597121f178ab5190b3062478823257d`.
The pointer stays at its last verified inputs: the earlier freshness attempt
records thousands of stale old-input TUs requiring a full baseline rebuild.
That unresolved prerequisite was not retried or marked successful here.

The remaining five-unit blockers include missing class providers, allocator
and container COMDAT conflicts, and selected-wrong base definitions. Detailed
before/after logs, original object snapshots and `object-diff.json` are local
in `build/count-tree-link-20261014/`.
