# Signed pointer-map bound provider blocker

At BFME2 71564a9349, current paired legacy preview keeps the int-pointer
map instantiation unit at 0/727 B; unsigned bound provider stays 733 B.
Only its signed _M_lower_bound/_M_upper_bound copies and their selection
are blockers. Native callees4FF3B6/4FF539 are proven unsigned37B workers
in stlport_map_int_ptr_lower.cpp (jb, not jl); their old signed pins are
not proof that the currently emitted signed implementations are correct.
The census contains only this unit's copies under the signed helper names.

Trial1: import-forceinline signed bound specializations delegate through
unsigned tree's public const lower_bound/upper_bound and declare native
unsigned _M workers only.21/23 rows pass; both equal_range wrappers acquire
stack frames, caller-owned iterator result slots and unresolved outlined
signed lower_bound/upper_bound calls instead of direct worker calls.
Trial2: also force-inline the unsigned const iterator wrappers and all four
signed iterator wrappers. The nonconst equal_range call displacement then
extends past its42B retail row (offset40 needs44B): this is a real changed
body, not a boundary or verifier error. No extent was raised.

The second trial is retained as adapter.patch against71564a9349. No source
or ledger change remains. Two failed scoped gates exhaust this bounded link
attempt. A future repair needs a direct ABI-preserving private-worker binding
that avoids hidden iterator-result temporaries, or a supported reconciliation
of the signed wrapper identities with native unsigned instantiations. Do not
add a second pin/name or linker alias to bypass it. No full census/link run.
