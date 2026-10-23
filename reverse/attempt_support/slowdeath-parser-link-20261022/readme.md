Slow-death parser link repair, 2026-10-22

At BFME2 21387ea4c9 with verified BFME1 inputs 37c3022d, current-object legacy
preview excludes SlowDeathBehaviorParsers.cpp (807 nonpadding B) for two names:
TheSlowDeathPhaseNames and the by-value WeaponTemplateSetHead::rva0045D859().
The matched provider at 45D859 instead has explicit output-pointer ABI
(?rva0045D859@WeaponTemplateSetHead@@QAEPAV1@PAV1@@Z). Both pass the output
address on the stack; changing the C++ call changes MSVC register allocation.

Retail DC9598 is exactly four pointers INITIAL/MIDPOINT/FINAL/HIT_GROUND plus
NULL (20 B), before a different table. BFME1's SlowDeathBehavior.cpp confirms
semantics; target strings and pointer values were independently read. Defining
that data alone cannot link this consumer while the helper name is unresolved.

Two careful scoped builds failed only parseDeathFlags (45E293, 237 B):
1. Inline pointer-taking constructor calling the provider, static initialized
   through that constructor: extra EBX save, source/output addresses use
   different registers, shifts the allowed-mask initialization.
2. Inline by-value wrapper with local result and explicit provider call:
   still changes parseDeathFlags; NRVO does not preserve the original shape.
The second complete candidate is preserved in wrapper.patch; no source or
ledger edit is retained. Scoped original frozen-source check passed. Original
ignored diagnostics: build/link-seat-current/slow-gate{,2}.log. Resume with a
new ABI/compiler-shape explanation; do not repeat these two source forms.
No link improvement, function coverage, data row or closed-strict gain claimed.
