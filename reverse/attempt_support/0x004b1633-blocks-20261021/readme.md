# EmotionTrackerUpdate::update 0x4B1633: the residue is a c2 pool-block count (2026-10-21)

Session: claude-opus-5-5, about 150 min. The bank `reverse/attempts/0x004b1633.cpp`
is unchanged (2194/2200 B; the only defect is the case-3 compare call order at +0x572).
This replaces the earlier meter explanations (period 32, threshold) with the c2
mechanism. Tools: `meter.py.txt`, `odemo.py.txt`. Scratch: `build/emo/`.

## Mechanism (validated in the running compiler)

The critical symbol is the A symbol c2 takes just before the second `status6`
inline. It is re-used as the inlined `getObject()` result temp at
`getObject()->rva0028B511()==other->rva0028B511()` (bank line 342). The body is
byte-exact when that symbol's number X lands in a later 32-number pool block:

* symshift on the bank (fidx 46): `A:+30..+36@0` gives bytediff 0. `A:+29..+31@935`
  also works, while `+28` and below keep the bank shape. The insertion must come
  before event 935, the take of that symbol.
* Exact exactly when X is in 927..934 in these runs. Base X=898 (block 896);
  `A:+37@0` gives X=935 and a 2206 B shape. With C padding (below), X=962 is also exact.
* X = 32 × (pool blocks allocated before its A block) + offset. In this function the
  blocks are A0, B, C, D, then C blocks every ~33 events, A block 2 during IL
  reading, more C blocks, and A block 3 during inlining (k870 to k930). The critical
  symbol is the 67th fresh A (offset 2 in block 3).
* With the debug colours as literals (WB pushes `0xff0000ff` and others, so the inline
  `GameMakeColor` in the bank is not faithful), X=866 (block 864). That needs one
  more block than the bank (`A:+62@0` exact).

**Proof that position does not matter for C temps.** The IL-read phase allocates a
fresh C temp for almost every expression temp (about 700 here, about 6 recycled; most are
pointer/address temps, plus about 95 labels). It runs over the whole function before
inlining starts. Adding 66..100 dead `obj->getPosition();` statements at the END of
the function (after the compare) makes the literal-colour body byte-exact (bytediff 0,
`build/emo/cal/tail_gp66.cpp`; 60 is one short). This is diagnostic padding and is
not landable. It does show the real requirement: **the original compile has roughly
64 to 100 more fresh symbols (A or C) than the literal-colour bank before A block 3
is taken.** Equivalently, it has one more pool block (one or two relative to the
`GameMakeColor` bank). Fresh A symbols count the same way: 32 more A symbols put the
critical symbol in the next A block.

## WB evidence (WorldBuilder 0x1230DD0, /Od with inlining)

* WB is the same source revision except the two player-filter lines. WB's random call
  is at line 604; retail's is at 0x25E = 606.
* Our /Od build of the r48 body (`build/nbr/r48/4b1633/w3M2.cpp`) aligns with WB on
  892 of 1188 rows (`odemo.py --loose`), with frame-slot counts of 90 and 91. The remaining
  differences are WB asserts (lines 343, 464, 471), layout offsets, the getModuleData
  temp copy, `pos` copied via `*getPosition()` under EH state 0 (an empty-dtor object;
  r48 found the plain struct copy changes bytes), and `flags[2]=(bestNeutral!=0)`.
  None of these is about 64 symbols. The /Od code folds member-access address
  temps into addressing modes, so pointer temps are invisible there.
* Real helper shapes from the WB bodies:
  * `Thing::getTemplate` (assert `!m_bTemplateGuard`, Thing.h:92).
  * `BitFlags<218,KindOfType>::test`: unsigned bit compare and the
    `(w[bit>>5] & (1<<(bit&31)))!=0` expression, BitFlags.h:383. It is called as a
    cdecl `TEST_KINDOFMASK(mask, bit)`.
  * The status-6 test is an Object wrapper over an inlined `BitFlags<101>::test(6)`.
  * `testStatus` is the out-of-line 0x4E536.

## Ruled out here (meter X / bytes)

| trial | result |
| --- | --- |
| `BitFlags::test(unsigned)` one-expression | not inlined, 2213 B |
| `test(int)` one-expression | 2198 B |
| locals form with an unsigned index | 2213 B |
| status6 through `BitFlags<101>` | 2182..2213 B |
| `Thing` base class for getTemplate/getPosition | 0 change |
| 10 extra getter calls | about +1 IL temp each |
| rejected inline candidate (`findObjectByID` is never attempted) | costs nothing |
| r48 faithful layers (w3M2) | +11 fresh C only (X stays 866) |

## For the next seat

Run `meter.py` (it prints the critical X and fresh A/C counts) on each candidate.
Exact needs X in 927..934, or a whole extra block. Look for faithful sources of
about 64 symbols that leave no /Od trace:

* retained inline formals through signedness-changing or unsigned-narrowing call
  boundaries. agAR calibration: +1 fresh A per expansion for enum/int↔unsigned,
  +2 for narrowing to unsigned char/short; enum→int, int→bool and int→float are
  inert. Micro TUs: `build/agAR/lever/`.
* deeper member-access paths: nested structs or base subobjects at non-zero offsets.
