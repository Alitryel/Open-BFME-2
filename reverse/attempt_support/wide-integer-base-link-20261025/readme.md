# Bind the last two wide integer parsers to their native base scanner

The signed-64 and unsigned-long _M_do_get_integer instantiations at A560
(260 bytes) and AAB0 (252 bytes) called an undefined narrow-character
_M_get_base_or_zero instantiation over the wide stream iterator. Their
complete native REL32 calls at body+36 both reach A0F0, whose existing
523-byte owner is the wide-character instantiation in
stlport_wide_get_base_or_zero.cpp.

Use that actual wide instantiation explicitly, following the already repaired
wide long and unsigned-64 sibling sources. The fourth parameter is a type
selection tag, not an output buffer: the provider and STLport 4.5.3
vendor/stlport/stl/_num_get.c both leave it unnamed and unused. The provider
builds its own five-wide-character atom array and performs wide comparisons.
Thus passing the existing pointer through a wchar_t pointer cast introduces
no read, write, buffer-size or alignment assumption about its pointee.
The callers' existing signatures, punctuation handling and layouts remain.

Prior attempt 14 established the wide provider's atom width, stack size and
ctype<wchar_t> do_widen slot from retail. Reference code supplies algorithm
structure; the callers' native destinations and the full verified provider
supply the actual binding evidence. BFME1 remains at the already verified
0bf534ea7ccde110c456edb9cd2dd5dae823c953; no freshness update is due.

Fresh original-source compiles and production objects have identical whole
body bytes and all relocation names except one intended callee change per
caller. The native targets are decoded independently in proof.json. No
new pin, alias, instantiation row, header or compiler setting is introduced.
The old candidate pin is left unchanged and is no longer needed here.

Normal byte verification passes all three caller/provider bodies. Both
changed sources have strict reusable current receipts, and both frozen-file
checks pass. EH and placement follow-ups are recorded separately. The paired
preview holds the provider at 523 linked bytes while both consumers move
from zero to their full 512 bytes. This is existing code predicted linkable,
zero new C++ coverage, and no claim of a new census or executable smoke test.
