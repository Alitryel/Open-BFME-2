# Formation preview: complete partial replacement

The bank for `?updateFormationPreview@InGameUI@@QAEXXZ` at RVA `0x002A4E1F` now reconstructs the complete preview flow. It is not an exact match. The original farm body omitted most operations, used seven unresolved or wrong helper declarations, and emitted less than three quarters of retail. The assignment's incomplete-bank exception applies; its region count cannot establish comparative closeness. The original three comment lines are preserved verbatim beneath the new bank metadata.

## Identity and native contracts

The native entry installs an EH frame and receives `this` in ECX, ends in RET at VA `0x006A57BC`, and abuts the independently matched map body starting at RVA `0x002A57BD`. The preceding matched preview-placement body ends at the target entry. WorldBuilder `0x00DC0B00` explicitly names `InGameUI::updateFormationPreview` and shares the relevant call relationships. This establishes the parent name and boundary independently of byte similarity. WorldBuilder is a debug-build relationship lead; native supplies all offsets, the selected-ID list and hash absent from that debug body, helper targets, cleanup conventions and final operations. No BFME 1 or Zero Hour function body was ported.

The facing helper is an ECX member returning Coord2D through a hidden output pointer, with RET 4, as independently supported by the matched `0x0029DB61` caller. The existing pin is reused; the bank's free-function/POD declaration was wrong. The established native providers supply selected-ID and Object list construction, Object-pointer insertion, both teardowns, formation selection/build/deletion, preview reserve/placement, pool lookup, color conversion, Drawable position and Thing orientation. No pin, source-provider or shared-header change was made. Native placement/build/pool helpers are now matched; the facing helper itself remains unrowed.

The complete C++ follows inactive fading, delay gating, selected-ID collection and hashing, Object filtering, formation rebuilding, per-entry transformation and drawable/decal placement, pool acquisition, and all four direction-decal updates. Borrowed address-named receiver views preserve established provider signatures; they do not claim additional original class names. Layout assertions cover every target member used by the reconstruction, including the placement stride and both preview payload layouts.

## Experiments and remaining mismatch

The pre-experiment hypothesis, evidence and refutation condition are in `build/formation-preview-w6/hypotheses.md`. The initial complete trial exposed unintended out-of-line math/getter calls; forcing the WB-supported inline operations removed these unresolved calls. The signed high-mask trial emitted SAR and was rejected as semantically wrong. Restoring an unsigned mask preserves the native logical rotation. The later signed-shift/low-mask spelling is equivalent but did not improve alignment. Const qualification alone did not preserve the facing-square intermediates. The retained candidate expresses the native cached SSE squared lengths, the unrounded x87 unit inverse and the scoped nonthrowing pool-list teardown directly. The packaged bank is byte-and-relocation identical to `trial04.cpp`.

The authoritative local measurements are `build/formation-preview-w6/measurements.json`, with unmodified tool outputs in `before-align.txt` and `candidate-align.txt`. The original body emits 516 bytes versus retail's 2462; the replacement emits 2436. Positional patched-byte differences are 2442 before and 1905 after, including missing-tail bytes. These byte counts are diagnostics, not the reason to replace the bank. Original alignment reports 31 structural regions, 28 memory and 21 register differences; replacement reports 45 regions, 123 memory and 46 register differences. The old body is too incomplete for that comparison. Replacement is justified by the complete native-supported behavior and size, not by treating an increased operand count as an improvement. Trial 2's 43/102/36 counts and trial 5's 47/124/43 counts are not monotonic improvements over the retained body and are preserved only as diagnostics.

The remaining native mismatch includes frame 0x74 versus emitted 0x78, missing explicit high-bit mask in the equivalent hash rotation, facing-square homes/CSE across calls, matrix sine-store and transform register scheduling, unit/perpendicular normalization evaluation and final decal update scheduling. No native operation was replaced with volatile barriers, dummy calls, asm or padding. The retained candidate resolves every direct call, but does not pass exact-byte equality. Further progress needs an evidence-backed hypothesis for these inline math and lifetime shapes; the five source trials and object/disassembly logs preserve the tested alternatives.

## Reproduction and checks

Input revision: `b65794c66d4aa9aa20756625c1405954c1f8a889`. Inspected BFME 1 reference revision: `a18d9ed50607e9175de4d6568798d7d73119de09`. Every compile and measurement set `BFME_OBJSTORE=off`; each trial used a fresh source/object path. Source settings remain in the preserved first `// cl:` line, with STLport configuration expressed as source preprocessor definitions. The bank's relative canonical includes also work from its new path.

`verification.txt` records comment preservation and body/relocation equivalence. `layout-align.txt` records a successful compile with 24 native layout assertions. `provider-boundaries.txt`, `prior-verdicts.txt`, `destination.txt`, `native-wb.txt`, the extracted WB text, every trial source, and the object/disassembly logs remain under `build/formation-preview-w6/`. The destination tool proposes `Code/GameEngine/Source/GameClient/InGameUISuperweapons.cpp` only by neighbour heuristic and says there is no usable approved TU (TU map proposes `InGameUI.cpp`); no production source was edited. CSV and pin checks are recorded in the same scratch directory. No exact-result source gate was claimed, no git write or network operation was performed, and no background process was started. Model: gpt-6.1-sol.

Final delivery checks passed: `call-proof.txt` compares every direct callee destination and count, every virtual slot and count, final body/relocations against the retained trial, and all original comment lines. `bank-final-align.txt` and `bank-final-object.txt` are fresh measurements from the bank after deleting its object and dependency receipt. `check-csv-after.txt` and `pin-check-after.txt` are successful hygiene checks. The first diff check reported CRLF as trailing whitespace because Python's Windows text output had mixed with re_log's LF metadata; only the two own delivery files were normalized to LF, and the fresh bank measurement is unchanged. `diff-check-final.txt` records the passing final diff check. No source-level exact-byte gate was run because no matching production row was added.

## Round r (claude-opus-5-5, 2026-10-19): 45 -> 24 regions

Levers that helped, each measured with `build/try.sh` on a fresh object:
- Hash: `unsigned hi=hash&0xF8000000;hash=(hash<<5)^(hi>>27)^id;` keeps retail's explicit `and 0xf8000000`.
- `Player *player=ThePlayerList->localPlayer;` hoisted after `SelectedIDs ids(allocator);`, passed to `getValidSelectedObjectsForPlayer`.
- Side vector member-wise: `Coord2D side;side.x=-facing.y;side.y=facing.x;`.
- Unit vector: `float unitInverse=1.0f/(float)sqrt((double)facingSq);` gives retail's `fdivr dword` + x87 multiplies.
- Loop body: `(float)it->y` evaluated before `(float)it->x`; `Coord3D pos` built x/y/0 then `+=start` (start.x lands in a register as retail).

Disproven (do not repeat): hash commutation variants and an unsigned hash; dropping COORD2D_VIEW_DTOR; non-const,
assigned or parenthesised facing init; explicit facing.x^2 in sideSq/facingSq; `normalize(unit)` (32 regions, +42 B);
`*=` unit (44); `1.0f/distance` (37); recomputed length(facing) for the inverse; `pos=start` copy (32); member-wise
start then += (29); `x+start.x` (28); y-first pos (29); a transform taking Coord2D (29); do/while preview loop (33);
`it=it+1` (no change).

Residue at 24 regions (ours 2469 B vs 2462): retail keeps facingSq in two homes (-0x30/-0x28) plus an x*x CSE at -0x38
and stores `fstp [ebp-0x20]` after the pops; hash `mov edx,ecx` register choice; matrix sine result stored late
(`fstp [ebp-0x28]` just before `movss xmm2`) where ours stores right after the call; preview-loop iterator held in esi
(`mov esi,[it]; add esi,0xc; cmp; mov [it],esi`) where ours does `add [it],0xc`; side/unit scheduling around +0x5e3;
arrows[1]->decal loads at +0x767; frame 0x74 vs 0x78.

## Round s (claude-opus-5-5, 2026-10-20): 24 -> 4 regions (ours 2459 B vs 2462)

Levers that helped:
- The facing helper `InGameUI::rva0029D9F9` (0x29D9F9) is now matched in
  `Code/GameEngine/Source/GameClient/InGameUIFormationFinalize.cpp`. With its real body in the same TU as
  this function (instead of an opaque declaration), the facing copy, its squared length and the
  angle temp keep retail's homes: in-TU mod/ref lets `facing` stay non-escaped.
- The WB twin's MathCoord2D inlines spelled as members of a TU-local `struct C2 : Coord2D` view
  (`GetLengthSqrd` = `sqr(y)+x*x`, `GetLength` with `<math.h>` sqrt, `Normalize` via `inv=1.0f/len`,
  `Scale`, `Add`, `Set`), with `C2R(v)`/`C2C(v)` casts at every WB member call site, unit and side included.
- `ObjectID` enum for `IdNode::id` and `Placement32::object` gives the ledger's real
  `findObjectByID(ObjectID)` mangling (no codegen change).

Remaining residue (both register/slot tie-breaks, all calls and relocations agree):
1. Hash: retail `mov edx,ecx; xor edx,eax; push ecx; mov ecx,[TheGameLogic]; mov edi,edx`, ours
   `xor eax,ecx; ...; mov edi,eax`.
2. Transform-loop iterator: retail homes it in [ebp-0x20] (packed with the dead `angle+pi/2` Matrix3D
   temp), enters with `mov esi,eax` and increments in a register at the latch
   (`mov esi,[ebp-0x20]; add esi,0xc; cmp esi,[ebx+0x5a4]; mov [ebp-0x20],esi`). Ours homes it in
   [ebp-0x14], reloads `mov esi,[ebp-0x14]` at the top and does `add [ebp-0x14],0xc; mov eax,..; cmp eax`.

Disproven this round (do not repeat): ObjectID-typed hash with three hash spellings (n52-n54);
a named `rot` local for the Matrix3D angle (n55); the iterator declared before the matrix (n56);
a while loop with `++it` at the end (n57). The hash forms of rounds n18-n27 and n39-n50 (commutation,
association, temps, a hashStep helper, unsigned/int types, the shift split) were all inert at st=4.

Bank: `reverse/attempts/0x002a4e1f.cpp` = `build/fp/n52.cpp`. Landing needs a home TU where the
0x29D9F9 body is visible (InGameUIFormationFinalize.cpp, or move both to the destination unit);
`tools/repair_queue.py dest 0x2A4E1F` proposes InGameUISuperweapons.cpp / InGameUI.cpp.

## Round t (claude-opus-5-5, 2026-10-20): landed exact

The body landed in `Code/GameEngine/Source/GameClient/InGameUIUpdateFormationPreview.cpp` (2462 B, 0 structural regions, 0 register differences; the 36 memory lines are absolute operands the gate fills). The bank was deleted by `add_match.py`.

Two levers closed the round-s residue:

- Transform-loop iterator. No priority tie: 1 to 16 extra uses never enregistered it, and chains of 20 to 180 copied locals at four positions changed nothing. Large diagnostic cuts (the fading alpha computation, or the arrows[1] block plus the tip) did enregister it with retail's `[ebp-0x20]` home. WB 0x00DC1CD8 opens EH state 4 around the loop position and states 5 to 7 for unit, side and tip, so the original Coord3D is retail's class with user constructors and the empty user destructor. Including `Lib/Coord3DCtorView.h` with `COORD3D_VIEW_DTOR` and building the four arrow positions with the three-float constructor gives retail's iterator in esi with its `[ebp-0x20]` spill home. Keep the loop position member-wise; the constructor form there swaps xmm0 and xmm2 in the transform.
- Hash. Retail's `mov edx,ecx; xor edx,eax` needs the rotation assigned to a local before the id: `unsigned hi=hash&0xF8000000; unsigned rot=(hash<<5)^(hi>>27); ObjectID id=it->id; hash=rot^id;`. The operand assigned later (id) becomes the copied destination. `id^rot` gives the same bytes; folding `hi` into `rot` does not.

`_STL::min(1.0f,alpha)` replaces the bank's `one`/`clamped` pair at identical bytes and matches WB's reference-returning min. The unit keeps its own `__declspec(noinline) inline` copy of 0x0029D9F9 (callee visibility, round s); its home `InGameUIFormationFinalize.cpp` now defines the helper the same way, and both still match. Coord2D::toAngle and length are inline in coord2d.cpp already. Trial sources and logs are in the seat's `build/w3_2a4e1f/`.
