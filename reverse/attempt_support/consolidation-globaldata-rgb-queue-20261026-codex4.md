# GlobalData getter prerequisite and stale RGBColor queue, 2026-10-26

Allocated family A shard 1/2, codex4. Runner `--check-tu
Code/GameEngine/Source/Common/GlobalData.cpp` exits 0. Normal `tu_skeleton.py
--plan` rebuilds routing in memory: 16 original-code approved rows, seven donors,
no mixed/refused donors. The current Common planner was reviewed: only this
GlobalData destination alternative for the named original-code rows; original
path/same-name/ZH/BFME1/WorldBuilder leads remain hints, not target identity or
merge approval. It flags private views, compiler settings, data ownership,
quoted includes, unplaced/folded rows and stale committed routing. No regenerated
map or move is included here.

## Verified prerequisite

The seed class lacked declarations for the two value-returning string getters
at 002360DE/002360FC (30 bytes each). Its actual fields are m_1240 and m_1244;
the donor called those same documented offsets m_string1240 and m_wide1244.
Declare the existing getters in the seed and consistently use its positional
member names in the donor. No method spelling, layout, visibility, compiler flag
or function body behavior changes. Normal file/RVA claims cover the complete
seed and getter donor; no other donor was edited.

Before trial (`build/codex4-globaldata-before.txt`): no accepted merge; getter
rejected for missing declarations. After trial
(`build/codex4-globaldata-after.txt`): seed and getter donor accepted, reporting
132 rows in the composed trial, including the two getter bodies (60 retail
bytes). The two official source files separately have 135 rows, including
existing folded/alias entries; the trial's row count is reported as printed,
not as new coverage. No merge was applied. This demonstrates a prerequisite
unblock for Luna, not a confirmed downstream landing.

The RGBColor adoption queue was also stale. GlobalData already directly
includes the canonical header and uses RvaGDColor as a derived constructor
adapter. `header_adopt_lane.py accept --class RGBColor` passes and retires its
one queue entry. This is acceptance of existing source, not newly authored C++.
The prior upstream source recovery/naming is retained and not attributed here.

## Checks and provider/consumer evidence

- `./build.sh GlobalData.cpp System/GlobalDataRva002360DE.cpp` with full Code
  paths before and after: 135/135 rows exact, seven string literals, 48 float
  literals and nine named imports verified. The frozen-file check passes both.
- `eh_verify.py` those files: all five EH rows EXACT, zero missing/nonexact.
- `data_check.py` both before and after: zero findings. No data debt retired.
- Before/after official objects saved under `build/codex4-globaldata/`.
  Scratch `proof.py`, using allowed_symbols COFF facts and data_check row facts,
  proves ALL code/data definitions, relocation digests, external references,
  linker directives, COMDAT selections and every row data binding unchanged.
  Thus this prerequisite changes neither selected-provider byte shape nor any
  consumer reference. The trial composition itself remains for Luna's normal
  composition/provider audit before applying a merge.
- Scoped identity reports remain shadow evidence, not a debt retirement. Before
  snapshot: 234 refs / 15 rows wrong; later snapshot: 218 refs / 13 rows wrong.
  These diagnostics depend on current object/cache state and are not claimed as
  a repair: the complete saved before/after object facts agree. No identity
  register key is removed or invented and no identity-debt reduction is claimed.
- Common planner refreshed after the source edits; `name_lane.py consolidate
  --check build/consolidation/common` passes. An earlier scan overlapped temporary
  dry-run files and correctly refused currency; it was regenerated after the
  trial ended. The planner is evidence only, not approval.

## Remaining blockers and batch handoff

Other donors still fail the normal trial: time-of-day and lighting code use
inconsistent terrainLighting/terrainAmbient members; rva00235312 lacks a seed
member declaration; options use secondaryScrollFactor/defaultIP private names;
Rva00236285 has a private STL allocator/vector-base view and declaration order
conflicts; Rva002362B4 has incompatible standalone/derived layout views and
constructor cleanup expectations. Those need their own evidence-backed
reconciliation. No speculative change was made to them.

The earlier SpecialPower prerequisite accepts 17 rows rather than 12, adding
five accepted rows / 227 existing bytes. It retired one AsciiString header key;
its separate data cleanup retired one data key and one linker alias. GameAudio
merged two donors into one TU, preserving two rows / 52 bytes (net one source
file fewer), with no identity-debt retirement. Inherited RayEffect/EyeTower/
Energy improvements were already upstream and are not new session gains.
SpecialPower's unedited destination/find/parser/store claims were released;
constructor/RVA/evidence claims remain until publication.

Other allocated probes this session: DemoTrap scope already held elsewhere;
ProjectileStream and Float have STL/private-base conflicts; OneRingPenalty has
pool/interface/module-data layout conflicts; SupplyCenterProductionExit has
pool/UpdateModule/interface/allocator conflicts. Prior RiderChangeContain,
Lifetime, ExperienceScalar and INIWater blockers were not blindly retried.
MessageStream's naming decision (issue #116) was left untouched. No maintainer
link cycle, smoke or nightly was run.

The full pending path audit still covers only the Audio move from merge-base
66a8afdbdc plus fixed-path repairs. Searches across active tools, hooks,
workflows, includes, build inputs, registries, Code and docs find old Audio
basenames only in historical census/evidence/provenance. No new path consumer
or path change was introduced by GlobalData. Protected registers are accounted
for; no map regeneration or code-identity retirement accompanies this repair.

`progress.py origin/master` before publication: byte-matched 7,978,500 (100%),
LINKING 7,370,962 (98.11%), LINKED 7,614,012 (98.75%), census 2026-10-26 08:28
at 47e030bafc; all byte deltas zero. No new census or linked-byte gain is claimed.
The fetched index is stale; carry any inconclusive pre-push audit findings to
the next census under existing LINK-017 rather than treating them as receipts.
Keep pending source/RVA/evidence claims until publication is confirmed, then
release file claims and run claims.py release --landed. Unrelated untracked
reverse/zh_sweep remains untouched. Runner session metadata records the actual
publication outcome and commit hashes.
