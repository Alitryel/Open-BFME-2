# WaterTracks flush header prerequisite, 2026-10-26 (codexb)

Allocated family B/shard 0 destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp`.
Inherited save/shutdown repairs and their handoffs are already on
`origin/master` at 55b51baee1. Their publication claims were released. No
earlier result is counted again here.

The current Water parent naming planner and in-memory TU plan were reviewed.
The ordinary `tu_skeleton.py --merge TU --dry-run` completes with the same
five-file, fifteen-row accepted subset: seed, constructor, initializer,
shutdown and save. Actual flush (`WaterTracksRenderSystemFlush_Flush.cpp`,
0x0010004D, 392 bytes) remains rejected. No merge was applied.

The six standalone files build 16/16 rows. The actual-flush rejection first
reports missing RenderInfoClass before dx8wrapper.h, then incompatible system
pointer/member spellings and the texture handle type. A scoped trial moved
the complete camera/render-info declaration before that include, aligned
system fields with the seed and used explicit body casts for the existing
buffer/list/texture views. Its standalone flush still builds 1/1. The six-file
union-first and union-longest compositions now compile, but retain only
12/16 exact rows:

- FE90D constructor: byte +7 is 08 instead of retail 10. dx8wrapper.h imports
  ShaderClass::Reset rather than the existing verified 0x10441b default.
- FE93B initializer: byte +49 is F7 instead of EF. The imported shader header
  implements its cull mask differently from the existing verified call view.
- FE379 WaterTracksObj::init: the tail diverges at +1379 because the imported
  TextureClass now inlines its refcount release where the seed's minimal
  declaration emits the existing external call.
- Its associated cleanup at 0x0076408F has no exact same-source parent EH
  location after that code change.

These are target-byte observations, not proof that a donor's class definition
is BFME 2's complete ABI. No shared shader/texture header or consumer was
changed. A local declaration-only edit cannot be accepted with those lost
rows; the attempt was restored exactly from the baseline source copy. All six
file claims were released and the blocked verdict was recorded through
re_log.py. The unchanged Common resource/list donors remain for family A.

Receipts: `build/sol-water-flush-{plan,views,before-build,before-trial}.txt`,
`build/sol-water-flush-six-{initial,first}-errors.txt`,
`build/sol-water-flush-diff.py`, `build/sol-water-flush-before.json` and its six
saved objects/source copies. The restored donor passes declared-unmatched.
The attempted source remains scratch-only in
`build/sol-water-flush-declaration-attempt.cpp`.

No authored byte growth, file reduction, debt retirement, binding improvement
or link-census change is claimed. No source/path/register change is published
from this trial. The next prerequisite is a coherent target shader/texture
interface with verified affected consumers and complete provider/COMDAT/EH
comparison; do not repeat the field/include-only trial unchanged.
