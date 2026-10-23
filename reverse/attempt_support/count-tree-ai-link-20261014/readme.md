# AI count-tree destructor link repair

At base commit `424f9aa918b5f65be4bcd83f136d4f4c33f7648f`,
`Rva00598E85Ctor.cpp` still emitted a 52-byte count-tree destructor competing
with the existing 56-byte provider in `Rva00501875KeyPresence.cpp`, row
0x004FF5F3. A declaration-only specialization now routes constructor EH
cleanup to that provider. This completes the supported sibling repair left
in `../count-tree-link-20261014/readme.md` after its earlier claim expired.

The original 131-byte constructor boundary, address-derived identities, class
layout and compiler settings are unchanged. The count element remains a
structural view; this repair establishes no new original type or class name.
No pin, alias, alternate name, header or baseline was added.

The controlled comparison uses runner census measurement `147cfae2cb`, dated
2026-10-14 07:27, index SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
Both previews replace the same six objects in that index, using preserved
before objects and current after objects. The provider and four previously
repaired consumers have identical before/after object hashes.

| Unit | Before findings | After findings |
| --- | ---: | ---: |
| Rva00598E85Ctor | 36 | 35 |
| Rva00501875KeyPresence | 0 | 0 |
| TerrainLogicCtor | 14 | 14 |
| CreateAHeroDataCtor | 25 | 25 |
| Rva004FD0DACtor | 3 | 3 |
| Rva0059DA34 | 10 | 10 |

The removed finding is the AI count-tree destructor COMDAT conflict. Total
findings fall 88 to 87; clean units stay 1/6 and existing linked authored bytes
stay 394. No clean unit becomes blocked. The AI unit still has three unresolved
names, thirty other COMDAT conflicts and two wrong-selected base definitions.

Six COMDATs totaling 155 bytes disappear: the 52-byte destructor and five unused
cleanup helpers. All 128 retained COMDAT bodies and relocation digests are
identical. Strong definitions and weak bindings are unchanged; the only new
undefined reference is the existing count-tree destructor. `object-proof.json`
records hashes, per-unit counts, the exact removed finding and provider copies.
The census classifier calls the provider destructor `unknown`; its 56-byte
ledger row instead passes the ordinary full-byte and relocation gate. This
repair does not change the classifier or claim stronger classification.

Acceptance checks:

- Bounded `link_check.py --prepare-current` passes 19/19 rows across the
  claimed constructor and provider before and after, with strict reusable
  receipts. The after `./build.sh` gate also passes 19/19. String, float and
  import reference checks pass.
- `eh_verify.py` passes all three EH rows exactly.
- Six-source local `link_check.py` produces the paired result above; exit 1
  remains expected because five units retain independent blockers.
- New-variant admission, class gate, undeclared-definition and CSV checks pass.
  Enforced converged-data checking judges eight addresses with zero second
  names; placement rescan finds zero bodies or pins.
- The commit hook passes. Its code-identity shadow check reports seven divergent
  template/base helper definitions; the enforced byte gate and shadow data check
  pass. Those independent definitions remain outside this destructor repair.

This is self-strict byte evidence for the constructor/provider and a bounded
legacy link preview. The four unchanged sibling objects lack current strict
receipts; no closed-strict or full-link-cycle improvement is claimed. No census,
index or link-status file was changed and no maintainer-only runner was started.

The BFME 1 verified pointer `23b143233b5a8664a3bdf8572df6d905c310a5a1`
contains declaration-only tree destructor repairs in
`game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0064D320PeerThreadDestructor.cpp`
and `game/GameEngine/Source/GameLogic/ScriptEngine/AttackPriorityInfoSetPriority.cpp`.
They support this technique, without transferring donor code, names or layouts.
BFME 2 byte/EH checks and the controlled local comparison prove applicability.

Freshness fetch found upstream `bc990782485c4111aa72d4fb8f8d00bb82e12f5b`.
The verified pointer is retained: the existing old-input baseline attempts
record compiler stalls and thousands of stale TUs. That unresolved full-gate
prerequisite was not retried unchanged or marked successful. Original objects,
complete local check logs and the exploratory proof remain under
`build/count-tree-ai-link-20261014/`.
