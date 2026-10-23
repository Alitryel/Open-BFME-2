# FoundationAIUpdate::construct 0x0045569D: retail's allocation needs the cost block outside the copy guard

Result: partial. The bank `reverse/attempts/0x0045569d.cpp` is unchanged and still the best semantically correct body (1175 B, 3 structural regions, 31 memory lines, 6 register lines). Model: claude-opus-5-5. Scorer: `tools/align_diff.py`. Exact means 1174 B, 0 regions, 21 memory lines, all of them relocations. This round did not repeat the 119 compiles in `foundation-construct-context-20261020.md`.

## Residue (bank)

- Retail loads `this` from `[ebp-0x10]` into EDI once, at +0x345 (the `onStructureCreated(getObject(), obj)` argument). It keeps EDI through the isRebuild block, both `findModule` calls (+0x3c5 `mov ecx,[edi-0x18]`) and the cost call. oldMember goes to EBX, and owningPlayer is reloaded into EBX at +0x3fa.
- Ours loads `this` into EAX at +0x345. It reloads it into EBX at +0x3bf (+3 B), gives oldMember EDI, and reloads `what` at +0x3f2 instead of owningPlayer.
- Retail's CFG is the bank's CFG. The residue is one choice: whether the +0x345 `this` load joins the later `this` web.

## Diagnostics (all semantically wrong; they locate the lever, not to land)

| Variant | Change from bank | Score |
|---|---|---|
| d3 | `if (!isRebuild) {cost}` moved out of the `newMember && oldMember` block | 1174 B, 2 regions, mem 21, reg 0 (retail allocation; CFG differs) |
| pbest (permuter best, 0.9973) | castle copy under `!isRebuild`, cost unconditional | 1174/2/21/0 |
| d1, m2a, m3e, m3g | cost under `!isRebuild && newMember && oldMember` as a separate block, in several spellings | 1178-1182 B, 3 regions, reg 0 (retail allocation, duplicated tests) |
| w4 | oldMember looked up through `obj` instead of `getObject()` | 1173 B, 0 regions, mem 21, reg 1 |
| v5 | volatile read of owningPlayer at the cost call | 1177 B, 1 region, reg 5 (owningPlayer CSE is a secondary coupling) |

So retail's allocation appears whenever:
- the `getObject()` use at the oldMember lookup is removed (w4); or
- the cost block is not an `if (!isRebuild)` nested directly inside the copy block.

Every CFG-equivalent spelling threads back to the bank's CFG and gets the bank's allocation.

## Ruled out this round (all 1175/3/31/6 unless noted)

- **Control flow** (about 40 forms):
  - m4a and m4b: duplicated copy arms, merged back by jump threading;
  - q1-q9: `while (!isRebuild) {...; break;}`, empty `if (isRebuild) ;` arms, switch and flag dispatch;
  - j4-j9: `oldMember && !isRebuild` guards and split castle copies;
  - s1-s4 and r1-r2: union views and empty blocks;
  - the else-if chain from `docs/recipes.md`.
- **Lifetime:**
  - w5: `self` cached at onStructureCreated (1170 B, 4 regions);
  - t1-t9: stats and player locals;
  - n1-n9: hoisted cost and builder locals;
  - w1 (`(Int)obj` cost argument, 1172 B, 4 regions) and w8 (`m_object->findModule`), with separate scopes for newMember, oldMember and cost;
  - se1-se3: split obj declaration (1177 B, 10 regions);
  - an Int cost.
- **Types and layout:** a struct-pair copy of keepID/castleID.
- **Callee visibility:**
  - h3: static inline copyMember, inert;
  - h1: `__forceinline` chargeBuild, emitted as a call (1113 B, 6 regions).
- **Flags:** f00-f15 add `/Oy-`, `/Op`, `/Ob2`, `/Ob1`, `/Ob0`, `/Ow`, `/Oa`, `/G6`, `/Gy`, `/GF`, `/Ot`, `/GR`, `/Og-`, `/arch:SSE2`, `/Zp4` or `/Ze` to the stock flags. f90-f93 try `/O2`, `/O1 /G6` without SSE, `/Oi` and `/EHsc` instead of `/GX`. None gained.
- **Numbering:** k-scan of top locals and new calls (`build/s45/kscan.py`); inert at 1175/3/31/6.
- **Permuter:** 30 min, seeded with fixed includes, best 0.9973 (= pbest, semantically wrong).

## Next angle for a closer

Find a natural reason for the oldMember lookup not to share the `this` web, while the copy and cost stay nested as in WB 0x11715D0 (lines 373-383):
- a module accessor that does not read `getObject()` inline (but retail does read `[edi-0x18]` inline);
- a different path to the object that c2 treats as a separate expression.

WB keeps the bank's nesting, so the lever is probably in a declaration, not the CFG.
