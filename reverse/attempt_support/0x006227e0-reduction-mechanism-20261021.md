# 0x006227E0 Q1Receiver0134FAAC::refresh: closed by reference declaration order (2026-10-21)

Exact at 3244 B (frame 0xBC, EH graph exact). The landed source is
`Code/Libraries/Source/assetmanager/AssetManagerImplRefresh.cpp`. It follows
`0x006227e0-licm-hoisted-s0-20261020.md` and `0x006227e0-per-arm-addressing-20261020.md`.

## Mechanism
- c2 flattens each `a.size() + b.size() + c.size()` into a list of terms, which
  FactCanonSort (c2_l.dll RVA 0x5CD11) orders by key. Larger keys sort first.
- With A as the finish-side temp or symbol number and B as the start-side one
  (all mod 65536):
  - node term `n = 32A + 64B + 0x15A`
  - start term `s = 32B + ((B&3)<<14) + 0xD6`
  - finish term `f = ((A&7)<<13) + 64A + 0xFC`
- A term whose two arms reduce to the same B symbol gets a high half of
  0x106 or 0x105, so it always sorts last.
- Retail needs these orders:
  - n2, n1, n0 in both arms;
  - f1 first in both arms (it head-merges with the n-sum before `test ebp`), then
    arm0 f2, f0 and arm1 f0, f2;
  - s2, s0, s1 in both arms.
- Local symbols are numbered in declaration order. The tracer
  (scratch, run under the debug API at 0x5CD11) showed r1=353, r0=354 and r2=355
  for the landed order. Arm1's fresh temps are created as A0, B1, A1, B2, A2.
  B0 is LICM-hoisted (1103).
- Declaring `r1` before `r0` is the one lever that moves n1 above n0 without
  breaking the s order. No addend permutation or term spelling reaches that.

## Landed tail
```cpp
Q1ReceiverQueue *queues = m_deques78;
Q1ReceiverQueue &r1 = m_deques78[1];
Q1ReceiverQueue &r0 = m_deques78[0];
Q1ReceiverQueue &r2 = m_deques78[2];
...
if (pass == 0)
    m_field1e0 = r0.size() + r1.size() + queues[2].size();
else
    m_field1e4 = r0.size() + r1.size() + r2.size() - m_field1e0;
```

## Grid (declaration order × arm0 addressing × arm1 addressing)
- Spellings:
  - `r` is a reference, `m` is `m_deques78[k]` and `p` is `queues[k]`.
  - The order spec `102` means r1, r0, r2.
- Configurations that came out exact with order 102:
  - arm0 `rrm` with arm1 `rrm`, `rrp` or `rrr`;
  - arm0 `rrp` with arm1 `rrm`, `rrp` or `rrr`.
- The landed one is `102_rrp_rrr`, where every declared local is used.
- Removing the unused `queues` or `r2` declaration renumbers the symbols and
  breaks the match.
- Disproven earlier in this pass:
  - addend permutations, both the same in both arms and different per arm;
  - `end() - begin()` spellings;
  - const casts;
  - arm1 local references or pointers under the old 012 order;
  - uniform arm1 shifts (key model).

## Flags
- The region default (`/G7`) loses the row. The unit keeps its own
  `/O2 /G6 /arch:SSE`, like its siblings `AssetManagerImplUpdate.cpp` and
  `Q1ReceiverDrain.cpp`.
- `flag_defaults.py propose` recorded the override.
