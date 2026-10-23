# SlowDeath complement result ABI

At BFME 2 92609eef98, the 46-byte helper at RVA 0045D859 already matched as an explicit-output-pointer member. Its only live call at 0045E2EE used an independently pinned return-by-value spelling, leaving parseDeathFlags unlinked. Correct the provider signature to the existing consumer contract and return the local complemented value normally. The ordinary MSVC 7.1 hidden-result ABI emits the same two copy-constructor calls, 76-byte local, 19-word NOT loop, destination return and RET4 as native. No caller source changes are needed.

This is a signature correction of the same placeholder member and owner, not a newly asserted method/class identity. The superseded decorated signature is tombstoned; the existing by-value pin is removed now that a real provider owns it. No alias, optimizer hint, explicit destination assumption, extra wrapper or shared header is needed. The obsolete placement-new helper is removed.

## Evidence and rejected approaches

retail.txt records the complete helper and the caller prefix. The guarded-static initialization passes E034F8 as destination and E03548 in ECX; native calls copy constructor 00045455 both into the local and into the destination. The by-value source exactly reproduces all 46 bytes including both relocations. Code-wide search finds the live caller plus an unused same-signature declaration in the split phase parser; no remaining consumer uses the retired explicit-output signature.

The prior slow-death-link-20261022 and slowdeath-callee-link-20261022 handoffs tested caller-side wrappers. They either added another 76-byte temporary or changed the caller register allocation. Their original caller remains intact. This attempt tests the independent provider-side representation instead. It passed on the first by-value trial with the existing /MD flags.

The BFME 1 pointer reviewed is 138757e9b74645fbcbb7724a7af2764e34931e11. Its current SlowDeathBehavior.cpp contains only the external parseDeathFlags declaration and field-parse registration; it adds no independent proof of this helper signature or name. The argument/return relationship and exact instructions here are target evidence, not a borrowed donor identity.

## Validation and scope

Focused build: 4/4 rows exact across provider and unchanged caller.
EH: 1/1 exact, no missing objects or baseline debt.
Strict prepare-current: both explicit providers accepted with reusable receipts.
Paired legacy preview against published index 456ce161c5 (2026-10-23 06:28): provider 46 -> 46; caller 0 -> 251; total 46 -> 297 linked bytes.
Declared-definition and pin-consistency checks pass; pin count falls by one.
place_bodies finds zero additional bodies and zero pins.
No newly recovered code bytes, closed-strict link claim, runtime claim, or full census update.
