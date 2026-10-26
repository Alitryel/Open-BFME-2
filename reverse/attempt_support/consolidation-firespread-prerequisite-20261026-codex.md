# FireSpreadUpdate declaration prerequisite: blocked, sources restored

Allocated family A shard 0/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Update/FireSpreadUpdate.cpp`.
No merge, source repair, file reduction, debt retirement or recovered bytes.

The current scoped planner and `tu_skeleton.py --plan` place ten ordinary rows
here, with five direct donors and three mixed sources. The untouched five-source
`./build.sh` passes 11/11 rows, four strings and one float. Frozen-file checks
pass; the seed retains its three already admitted unrowed definitions. The
ordinary baseline dry-run accepts no group: the pool key lacks a declaration in
the seed receiver, while the module-data ctor needs different member names,
the delay/start donor needs its raw receiver and the update donor conflicts on
Coord3D and PartitionManager's closest-object signature. Mixed sources stayed
untouched. Current identity/header queues were inspected; no key was retired.

A minimal trial copied the seed's existing Zero Hour FireSpreadUpdate header to
a TU-scoped view, preserving its provenance, layout and interfaces, and added
only `static NameKeyType rva00048B690();`. The seed included that view; the pool
donor was unchanged. All five before/after objects kept identical external code,
data, undefineds, aliases, non-debug sections, bytes, relocations and COMDAT
policies. All 31 scoped reference facts and data facts were unchanged; 6/6 seed
and pool rows and three EH graphs were exact. Nevertheless the ordinary full
trial refused its final accepted-set recheck with C2039 for rva00048B690.
This is not a demonstrated accepted merge.

A concrete tool defect was reproduced without changing the verifier:
`Verifier.matched` caches failed compilations as None but does not cache their
`all_errors`/`errors`. Compiling candidate A (C2011 for type A), then candidate B
(C2039 for memberB), then requesting cached A returns B's diagnostics, with only
two compile calls. `attempt` uses these diagnostics to decide which type copies
to drop. The isolated reproduction and real trial are in local receipts
`build/codex-firespread-cache-repro.txt` and
`build/codex-firespread-after-trial.txt`. Recorded as a false reject in the
attempt log; no tool change or bypass was made in this source attempt. A tooling
owner should add a cache-hit diagnostic regression test and fix the cache in a
separate Verifier-Change commit before retrying the minimal trial.

A second, broader experiment made the pool donor include the full shared view
under the seed's STL, snapshot and include environment. Its ordinary full trial
accepted seed plus pool (six rows). Combined code definitions were unchanged,
and the composition kept all 56 definitions and their COMDAT policies. However,
the pool object acquired duplicate include-generated sections and its local
guard changed from `$S1` to `$S11` at 0x00A03904, producing a new wrong-name
finding outside the data baseline. This is not an acceptable prerequisite repair.
It was reverted, with all original debt preserved. No shared header remains.

Restoration verification: `./build.sh` seed and pool passes 6/6 rows, two strings;
`find_declared_unmatched.py` passes with the same admitted seed note. Both files
are byte-for-byte restored from their initial snapshots. Claims for all five
source candidates and the abandoned new header are released. Do not repeat the
unchanged layout failures or publish either experiment as a merge unblock.

Publication audit covers the inherited TunnelTracker range
`origin/master..HEAD` plus this documentation/log change. HEAD is three local
TunnelTracker commits ahead of the common ancestor; upstream-only hash-table,
B03 and tool changes visible in the raw two-tip diff are not pending local
moves. No local source path moved or disappeared; active TunnelTracker header
consumers remain the two already verified units. No build inputs, registries,
historical EA paths or protected registers need repointing for this handoff.
