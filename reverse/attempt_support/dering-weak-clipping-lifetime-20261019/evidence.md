# Weak deringing: separate clipping lifetime

Target `_DeringBlockWeak_C`, RVA 0x001C22C0, complete 1526-byte extent ending at
0x001C28B6. Only approved clean-room specs 001c22c0/001c1ad0, retail, prior
attempts and repository-authored code were read. No external decoder source.
The whole DeringFrame.cpp neighbour and the complete existing bank were reviewed.

Retail retains the blended integer in EBP and computes the clipped integer in
another register before writing the low byte. The previous bank modified the
blend in place. Giving the clipped integer its own local restores that output
shape and the complete 1526-byte extent, versus the previous 1523 bytes. Ordered
byte alignment improves from 1358 to 1427 of 1526 (0.9351245). The remaining
250 fixed-offset differing bytes, starting at +0x63, include weight-pointer
bias, stack-slot choices, commuted address operands, signed column branches and
output scheduling. The alignment score is diagnostic, never exact coverage.

Twenty-eight normal isolated explain_mismatch trials tested clipped byte versus
integer lifetimes; one-based weight loops; signed/unsigned and phase-local
column counters; native-guided weight declaration order; phase scopes and reused
phase-local names; two-dimensional weight arrays; grouped coefficient arithmetic;
direct array reads; and a direct clipping expression. The integer clipping form
is strongest. Const on the blend and equivalent coefficient groupings are inert;
byte clipping emits 1519 bytes; one-based loops, local counters and declaration
reorders regress. Dimensional arrays and separate phase scopes reproduce the
same best code. No scheduling barrier, volatile access or fabricated operation
was added. Existing stronger phase/pointer structure is retained.

The earlier tracked independent-spec oracle passes 2560 native/candidate/spec
cases for this new complete body: both pitch signs, all 64 sharpen entries,
flat/checkerboard/ramp/random inputs, and separate/same/partially overlapping
buffers. Full buffers and canaries, saved registers, cdecl stack and scale table
are checked. This supports behavior in those cases, not exhaustive equivalence
or byte identity. Immediate stores preserve the weak filter's alias behavior.

Normal compiler diagnostics use /O2 /G6 /DNDEBUG /MD, as recorded in inputs.json;
the single sharpen-table DIR32 relocation is resolved to its established native
VA 0x00DB7A28. Whole emitted extent is read separately from row-limited patches.
No source or row is admitted under Code, and no pin, alias, header, compiler or
verifier edit is included. Preserve this stronger complete bank and resume from
remaining.diff rather than repeating the exhausted lifetime/array hypotheses.
Model: gpt-6.1-sol.

Follow-up at 28b1b5c69e: three genuine inline-helper forms do not improve the
bank. Extracting only the repeated weight clamp reproduces the same 1526-byte
body and 250 fixed differences. Factoring the complete pair-to-weight operation
with int or short returns emits 1552 bytes and lowers ordered alignment to 953.
No source, bank or row change; no new behavior verification is claimed for the
rejected helper forms. Raw diagnostics: build/weak-dering-helper-oct19.
