# Linking obstacle register

Required reading before selecting linking work; required updates with repairs
and attempt handoffs, and before ending a linking pass. Workflow:
[linking.md](linking.md#shared-obstacle-register). This is a shared handoff,
not an authoritative progress counter. Claim work through the normal claim tool.

## Maintaining this register

- Update only the entries your evidence affects. Record the date, source revision,
  affected symbols/units, work completed, verification result, remaining blockers
  and next useful check. Link a repair commit or tracked attempt evidence. For
  previews, identify the index revision, current-input checks and measured scope;
  put detailed receipts in the repair's normal evidence location.
- Reuse an existing ID for the same cause; give a new cause the next unused
  `LINK-NNN` ID. If a broad entry is only partly repaired, keep it open and list
  the repaired subset or split off a narrower entry. Do not mark a whole family
  cleared because one consumer links.
- Use **Open** for an unresolved lead, **Blocked** with a named prerequisite,
  **Repair landed / awaiting verification** for an unconfirmed repair, and
  **Cleared** only with verification of the stated scope against current inputs.
  State separately whether a later census confirms it. A preview clearance does
  not change the headline; a source edit or provider's existence alone is not
  proof that its consumers now link.
- Keep cleared entries and their evidence. Reopen an entry with the new failing
  revision and evidence if it regresses. Preserve other agents' updates when
  rebasing. Do not repeat an unchanged failed trial without new evidence or a
  resolved prerequisite.

For a new entry, use this shape:

```text
### LINK-NNN: concrete cause and affected scope
Status: Open. Updated: YYYY-MM-DD; inspected revision: <SHA>.
Evidence / affected units: <symbols, files, tracked evidence, index revision>.
Completed: <repair or attempt, commit and measured result, or none yet>.
Remaining / next check: <specific dependency and how to verify it>.
Clearance: <scope, current-input verification and evidence, or pending>.
Census confirmation: <published measurement revision, or awaiting / not claimed>.
```

## Baseline for the initial entries

Seeded on **2026-10-25** from the investigation at `76efac458e`.
The historical census measured `d2636bb381` at **2026-10-25 09:42 UTC**;
its status was published by `b78c9ed16e`. It records **7,343,016 / 7,512,658
executable-game bytes (97.7419%)**, leaving 169,642 bytes and 385 blocked units.
Use the published status: the status file inside the measured commit itself
describes the preceding census.

The official provider index inspected had provider facts updated to `51fde01dff`
at **2026-10-25 13:53 UTC**, but retained the 09:42 census's blocker lists.
Index SHA-256:
`7225d4beb4d607e264bb010fef0dc8fdcb36d15b684d16fc7e654ee776a037ed`.
Thus the counts below are historical leads, not freshly measured failures on
master. Recheck current inputs before choosing work. The register's initial
entries claim no new census or current-master compile result.

Start by verifying landed repairs, then reconcile container identities and
shared headers/providers in coherent batches. Do not total overlapping units,
authored-byte previews or commit-title gains into a projected headline.

## Obstacles and handoffs

### LINK-001: landed repairs still appear in the historical census

**Status: Repair landed / awaiting verification. Updated: 2026-10-25.**

- **Evidence / scope:** the deleting destructor
  `??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` blocked 34 graphics units;
  it was the sole blocker in 30, holding 45,189 authored nonpadding bytes
  (about 45 KB). The inspected provider index now has 33 retail-correct copies
  with identical digests. Provider evidence alone does not remeasure consumers.
- **Verified graphics subset (2026-10-25, `91fe970939`):**
  [the bounded verification](../reverse/attempt_support/weightinfo-verification-20261025/readme.md)
  passes 404/404 matched rows across all 34 units. Current-object inspection
  confirms 33 retail-correct copies and a correct selected body; W3DScene
  intentionally stopped emitting the incorrect copy. No destructor blocker
  remains in these 34 objects. The ordinary preview links all 30 historical
  sole-blocker units, covering **45,204 authored nonpadding bytes**. The other
  four retain unrelated dependencies, listed in that evidence. This graphics
  subset is **cleared in the bounded ordinary-preview scope**; census and
  closed-strict confirmation remain unclaimed. Strict receipt prerequisites
  found during verification are tracked separately as LINK-008.
- **Completed:** `51fde01dff` removed W3DScene's nonretail emission; its source
  was unchanged at investigation time. The earlier graphics gains overlap.
  Other landed repairs also have scoped evidence:
  [PlayerTemplate bucket copy](../reverse/attempt_support/object476-copy-link-20261025/readme.md),
  [record helpers](../reverse/attempt_support/asciistring-record-link-20261025/readme.md)
  and [narrow strings](../reverse/attempt_support/narrow-string-selective-link-20261025.md).
  Several historical `_Destroy` names already resolve to defined providers.
- **Remaining / next check:** check the next normal maintainer census for the
  verified graphics subset. Verify the other landed repair families' current
  consumers and providers before attempting another repair.
  Do not reopen a repaired name solely because `link_rank.py` still lists it.
- **Clearance / census confirmation:** graphics ordinary-preview scope cleared
  at the revision above; other families and census confirmation remain pending.
  Keep individual repair previews separate from later census confirmation.

### LINK-002: distinct container element identities and exception contracts

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** equal-sized `BfmePod28` / `BfmePod32` views conflate
  native types with different constructors and copy operations. The
  [element-split handoff](../reverse/attempt_support/pod-element-split-20261023/readme.md)
  names the provider and consumers: the vector at `0x00541434` calls copy helper
  `0x005411C8`, while its current spelling resolves to `0x00215F38`; the vector
  at `0x0052C823` calls `0x0052C27E`, not `0x00421D28`.
- **Completed / failed trials:** the
  [vector exception-contract bank](../reverse/attempt_support/vector-587c40-construct-link-20261025/readme.md)
  shows that a throwing copy declaration preserves the 189-byte parent but emits
  the wrong helper; `throw()` fixes that helper while breaking the parent.
  Suppressing the control overflow definition also broke another matched row.
  These trials were restored; they are not repairs.
- **Remaining / next check:** reconcile element identity, native callees,
  ownership, shared declarations and EH contracts together. Verify every
  affected provider, consumer and emitted copy. Size equality and a renamed
  template do not prove a shared native type. Clearance and census confirmation
  remain pending.

### LINK-003: residual Zero Hour memory-pool interfaces

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** historical blockers include `MemoryPool::freeBlock`
  in 21 units and `allocateBlockImplementation` in 15; these sets overlap and
  predate later repairs. The inspected provider index has neither operation.
- **Completed:** `d7d2a0c653` changed the sweep `GameMemory.h` to BFME 2's native
  virtual destruction / global delete and global allocation contract. BFME 1
  and ZH interfaces remain reference leads, not proof of BFME 2 behavior.
- **Remaining / next check:** find residual imported declarations and callers,
  prove their native BFME 2 contracts, and repair the class/header family.
  [Scripts.cpp's handoff](../reverse/attempt_support/network-byte-setter-astra-s2-20261023/readme.md)
  records pool calls alongside ScriptGroup/OrCondition, signed-byte and parser
  ABI blockers. Removing a pool call does not clear those other dependencies.
  Verify the affected consumers together; clearance and census confirmation
  remain pending.

### LINK-004: missing or incompatible shared providers and declarations

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** recurring historical names include `AudioEventRTS`
  destruction, assignment and `setObjectID`; `UpdateModule::crc`;
  `DamageInfo` / `DamageInfoInput` / `DamageInfoOutput` transfer methods;
  `INI::scanIndexList`; `ParticleSystemManager::createParticleSystem`;
  `Object::setProducer` / `setStatus`; and `DISABLEDMASK_NONE`.
- **Completed:** the initial `link_rank.py --owner-gaps --top 12 --near 3`
  inspection found 23 unresolved names with matched-address candidates. This
  is an ownership lead, not a repair or identity proof.
- **Remaining / next check:** resolve the real existing owner, parameter types,
  ABI and data ownership from native references; reconcile canonical headers
  with implementations and consumers as a batch. Verify all affected rows and
  selected definitions. Do not add a duplicate identity, stub or escape hatch
  to satisfy an old spelling. Clearance and census confirmation remain pending.

### LINK-005: units blocked by several incompatible dependencies

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** the historical blocker lists contain ConnectionManager
  (51 names), particle-module copy constructors (28), MapUtil (26), `texture.cpp`
  (21) and `ww3d.cpp` (20). These counts overlap the causes above and are not
  counts of independent missing implementations.
- **Completed:** the initial investigation grouped these as coordinated repair
  families; it made no source repairs or current-object measurements.
- **Remaining / next check:** refresh each unit's actual blockers, then reconcile
  shared string/map/vector views, destructors/vtables, signatures and graphics
  interfaces. Track resolved subsets and remaining names here or in a linked
  family handoff. A repaired dependency is partial progress until all blockers
  in the stated unit scope are checked. Clearance and census confirmation
  remain pending.

### LINK-006: compiler emission and the selected copy still disagree with retail

**Status: Open. Updated: 2026-10-25.**

- **Evidence / scope:** string erase/replace helpers and Render2D container
  destruction can resolve a symbol while retaining an incorrect selected body.
  Read the [prior linking handoff](../reverse/attempt_support/link-seat-20261025-final.md)
  and its referenced string/compiler banks before trying another emission shape.
  The vector parent/helper contract in LINK-002 is another concrete example.
- **Completed:** selective emission has repaired some other families, recorded
  under LINK-001; it does not establish a fix for these remaining cases.
- **Remaining / next check:** prove the native provider and inspect all emitted
  symbols, relocations, parent extents and EH graphs with current inputs. Merely
  suppressing a helper or changing an exception declaration can break a matched
  parent. Clearance and census confirmation remain pending for this scope.

### LINK-007: incomplete data ownership beyond clean symbol resolution

**Status: Open; one storage subset repaired. Updated: 2026-10-25.**

- **Evidence / scope:** the [linking handoff](../reverse/attempt_support/link-seat-20261025-final.md)
  identifies missing shader/filter root objects and the unowned 52-byte
  ScreenBWFilter group at `0x009B5B54`. Complete native objects and vtables are
  prerequisites; a symbol alone does not prove their storage or relocations.
- **Completed:** the [VP6 storage repair](../reverse/attempt_support/vp6-idct-storage-link-20261025/readme.md)
  proves the table's 548-byte allocation and records a fixed-comparison
  **17,413-byte placed closed-strict gain**. Those units already counted as
  linked in the headline. This is scoped closure evidence, not a new headline
  measurement of master; follow that lane's clean-room rules.
- **Remaining / next check:** shader/filter object ownership and the recorded
  `g_bfmeFilterLimit` / `g_bfmeDeringModifiers` data dependencies remain separate
  work. Verify storage extents, initial bytes, relocations and dependent closure
  through the existing ownership gates. Family clearance and census confirmation
  remain pending. Preserve the no-stubs/no-`/FORCE` runtime exit requirements.

### LINK-008: include inventories prevent strict reusable graphics receipts

**Status: Blocked on complete include inventories. Updated: 2026-10-25.**

- **Evidence / scope:** [graphics verification at `91fe970939`](../reverse/attempt_support/weightinfo-verification-20261025/readme.md)
  ran the normal gates successfully for 34 units, but its initial 17-unit
  `--prepare-current` run refused strict reuse. W3DShadowTextureCtor,
  W3DDebrisDraw, W3DDebrisDrawLegacy and W3DVolumetricShadow reported macro or
  parent-traversing include roots, or headers outside inventoried search roots.
- **Completed:** all 34 ordinary byte/receipt checks pass; 13 objects also have
  strict reusable receipts. The other 17 units were checked through the ordinary
  path; no claim is made that all of them are uncacheable. The refusal is retained
  in the evidence, and no gate was relaxed. LINK-001's destructor preview result
  does not establish strict closure.
- **Remaining / next check:** prove and make the actual include graph
  inventoryable under the existing gates, then repeat bounded strict preparation
  for all affected providers/consumers. A needed verifier repair follows the
  separate false-reject workflow. Do not substitute ordinary receipts for strict
  witnesses. Clearance and closed-strict confirmation remain pending; no census
  change is claimed for this inventory work.

## Investigation-specific validation limitation

The initial investigation preserved a pre-existing BFME 1 checkout at
`f5140c1cff6a58e16276fd6de6788186286953d4`, while BFME 2 pinned
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. Fetching the provider index succeeded,
but normal object import refused that mismatch. No check was bypassed and no
fresh local compile-based preview was claimed. This is a local input limitation,
not evidence that other agents or the whole repository are blocked. Use a
consistent verified checkout before taking new compile-based measurements.

The graphics follow-up above used a separate checkout with the pinned reference
and completed ordinary compile-based verification. The original checkout was
preserved; its mismatch did not block that isolated check. LINK-008 records the
separate strict receipt limitation encountered there.
