# SquishCollide constructor binding

At faf0cd8770, SquishCollideOnCollide calls the DamageInfo constructor
spelling pinned at 0x00263895. All kept definitions under that spelling
are non-retail private views. The verified 45-byte constructor provider
already exists as Rva00263895Member in Common/RTS/Rva00263895Init.cpp.
Use that provider's receiver name for the existing 0x7C stack field view,
then cast its address to DamageInfo at the two Object::attemptDamage
calls. The byte gate proves the receiver address, field offsets, constructor
call and consumer ABI stay exact. No constructor implementation, layout,
pin, global, vtable or provider changes; no extra wrapper or alias emitted.
The placeholder class name does not assert recovered target identity.

The prior attempt in damageinfo-ctor-views-20261019.md renamed the
provider globally, creating duplicate definitions and missing xfer.
This limited caller binding leaves that broader reconciliation outstanding.

Same-index paired legacy prediction (b73720bed9, 2026-10-20 05:34):
SquishCollide 0 -> 1,152 B; constructor provider stays 45 B. Total pair
45 -> 1,197 B. No self-strict or closed-strict link-cycle gain claimed.

Acceptance: ./build.sh 2/2; eh_verify.py 1/1 EXACT;
find_declared_unmatched.py all definitions matched; diff check clean.
Source compiler flags unchanged. Original source cites ZH SquishCollide
at donor874e38488; this repair uses BFME2's existing provider/callsite
proof, not a donor layout change. Current BFME1 linking scan at0dc8a26a9
is recorded in the script-cleanup session evidence.
