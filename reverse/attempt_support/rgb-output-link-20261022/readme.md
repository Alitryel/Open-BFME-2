RGB output link repair, 2026-10-22

Base: 71564a9349; published census ae3b3e68e2 (2026-10-22 11:05 UTC).

Rva0055C0E1.cpp emitted a non-retail _M_put_num<char, char_traits<char>, long>
COMDAT alongside its three rowed bodies. The independently rowed numeric worker
at RVA 0x0055C000 belongs to stlport_narrow_ostream_put_num.cpp. These are the
only two indexed emitters. Declare that specialization without a body in the
RGB unit and explicitly instantiate its already-rowed use_facet lookup, which
otherwise disappears with the unused helper. No names, pins or layouts change.

Paired commands (same census and current RGB object, before/after):
  python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/Rva0055C0E1.cpp
Before: non-retail numeric worker COMDAT, 0/203 bytes link.
After: zero blockers, 203/203 bytes link. The unreferenced setstate diagnostic
remains exempt under the current rules. This is a legacy scoped preview gain,
not a closed-strict measurement or an updated census.

Acceptance: build.sh 3/3 exact with all three string literals verified;
link_check --prepare-current gives a reusable self-strict source receipt;
find_declared_unmatched and new-variants checks pass. No authored-byte growth.

The same commit includes the independent map-bound failed-trial handoff; that
source was restored and its claims released. It contributes no linked gain.
