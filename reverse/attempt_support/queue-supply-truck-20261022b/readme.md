# queueSupplyTruck (0x4F37B0, 1537 B) — session 2026-10-22b

Bank unchanged: `reverse/attempts/0x004f37b0.cpp` (0.7867). The clean base
(the bank with the real `KINDOFMASK_NONE` global, see 20261022) compiles to
1537 B, r=19 m=70 g=22. Same residue as `../queue-supply-truck-20261022/`.
Ended early on the runner's wind-down signal.

## Findings

- **The zero register and the vft hoist come from one root.** Retail's
  build-list loop is guarded. It hoists the base filter vftable 0xBC26E0 into
  esi at the loop header and reloads `info` from [ebp-0x18]. Ours is unguarded,
  so there is no LICM. The zero literal then takes esi, which extends to
  `cmp [ebp-0x1c],esi` and puts supplySource in memory. Once the hoist appears,
  the info reload and the ecx zero follow from it.
- **Recipes that give the hoist (diagnostics only; they break elsewhere):**
  - H_head and H_1c from w5b.
  - Making the loose-loop iterator, desiredGatherers or supplyCenter
    address-taken.
- **c2 allocates by live range, not by variable.**
  - Reusing one `PlayerTeamList::const_iterator` across loops 1, recount and
    loose (R1-R3) gives bytes identical to base.
  - The a1-a5 and b1/b2 named-filter scope forms are identical to base (b1/b2)
    or shift the frame (a1).
- **Loop 1's register swap is a priority near-tie (gap of one weighted use or
  less).**
  - Retail: it=esi, team-iterator cur=edi. Ours: it=edi, cur=esi.
  - Probe P1 (base cut after loop 1, plus `m_teamDelay = totalHarvesters;`,
    213 B): one extra `g_out[1]=(int)*it;` before the team for-loop flips the
    probe to retail's picture (p1a/p1c/p1d).
  - The same edit in the full function (X1) does not flip. The full body adds
    weight elsewhere, so the tie is not local to loop 1.
- **Loose loop:** ours keeps a redundant `test eax,eax; je` after the obj load.
  Retail folds it. This is the same priority mechanism (it/obj against
  supplyTruckAI).

## Disproved this session (do not repeat)

- **Compiler flags:** removing /Ob1, removing /Oy-, /Ob2, /EHsc, /Gy, /Oi, /Op,
  /G6, /O2, /Ox.
- **Condition and assignment spellings:**
  - temporaries in the condition;
  - `== NULL`;
  - separate assignment;
  - one-line continue.
- **Inline-body changes:**
  - empty center dtor;
  - the throw() family;
  - gen13 single spellings;
  - D_curfirst;
  - F_radinline;
  - WB aiDock (AICommandParms temp + vtable[0] + dtor 0x470447): no change.
- **Scope forms:** a1-a5 and b1/b2 named-filter scope forms.
- **Iterator reuse:** R1-R3.
- **Probe families with no effect on the loop-1 swap:**
  - it++;
  - non-const getPlayerTeams / non-const iterator;
  - reversed end compare;
  - declaration in the for-init;
  - removing the team local;
  - removing the null test;
  - an if-wrapped loop;
  - the ZH DLINK spelling;
  - unconditional advance;
  - declaration orders d1-d3;
  - a k-scan of 1-8 inert Int dummies before (k1-k8) or after (j1-j8) `it`;
  - f1-f6, t1-t5, p1e, p1f.

## Next angles (untried)

- Find what in the rest of the body outweighs the probe flip. Grow P1 one region
  at a time (truckInQueue, build-list, recount, loose) with the p1c edit kept,
  and see where retail's loop-1 picture is lost. That region's weight is the
  lever.
- Loop 1 variants:
  - as a `while`;
  - with `end()` cached in a local;
  - with the list through a separate local
    (`const PlayerTeamList *teams = m_player->getPlayerTeams();`);
  - with the team iterator declared outside the for.
- `iterate_TeamInstanceList` returning through a named temporary.
- An out-of-line DLINK_ITERATOR<Team> constructor.

## Tools (untracked, build/)

- `build/q4g/zf/base.cpp`: the clean base. The function is at lines 1133-1338.
- `build/q4g/zf/shape2.py <names>`: prints the register picture. Run it from the
  repo root.
- `build/q4g/p1/`: the probe, with `dumpobj.py`.
- `build/q4f/score.sh`: scores a candidate against `build/q4f/retail.txt`.
