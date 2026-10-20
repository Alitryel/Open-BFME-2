Narrow num_put provider handoff, 2026-10-20

Original self-strict 19/19; frozen e7a7769fe5 has two losing/selected
helpers, legacy0/905 nonpadding bytes. 2arg range initializer17790 (23B)
forces its 3arg forward-tag instantiation. The conflicting char-pointer
POD __uninitialized_copy is also emitted. No new identity or pin needed.

Trial1 declaration-only specialization of 3arg member template plus native
__uninitialized_copy declaration hits C1001 P2/main.c148 in vendor
_string.h376 (the 2arg wrapper). Trial2 extern-template declaration of
that 3arg member plus same copy declaration hits identical ICE. Retrying
one source through overlapping baseline/link commands also hit the same
compiler error; it is not a third hypothesis. Both commands were polled,
then the two actual hypotheses were stopped. Original source restored.
Diagnostic zero-context patches preserve exact attempted changes.

Needs compiler-safe member-template ownership preserving the rowed
2arg wrapper; neither global helper substitution nor a new pragma is
justified. No repair gain, source/header/ledger/verifier change retained.
BFME1 review unchanged4483e88da1c2; source is STLport4.5.3 and native
provider declarations, no donor address transplantation. t=6min
model=gpt-6.1-sol.
