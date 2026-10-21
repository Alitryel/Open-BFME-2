# HordeMeleeAmoeba::updateMeleeAttack 0x005881DB (2199 B): c2 allocator trace, 2026-10-21

Result (two passes): the bank is unchanged: `reverse/attempts/0x005881db.cpp` emits 2196 B, scores 0.9772 and has one structural region left, residue (A) in the w6 note. Model claude-opus-5-5. No change to `Code/`, the ledger or pins.

This pass ran MSVC 7.1 `c2.dll` (base 0x10700000) under winedbg and traced the register allocator on the bank. It found the exact allocator decision retail took differently and proved that decision is sufficient. The source shape that produces the decision is still open.

## Key proof: node alone, split per reference, is exact

The allocator runs in rounds; a round is counted by entries to 0x82978. In some rounds the loop-1 list node fails coloring, and it is always split together with other failed records through `a8f54`'s complex group path (`ae60f`). That path places split markers per block group.

`inj.py` removes node's bit from the a8f54 split set and injects a per-reference split, `a9634(rec, arg3)`, which is what the simple path does for each record. The result is **EXACT 2199 B** in either of two rounds:

- `inj.py bank.cpp inj_r2.obj 2:node`: node is idx 0xb at round 2, score `2199 0 exact`.
- `inj.py bank.cpp inj_r4.obj 4:node`: node is idx 0x77 at round 4, score `2199 0 exact`.

Equivalent forcings reach the same exact body: node spilled at round 3 or round 5, each combined with lowering node's frame-slot weight by 2 (`slotmove2.py`, `node@3` / `node@5` with `dec=node:2`). The frame weight matters on its own:

| Weight decrease | Result |
|---|---|
| 1 | nd8 |
| 2 | exact |
| 3 | nd43 |

Retail's node therefore ended with frame weight 4: in the bank it is 5, index is 4 and count is 4. Retail split node per reference: every node load and store is a separate split, which is retail's `mov eax,[ebp+0x60]` at the loop head and at the latch. All the other failed records were group-split as in the bank.

## Corrected c2 allocator pipeline (per round)

1. `82473`: reference count, cost and priority for each record.
2. `82978` filter:
   - w9 < 2: spill through `891f3`, unless cost > 0 and `[+0x3c]` is null or the op is 0x26a.
   - w9 == 2: `820b7`.
3. `8ba60`: priority list, sorted by w3.
4. Coloring at `82a4d`. A record with cost <= 0 goes to `896ae`, the plain spill; this is wrong here (node with cost <= 0 at round 3 or 5 is not exact).
5. Coloring failures go to `a8f54(func, set, a3)`:
   - popcount(set) < 3: **simple path**, `a9634(rec, a3)` for every record, which inserts per-reference split markers.
   - Otherwise `ae60f`, which starts `cmp [0x108817b8],0x64; jl` and takes the **simple path** when the IR block count is below 100.
   - Otherwise the **complex path**: per-block grouping with group markers from `967b2`. `40ebc(block, rec, set)` runs only for blocks whose free-register set (after `5a28a`, tested at `40aeb`) is empty. Per-record markers come from `411c3`, inside 40ebc, for tuples flagged `[+9]&1` that are not op 0x26b and whose operand entry (byte 1) has `[+0x1c] == rec`.

Record fields used here:

| Field | Meaning |
|---|---|
| w0 | symbol |
| w3 | priority |
| w7 | idx |
| w9 | number of references |
| w10 / w11 | first / last block |
| w12 | hash chain |
| +0x40 | cost |

A record is found at `[0x108807b8+(idx&0x3ff)*4]`, following the w12 chain until w7 matches. Sets are linked chunks `[base, next, bits32]`.

The frame-slot weight is accumulated by `89a99` (`[sym+0x38] += ebx`, then a sorted insert); its callers come from `8863a`.

## Split history of the bank (a8f54 sets per round)

| Round | Records split |
|---|---|
| R1 | `40267` call {forcePosition:13, outside:17}; a8fdd call with 17 records (this:3, victim:a, unit:14, i:18, j:19, ...) |
| R2 | unit:4, count:5, **node:b**, index:10, ?:35, ?:65, victim:7e, this:7f |
| R3 | loop-2 records (attack, other, fallback, i, j, ...) |
| R4 | ai:7, victim:2a, ?:39, ?:69, index:72, **node:77**, count:7a |
| R5 | count:43, ?:7d (2 records: simple path) |
| R7 | 3 records |
| R9 | ?:7a |

Node pieces:

- At R3, node:77 has w9 6, cost 7 and w3 33, and spans cc04f4..cc82a8.
- The R4 complex split leaves it whole. At R5 it is node:44 with the same extent, w9 6, cost 1 and w3 51, and it colors to EBX: this is the bank's residue.

## tr40 per-block trace (complex path, rounds 2 and 4)

`res` printed at `40aeb` is the block's set of free registers (1, 2, 3, 4, 7, 8). Records whose idx collides with those numbers print with names, for example `unit:4` and `ai:7`.

- R2: `40ebc` runs only in block cc10ac, the only block with no free register.
- R4: `40ebc` runs in cc0e54, cc0f1c, cc0fe4 and cc10ac.
- `411c3` per-record markers hit unit:4 and ?:35 at R2, and ai:7 at R4 in cc0fe4 and cc10ac. **They never hit node**: node is live through those blocks (it is in s50) but none of their tuples reference it.
- Group markers (`967b2`) come from return addresses 40cfb, 40cc5, 40dd6, 40dff, 409bc and 4128b.
- Node is referenced in the loop-1 head and latch blocks (cc04f4, cc05bc, cc81e0, cc82a8 area). Every one of those blocks has 4 to 6 free registers, so the complex path can never give node per-reference markers there.

## Disproven in this pass (beyond the w1, w6 and 2026-10-19 lists)

- Node inside a struct, an array or a union, six aggregate spellings (`agg/a1..a6`): not exact.
- Node spilled at round 2, 4, 6, 7 or 8 (`slotmove2.py`): not exact. Node forced at round 1 crashes c2.
- Node cost <= 0 at R3 or R5 (`force.py`): goes to the 896ae spill, not exact.
- Frame weight decrease of 1 or 3 (table above).

## Second pass, same day: what retail's node lacks

### Allowed-set decode

Registers are bit numbers 1 eax, 2 ecx, 3 edx, 4 ebx, 6 ebp, 7 esi, 8 edi; the initial set is 0x1de. Removals for node:b (chunk 0xc7c978) at R2:

| Removed | By | Why |
|---|---|---|
| eax, ecx, edx | `87b9b`, `5a2ac` | calls in node's range |
| esi | `87b9b` in block cc10ac | the idle-branch MOVSD (aiIdle call + `movsd` x3) |
| edi | `88ba6` in cc10ac | same block |
| ebp | `5a7c9` | frame |

That leaves {ebx}.

R2 coloring order: R1 popped entry:15 (ebx) and 19 records failed. R2 pops this:67 (allowed [7,8], colors esi), then entry:12 (w3 121, allowed [4], colors ebx); node:b (allowed [4]) and this:7f fail.

### 831f7 / a90e6 / 40941 failure routing

When `831f7` (remove a newly colored register from the neighbours) empties a neighbour's set, `a90e6` tests `[rec+5]&4`:

- set: the record goes to the failure set;
- clear: `40941` decides. 0 goes to the failure set; nonzero goes to the arg4 set through `5a796`, or nowhere.

`40941` is a rematerialization check, `3fe0c(def tuple of rec->w15)`. It returns 0 for node.

### Hard-register removal at split time: `a85c4..a8ce1`

The ebx bit of node's R3 piece (node:77, chunk 0xcb9108, created during R2's split) is cleared at `a8ce1`: 0x1d0 becomes 0x1c0.

The loop at `a85f5`/`a8cb8` walks a block's tuples with a live-record list (chained through `+0x14`). For an operand whose record has an assigned register (`mask = 1<<reg`), it clears the mask from every live record. The `a8c44` path does this for operand records with kind byte `[+4]==2` and `[+5]&1`, skipping the record itself.

So entry:12, which colored ebx in R2 and is used inside loop 1, strips ebx from node:77. Watch trace: `wset4.txt` with `WI=119 KA=2 KD=3 WATCH=cb9110`, raw output in `wset4_r2r3.out.txt`:

- `af9b1` = 0, then `5a20c` = 0x1de;
- `87b9b` removes ecx and eax, `5a2ac` gives 0x1d0, `87b9b` removes edx;
- `a8ce1` gives 0x1c0;
- `a8628` (x2) and `88ba6`/`87b9b` (ecx fixed uses in cc0e54, cc0f1c, cc81e0) leave it at 0x1c0;
- `5a7c9` later removes ebp, so node:77 pops with [esi, edi].

### R3 to R5 coloring of node's pieces (bank)

| Round | Piece | Allowed at pop | Outcome |
|---|---|---|---|
| R3 | node:77 | [7,8] | high-priority loop-2 records pop first (?:47, leaderPos:30, leaderPos:34) |
| R4 | node:77 | [7,8] | ?:4a takes eax, this:28 takes esi (7), unit:7c takes edi (8); node fails, R4 complex split |
| R5 | node:44 (w9 6, cost 1, w3 51, blocks cc04f4..cc82a8, chunk 0x50 = {ebx, ebp}) | [4] | colors ebx, nb=6: **the residue** |

R5 pop order is ?:6c (ecx), ?:26 (ebx), ?:58 (eax), node:44 (ebx).

?:26 is a 5-reference piece confined to block cc81e0, the ordered-pointer store block (`ordered[count]` writes, `0x157..0x180`). It colors ebx but is not node:44's neighbour: node:44 is the head (0x71..0xdc) plus the latch (0x180..0x18d), with its middle in memory at [ebp+0x70].

### New exact forcing: node's set empty at a later round entry

`dt10.txt` with `PFL=1RR:idx:0` (allowed bits set to 0 at the 82978 entry of round RR):

| Forcing | Result |
|---|---|
| `102:b:0` (R2) | 2196 25 0.95334 (unchanged) |
| `103:77:0` (R3) | **2199 0 exact** |
| `104:77:0` (R4) | **2199 0 exact** |
| `105:44:0` (R5) | **2199 0 exact** |

Retail therefore behaves as if node's R3+ pieces had no register left, and no frame-weight change is needed for this route.

In retail ebx is unused at the loop-1 head and latch (entry holds ebx at 0xdf..0x156, the ordered pointer at 0x15d..0x180), so retail leaves the back-edge ebx gap empty.

The source question is now: **what in retail removed esi and edi (and kept ebx removed) from node's head+latch piece?** The removal could come from block-based constraints (87b9b/88ba6, as the MOVSD block does) or from a precolored record used inside the piece (a8c44).

### Rounds are incremental; how node:44 gets its R5 set

Records colored in a round keep their register; the next round colors only the new split pieces. R5 pops only ?:6c, ?:26, ?:58 and node:44.

Watch on node:44's chunk (0xc837ac) from R4 entry to R5 entry (`wset4.txt`, `WI=68 KA=4 KD=5 WATCH=c837ac`; raw output in `wset4_r4r5.out.txt`):

| Step | Set |
|---|---|
| `5a20c` init | 0x1de |
| `5a2ac` (set difference) | 0x15c (eax and esi removed) |
| `a8628`, the hard-register pass: unit holds edi from R4 and is used in the head | 0x5c (edi removed) |
| `87b9b` calls, then `5a2ac` | 0x50 (ecx and edx removed) |

That leaves {ebx, ebp}, and `5a7c9` later removes ebp.

ebx survives because no record that kept ebx is live or used in node:44's blocks: the head (0x71..0xdc) and the latch. For the R5-empty route, retail would need such a record there. Retail's final code has nothing in ebx at the head or latch, so the R2 per-reference route (`inj.txt`, R2 exact) is the more likely one.

Probe `tr43.txt` (`FR=2 FB=<blocks>`: force the 40aeb free set empty in the listed blocks at R2), all **not exact**:

| Blocks forced empty | Result |
|---|---|
| cc04f4 | 2196 124 0.89143 |
| cc05bc | 2195 116 0.89821 |
| cc82a8 | 2195 116 0.89821 |
| all three | 2196 119 0.89416 |

40ebc then gives per-record markers to ?:35 and this:7f too, not only node. Retail's head and latch blocks were therefore not register-full at R2.

### R1 takes the complex path; the "NEITHER" cut variants are a red herring

The bank's IR has 104 blocks (`[0x108817b8]`), so R1's a8f54 takes the complex path. Only block c30d88 (loop 2) has an empty free set there.

That split produces separate loop-1 pieces, this:7f (w9 9, cc029c..cc8370) and victim:7e (w9 4, cc029c..cc82a8), which fail at R2. The cut variants that turned loop 1 into retail's NEITHER state (c4, c7; 937 of 1024 `fcut` combinations) have fewer than 100 IR blocks, so every round takes the simple path. That is not retail's mechanism.

`simp.txt` (block count forced to VAL in the listed rounds):

| Simple path forced at | Result |
|---|---|
| R1 | 0.874 |
| R1+R2, R1+R3, R1+R4, R1+R2+R3, all rounds | 0.849..0.874 |

So retail's R1 was complex. The old lead "simple path for a whole round" is **disproven**: rounds R2 and R4 were tested in the first pass, R1 and combinations here.

WorldBuilder facts are in `amoeba5881db_20261019/README.md` (section "WB 0x146DC50 facts") and the w6 note (best/bestCell at loop-2 body scope). Nothing new from WB this pass.

### Disproven source shapes in this pass

| Trial | Result |
|---|---|
| `f2.txt`, 1536-combination loop-2 factorial (pathfinder inline; cell init; candidate init; 3 leader forms; best-store order; distance operand order; both timer blocks inverted; flat `valid[9]`; `!i&&!j`) | all NODE state |
| `f3.txt`, address-taken node (`**cur=&node` in 4 use forms; `*&cur` alias; `node[1]` array) | all NODE |
| `gnest.txt`, 64 loop-1 continue-to-nesting combinations | all 2196 NODE |
| Loop-1 forceinline helpers | 0.944 / 0.920 |
| Victim/parent forms, leader local, ordered declared before range | identical |
| count declared before range | worse |
| Separate target variable | 0.87..0.88 |
| Other-block reshapes r1..r9 | all NODE; r1 is 2199 B but 0.96588, other block differs |
| while/goto loop forms | nd82 |
| k4n / k2n | 2197 nd113 / 2192 nd173 |

Allocator forcings that are not exact:

| Forcing | Result |
|---|---|
| Flag bit 4 cleared | unchanged |
| 0x80 flag | 0.923 |
| Allowed set empty at R1 | 0.898 |
| Allowed set {ebx} at R1 | unchanged |
| Timer cut | 0.817 |
| Priority raised | nd50 |
| Cost edits | unchanged |
| Simple path at R2 or R4 | not exact |

### Exact forcings, all known

1. Per-reference inject at R2 or R4 (`inj.txt`).
2. Node dropped from the R2/R4 failure set.
3. `slotmove2` node@3 / node@5 with `dec=node:2`.
4. Allowed set empty at R3, R4 or R5 entry (`dt10.txt`).

## Open leads for the next session (ranked)

1. **Make node live through a block that pins esi/edi.** In the bank, node:b at R2 loses esi/edi only because it is live through cc10ac (the MOVSD block). After R2's group split, node's pieces leave cc10ac and get esi/edi back.

   A source shape where the head+latch piece itself crosses a MOVSD or fixed-register block would empty its set. Examples: a struct copy (`entry.position=unit->m_position` is the MOVSD) placed in a block node stays live through, or the copy moved to the loop tail/latch side.

   Trace each candidate with `wset4.txt` (watch node:77's chunk) before scoring.
2. **A precolored record inside node's piece.** `a8c44`/`a8628` remove a kept record's register from every live record where it is used. At R4 to R5, unit (edi) strips edi from node:44 this way, and `5a2ac` strips esi.

   Only ebx is missing for the R5-empty route, and retail's final code has no ebx user at the loop-1 head or latch. So this lead mainly explains the mechanism; the R2 per-reference route (lead 1, `inj.txt` R2 exact) is the more likely retail path.

3. Check the frame-weight route again: `slotmove` exactness needed `dec=node:2`, but the empty-set route needs no weight change, so the weight difference may be a consequence of the per-reference split rather than its cause.

## Files

The `*.txt` scripts are the scratch tools, renamed with a `.txt` suffix. They run from `build/c2tr/` with the bank copied there as `bank.cpp`.

| Script | Purpose |
|---|---|
| `wdbg.py` | winedbg driver over `build.compiler_command` |
| `inj.py` | lists a8f54 sets per round; with `ROUND:NAME` moves a record to a per-reference split |
| `tr40.py` | logs 40ebc, 411c3 and 967b2 calls and the 40aeb per-block sets |
| `slotmove2.py`, `slotmove3.py` | frame-slot list moves, `name@round` spill forcing, `dec=name:N` weight changes |
| `force.py` | cost edits at 82978 |
| `rec7.py` | record dumps |
| `ra8.py`, `watch7.py` | earlier tracers |
| `odis.py` | object disassembly |
| `cerr.py` | compile to a private object |
| `objscore.py` | scorer |
| `vrun.sh` | 8-way parallel variant scoring |
| `runf.sh` | forcing run plus score |

Scripts added in the second pass (same conventions; each `.txt` is the `build/c2tr/*.py` of the same name):

| Script | Purpose |
|---|---|
| `dt10.txt` | allocator forcings: `PFL` (`R:name:flags` at insert, `-R:name:v` at coloring, `100+R:idx:bits` allowed set at round entry), `PSET`, `TRACE=rounds` coloring trace, `WN`/`WI` watch a record, `F40941` |
| `dt.txt`, `dt3..dt9.txt` | earlier versions of dt10 |
| `wset.txt`..`wset4.txt` | allowed-set chunk watches; `wset4` arms `WATCH` at 82978 entry `KA` and dumps record `WI` at entry `KD` |
| `simp.txt` | sets the IR block count `[0x108817b8]` to `VAL` in the listed rounds (simple path) |
| `tr42.txt`, `tr41.txt`, `tr831.txt` | tr40 with a call-number filter; 831f7 neighbour-removal trace |
| `inj2.txt`, `keep.txt`, `drop.txt`, `add.txt`, `prio.txt` | failure-set edits and priority forcing |
| `chunk.txt`, `scr.txt`, `xref.txt`, `c2dis.txt` | set decoder, scratch, c2.dll xrefs and disassembly (capstone) |
| `f2.txt`, `f3.txt`, `gnest.txt`, `fgen.txt`, `fcut.txt`, `fv1.txt`, `vstate.txt`, `vloop1.txt`, `s1f..s9f.txt` | source-variant generators and the loop-1 state classifier (NODE / NEITHER / IDX) |
| `wset4_r2r3.out.txt`, `wset4_r4r5.out.txt` | raw chunk watches for node:77 (R2 to R3) and node:44 (R4 to R5) |
| `tr43.txt` | tr40 plus `FR`/`FB` free-set forcing at 40aeb |
