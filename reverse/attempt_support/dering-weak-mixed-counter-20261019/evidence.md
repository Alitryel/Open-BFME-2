# Weak deringing: separate horizontal counter

Target `_DeringBlockWeak_C`, native `0x001C22C0..0x001C28B6`, 1526 bytes.
Inputs: BFME2 `193aec803d97`, BFME1 `cf0a80c22858`, MSVC 13.10.3077,
`/O2 /G6 /DNDEBUG /MD` with the ordinary base options. Only approved specs
`001c22c0.md` and `001c1ad0.md`, retail disassembly, and repository-authored
evidence/code were read. No external decoder source was consulted.

The previous bank has a signed column variable shared by all three phases.
Giving only the horizontal-weight phase its own unsigned counter, while casting
its bounded index to `int` for neighbor addressing, preserves the full native
extent and improves ordered byte alignment from 1427 to 1441 of 1526 bytes.
Fixed-offset differing bytes decrease from 250 to 243. This is an improved bank,
not exact coverage. First difference remains +0x63. The stored source is
`reverse/attempts/0x001c22c0.cpp`.

Twenty-eight ordinary mismatch-tool diagnostics are summarized in `trials.json`.
They distinguish pointer-stream stores, legal one-short pointer views, explicit
native four/three-element unroll groups, independently typed phase counters,
unsigned condition casts without type changes, short-valued weight locals,
commuted index association, and C89/C++ phase-scope controls. Stream stores and
short locals regress; index association and the C frontend are inert. Explicit
vertical groups improve the original bank slightly but lose that improvement
when composed with the stronger horizontal-counter form. Other mixed counter
lifetimes do not improve the selected candidate. No volatile access, barrier,
padding, fabricated operation, pin, alias or compiler change was introduced.

Retail and candidate already agree on the actual array bases and effective
weight addresses. The remaining difference is the compiler's cursor bias
(vertical +1 versus +2 shorts, with correspondingly adjusted store offsets),
instruction scheduling, stack homes, output register roles, and a signed versus
unsigned output-loop branch. Changing physical array layout has no target basis.
`remaining.diff` preserves the new best comparison. The metrics for trials longer
than retail describe only the compared prefix; their emitted extent is recorded
separately and none is eligible for landing.

The existing independent-spec emulator was rerun on the exact tool-written bank.
`oracle-banked.json` records 2560 passing native/C++/spec comparisons: complete
buffers and canaries, all 64 sharpen indices, both pitch signs, disjoint/same/
partially overlapping buffers, cdecl stack, saved registers, and unchanged scale
table. These cases support the bank's behavior; they do not prove byte identity
or exhaustive equivalence. Reproduce after an ordinary mismatch compile with
`python3 reverse/attempt_support/dering-weak-bank-20261019/oracle.py reverse/attempts/0x001c22c0.cpp`.

No production source or function row is added. Preserve this stronger bank and
do not repeat the listed hypotheses without new compiler or target evidence.
Model: GPT-6.
