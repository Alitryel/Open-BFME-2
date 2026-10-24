# BFME 1 reference freshness, 2026-10-24

Controlled official-master update from clean verified donor
`f5140c1cff6a58e16276fd6de6788186286953d4` to
`32774ab03393709a7f14331ba8d98d281a55ffd9`. Both full comparisons use
BFME 2 production sources at `49e88f596aae1bc8659ccf98028c6e11521a8f04`.
The previous checkout remains reachable as local branch
`bfme2-verified-f5140c1c`; no dirty or unpublished donor work was discarded.

Both full `PYTHONUNBUFFERED=1 BUILD_POOL=8 ./build.sh` runs pass all
98,200 function rows across 23,422 sources and all 2,179 data rows, plus
literals/imports/floats, DIR32 consistency, pins, module registry, source
claims and no-op patch. The new-pointer pass compiles zero of 23,421 TUs
with current dependency caches. No update regression or baseline change.
The ignored freshness success stamp was written only after both full gates
and the EH comparison passed.

Both complete EH checks contain 11,871 exact rows, 23 bytes_differ and one
retail_only, all 24 existing findings baselined, with no missing objects.
The JSON results are identical, SHA256
`8a02dc7ae02f348b3e7990773fdd470df3bd1501a02ccb862fe934d91f3f684e`.
Text summaries are retained here; complete JSON remains under ignored
`build/seat-freshness-{old,new}-eh.json`.

The donor changes 83 files, including 57 game C++ sources; no headers,
inputs or layout changed. The existing resolver selects game/ and
inputs/{reference,vendor,toolchains,baselines}. The resolved vector and
AsciiString headers, lift tool and compiler DLL exist, and their old/new
hashes agree (inputs.json). No repeated layout migration or header
substitution was needed.

Separate reference lanes were refreshed at 32774ab0:

* BFME 1 scan: 38,788 donors; 5,525 placements, all claimed;
  5,516 independent boundary controls. Ranked and near each return zero.
* Named lift lane: 146 bodies, 103 servable (79,182 B); source leads only.
* ZH compile: 918 current cached objects, zero built, 68 existing failures
  among 986 sources (missing WWAudio/oaidl dependencies and armor/DirectX
  configuration). Relevant headers/toolchain/flags did not change between
  donor pointers, so these are pre-existing failures, not update regressions.
  Fresh match: 26,993 functions, no free exact placements. Fresh packets:
  zero candidates, 241 addresses already claimed. Packets were redirected to
  ignored build/ to preserve unrelated untracked reverse/zh_sweep work.
* The previous clean RTS2DSceneDestructorThunk donor compile/search remains
  valid: its unchanged source produced zero placements/pins. This does not
  establish exhaustion of all reusable donor C++.

The linking donor review includes the latest e8ed3571cc locale repair:
BFME 2 already uses its custom locale implementation, so that change is
inapplicable here. Previously reviewed string, topple, online, geometry and
terrain repairs remain inherited or depend on recorded native prerequisites.
No maintainer-only verification runner was used.
