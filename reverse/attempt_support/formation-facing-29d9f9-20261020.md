# Formation-facing helper 0x0029D9F9: unchanged bank

The complete 360-byte RET4 target and the complete bank were reviewed with all
prior attempt entries. The existing `reverse/attempts/0x0029d9f9.cpp` remains
unchanged (SHA256 b345044a610684be1f2a9fc888543924039f9506fbb0a1719ea2f775a4f150a6).
No reconstruction was installed in Code and no pin or header was changed.

The bank emits 355 bytes with no unresolved calls, first different byte +0xE.
Retail keeps threshold/y/square in XMM1/XMM3/XMM2; the bank uses XMM2/XMM1/XMM3.
The native tail also reloads y before storing the reciprocal, and preserves it
in XMM3 through normalization, half-threshold scaling and the hidden return.
The bank coalesces reciprocal and y and lacks that five-byte reload. The list
loop, cached-return copy and return convention already agree.

## New hypotheses tested

45 normal explain trials, with aligned diagnostics for the first 19:

- 19 helper-context trials: square components passed as values/references,
  one-component in-place multiplication and two-component scale updates with
  value/reference factors at normalization/scaling/both sites, plus the real
  `Coord2D::normalize` member form. Squares/member form keep 355 bytes; scalar
  reference updates give 361 and worsen the tail. The prefix allocation stays.
- 2 documented destructor contracts from Coord2DCtorView.h: the real inline
  empty destructor is neutral at 355; declared out-of-line destructor yields
  446 bytes and EH/call changes. Neither restores the native reload.
- 10 genuine value-lifetime forms: copy the input, mutate a copied result,
  retain separate x/y scalars, or return a normalized Coord2D by value, each
  with x/y and y/x update orders. Results range 355..382; none improves.
- 5 compiler cost/inlining profiles: O2 gives 372, Ot 384; G6, Og- and Ob2
  retain 355 and the same first mismatch. No alternate compiler was selected.
- 3 layout/container controls: genuine STLport selected-drawable list, actual
  three-float formation endpoints supported by the matched finalize caller,
  and both together. All retain 355 and the register permutation.
- 6 threshold controls: value/reference length or coordinate predicates,
  assistant member predicate and its logical branch inversion. Five retain
  355; inversion gives 354. The inversion uses logical negation to preserve
  unordered comparisons, rather than substituting an inequivalent >=.

The successful ship recovery's mutable-reference helper technique therefore
does not transfer to this function. These trials cover value identity, actual
type/lifetime, layout, compiler cost and control flow; no new justified lever
emerged. Keep the existing bank rather than respelling the same arithmetic.

## Inputs and diagnostics

Canonical constructor-view header SHA256:
`c9cdd85f8fdfee5a1a7bd238f94ec2d5161abd34c0e703a7cf241c3a59fe43bc`.
BFME2 final input 8ae04b9a8babf31760e40bbedcc3f78406590e7d; BFME1 pointer
b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b. The relevant headers did not change
across the ordinary synchronization during this attempt. Flags remain
O1/G7/arch:SSE/MD/EHsc, include Code/Libraries/Include.

Raw normal verifier outputs, trial sources, aligned diffs and hash-bound input
manifest remain under `build/formation-facing-oct20/`. Note that a size-mismatched
explain stream can display corrupted-looking literal operands because it copies
DIR32 bytes at unequal offsets; the raw-object aligned diagnostic distinguishes
that relocation noise from the actual register and y-reload differences.

The WB DC3470 guide and rowed 29DB61 caller establish the behavior/receiver and
hidden-result ABI as recorded in the bank; an original lexical method name is
not established. No new identity assertion is made here. A future recovery
still unblocks the larger formation preview, and must verify every byte.
