Time-facet string provider repair, 2026-10-18

Same-index ordinary legacy link_check on four time-facet/provider units:
before 1/4, 253 linked nonpadding bytes; after 2/4, 819 bytes. The NEW gain
is 566 bytes, all stlport_time_get_locale_ctor.cpp. The prior 253-byte
_Time_Info provider repair is not counted again. Both time_put units retain
their deferred ostreambuf_iterator assignment blockers. No closed-strict
closure gain is claimed.

These three units emitted the same differing basic_string<char> destructor
copy. Declare that specialization before locale instantiates it, as existing
stlport_narrow_ostream.cpp does, to bind to the retail 14B RVA00142D70 provider.
No throwing contract, inline allocator implementation, fields, pin or alias
changes. The complete 20 target rows and their EH relationships remain exact.
A declaration after <locale> was refused C2908 (already instantiated); moving
it before <locale>, after <string>, passes. This does not retry the recorded
inline-only allocator teardown variants in unrelated callers.

./build.sh: 20/20 exact across three touched units, literals/floats/imports
pass. link_check.py --prepare-current: the same 20/20 exact with strict reusable
receipts, explicitly no link-closure check. The ordinary paired measurements
use index 1a1c90e405 / census c2c5ac8c27. Source declaration guards pass.
Local logs: build/seat-time-string-{before,after,gate,gate2,strict}.log.
BFME1 donor64d369b90170 is unchanged; provider binding is inherited technique,
not an imported BFME1 body or ABI. No census/status or full link cycle run.
