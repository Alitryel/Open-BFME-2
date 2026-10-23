# ControlBar context evaluation at 0x0031D230: STLport form and the null-object exit

## Result

Blocked. `reverse/attempts/0x0031d230.cpp` stays unchanged as the bank. Symbol `?rva0031D230@ControlBar@@QAEXXZ`, retail 0x0031D230..0x0031D5F8, 968 bytes. No `Code/` source, pin or ledger row changed. Model: claude-opus-5-5.

The WorldBuilder-literal body with the real STLport `std::list<Drawable *>` is kept next to this file as `controlbar-context-31d230-20261020-stlport.cpp.txt` (it stands in for the `h3.cpp` the previous verdict cites, which is not in the tree). It is exact from the contain block to the end of the function. It is not banked, because it has fewer structural regions but more memory and register differences than the bank.

## Measurements

All with `BFME_OBJSTORE=off python tools/align_diff.py <file> ?rva0031D230@ControlBar@@QAEXXZ 0x0031D230 968`, each trial at its own path, n=1 per configuration. The memory column includes the 14 unpatched global-address operands every body shows.

| body | size | structural | memory | register |
|---|---:|---:|---:|---:|
| bank (shim list, early draw shares `drawToEvaluateFor`) | 967 | 4 | 18 | 3 |
| STLport WB-literal form (the `.cpp.txt`) | 959 | 3 | 22 | 9 |
| same, shim list instead of STLport | 967 | 4 | 20 | 3 |
| STLport form, `/Op` added | 967 | 4 | 18 | 3 (alignment identical to the bank) |
| STLport form, null-object exit without its `switchToContext(0, 0)` (behaviour-changing diagnostic) | 965 | 3 | 17 | 0 |

## What the STLport form still gets wrong

The opening swaps `this` (ESI, retail EDI) and `selectedDrawables` (EDI, retail ESI). Because `this` is no longer in a register at the null-drawable check, the null-drawable and null-object exits merge, where retail keeps two exit blocks (`mov ecx,edi` and the shared `[ebp-0x10]` tail). `selectedDrawables` also keeps a register piece from its definition through the controllable path to the second `front()`, reloaded at the join after the uncontrolled block; retail reloads it from `[ebp-0x18]` only at that `front()`.

## New findings

1. Only the first `front()` decides the state. Writing the second `front()` as a single expression inside the STLport form is inert. Writing the first one as a single expression gives the shim state (opening right, contain block wrong).
2. The opening contest is decided by the `this` use on the null-object exit. Dropping that one call gives retail's opening registers with the contain block intact (last table row); only the dropped call and the join reload remain. Dropping the null-drawable call instead leaves the opening wrong, and dropping the null-player call only reorders blocks. Adding straight-line uses of `this` (one to three) or of `selectedDrawables` does not flip the opening, so it is not a simple priority gap between the two. Passing the null `draw` or `drawToEvaluateFor` to the none-context calls, and routing the null exits through a shared `goto` label, compile identically and are inert.
3. `/Op` on the STLport form flips both contests back to the bank's exact alignment, so both contests react to IL far away in the body (the float compare).
4. The brief's visible-callee lever does not apply. `amount` is the only address-taken local, and a visible copy of 0x0028C15E still hands its address to the opaque 0x00403448. Replacing `&amount` by a global's address (diagnostic) changes neither wall.

## Hypotheses ruled out (identical output or no gain)

- Visible `__declspec(noinline) inline` copies of 0x0028C15E and of `InGameUI::areSelectedObjectsControllable` (0x0029C752), on both the bank and the STLport form.
- Inline accessors as the WB shows them (`getObject`, `getContain`, `getLocalPlayer`, `getTeam`); non-const list (its iterator has a user-written copy constructor); bool-returning purchase-science getter; `empty() == 1` and bare `empty()`; dropping the WB's redundant `contain &&`; routing the null exits through a shared `goto` label; `else if` chains after the early returns (null object then beacon, empty list then controllable check), which the WB cannot tell apart and which compile identically.
- Compilers `vc71-sp1` and `vc71-ddk-4035`; `/O2` and `/O1 /Ot` (34 to 36 regions); `/EHa` (worse); `/EHs`, `/GX` (inert).
- `tools/permute.py` from the STLport form (1629 trials) reached only the behaviour-changing null-object variant plus `/Oy- /Op`. A restricted hill-climb with only behaviour-preserving mutations (comparison, negation, width, if/else, temporary and compound) over three seeds, about five minutes each, never improved on the start.

## Next step

Look for a semantics-preserving change that lowers the weight of `this` on the uncontrolled path (the direction of finding 2) and removes the `selectedDrawables` register piece across the controllable path. The shim world and its contain-block contest are exhausted by earlier attempts.
