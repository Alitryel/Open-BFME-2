# queueSupplyTruck (0x4F37B0, 1537 B), fourth session of 2026-10-23

There is no exact recovery. The bank `reverse/attempts/0x004f37b0.cpp` (official
score 0.7867) is unchanged, because no real-source body beat it. The session
ended on the runner's wind-down signal.
Model: claude-opus-5-5. Tree: bb6a52e5d9.

## Base

`cb-from-bank.patch` turns the bank into the clean base `cb.cpp`. The patch uses:

- the real `aiDock` name;
- the `KINDOFMASK_NONE` global;
- `_ReadWriteBarrier()` before `if (!obj->getAI()) continue;` in the loose loop.

The base compiles to 1537 B, with r=19 m=70 g=22 and score 0.7533 under
`objscore.sh`. That scorer is not the official one. All line numbers below refer
to `cb.cpp`, where the function starts at line 1130.

## New finding: the head defects are one chaotic c2 decision

Retail's head is the following sequence:

- +0xe1: `test eax,eax; mov [ebp-0x18],eax; je +0x5f2`. This guard, G, is
  absent in the base.
- +0xec: `cmp byte[eax+0x46],0; mov esi,0xbc26e0`. The vftable web is hoisted
  into esi inside the loop top; call this V.
- +0x10a: `mov eax,[ebp-0x18]`, a reload with no jump target. The base emits
  `jmp +0x5cb` instead.
- The supplySource `test eax,eax`.
- The loop-1 shape.

All of these appear together, at 1562 B and 0.8289, when **one extra integer
global load with a use** sits at certain positions. Examples:

- `if (g_x1) g_x2=1;`
- `g_x2=g_x1;`
- `volatile int v=g_x1;`
- `if (TheGameLogic==0) continue;`
- `if (ThePartitionManager==0) continue;`
- `if (TheWritableGlobalData==0) continue;`

The extra load works even as dead code after a `continue`. So it acts in an
early phase (IL or symbol numbering, block formation), not in the emitted code
path. `diagnostic-dummy.patch` is the strongest such probe (+0x1257). It is
**diagnostic only, not bankable**: the dummy globals have no retail counterpart.

### Positions, from the geny position scan

The dummy was inserted after each source line in turn.

**Works:**

- the top of the outer build-list body (before line 1179), and after lines 1180
  and 1181;
- after line 1249, at the end of `if (supplyCenter)`;
- after line 1253, the start of the else arm;
- after line 1256, the loose `Team *team = iter.cur();`;
- after lines 1286 and 1287, after the loose loops;
- inside `if (totalHarvesters >= desiredGatherers*3)`, before `continue`;
- after line 1333, the restore.

**Fails:**

- before the build-list loop;
- anywhere from the then-arm top through the recount loop;
- after line 1250;
- inside the object loops;
- in the factory part;
- after the if/else join.

### Inert forms (no change from the base)

- dummy stores only, calls only, stack-local loads and member loads (except an
  `m_player` read at line 1179);
- zero-code forms (`genz`): `if (g_x1) {}`, `{int z=0; if (g_x1) z=1;}`,
  `if (!info) continue;`, an extra `_ReadWriteBarrier()`, and similar;
- `availableCash` spellings (`genv`);
- the radius read through the literal's data alias:
  `extern [const] float g_bfmePropagandaRadius`, which is 0xBCE190
  `__real@43480000`. All five forms are byte-identical to the base.

### gen11 and gen12

`gen11`, an 18-factor IR-changing factorial, is in `../queue-supply-truck-20261023c`.
It has the letters a-k plus more: control-flow, temporary, test and arm-inversion
choices. No variant beat the base.

`gen12` crossed the gen11 factors with dummy L (after line 1256) and dummy M
(`g_x2=g_x1;` before `if (totalHarvesters`), giving 400 variants:

| Variant | Size | r | m | g | Score |
| --- | ---: | ---: | ---: | ---: | ---: |
| L_0 / L_A | 1562 / 1556 | 12 | 50 | 15 | 0.8289 |
| M_0 / M_A | | | | | 0.8267 |

No factor fixed the remaining loop register roles on top of the rescue.

## Residue left once the head is rescued

**Recount loop.**

- Retail:
  - `xor edx,edx; mov [ebp-0x1c],edx` for `curGatherers = 0`, with edx reused
    for the adjustor store `[ebp-0x40]`;
  - `it` lives in memory at [ebp-0x24], with ecx at +0x282 and +0x339;
  - obj is in esi from the latch (`mov esi,[ebp-0x94]`), then
    `mov ecx,[esi+0x258]` at +0x2d4 and +0x308;
  - supplyCenter is in edi.
- Ours: no zero sharing, obj is not in esi, and the `&obj->m_ai` address is CSE'd.

**Loose loop.**

- Retail:
  - the team test is `cmp [ebp-0x5c],0; je +0x44f`, then `mov ecx,[ebp-0x5c]`;
  - obj is in edi from the latch (`mov edi,[ebp-0xac]; test edi,edi; jne +0x3b3`);
  - supplyTruckAI is at [ebp-0x1c];
  - the tail at +0x5e1 is `mov ecx,[edi+0x258]`.
- Ours: obj is not in edi.

## Leads for the next session (untested)

1. Find a **real** construct at one of the working positions that reads an
   integer global and uses it. Plausible candidates:
   - a DEBUG_LOG or assert-like construct whose release build still reads a
     global;
   - a TheGlobalData or TheAI accessor;
   - `m_player` state reached through a global, at the loose team line or the
     else-arm top.

   ZH has `DEBUG_LOG(("Re-attaching supply truck to supply center.\n"))` before
   the loose `return`.
2. Loose team test spellings: `if (!iter.cur()) continue;` with no team local,
   or `== NULL`. Retail reads the team from memory, `cmp [ebp-0x5c],0`.
3. ZH-style named filter locals (f1, f2, filterMapStatus) with explicit link
   calls.
4. A real MI layout for AIUpdateInterface, calling `obj->getAI()->aiDock(...)`
   directly.
5. A WB-shaped KindOf helper. The WB twin at 0xCF6160 calls cdecl 0x40779d,
   then 0x4d0390 `f(&kindof, bit)`, with the assert `bit < 0xda`.

## Tools

Copy each file to `build/` without its `.txt` suffix. The scripts contain the
paths this session used (`build/q8`, `build/q9`, `build/qAf`, `build/qAj`), so
fix those paths or recreate the directories.

- `probe.py`: compiles one `.cpp` into a sibling `.obj`. Run it as
  `xargs -P 24 -n 1 python3 probe.py`.
- `objscore.sh OBJ` (`KEEP=1` writes `.align`) and `reps.sh DIR`: group the
  objects by function hash, score them, and print the G and V flags.
- `odis.py` and `rdis.py`: disassemble our object and retail.
- `gen11`, `gen12`, `gens`, `geny`, `genz`, `genv`: the family generators used
  above.
