# DiagonalBlur 0x001C2B80 (916 B): closed by symbol-id alignment, 2026-10-23 (c)

Spec `reverse/vp6_cleanroom/specs/001c2b80.md` and retail only; no decoder
source read. Landed as `Code/Libraries/Source/VP6/DiagonalBlur.cpp`, all 916
bytes verified. Earlier handoffs: `../diagonal-1c2b80-20261022.md`,
`../diagonal-1c2b80-20261023/readme.md`, `../diagonal-1c2b80-20261023b/readme.md`
(c2 id model, kind-15 arena and FactCanonSort key layout).

## The condition

The bank was retail's structure with two SIB base/index swaps; injecting ids
under winedbg made it exact. Measured with `cst.sh.txt` (prints the first
kind-15 id `f15`, the kind-15 burst `B`, the kind-3 count `A`, the chunk
bases and the tail of the event list), the exact compiles all satisfy

    f15 + B' = 1279    (B' = kind-15 ids in the first burst, with tail befdf5)

where `f15` is set by the kind-3 ids taken before the first hash var and is
always a multiple of 32. Kind-3 ids injected before that point only count as
chunks: 32 extra kind-3 at allocation 1, 300 or 600 gave the same result.
Proofs (`inject3.py.txt`, spec `kind:at:count`):

- bank (dc2: f15 896, B 345) + `3:1:32,15:1:6` -> nd 0
- natural two-pass source (f15 896, B 287) + `3:1:96` -> nd 0
- natural + `3:1:64,15:1:32` -> nd 0

`comp2.sh.txt` computes the needed injection (N = 1279 - f15 - B, as kind-3
chunks when negative) and prints the compensated nd: a variant whose
compensated nd is 0 has retail's structure, and only its numbering is off.

## What moves the two numbers

- `f15` (whole chunks): kind-3 lumps come from c2 cloning temporaries for
  block copies (callers 47d50 <- 47b57 <- 47c88 <- f1f0). A split statement
  or a named local inside pass 1's body adds +64 (896 -> 960); inside pass 2
  +32 (-> 928); both gives 960 with a different body (A 770, nd 21,
  compensated 9). It is per pass, not per local, and the declaration level
  of the local is irrelevant.
- `B`: a separate pass-2 column counter +58; a separate pass-2 row counter
  +5; a `while (row--)` row loop instead of a for loop +1 each
  (r00111 350, r03111 351, r33111 352).
- Inert for B: tap order and grouping, the placement of `16 +`, `x * 8`
  against `<< 3`, distributing the weights, index spellings, `2 * pitch`
  forms, the order and grouping of the subtractions in pass 2, `++col`.
- `!=` in the column compare changes the loop structure (not retail).

Retail's 1279 = 928 + 351: pass 2 has one named local (the centre pixel),
its own row and column counters and one count-down row loop.

## The factorial (`gen13.py.txt`)

432 variants over the row-loop form of each pass (k: 0 for up `< 8`, 1 for
8 -> 1 down, 2 for 7 -> 0 down, 3 `r = 8; while (r--)`, 4 do-while
`++r < 8`, 5 `!= 8`), separate pass-2 row and column counters and the named
centre. Exact (nd 0): r03111 r05111 r13111 r15111 r23111 r25011 r25111
r30111 r31111 r32111 r50111 r51111 r52011 r52111. The landed body is r03111
(pass 1 for-up, pass 2 `while (row2--)`), the plainest of them.

## Tooling notes

- Run parallel winedbg compiles in separate prefixes with their own TEMP
  (set in each prefix's `user.reg`); a shared TEMP mixed the compilers'
  intermediate files and gave nonsense counts.
- Scripts: copy `*.txt` to `build/db/` and `wdbg.py.txt` from
  `../diagonal-1c2b80-20261023b/` to `build/c2tr/wdbg.py`. `slot.sh.txt`
  runs one variant in a free prefix, `st.py.txt` reduces an event list to
  the numbers above.
