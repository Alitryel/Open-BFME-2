# WeightInfoStruct deleting-destructor verification, 2026-10-25

The landed `51fde01dff` repair passes a bounded current-object check at BFME 2
`91fe9709390e5042aa9344a90a9cb10615c87d26`, using its pinned BFME 1
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. No additional source repair was
needed. No source, ledger, verifier, baseline, pin or census status was changed.

## Result and scope

- All **404/404 matched rows across 34 units** pass the ordinary byte gate,
  including the data, string, float and named-import checks. Four data rows
  pass; the gate also checks the current EH parent binding of 39 funclet rows.
- After replacing all 34 units' indexed definitions with their current objects,
  the destructor `??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` has
  **33 copies, all retail-correct, with one digest**. The normal selection rules
  choose `animobj.obj` and grade the selected definition `ok`.
- None of the 34 objects has a remaining blocker for this destructor.
  W3DScene is the historical affected unit that no longer emits a copy:
  `51fde01dff` removed its incorrect emission. A separate 34th copy is unnecessary.
- The ordinary link preview reports **30/34 units clean; 0 -> 45,204 authored
  nonpadding bytes** against the published index. All 30 are the historical
  sole-blocker units. This is a scoped preview result, not new unique matched
  coverage or a new census headline. The earlier historical 45,189-byte weight
  and today's 45,204-byte preview have different ledger inputs; do not add them.

The other four current objects retain these preview blockers against the
published providers; categories overlap where a name is both a COMDAT and
selected-copy problem:

| Unit | Unresolved | COMDAT | Selected | Main families to reconcile |
| --- | ---: | ---: | ---: | --- |
| W3DModelDraw.cpp | 12 | 5 | 3 | Drawable, particles, INI, W3DAnimationInfo/BitFlags copies |
| W3DTankTruckDraw.cpp | 12 | 3 | 1 | AudioEventRTS, W3DModelDraw, Drawable, Render2D containers |
| W3DGameClient.cpp | 10 | 2 | 2 | client/UI/display constructors, Drawable, Render2D containers |
| W3DTerrainVisual.cpp | 30 | 0 | 0 | terrain/height-map/water interfaces and file streams |

Full decorated names and per-unit results are in [audit.json](audit.json) and
[preview.log](preview.log). Other families may have newer repairs outside this
provider snapshot; confirm their current owners before attempting fixes.
The destructor selection itself is cleared in this ordinary-preview scope.
Closed-strict closure, executable placement, runtime and census confirmation
are not established here.

## Inputs and verification commands

The verification ran in an isolated worktree with the correct reference pin.
The main checkout's pre-existing BFME 1 revision
`f5140c1cff6a58e16276fd6de6788186286953d4` was preserved. Official BFME 1 master
was fetched and observed at `5d6792fa0e7b65d020454d42137389bd00adb56a`; this scoped
check does not advance or claim to verify that newer reference revision.

The published index has provider facts from `51fde01dff` at 2026-10-25 13:53 UTC
and historical blockers from census `d2636bb381` at 09:42 UTC. Its SHA-256 is
`7225d4beb4d607e264bb010fef0dc8fdcb36d15b684d16fc7e654ee776a037ed`.
The downloaded index was retained unchanged. The optional whole object-cache
import was stopped after downloading it; no verification verdict depends on
that import completing. Ordinary dependency checks validated any restored objects.

Commands used Python 3.13 with `BUILD_POOL=4`, no `CL` / `_CL_` overrides:

```text
python3 tools/link_check.py --prepare-current --paths-from build/weightinfo-verification/sources-1.txt
python3 tools/build.py <the 34 explicit source paths in sources.txt>
python3 tools/link_check.py --paths-from build/weightinfo-verification/sources.txt
python3 build/weightinfo-verification/audit.py
```

`tools/build.py` here is the normal `build.sh` entry point, not a call to the
low-level compiler API. The preview's exit code is **1**, because four units
remain blocked on other names; the byte gate's exit code is **0**.

To repeat the scoped check, use a consistent checkout at the recorded revisions
and the same published index hash. Copy `sources.txt`, `sources-1.txt` and
`historical.json` into `build/weightinfo-verification/`. Copy
[run_step.py.txt](run_step.py.txt) there as `run_step.py` and
[audit.py.txt](audit.py.txt) as `audit.py`. Run the driver with `prepare-1`,
`byte-gate` and `preview`, then run `audit.py`. It invokes ordinary tools, checks
receipts and selection rules, and refuses changed tracked inputs. A different
index is a new comparison; record its metadata and do not attribute all changes
to the destructor repair. Never run a census merely to reproduce this preview.

## Strict reusable receipt limitation

The initial 17-unit `--prepare-current` run compiled its explicit scope but
**exited 1 before its ordinary byte-gate stage**. Four sources reported no
include inventory because of macro/parent-traversing include roots or a header
outside inventoried search roots:

- `Code/GameEngine/Source/Common/W3DShadowTextureCtor.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawLegacy.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`

The full ordinary byte gate ran separately and passed. The audit checks all
34 ordinary source/header/command receipts; **13** also satisfy strict reusable
receipt checks. The other 17 units were checked through the ordinary path;
their lack of strict receipts does not prove that all 17 are uncacheable.
No second strict-preparation batch was run after the first refusal.

This is not a successful all-unit strict preparation or closed-strict witness.
Do not bypass the inventory refusal or reuse this evidence as one. The next
prerequisite is proving the actual include graph and making the named inputs
inventoryable, then repeating bounded strict preparation. Any needed verifier
repair follows the separate false-reject workflow. See register `LINK-008`.

## Evidence

- [audit.json](audit.json): source/object/receipt SHA-256 values, ordinary and
  strict currency results, all provider verdicts, selection and remaining names.
- [historical.json](historical.json), [sources.txt](sources.txt): exact original
  34-unit scope and historical weights, rather than a newly ranked work list.
- [byte-gate.log](byte-gate.log), [preview.log](preview.log),
  [prepare-1.log](prepare-1.log): normal tool outputs including the refusal.
- The corresponding `*-result.json` files bind commands, exit codes, elapsed
  times and raw log SHA-256 values. Raw logs retain their original bytes.

The actual objects and dependency sidecars remain in the isolated worktree's
`build/match/`; they are not shipped as fresh census or closure receipts.
