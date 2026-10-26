# Texture statistics scalar ownership

2026-10-26, control `d831bc24031`, BFME 1 input `ff391a5e90aa18ebd01e470c1a7bea5fc3b97c7d`.
Served file: `Code/Libraries/Source/WWVegas/WW3D2/DebugStatisticsRecordTexture.cpp`.

The recording unit had a private copy of the mode read/written by the existing
`statistics.cpp` setter and getter. The reporting companion independently held
seven private last-frame counters whose public getters read different storage.
Bind these consumers to the existing definitions in `statistics.cpp` instead.
No new global name, pin, data owner, function row or source path is introduced.

| Existing owner symbol | Retail RVA | Repaired consumer |
| --- | --- | --- |
| `record_texture_mode` | `009EE8F4` | DebugStatisticsRecordTexture.cpp |
| `last_frame_texture_memory` | `009EE89C` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_texture_count` | `009EE884` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_lightmap_texture_memory` | `009EE8D0` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_lightmap_texture_count` | `009EE878` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_procedural_texture_memory` | `009EE8D8` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_procedural_texture_count` | `009EE8D4` | DebugStatisticsRecordTextureEnd.cpp |
| `last_frame_texture_change_count` | `009EE8BC` | DebugStatisticsRecordTextureEnd.cpp |

These bindings are target facts from matched DIR32 sites and the existing
data-ledger owners, not a new donor-name inference. The untouched owner supplies
the same integer or enum type. The source declaration changes remove exactly
eight private storage definitions. They preserve all initialization and teardown
code in the consumers.

## Verification

- Normal before/after builds: 51/51 matched rows across both consumers and
  `statistics.cpp`, plus its one data row. All defined functions remain matched.
- 4/4 EH graphs EXACT. Strings (17 literals plus 3 empty references), floats
  and the named import pass the normal checks.
- Full emitted-code comparison: 22 recording, 17 reporting and 40 provider
  definitions unchanged in bytes, extent and relocation targets after applying
  only the eight intended data-binding substitutions. No code provider added
  or removed. The comparison includes unrowed compiler-generated code.
- `link_check.py --prepare-current`: all three sources have strict reusable
  receipts; this prepares inputs and is not a closed-link result.
- `repair_queue.py retire data SOURCE`: two recording keys and fourteen
  reporting keys retired by the owning tool; eleven keys remain for each file.
  The register is not edited by hand. Converged-data checking reports zero
  second names and zero unjudged rows.
- Fixed index `47e030bafc`, dated 2026-10-26 08:28: before/after ordinary
  previews keep both consumers clean, 774 + 1,006 authored bytes. The unchanged
  `statistics.cpp` provider has the same unresolved string, duplicate and
  selected-copy findings in both controls. Several refer to pre-consolidation
  objects. No new linking bytes or family closure is claimed.

The source batch will also receive the normal pre-push provider/consumer audit.
The available index predates this source base; any inconclusive result belongs
to LINK-017's current-index prerequisite and the next maintainer census, not a
measured loss or gain. No maintainer-only runner is used.

## Whole-file remainder and restored trial

Changing the reporting unit's own `recordTextureMode` to the shared external
mode changes instruction scheduling around the StringClass null-byte store.
The 948-byte `Record_Texture_End` parent fails the normal byte gate; this
independent mode trial was restored. Its seven last-frame bindings then pass
the whole cohort. A future repair must preserve that ordering without adding
an optimization hatch or changing the verifier.

`TextureStatisticsVector.cpp` was held by another worker when the companion
claim was attempted, so it was not edited. Eight current-frame counters depend
on reconciling that reset provider and the reporting consumer together.

The selected vector debt is not safely fixed by replacing it with an extern
reference to the provisional `unsigned g_Va009EE920`: that owner is only four
bytes, while the recording file has a real DynamicVectorClass object and a
matched initializer at `007ACD20`. `latest_texture` similarly owns a matched
initializer at `007ACCC0`; its shutdown spelling and separate provider are
already a recorded prerequisite in `reverse/re_attempts.log` (007B7040).
The reporting StringClass object also has its own matched initializer.
Their extent, initialization, teardown and one-owner reconciliation remains
open. No lifetime definition or initializer was removed to hide those keys.

This batch retires sixteen data-debt keys, with zero new C++ exact bytes.
It makes no census, image-ownership or runtime claim.
