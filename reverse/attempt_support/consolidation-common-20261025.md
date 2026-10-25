# Common TU consolidation, 2026-10-25

Scope: `Code/GameEngine/Source/Common/`. Started from `91fe970939` with a
clean tree and passing `tools/check_csv.py`. The scoped consolidation planner
catalogued 173 retail C++ paths; its snapshot passed `--check` after the trial.
The committed TU map was stale; `tu_skeleton.py` rebuilt routing in memory.

## SubsystemInterface.cpp

`tu_skeleton.py --plan Code/GameEngine/Source/Common/System/SubsystemInterface.cpp`
reported 18 approved rows, eight eligible donors, six mixed sources and no
protected-register refusals. The donor declaration check passed before trial.

The ordinary `--merge ... --dry-run` returned exit 2:

```
accepted: []
rejected: {'Code/GameEngine/Source/Common/SubsystemInterfaceList.cpp': 'no baseline match'}
blocked: no verified merge of two or more donors
```

No source or ledger edits were made and no claims were acquired. The constructor
donor includes `../../../Libraries/Include/Lib/BfmeE16.h` relative to `Common/`;
that spelling does not resolve to the same header from `Common/System/`.
The destination also imports the donor subsystem header, while eligible fragments
declare differing private `SubsystemInterfaceList` views and compiler settings.
The trial does not identify which reconciliation would make the full set match.
Resolve and byte-verify prerequisites individually before retrying.

Mixed sources remain outside this merge, including
`Code/Libraries/Source/subsystem/SubsystemInterface.cpp` (370 foreign rows,
outside this seat's destination scope). Do not split them inside a merge.

The existing destination's `postProcessLoadAll` row and the address-named
`Rva001B4E49Loop.cpp` row both already cover RVA `0x001B4E49`; this trial did not
create that duplicate. Preserve current coverage while investigating ownership.

## Energy.cpp

The dry run and normal claimed merge both accepted the existing destination,
`EnergyAdjustPower.cpp`, `Energy_getEnergySupplyRatio.cpp` and
`Rva004DF17FCompare.cpp`: seven matched rows, three source files removed.
`./build.sh Code/GameEngine/Source/Common/RTS/Energy.cpp` passed 7/7, including
the float literal check; `find_declared_unmatched.py` and `check_csv.py` passed.
Only the existing map's three source columns were repointed; no map was
regenerated on disk.

Remaining donors: `EnergyXfer.cpp` fails after preprocessing is lifted ahead of
its forward declarations (`BfmeXfer.h`: undeclared `Snapshot`, `AsciiString`).
`Rva004DF18DAdd.cpp` and `Rva004DF1AFAdd.cpp` have incompatible private Energy
views; the reported strategy loses the `getEnergySupplyRatio` declaration.
`Disp32DwordFieldGetters.cpp` remains mixed (21 foreign rows). No rejected donor
was edited or moved.

Path-consumer audit: fetched origin/master at `2a08265ac7`; reviewed all pending
paths from the `91fe970939` session base through the staged Energy merge (no
earlier unpublished commits). Searched all tracked files for the three deleted
paths, basenames and stems. There are no active tool, hook, workflow, include,
build-input or source-registry consumers. Remaining references are the merged
TU's provenance comments, append-only `name_basis.csv`, the maintainer's
`link_status.csv` census snapshot, and independent BFME 1 historical records.
Those references are intentionally retained. Generic build/tool source discovery
continues through the current ledger; the normal build verified the new path.
The old planner snapshot must be regenerated before selecting further work.

## RandomValue.cpp

After refreshing the planner, the current in-memory TU map approved both
`ClientRandomValue_getValue.cpp` and `GameLogicRandomValue_getValue.cpp` into
`Common/RandomValue.cpp`. Both bodies carry the original retail RandomValue.cpp
path string; the existing GameClient setter source remains mixed (seven foreign
rows). Dry run and claimed application accepted both getters with no rejection:
two matched rows preserved, two fragments replaced by one TU (one fewer file).
`./build.sh` passed 2/2 with both strings and float literals verified;
`find_declared_unmatched.py` passed.

Repeated the combined pending-move consumer audit from base `91fe970939` through
the staged RandomValue merge after fetching origin/master. All five deleted
source paths across Energy and RandomValue have no active consumers requiring
repair. Retained exact old-path hits are provenance, the census snapshot,
append-only naming records or independent BFME 1 evidence. Stem-prefix matches
to the separate `getValueInt.cpp` and `getValueReal.cpp` sources are unchanged
live sources, not removed paths. The two original EA assertion strings remain
unchanged and verified.

## FunctionLexicon.cpp

Dry run and normal claimed application accepted the existing System destination
and `Rva002D22CAValidate.cpp`: four matched rows preserved, one fragment removed.
The normal build passed 4/4 and the declared-unmatched check passed. Only the
validator's source columns were repointed in the existing ledgers.

The constructor donor still fails because lifting its subsystem include ahead
of its local typedef leaves `Bool` undefined. The registry-lookup donor fails
because the combined declaration strategy loses protected `findFunction`
access. Both remain unchanged, as does the mixed deleting-destructor source.
Reconcile those declarations in separate verified prerequisites before retrying.

Fetched origin and repeated the combined audit from `91fe970939` through this
staged move, covering all six deleted paths. The new validator-path references
are merged provenance and the maintainer's census snapshot. No active tools,
hooks, workflows, includes, build inputs or registries require repair; earlier
historical and distinct stem-prefix references retain their prior classification.

## Dict.cpp

The current plan approved `DictSetReal.cpp` alongside the existing Dict.cpp.
Both the dry run and claimed merge accepted both sources without rejection:
two matched rows preserved and one source removed. `DictPairClear.cpp` remains
mixed (seven foreign rows) and was not split. The normal build passed 2/2;
the declared-unmatched check passed. The existing TU map only changed the
setReal source column, alongside the corresponding function row.

Fetched origin and audited all seven pending deleted paths from `91fe970939`
through the staged Dict move. The new old-path hits are the merged provenance
comment and the maintainer's census snapshot. No active path consumer needs
repair, and all earlier audit classifications still hold.

## GameMemory.cpp

The current in-memory map approved the two guarded flag helpers at 0x00030890
and 0x000308B0 into System/GameMemory.cpp. The committed map remains stale;
only its source columns were repointed, not its routing. Dry run and claimed
application accepted both fragments without rejection. Two rows remain matched,
two fragments become one TU (one fewer file). The normal build passed 2/2 and
the declared-unmatched check passed. The single external MemoryPool::g_heaps
declaration and existing compiler flags remain; no second global was defined.
Mixed memory-pool sources, protected-register donors and vendored sources were
excluded by the lane and left unchanged.

Fetched origin and repeated the combined audit from `91fe970939` through this
staged move, covering all nine deleted paths. New path hits are provenance and
the census snapshot. Stem hits also identify unchanged function declarations,
calls, ledger identities and a naming tier; they do not depend on source paths.
No active consumer needs repair; previous historical classifications still hold.

## TunnelTracker.cpp

The dry run and claimed merge accepted the existing RTS destination plus
`Thing/Rva004F53A3.cpp` and `Thing/Rva004F5436Count.cpp`: four matched rows
preserved, two fragments removed. The normal build passed 4/4 and the
declared-unmatched check passed. The current routing approved both helpers;
only their source columns were changed in the existing map and function ledger.

The other eight eligible donors remain unchanged. Most fail against differing
Object/TunnelTracker declarations, with allocator<char> specialization conflicts
in several combinations. The deleting-destructor donor loses its byte match.
Two other sources remain mixed, and the getCurNemesis/xfer sources remain
protected by their existing registers. Reconcile prerequisites individually;
the successful subset does not establish a unified class layout for those rows.

Fetched origin and audited the combined eleven deleted paths from `91fe970939`
through this staged move. New exact path hits are provenance and the census
snapshot. Other stem hits name unchanged symbols, structural evidence and WB
name leads; they do not consume the removed files. No active tools, hooks,
workflows, includes, build inputs or registries need updating. Generic source
discovery still includes the destinations; no source directory was moved.

## ResourceGatheringManager prerequisite

The first trial accepted only the removal-list fragment. Its ObjectID typedef
was unsigned while the already-verified insertion owner uses int and binds the
signed list push_back at 0x0005548F. Class-view inspection found eleven views
and no registered canonical header. Changing only the removal fragment's
typedef to int aligns its identical list field layout with the insertion owner;
the two equality-only removal bodies still pass 2/2 byte checks (118B).
The declared-unmatched check passes. No names, pins, layouts or flags changed.

This prerequisite adds no path changes or consumers. The combined eleven-path
audit through the TunnelTracker merge remains applicable to the pending batch.
