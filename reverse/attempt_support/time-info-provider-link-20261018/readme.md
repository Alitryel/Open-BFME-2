STLport time-info provider repair, 2026-10-18

Same-index legacy link_check preview at index 1a1c90e405 (census c2c5ac8c27):
stlport_time_info_dtor.cpp changes 0 -> 253 linked nonpadding bytes (243B
owner plus 10B EH row). The three consuming time-facet units remain blocked
on independently differing string/iterator copies; none of their bytes is
counted. No closed-strict closure gain is claimed.

Target evidence: the exact existing _Time_Info::~_Time_Info provider at RVA
00007A00 is displaced by identical wrong copies in stlport_time_put.cpp,
stlport_time_put_wide.cpp and stlport_time_get_locale_ctor.cpp. The local
STLport 4.5.3 header view adds only an explicit destructor declaration, keeping
all fields and other bodies. Its source is the retained BFME1 64d369b90170
vendor header; the donor establishes the declarations, while the existing
owner and 22 preserved target rows establish byte/call compatibility. This
uses the declaration-only provider-binding technique reviewed in BFME1
c42f040f; no donor ABI or address is imported.

./build.sh on the four providers/consumers: 22/22 exact, literals/floats/imports
pass. link_check.py --prepare-current on the same set also passes with strict
reusable receipts; link closure is explicitly not checked by that command.
The ordinary paired link_check changes 0/4 -> 1/4 clean, 0 -> 253 bytes.
Local raw logs: build/seat-timeinfo-{before,after,gate,strict}.log.

The BFME1 pointer remains at the last retained inputs: the recorded update
blocker is unchanged (Rva0007DF07 ambiguous vtable DIR32). No freshness stamp,
pin, alias, data claim, census status or full link cycle changed.
