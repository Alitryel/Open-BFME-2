# queueSupplyTruck (0x4F37B0, 1537 B) — session 2026-10-22

Bank unchanged: `reverse/attempts/0x004f37b0.cpp` (0.7867). Best clean base this
session compiled to 1537 B (r=19 m=70 g=22 against retail), no gain over the bank.
Spell the KindOf mask through the real global
(`template <int N> class BitFlags; extern BitFlags<116> KINDOFMASK_NONE;`),
never the address-named `g_00DFEFA4StoragePrototype`.

## Residue (unchanged root)

- Retail keeps the base filter vftable 0xBC26E0 in esi, reloaded at the top of
  the build-list loop body (after `cmp byte [eax+0x46],0`); the loop is guarded.
  The zero literal is in ecx, local. Ours: zero in esi (it also feeds
  `cmp [ebp-0x1c],esi` after getClosestObject), vft in eax, loop unguarded
  (`jmp` to the test).
- supplySource: retail `test eax,eax; mov [ebp-0x14],eax` then `mov esi,[ebp-0x14]`
  (split range sharing the -0x14 home with desiredGatherers, the 4584D temp and
  the factory). Ours keeps it in memory at -0x1c.
- Recount loop: retail obj=esi reloading `[esi+0x258]` twice, supplyCenter=edi,
  curGatherers and the ptmf adjustor share one zero in edx. Ours CSEs
  `lea esi,[eax+0x258]` and uses `and [ebp-0x20],0` plus `xor ecx,ecx`.
- Loose loop: retail it=esi, obj=edi, supplyTruckAI in [ebp-0x1c]; ours it=edi,
  supplyTruckAI=esi, obj in memory.

## Frame (retail / ours)

| local | retail | ours |
|---|---|---|
| desiredGatherers/4584D temp/supplySource/factory | -0x14 | -0x14 (no supplySource) |
| info | -0x18 | -0x18 |
| curGatherers / supplyTruckAI | -0x1c | -0x20 |
| totalHarvesters | -0x20 | -0x28 |
| recount list iterator | -0x24 | -0x1c |
| byte local | -0x25 | -0x21 |
| radius | -0x68 | -0x50 |
| loose iterator | -0x5c | -0x60 |
| first objIter | -0x64 | -0x68 |

Everything else (teamName -0x2c, filters -0x3c/-0x70, center -0x7c, iterators
-0x94/-0xac, BitSet -0xc8, 4584D -0x108) already sits at retail's offset.

## EH

Retail FuncInfo 0xd457dc (read with `eh.py.txt 0xb92e4c`): state 0 OnMap filter
(-0x70, ICF base dtor 0x49c38a), 1 player filter (-0x3c), 2 4584D temp (-0x108),
3 static guard [0xe044d0], 4 teamName AsciiString (-0x2c). Our funclets
(`funclets.py.txt <scratch.cpp>`) have the same shape and actions: the EH table is
not the cause.

WorldBuilder twin (0x10f6160, 3853 B): state 0 is set right after the `center`
copy and held to the end of the supplyCenter block; filters are states 1-3, the
static guard 4, and an AICommandParms temp (ctor 0x351BD0, dtor 0x470447) in the
recount aiDock path is state 5. So in WB `center` or a hidden object right after
it carries a destructor, and the dock call goes through a parms temporary. WB's
base PartitionFilter has two fields (+4, +8) where retail has one. Untested leads:

1. `center` as a type with a trivial copy and a user-declared empty dtor (or an
   object constructed after the copy) — retail has no extra state, so this
   only matters if it was optimised out after shaping IL weights.
2. recount aiDock as an inline wrapper building an AICommandParms temp (retail
   calls 0x26c3ac directly with `push 0; push edi; add ecx,0x20`).
3. `throw()` factorial on the opaque callees (link, getClosestObject,
   findObjectByID, queryModule, getRelationship, checkForSupplyCenter, iterator
   ctor/advance, nameToKey): the stack-colouring lever that closed 0x95821,
   0x41D60B and 0x24797E.

## Disproved this session

Named filters with a block scope (a1-a5: guarded loop but +14..18 B, zero still
esi), do-while loop forms (g1/g2), struct-copy center (t1, 1518 B), count read
order (o1/o2), 62-variant kind-accessor scan, assignment-in-condition (z6),
EH funclet shape. Earlier sessions: see the 20261019-20261021 handoffs (KindOf
depth, ai caching, dock inline, iterator reuse, flat continue, empty virtual
dtors, getTeam accessor, ZH initialised declarations, k-scan 1..48, TU dummies,
in-TU ctors, callee stubs, permute flags).
