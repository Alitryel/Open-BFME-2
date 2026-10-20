# 0x0041D60B ActionManager::canDoSpecialPowerAtLocation — stack-home study (2026-10-20, claude-opus-5-5)

Banked body: `reverse/attempts/0x0041d60b.cpp` (clean form, no farm levers;
the farm diff-feedback body with `_ReadWriteBarrier` levers stays in git at
b1fa024ca3). Flags: `/O1 /arch:SSE /G7 /MD /GX`.

## Residue (unchanged by every trial below)

- Instructions (1035), branches, calls, switch table and the 20 EH states are
  identical. Only `[ebp-x]` homes differ: 42 of 250 refs; frame 0x2C4 vs 0x2B4;
  one healing-mask LEA needs disp32 (3712 B vs 3709 B).
- Retail packs three switch3 temporaries onto case-0x55 named locals of the same
  size: healing `alive` filter -> -0x28, healing mask -> -0x60, case 0x48
  `FILTER(0x3c)` -> -0xFC. It also overlaps the relationship local (-0x40) with
  the 0x55 castle delta and keeps `ymax` at -0x44. Retail's 0x55 `filter` does
  NOT share the 0x41/0x8c named-filter slot (-0xA0).
- Our build CAN pack a temp onto a switch2 named local (healing `alive`
  [-0x34,-0x2C) overlaps the 0x55 `delta` Coord3D), so packing is possible; the
  difference is which slot the allocator chooses (allocation order), not
  whether temps may share.
- Temp-region allocation order differs:
  masks retail 0x52,0x41,0x78,0x8c,0x63,0x55spfa,0x48 vs ours
  0x8c,0x78,0x52,healing,0x55spfa,0x41,0x48,0x63; filters retail
  0x52,healing,0x63,0x78 vs ours 0x52,0x63,0x48,healing,0x78.

## Disproven this session

- `tools/permute.py --flags 0x41D60B`: 0 of 1 closed.
- 1..24 unused int locals at function top: frame and homes unchanged.
- Toy TUs (build-local): a compiler temp never packed with a named local or
  another temp in any small variant (braces, loops, if-blocks, reference-bound
  locals, sibling named locals, extra block around switch2); an inline helper
  holding EH temps is not inlined at /O1. The packing seen in the real body
  needs its full size, so toys cannot reproduce the ordering rule.

Earlier seats (crack-e/j/w json, attempt log) covered callee visibility,
scope/lifetime, factories/types, control-flow forms, flags (/O2 /Os, /Ox, /Ob2,
/EHsc, /Z7, /Oa, /Op, EHs-c-), preceding-TU numbering and 1277 permute trials.

## Next angle

Find what orders the temp region (symbol creation order vs. weight). Try
reordering where the case-0x48/healing/0x55 temporaries are *created* in source
order relative to switch2 (e.g. move the healing block into a helper-free
earlier statement, or create the 0x55 named filter after its loop masks), and
compare the temp-region order table above rather than the mismatch count.
