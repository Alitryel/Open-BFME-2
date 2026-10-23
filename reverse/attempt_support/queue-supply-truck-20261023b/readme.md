# queueSupplyTruck (0x4F37B0, 1537 B), second session of 2026-10-23

The bank is unchanged: `reverse/attempts/0x004f37b0.cpp`, official score 0.7867.
That score is one minus (unmatched retail instructions + memory + register) over
450, from `BFME_OBJSTORE=off tools/align_diff.py`. The clean base is the bank with
the real `KINDOFMASK_NONE` global (see `../queue-supply-truck-20261022/`). It
compiles to 1537 B with r=19 m=70 g=22. This session also ended on the runner's
wind-down signal. Model: claude-opus-5-5.

## Feature legend (retail `GHZT-`, base `----L`)

- **G**: the build-list loop is guarded at its entry. Retail has
  `mov eax,[ebx+0xc]; mov eax,[eax+0x278]; test eax,eax; mov [ebp-0x18],eax; je 0x5f2`.
  Base has `jmp 0x5cb` into the latch's shared test.
- **H**: retail runs `mov esi,0xbc26e0` in the loop header at +0xf0 on every
  iteration. A reload `mov eax,[ebp-0x18]` follows at +0x10a. The three filter
  vft stores at +0x1e7..0x1f0 then come from esi.
- **Z**: the centre loop keeps zero in ecx in retail and in esi in base.
- **T**: retail has `test eax,eax` after `getClosestObject`. Base stores the result
  and compares it through memory.
- **L**: base only, `lea esi,[eax+0x258]`; retail reads the field through
  `obj` in esi.

## Allocation table (retail / base)

| item | retail | base |
|---|---|---|
| loop-1 `it` / cur | esi / edi | edi / esi |
| totalHarvesters | -0x20 | -0x28 |
| objIter1 | -0x64 | -0x68 |
| radius | -0x68 | -0x50 |
| supplySource | -0x14, then esi | -0x1c |
| centre-loop `it` | -0x24 | esi (spill -0x1c) |
| centre-loop curGatherers | -0x1c | -0x20 |
| centre-loop obj | esi | eax + L |
| loose `it` | esi | edi |
| loose obj | edi, null test merged into the loop test | [ebp-0x20], redundant test |
| loose sta | -0x1c | esi |
| loose team | -0x5c | -0x60 |
| isSupplyTruck | -0x25 | -0x21 |
| desiredGatherers at the imul | reloaded into eax | ecx |

## EH finding (retail FuncInfo 0xD457DC)

Retail has 5 unwind states:
- 0 → -1, 1 → 0 and 2 → 1 are the filter dtors at -0x70, -0x3c and -0x108;
- 3 → -1 is the static guard 0xE044D0;
- 4 → -1 is the AsciiString at -0x2c.

There are no new-expression cleanup states. The WorldBuilder twin has two
(`local_4` = 6 and 7), so retail's `WorkOrder`/`TeamInQueue` constructors cannot
throw. The base gets this from `WorkOrder() throw()` and `TeamInQueue() throw()`.
In-TU constructor bodies without `throw()` give identical code. Do not spend
trials on allocation EH.

## Tried this session (none beat the bank)

- `d1`: a duplicated restore `setCanBuildUnits(canBuildUnits)` before the
  factory `break`. Identical to base.
- `d4`: the restore behind a goto label. Identical to base.
- `d5` (`d5.patch` against base): `for(;;)` with
  `if (!tTemplate) { restore; break; }`, no restore after the loop, and none on
  the factory path.
  - This is NOT behaviour-equivalent: the factory path skips the restore.
  - It gives G only (1554 B, no H). Its official score is 0.7867, a tie with the
    bank.
  - It confirms the 20261023 finding: removing the block between the tTemplate
    loop and the build-list latch flips G. Retail still restores on both paths,
    though.
- WB getAI double-temporary: WB stores `obj` and then `obj->m_ai` into a second
  frame temporary before the `+0x17c` virtual call. That is an unoptimised-build
  artefact. It was read, but no variant was compiled before wind-down.

## Disproved (cumulative; do not repeat)

- **Flags and placement:** all flag variants, including `/Zi`, `/Z7` and `/Zd`;
  the home TU and same-TU stubs; in-TU ctors without `throw()`.
- **Factorials:** the A-Q factorial; the `throw()` factorial on opaque callees;
  the 62 inline KindOf variants.
- **canBuildUnits:** v1-v11, const `Bool&`, volatile; restore replacements x1
  and z1-z5; the d1 and d4 restore shapes.
- **Inert locals:** the k-scan over 113 positions.
- **Single changes and loop 1:** natural singles (q6g); loop-1 probes.
- **Build-list and template loops:**
  - do-while build list (guarded, 1556 B);
  - the tTemplate loop wrapped in an if, or written as a for;
  - explicit continue edges (G, 1562 B).
- **Filters and centre:**
  - named filter scopes (a1-a5, b1/b2);
  - empty derived virtual dtors (u1/u2);
  - struct-copy centre (t1).
- **Iterators:** reuse (R1-R3); ZH initialised declarations; count read order.
- **Other:**
  - the WB aiDock `AICommandParms` spelling;
  - the raw list walk;
  - q9a, q9b and q9c probes;
  - F1-F3; F8 (G at 1551 B).

## Untried (next session, factorially)

- A tTemplate loop exit with one restore that keeps behaviour and stays at 1537 B.
  For example `for(;;){ if(!tTemplate) break; ... }` with the restore after the
  loop, crossed with a `goto` to a label just before the latch.
- Loop 1 written as a `while`.
- The team iterator declared outside its `for`.
- `iterate_TeamInstanceList` through a named temporary.
- sta/obj declaration order in the loose loop.
- `ObjectID` as an enum instead of an Int typedef.
- newInstance-style allocation, or class `operator new`/`delete` for
  `WorkOrder`/`TeamInQueue`.
- The getAI double temporary as a real local:
  `AIUpdateInterface *ai = obj->getAI();` with a separate `if (ai)`.
- Theory for all of the above: the priority race of the 0xBC26E0 web against the
  zero literal, the loose `it`, desiredGatherers and supplyCenter (see
  `../queue-supply-truck-20261020-w5b/`). Any shape that removes one basic block
  before the build-list latch, while keeping the same instructions, is the target.
