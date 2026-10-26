# FireSpreadUpdate declaration prerequisite: trial history and verified retry

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

## Verified minimal retry after the separate cache repair

Retry 2026-10-26, codex, family A shard 0/2. Fresh runner allocation check
accepts this TU; normal claims cover seed, pool donor, new view and this handoff.
The diagnostic-cache repair is a separate commit, fc3e3896ff. The minimal source
change is now retained: FireSpreadUpdateView.h copies the seed's existing Zero
Hour declaration header with its original license and adds only the already
rowed pool-key declaration. The seed includes that TU-scoped view. This is not a
recovered BFME 2 header or complete class-identity claim. The pool donor and its
compiler environment remain unchanged; the rejected broader trial above is not
reapplied. No paths, rows, flags, debt keys or data owners move.

Current scoped Update planner packets list one FireSpread destination alternative
for the seed/pool bodies, as hints rather than independent target proof. Their
EH placements remain unresolved by the planner. Actual routing is rebuilt in
memory by tu_skeleton; no regenerated map is committed. The planner records
internal linkage, include/macro context, seed unrowed definitions and protected
data/hatch registers as prerequisites; none are dropped by this source change.

The ordinary current-verifier baseline accepts no group (missing pool member).
After the declaration change, ordinary `tu_skeleton.py --merge TU --dry-run`
accepts seed plus pool: six existing rows, 286 retail bytes. This demonstrates
removal of the declaration/byte-composition blocker only. The composition is not
applied, and the static-guard data findings below still need resolution before
Luna treats it as fully merge-ready. The module-data member names, raw delay
receiver, Coord3D/PartitionManager conflicts and mixed sources are unchanged.

## Acceptance and composition evidence

- Before/after `./build.sh` all five source candidates passes 11/11, four strings,
  one float. `link_check.py --prepare-current --paths-from
  build/codex-firespread-retry-sources.txt` passes all five with strict reusable
  receipts. Frozen-file checks retain only the seed's three existing admitted
  definitions; class gate passes. EH verification of seed/pool: three EXACT.
- Supported upstream COFF readers compare every before/current object. All code
  definitions, undefined references, aliases, external data and non-debug
  sections preserve bytes, flags, relocations and COMDAT policies. Counts are
  55/1/13/2/1 code definitions and 616/2/23/4/8 sections across the five sources.
  All 31 standalone reference facts and data definition/reference facts are
  identical. Thus no standalone provider candidate or selected binding changes.
- Staged code identity: four rows, zero new findings. Data: one existing seed
  finding, zero outside baseline. Converged data: two sources, ten addresses,
  zero second names or unjudged rows. No register is retired or changed.
- The accepted seed/pool scratch composition preserves the union's 56 external
  code definitions and 547 external data definitions, their byte/relocation
  identities, COMDAT policies and aliases. External undefined references are
  identical after resolving definitions inside the composition. Data ownership
  facts are identical. There are no new external provider/consumer bindings.

Composition changes two compiler-local guard names: allow's $S21 becomes $S22
at RVA 0x00A0390C; pool-key's $S1 becomes $S21 at RVA 0x00A03904. Each still has
its own four-byte, zero-initialized, STATIC non-COMDAT section, identical flags,
no storage relocations, and the same unique parent and retail target address.
All other data reference facts agree exactly. These checks verify what changed;
they do not retire existing wrong-name findings or authorize new baseline keys.
The existing debt remains keyed to the unchanged standalone sources. Before an
actual merge, resolve the generated-guard findings through the data lane and
check the transfer's fresh verdict; do not hand-add or silently lose the old
keys. This is a remaining merge prerequisite, not an identity cleanup result.

Receipts: build/codex-firespread-retry-{before-build,after-build,before-trial,
after-trial,prepare,variants,allowed}.txt, *-object-proof.json,
*-reference-delta.json, *-data-delta.json, *-composition-proof.json and *-eh.json.
The composition receipt records both raw unequal guard names and their verified
storage/parent/address correspondence. All compilation uses the normal build
or tu_skeleton's safe scratch verifier; no manual match-cache compile.

## Complete pending batch audit

The complete outgoing range plus staged change has no source move, rename or
deletion. Its added source artifacts are GameMemoryGuardView.h (two verified
consumers) and FireSpreadUpdateView.h (the seed only). Combined path/basename
searches cover active tools, hooks, workflows, includes, build.sh, doxygen inputs,
class/header registries and queues. No active consumer requires repointing;
historical EA paths and all current ledger/debt owners remain. Raw two-tip diffs
also show incoming upstream changes, excluded from our outgoing merge-base diff.
Audit receipts: build/codex-firespread-retry-path-audit*.txt.

File reduction 0 (one header added), recovered C++ bytes 0, debt retired 0,
measured linking/ownership gain none. The source prerequisite is verified; the
merge remains blocked by guard identity and the other donors above. Retain four
FireSpread file claims and the earlier pending batch scopes until publication
is confirmed, then release file scopes and settle landed RVAs. No confirmed
Luna landing is claimed.
