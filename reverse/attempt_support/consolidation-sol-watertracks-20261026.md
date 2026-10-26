# WaterTracks render-system declaration prerequisite, 2026-10-26

Seat codexb, family B shard 0/2. The allocated runner queue and `--check-tu`
authorize W3DWaterTracks.cpp. The scoped Water/ planner's original-path,
alternative-placement and prerequisite packets were reviewed; its currency
check passed before both ordinary trials. The current in-memory TU plan is
the routing authority; reverse/tu_map.csv is not regenerated on disk.
The seed, constructor and initializer file scopes are claimed together.

The ordinary baseline `tu_skeleton.py --merge
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
--dry-run` accepts no merge. The ctor fails C2600 because the seed's private
WaterTracksRenderSystem declaration has no constructor. The initializer also
fails declaration composition. The old composer-semicolon refusal is already
fixed upstream and is not the repair here. Baseline receipt:
build/sol-water-before-trial.txt.

The three existing views now agree on the resource pointers at +0/+4/+8,
ShaderClass at +C, list pointers at +10/+14, strips at +18/+1C, batch at +20,
level at +24 and AsciiString at +28. These offsets come from the already
matched BFME 2 constructor, initializer and seed accesses, not an external
layout inference. The seed's FeNode view retains its +B0/+B4 links; init still
allocates the target-proven 0xB8 BfmeThingSH and invokes the same constructor,
then casts that local pointer to the seed view. This does not assert that the
two names denote one recovered source class. The existing ShaderClass views
are combined without changing its emitted behavior or importing a donor header.
No shared header, canonical-class copy, pin, data definition or row is added.

## Standalone verification and binding evidence

`./build.sh` on the seed, WaterTracksRenderSystemCtor.cpp and
WaterTracksRenderSystemInit.cpp passes before and after: 10/10 matched
functions, one byte-verified data row, one parent-bound renumbered funclet,
two literals plus one empty-string reference, 27 compiler floats and zero
named imports. The declared-unmatched scan passes all three files before and
after (the seed retains its existing three unclaimed definitions).
Receipts: build/sol-water-{before,after}-build.txt.

Saved original objects are indexed by build/sol-water-before.json. The
supported allowed_symbols.Obj and link_census COMDAT readers compare all
external code/data providers, raw bodies, sizes, normalized relocation
referents, section flags, COMDAT selection modes and undefined references.
All 76 seed providers, four ctor providers and two init providers are
identical to their baselines. Local labels are compared by containing
provider and exact offset, not their compiler-generated spelling.
`python3 build/sol-water-proof.py` reproduces the scoped comparison.

The scoped code_identity_gate.check verdict is unchanged: 10 rows, 53
findings and one outside-baseline divergent Vector3 copy-constructor provider
in the unchanged header closure. Existing debt is preserved. data_check.py
reports zero findings; --converged reports 10 addresses, zero second names
and zero unjudged rows. link_check.py --new-variants --staged-peers --shadow
on all three sources exits zero with no variant findings. This preview is
not a census or full-link result. No identity or data key is retired.

## Demonstrated composition improvement

The repaired ordinary dry-run accepts exactly the seed, ctor and init,
10 rows across three files, versus no accepted merge before. The two ordinary
donor bodies (46 and 140 bytes) are newly compatible; these are existing
matched rows, not recovered bytes. Receipt: build/sol-water-after-trial.txt.
The accepted merge is left for Luna. No downstream Luna landing is claimed.

The final composed object build/tu_skeleton/b7d18def8acf7ac1.obj preserves
the complete union of the saved standalone code/data providers, bytes,
relocations, flags and COMDAT selections. No provider or undefined reference
is added, removed or changed; there are no baseline multi-variant names.
The unchanged anonymous-namespace BoundsValue constructor and assignment
receive a different MSVC filename hash in the verifier's temporary source.
Only those two observed local-name hashes are normalized; their full bodies
and relocation referents are still compared. No public symbol is normalized.
`python3 build/sol-water-composition-proof.py build/sol-water-before.json
build/sol-water-after-trial.txt` passes. The supported eh_verify.verify_row
API verifies both composed parent EH graphs EXACT, including the parent-bound
funclet at 0x0076408F. Receipt: build/sol-water-composition-proof.txt.

Remaining independent donors: Common/Rva000FE001Move.cpp lacks releaseTrack
in the seed view; Common/Rva000FE207Find.cpp still fails type composition;
WaterTracksObjRender.cpp collides with RealRange in BaseType.h;
WaterTracksRenderSystemFlush.cpp lacks shutdown;
WWMath/Rva000FF50DSaveTracks.cpp lacks WaterTracksObj::m_initTimeOffset;
WaterTracksRenderSystemFlush_Flush.cpp lacks flush. Their additional class,
field and compiler prerequisites are not inferred fixed by this repair.
The three mixed Common/TestUpdate donors remain untouched. Work on Common
prerequisites must be handed to their assigned owner before editing them.

## Batch audit and ownership

The audit at local HEAD 3bdbc42502 over `git diff --name-status --find-renames
origin/master..HEAD` plus this pending change covers the font global repair,
NetPacket attempt evidence and these three in-place WaterTracks edits.
There are no outgoing source path moves, deletions, splits or absorbed donors.
The initializer adds only the already-used ascii_string.h shim include and
its existing supported include directory. The before/after object comparison
verifies its complete emitted closure. Active tools, hooks, workflows,
includes, build inputs and registries require no path repointing; historical
EA paths and all debt keys remain intact. No TU-map update is staged.

File reduction 0; recovered C++ bytes 0; identity/data debt retired by this
WaterTracks prerequisite 0. The separate font commit retires one data key and
three alternatename occurrences. Keep the three WaterTracks file claims and
this handoff scope until publication is confirmed; then release them.

Class gate passes all three sources. Scoped Microsoft-header scan completes
with no failures or conflicts; only the seed's existing strcpy/strlen local
prototypes remain (same severity, existing unverified queue ownership).
Neither donor adds a local Microsoft declaration. Receipt:
build/sol-water-msheaders.txt.
