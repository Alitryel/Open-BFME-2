# 0x001C5E30 predict-filtered setup: frame-slot regimes (2026-10-20)

The bank `reverse/attempts/0x001c5e30.cpp` went from 0.88 to 0.975260 (byte
ratio). Permute fitness is now 0.9767 and the size is 768 B, the same as retail.
Everything here comes from clean-room spec `reverse/vp6_cleanroom/specs/001c5e30.md`
and retail disassembly. No decoder source was consulted. The retail dispatch
oracle (`../predict-filtered-bank-repair-20261018/oracle.py`) passes 1238 of 1238
cases on the new bank. It needs `pip install unicorn==2.1.4`.

## What the bank fixed

- **Filtered branch.** It now reloads `pbi->vectorMask` after the builder call
  and computes the phases from it.
- **Unfiltered branch.** It now keeps `mask` in edx.
- **Base expression.** It is one statement:
  `frameStride * yterm + reconIndex + source + xterm`.
- **Threshold.** `limit = (1UL << (t - 1)) << 2` gives a bare `shl`. x86 masks
  the count to five bits, and the oracle confirms this matches retail for every
  byte value.

## Residue

The remaining residue is frame slots and one register.

| Variable | Retail slot | Bank slot |
|----------|-------------|-----------|
| mvx      | 0x18        | 0x1c      |
| mvy      | 0x1c        | 0x20      |
| y        | 0x20        | 0x18      |

`limit` shares mvy's slot.

In the unfiltered branch, retail keeps y in ecx: `mov [0x1c],ecx` (mvy),
`movsx ecx,cx`, `mov esi,ecx`, ..., `add esi,ecx`, `mov ebp,ecx`,
`mov [0x20],ecx`. The bank puts y in esi, spills it early and adds it back from
the slot.

## Three regimes, controlled by where the unfiltered branch computes xPhase

Retail needs three things at once:

- retail slots;
- the x-term spill: retail spills `(x + ((x >> 31) & mask)) >> shift` to
  `[esp+0x14]`, offset1's slot, while ebx holds xPhase;
- the prologue that keeps `source` in eax across the profile tests (`mov cl,`
  byte tests).

Each regime gets only two of them:

| xPhase statement                         | Slots  | x-term spill | Prologue                                                          |
|------------------------------------------|--------|--------------|-------------------------------------------------------------------|
| before `x = mvx` (`mvx & mask`)          | retail | yes          | wrong: `al` tests, source reloaded into esi, +12 lines            |
| between `x = mvx` and the x-term add     | bank   | yes          | retail                                                            |
| after the x-term add                     | retail | no (759 B)   | retail                                                            |

The middle regime is the bank. `slots-spill-prologue-wrong.cpp.txt` (0.933594)
is the first regime. `slots-prologue-no-spill.cpp.txt` (0.935167, 759 B) is the
third. Measured with the scratch sweeps t4/t5: 63 positions × 3 operand forms.
The regime depends only on where xPhase sits. Every member of a regime has the
same slots, spill and prologue; the bytes differ only in instruction schedule.

## Disproven (do not repeat)

- **Declarations.** Order, names and the types of xPhase, yPhase, stride and the
  offsets (int or unsigned) are inert in every regime. A splice of the
  declarations between the two diagnostics gives identical bytes.
- **Base spelling.**
  - Single-expression term orders: all 24.
  - Splits into 2, 3 or 4 statements: a 3000-sample random topological sweep
    over the statement order of the unfiltered branch found no candidate over
    0.9505.
  - Base forms are inert inside the first regime: 8 forms.
- **Statement order of the unfiltered branch.** Every topological order of
  mvx, x, mvy, y, xPhase, yPhase and base, with three operand forms for each
  phase (908 per head), on three heads (the bank, cb5 and cb6). Nothing beats
  0.975260. The retail slots appear only with xPhase before `x = mvx`.
- **Prologue spellings in the first regime.** 41 combinations, all inert or
  worse:
  - source selection as a ternary, an if/else, or with `!= 2`;
  - mask read first or last;
  - the profile condition spelled `0 !=`, `!= 0` or bare;
  - the call argument written `reconIndex + source`.
- **Named x-term and y-term temps** (`dx`, `dy`) with xPhase between them, 70
  variants. Every one falls into the bank regime; the best equals the bank.
- **Earlier rounds.**
  - Base computed from y or mvy.
  - Tail swaps P1–P4 and V1–V6.
  - A flags sweep (`permute --flags`).
  - Hill climbs over filtered order, unfiltered order, types, declarations and
    term order, one of them with a slot penalty. The best climb plateaued at
    the first regime, fit 0.9438.
- **Permute from this bank.** 763 trials, no gain.
- **Builder call in the first regime.** A function-scope `ref` pointer, and
  `__forceinline` and `inline` helpers that take `source + reconIndex` or
  `source` and `block`: 4 variants, all byte-identical (prologue still wrong).

## Untried

- A structural option: compute xPhase and yPhase after the if/else from
  a `mask` the filtered branch reassigns (`mask = pbi->vectorMask` after the
  call). This only works if the compiler duplicates the tail into the arms, so
  it is unlikely.

Scratch, untracked: `build/c1c5e30/`.

- `mini.py FILE...` writes `.dis` files and prints scores.
- `enum5.py HEAD.cpp LOG` runs the topological sweep of the unfiltered branch.
- `enum8.py` runs the random sweep.
- `slots.py` holds the slot probe: `yslot`.
- The `t3`–`t6` directories hold the splices and position sweeps.

Model: claude-opus-5.5.
