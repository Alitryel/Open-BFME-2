# Energy Xfer composition prerequisite, 2026-10-26

Allocated destination: `Code/GameEngine/Source/Common/RTS/Energy.cpp`
(`consolidation_queue.py --check-tu` exited 0). Read the prior Common and Energy
adder handoffs. The scoped Common/RTS planner retains only Energy.cpp as the
same-spelling path alternative, with unresolved opaque rows, stale-map and
mixed-source qualifications. These are investigation leads, not placement proof.
The supported merge tool independently rebuilt routing in memory: 11 approved
rows, one getter in a mixed source with 21 foreign rows. No TU map was staged.

Before this change, ordinary `tu_skeleton.py --merge ... --dry-run` accepted no
two-file composition. EnergyXfer's separate Player/Energy views collided with
the seed; lifting BfmeXfer.h also bypassed its operand forward declarations.
Both originals passed the official build before editing (10/10 functions).

The two files now include one private EnergyView.h. It retains the Xfer donor's
three unnamed virtual slots followed by xfer, replacing the seed's explicit
vptr word without changing accessed offsets. Production remains +4, consumption
+8, owner +0xC; Player retains the directly accessed index +0x54 and the seed's
existing brownout notification declaration. All Xfer operand forward declarations
precede BfmeXfer.h inside the header, including during composition. No new names,
global aliases, compiler flags, ledger rows or complete-class recovery claims.

Verification:

- `./build.sh Code/GameEngine/Source/Common/RTS/Energy.cpp
  Code/GameEngine/Source/Common/RTS/EnergyXfer.cpp`: 10/10 functions exact before
  and after; one float literal exact. `find_declared_unmatched.py` passes both.
- Ordinary `tu_skeleton.py --merge Code/GameEngine/Source/Common/RTS/Energy.cpp
  --dry-run` now accepts both files, all ten rows / 378 existing retail bytes,
  with no rejected clean donor and no carried flag override. Leave this merge
  for Luna. The mixed getter remains untouched; the planner's constructor-thunk
  lead is not a current approved donor and was not claimed or edited.
- Standalone before/after COFF code definitions, digests, sizes, exclusivity,
  COMDAT selection, data definitions and undefined references are identical.
  Composed object `build/tu_skeleton/c916be0c59e01618.obj` equals their union:
  12 code definitions, one external data definition, five unresolved references
  after internal resolution. All ten row DIR32 data-reference sets are unchanged.
  Local reproducible comparison: `python3 build/codex4-energy/proof.py`.
- `allowed_symbols.py --source` both files: 12 references, ten owner/two fold,
  zero wrong bindings. `data_check.py`: zero findings; `--converged`: ten
  addresses, zero second names/unjudged rows. EH: zero rows requiring EH data,
  zero missing objects. Existing identity/data/header register keys and owners
  stay intact; no debt retirement is claimed.

Before committing, audit the full pending range `origin/master..HEAD` together
with this staged prerequisite, including the EyeTower prerequisite. No source
path is moved, absorbed, renamed or deleted. New private headers have only their
intended source includes; active tools, hooks, workflows, build inputs and
registries need no path repointing. Historical EA paths remain unchanged.
Planner refreshed and currency check plus check_csv pass. Local receipts are
`build/codex4-energy-{trial-before,trial-after,build-before,build-after,proof,
identity,data,converged,eh,planner-final,path-audit}.txt`.

This demonstrates a prerequisite unblock, not a later Luna landing. File
reduction, retired debt and recovered C++ bytes are all zero. Keep the two source,
new header, this handoff and ten RVA claims until publication is confirmed;
release explicit existing-row RVA claims as well as file claims after landing.

## Inherited batch recheck, 2026-10-26

The next session recovered the rebased prerequisite commits `05315ab7e0`
(EyeTower), `c68ece0e45` (Energy), and `65fbeb2793` (TerrainRoads handoff).
The official five-source build still passes 17/17 function rows and its data
row; the frozen-file check and both saved provider/COMDAT/data-binding proof
scripts pass. Fresh normal dry-runs still accept Energy's ten rows and
EyeTower's seven rows, with the same remaining STL/header blockers. No merge
was applied. Receipts: `build/codex4-{energy,eyetower}-recovery-trial.txt`.

Reaudited the complete `origin/master..HEAD` batch: no existing source path
moves, deletes or renames; the two new private headers have precisely the five
intended consumers, all verified above. Active tools, hooks, workflows and
registries require no repointing; historical paths and protected debt keys
remain intact. Receipt: `build/codex4-recovery-path-audit.txt`. The inherited
25 claims remain held until publication is confirmed. This recovery adds no
recovered bytes, file reduction or debt retirement.
