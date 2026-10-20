# 29530: real POD-copy proof; parent frame remains open

Native 29530..297C6 is 662 bytes, RET12. The existing bank remains unchanged:
662 bytes, frame 6C versus native 70, 45 differing byte positions (617/662).
Target wrapper and WB twin evidence and donor-derived string-insert semantics
remain as recorded in string-insert29530-helpers-20261020.md. No stronger target
name, character signedness, or class-layout identity is asserted here.

The bank's emitted Rva000179B0UninitializedCopy is 68 bytes, whereas the native
__copy_trivial owner at 179B0 is 41. The existing pin resolves call addresses
but is not whole-body proof for that unoptimized helper. Normal diagnostic
verification refuses its body at offset zero. This is an existing helper/link
debt, not a new pin admitted by this attempt.

There is now a positive whole-body lead: actual vendor STLport headers at /O2
/Ob2 emit the Rva wrapper as exactly the native 41-byte function. The entire
body verifies, including the owner's sole relocation to __imp__memmove at the
same offset/type/addend (relocations.json). The vendor's conditional-expression
copy body matters: a semantically equivalent if/local-count implementation is
42 bytes. /O1 emits a five-byte tail jump instead. A char-pointer specialization
using that native conditional expression also emits 41 exact bytes and no
other functions. Its semantic basis is the donor's POD uninitialized_copy;
the target fact is the 41-byte copy operation and its native caller destinations.

This proof does not itself repair the existing caller/provider relationship.
An explicit specialization declaration or extern template declaration in the
existing range-insert consumer suppresses the bad helper but shrinks its
848-byte matched parent to 737 bytes and loses native frame 90. Retaining a
different template definition under the same external name would need proper
ODR and provider reconciliation. The broad narrow-string owner already has
ten COMDAT blockers; the range-replace consumer also has erase, replaceBase and
empty-destroy blockers. No speculative provider, alias, source or pin was landed.

Parent controls: 10 inline-site/depth controls and 11 genuine allocator/assign/
free/copy visibility controls gave no improvement. Visible vendor char fill
produces the native frame 70 but expands two calls (682 bytes); declining it
via depth or noinline loses the word. Actual allocate/assign/free bodies alter
instruction shape or add too many slots. These are refuted controls, not source
recommendations. The bank and its previous score are preserved.

Replay drivers use normal explain_mismatch CLI and isolated build/ paths.
The owner proof also verified a header-based Rva wrapper inside a scratch copy
of the whole existing narrow-string owner. No naked code, volatile padding,
equal-arm expressions, gate edits or new pins were introduced. All substantive
new evidence and drivers are retained here; transient logs remain in the named
build/ directories. Model gpt-6.1-sol, about 25 minutes including helper audit.
