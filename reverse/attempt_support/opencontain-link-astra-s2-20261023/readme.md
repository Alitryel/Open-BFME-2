OpenContain construction/unwind link repair, Astra s2, 2026-10-23

Inputs: BFME2 7aae99cc67; verified BFME1 pointer 138757e9b74645fbcbb7724a7af2764e34931e11.
Compiler: repository MSVC 7.1, existing source flags unchanged.
Prior handoff: ../opencontain-link-20261023/readme.md and its lifetime trial.

Target facts: native constructor 465124 (253 B) initializes its +4C set through
463D59 (25 B). Unwind action 78AC44 (11 B) calls 256641 (5 B), whose complete
body is JMP 256461. The existing Rva00255CD1 destructor at 256461 (56 B)
clears the tree via 255CD1 and releases its header. These are retail call
relationships, independent of the unresolved semantic identity of the element.
The STLport set spelling/layout is inherited structural inference.

Original current-source scoped build passed 11/11. Legacy link preview against
published census 491a8b3d87 reported 0/290 B, solely the unresolved destructor
of _Rb_tree<Rva00463D59Element,...> (before-link.txt).

New evidence-backed trial: explicitly forceinline the wrapper constructor from
the old lifetime trial. Placement construction then reaches the real set ctor,
but adds a null check, stack spills and an EH state, so fails the parent byte
check. The fully qualified MSVC constructor call instead preserves the exact
native initialization without placement-new machinery. Aligned storage retains
the set extent/alignment; its destructor binds to the existing tree provider.
The outer member wrapper emits the exact native tail jump, with no new pin,
ledger alias, barrier, pragma, baseline change or asm.

Validation: focused byte gate 11/11; EH graph EXACT 1/1; separately resolved
??1Rva00256641@@QAE@XZ at 256641 is exactly 5 bytes (explain_mismatch).
Strict preparation passed for the one explicit source with reusable receipts.
Final link-preview output is adjacent (after-link.txt). The reported
290-byte improvement is the published census scoped legacy metric, not new
recovered bytes or a claim of closed-strict linking or a link.exe run.
