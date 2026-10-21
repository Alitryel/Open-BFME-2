# HordeMeleeAmoeba::updateMeleeAttack 0x005881DB (2199 B): c2 allocator trace, 2026-10-21

Result: the bank is unchanged: `reverse/attempts/0x005881db.cpp` emits 2196 B, scores 0.9772 and has one structural region left, residue (A) in the w6 note. Model claude-opus-5-5. No change to `Code/`, the ledger or pins.

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

## Open lead for the next session (untested, ranked)

1. **Simple path for a whole round.** Retail would split node per reference if the round that split node took a8f54's simple path. The complex path cannot produce that for node, as the tr40 trace shows. The simple path is taken when the IR block count `[0x108817b8]` is below 100, or when that round's failure set has fewer than 3 records. Next test: modify `inj.py` to set `[0x108817b8]` to 50 at the R2 (then R4) a8f54 entry and restore it at return, so that every record in the round is split per reference. If that is exact, retail's IR had fewer than 100 blocks at that point. Then look for a source shape with fewer IR blocks but the same final code: merged conditions, `&&` chains instead of nested `if`/`continue`, fewer EH or `continue` edges. The w6 note's "88 final blocks" threshold is probably this 100-block IR test.
2. If only a small failure set fits: find which records retail lacked in the R4 set (ai, victim, ?:39, ?:69, index, count), so that node failed together with at most one other record.

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
