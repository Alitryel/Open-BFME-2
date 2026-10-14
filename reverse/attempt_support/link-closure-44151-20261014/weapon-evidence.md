# Weapon and customized renderer link repairs

Bounded same-index previews gain **2,523 unique existing retail bytes**: WeaponBarrels 1,657 (1,659 raw) and CustomizedRender 866 (868 raw). No native recovery, ledger rows, pins, aliases or globals are added. Production changes are frozen.

## Scopes and provider identity

- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp`: adds `/DBFME_WEAPON_BARREL_INLINE_ONLY` to existing compiler flags.
- `reference/shims/w3dmodeldraw8/W3DDevice/GameClient/Module/W3DModelDraw.h`: opt-in decorates existing `ModelConditionInfo::WeaponBarrelInfo()` with imported forceinline; default header behavior and `clear()` body are unchanged.
- Unchanged real constructor owner: `W3DModelDrawO1Inlines.cpp`, native B493B / 32 bytes. Existing `clear()` owner remains `W3DModelDraw.cpp`, B2960 / 82 bytes.
- Unchanged consumer: `Code/GameEngine/Source/Common/Rva000BE775WeaponBarrels.cpp`, BE775 / 1,659 bytes. Its constructor is already declaration-only; removing the competing O2 emitter clears its sole wrong selection.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva007406E1CustomizedRender.cpp`: same-line imported forceinline decoration on `GenericMultiListIterator::First(void)`, matching its existing `Next(void)` technique. The body remains `CurNode = List->Head.Next`; native CustomizedRender 7406E1 / 868 bytes stays exact.

Weapon release ABI is independently supported by the verified consumer/providers: 60-byte record, three integers at 0/4/8 and Matrix3D at C. The O1 constructor default-constructs Matrix3D members then calls `clear()`; the suppressed O2 constructor performs the same initialization directly. No layout merge occurs.

## Production proof

Weapon `production/delta.json`, `production/proof.py`, `production/paired-proof.json` compare saved production-before and actual production-after objects. All nine matched provider bodies retain exact bytes, extents and relocations, including the 82-byte clear owner. Only the padded 84-byte constructor section disappears and the approved, existing **present-unmatched** `validateWeaponBarrelInfo` changes from 2,013 to 1,993 bytes through inlining of the same constructor/clear semantics. That change is uncounted and is not native recovery. All other nondebug data/EH sections, local relocation destinations and normalized `.sxdata` remain identical; no imports appear.

Custom `customrender/delta.json`, `proof.py`, `paired.json` compare actual production objects: only the unused five-byte First COMDAT disappears. Every retained function and remaining nondebug section, data, EH, relocation and normalized `.sxdata` remains identical; no imports appear. Local references normalize by destination section and offset; BSS uses section size, avoiding raw-pointer-zero file-header reads. The corrected normalizer also reconfirms Weapon.

Independent EH checks: Weapon's 23 rows are equal before/after with zero missing objects; Custom's native EH is EXACT before/after with zero missing objects.

## Gates and receipt status

Weapon normal `build.sh` passes 23/23 rows, three strings plus one empty reference, three floats and two named imports. Custom passes 1/1 with no literal/import findings. Both pass scoped frozen, class and new-variant checks. Original line endings and existing compiler options are preserved; only Weapon's opt-in define is added, and header default behavior is unchanged.

The initial Weapon strict preparation refused an uncacheable receipt. Root now reports that diagnostic resolved and owns final `prepfinal` evidence and the full header-triggered commit gate. No fallback or weaker check was used here.

Weapon's explicit three-object preview clears the consumer's selected constructor; provider/owner unrelated findings are uncounted. Custom's explicit one-object preview clears its sole First loser. This is a bounded prediction, not a new census or link.exe result.

## Provenance and claims

Reviewed verified donor a7c38d3 and repairs d003077f, d3f9000f, d2e21369: direct provider ownership and competing constructor/helper suppression guide the technique. No donor address, layout or alias scaffold is transplanted. Existing BFME2 matrix3d imported-inline suppression and Custom's Next decoration are target-specific precedents.

Rejected declaration-only trials never reached production: Weapon loses matched clear emission; Custom changes native bytes. Root holds Weapon consumer/provider/header claims under `codex-link-3528-link08`; Custom claim `file:8b24e81fe5d96d97` remains held under that owner. No worker git, ledger or index mutation occurred.
