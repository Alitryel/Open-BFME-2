# Closer camera-ray bank

The bank at `reverse/attempts/0x0009bf33.cpp` is a corrected 440-byte candidate with four differing bytes. Its canonical symbol is `?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAUCoord3D@@@Z`. The earlier `PAVCoord3D` spelling came from a private class declaration; the canonical header declares a struct. The receiver and method retain address-derived names because their original identities remain unproven.

The actual extent is `[0x0009BF33,0x0009C0EB)`. Retail has an independent EBP prologue and `ret 12` at `0x0009C0E8`. The preceding matched body starts at `0x0009BD98` and spans 411 bytes; Ghidra independently records this start and a 440-byte size. The assignment's 412-byte extent ends inside the final position copy. No ledger extent was changed. `repair_queue.py dest` offers `Code/GameEngine/Source/Common/VslotMiscForwarders.cpp` as a neighbor heuristic, with no approved TU. No candidate was placed in `Code/`.

Retail calls camera slot `+0x50`, `CameraClass::Get_View_Plane` at `0x00134080`, `Coord3D::Normalize` at `0x00005A70`, and `RenderObjClass::Get_Position` at `0x0013B8A0`. Its owner fields are camera `+0xC0`, flag `+0x19`, origin pair `+0x1B0`, and signed dimensions `+0x1B8/+0x1BC`. The alternate path uses unsigned display dimensions from singleton `0x00DFE9D8`, slots `+0x40/+0x44`. Matrix reads are the three basis rows at camera `+0x18/+0x28/+0x38`. These are target facts, independently read from retail. Related BFME1 and ZH `W3DView::getPickRay` routines have different endpoint semantics and were not ported; they do not establish this function's name.

The old bank reused the cached camera across callbacks, read screen coordinates before display callbacks, introduced a `+4` RenderObjClass base adjustment, and stored direction components before completing all matrix reads. The replacement follows retail's camera reloads, screen access timing, unadjusted polymorphic base, and three local direction results before stores. It removes unused barrier and volatile helpers. Every original comment line is retained, including old metadata. Canonical Vector2 and Coord3D headers are included with paths valid from the bank directory.

| Measurement | Before | Replacement |
|---|---:|---:|
| Emitted bytes | 394 | 440 |
| Full 440-byte structural regions | 20 | 0 |
| Full raw memory differences | 18 | 8 |
| Full register differences | 9 | 0 |
| Relocation-patched differing bytes, including missing tail | 365 | 4 |
| Requested 412-byte structural regions | 19 | 1 |
| Requested 412-byte memory differences | 15 | 8 |
| Requested 412-byte register differences | 8 | 0 |

Six of the replacement's raw memory differences are DIR32 relocation operands, not defects. The requested 412-byte comparison truncates a retail instruction and reports the valid tail as a structural region. The complete-body comparison and independent boundary evidence should govern the next attempt.

The remaining mismatch is exactly two adjacent reloads. At retail offset `+0x9C`, retail loads `xmm3` from `[ebp-0x0C]`, then at `+0xA1` loads `xmm2` from `[ebp-0x10]`. The candidate performs those same independent loads in the opposite order. All other relocated instruction bytes match, including the full matrix schedule and epilogue. There are no unresolved callees.

The recorded hypotheses and refutation criteria are in `build/worker-9bf33/hypotheses.md`. Trial01 restores retail access semantics and local matrix outputs. Trial02 groups delta components. Trial03 adopts canonical headers. Trial04 models coordinate subtraction as an inline point operation and establishes the best alignment. Trials05/06 reorder independent coordinate calculations without improvement. Trial07 changes wider SSE allocation. Trial08's Y-first delta definition changes wider scheduling. Trial09's copy then subtraction is unchanged. Trial10's scalar aliases enlarge the frame. Trials11/14's grouped dimensions enlarge the frame. Trial12's shared screen-coordinate object is unchanged. Trial13's source branch swap changes block layout. Trials15/16's direct constructor and Set spellings are unchanged. The final cleanup also leaves the best alignment unchanged. No further justified experiment was identified.

Raw evidence remains under `build/worker-9bf33/`: `retail.log`, `identity.log`, `before-align-requested.log`, `before-align-full.log`, `before-metrics.json`, `final-align-requested.log`, `final-align-full.log`, `final-explain.log`, `final-metrics.json`, and each `trialNN` source and alignment log. `before.cpp` preserves the prior bank. `comments.log` records comment preservation. `pins.log` records the passing pin-consistency check. The post-bank raw checks and remeasurement are recorded beside these files; `manifest.txt` lists the task artifacts.

Inputs: BFME2 `af72028f8f334a7becdfa74206ce7acfe6391b75`, BFME1 `a18d9ed50607e9175de4d6568798d7d73119de09`, default MSVC 7.1, `/O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG`, with `BFME_OBJSTORE=off` for every compilation and measurement. Model: `gpt-6.1-sol`. No git writes, network requests, pins, ledger rows, or Code changes were made.
