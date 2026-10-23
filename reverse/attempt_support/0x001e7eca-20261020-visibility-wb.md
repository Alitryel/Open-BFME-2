# 0x001E7ECA: callee visibility and WorldBuilder structure, blocked

Result: blocked. The bank `reverse/attempts/0x001e7eca.cpp` is unchanged and remains the best body. No Code source, pin or ledger row was changed. Model: claude-opus-5-5. Symbol `?rva001E7ECA@Locomotor@@QAE_NPAVObject@@PBUCoord3D@@@Z`, extent 1563 bytes (1527 code plus the 36-byte nine-entry jump table).

## Measurement

`tools/align_diff.py` on the bank, BFME_OBJSTORE=off: ours 1567 B against retail 1563 B, 6 structural regions (five real ones plus the jump-table tail, which is noise), 27 memory and 4 register differences. Every trial below either compiled the target symbol byte-identical to the bank (checked by comparing the raw symbol bytes, not only the counts) or measured worse. The five real regions are the known zero-constant web: case 1 (retail +0x18F, +0x1C3, +0x1CC: ours puts 0 in EDI for the two underwater zeros and the layer normal NULL, then spills the TerrainLogic vptr to [ebp+0xC]) and case 6 (retail +0x28A and +0x2AC: ours starts the EDI zero web at the ground normal NULL, retail at the KindOf mask push).

## New evidence: the WorldBuilder body

`python tools/wb_show.py 0x001E7ECA` pairs the target with WorldBuilder 0xAEB870 (4953 B, debug build, call-graph match score 3.0). Its body is a structural lead, not byte proof, and it is a different source revision: WB's case 8 calls Object::setNextPosition twice, where retail calls 0x001E5F1D. Facts it supplies about the original source:

- Case 1 tests `obj->isDisabledByType(DISABLED_HELD)` (a BitFlags<11> test; retail inlines it as `test byte [esi+0x1C8], 8`) and `obj->getTemplate()->isKindOf(0xBB)` (template KindOf mask at +0x108; the bank's `flags11f & 8` is that bit). The speed it scales is read through a Locomotor float getter at +0x40 (WB 0xADE380).
- The matrix translation store is a Locomotor member taking `const Coord3D *` (WB 0xAF0D30, inlined in retail), and the final future-position write is Object::setNextPosition (WB 0xAE3CF0, inlined in retail).
- Case 6 keeps a named range local of 1.0f and passes the address of a temporary KindOf filter whose base vptr is reset right after the range query, as the bank does. Its loop is a single `next()` test per iteration, as in the bank.
- Case 7's normal, the future position and the current position are separate locals in WB; retail packs normal and future into one stack slot, which the bank reproduces with a union.
- WB's Coord3D locals carry EH states and an initializer read from a global; retail shows neither, so both are absent from or inert in retail's build.

## Hypotheses tested (all refuted)

1. Callee visibility (the AptLoad / 0x00307EDC lever). `__declspec(noinline) inline` copies (semantically faithful to the rowed homes; their own bytes were not re-verified) in the trial unit of the same-unit Locomotor helpers 0x001E41D3 (with the home's user-written ctor and copy ctor), 0x001E434A, 0x001E40D9 and getMaxSpeed 0x001E46E1, and of the case 6 header pieces BfmeWideResult::next 0x00045623, ~BfmeWideResult 0x0004AA28, the KindOf mask ctor 0x00045411 and the filter ctor 0x0004584D: each alone and all together compile the target byte-identical to the bank.
2. Case 6 structure: a nested block around the query and loop, a named `range` local, a `while (Object *e = next())` condition declaration, `for(;;)` with break: identical. Declaring the result in a for-init moves its destructor ahead of the translation store (semantically wrong, 1534 B) and leaves the zero web as it was.
3. Case 1 structure: `water` declared before the disabled test, and the case body under `if (!disabled)` instead of `break`: identical. WorldBuilder-style inline BitFlags tests and a speed getter: worse (bit tests no longer narrow to byte tests), zero web unchanged.
4. Return and receiver types: ground and layer returning double, a polymorphic TerrainLogic declaring the virtuals itself (no view cast), and a Snapshot plus SubsystemInterface multiple-inheritance TerrainLogic with ZH's slot order (ground at slot 6, layer at 7, underwater at 19): identical.
5. Empty user destructor on the position type (with and without user ctor/copy ctor): identical; cl drops the EH states for it.
6. Exception specifications: `throw()` on the three terrain virtuals: identical; `throw()` on the direct callees only removes EH state stores, zero web unchanged. /G6 instead of /G7: identical.
7. Function-wide zero count: removing zeros elsewhere (mode reset, markAsDetected arguments) or adding three or six volatile zero stores in case 8 leaves the case 1 and case 6 webs unchanged, so the web decision is local to each case.

## What remains

Retail never carries a zero register across a TerrainLogic virtual call (underwater at retail +0x1A3, ground at +0x29C), while in case 6 it does carry one across the direct calls (mask ctor, filter ctor, range query, next, getMaxHeightAbovePosition). Ours carries it across both kinds. The W9-O2 value probes (prior verdict, not re-run here) say: replacing either normal NULL with a non-zero value makes that case retail-exact, so the residue is exactly which zeros join the web. Not tested here: visibility of 0x001E5F1D and 0x001E6532, whose calls lie outside the affected cases.

A byte scan of the 26,319 matched rows of at least 60 bytes outside generated sources found 22 bodies that both push a callee-saved zero register and pass a literal NULL to a TerrainLogic virtual call (slots 0x18, 0x1C, 0x4C). The two inspected, Pathfinder::AdjustHordeMeleeDestination 0x002FA202 and AIGiantBirdSwoopState 0x0036C438, separate the NULL from their zero web by a call or a branch, so neither is a same-block analog of case 6. The script is `build/w4_1e7eca/scan_terrain_zero.py` in the seat; the other 20 hits are unread.

## Scratch

Trial sources, align logs, the full WorldBuilder listing (`wb_show_full.log`) and the hypothesis note are in the seat checkout's untracked `build/w4_1e7eca/`.
