Deque iterator comparison binding
=================================

BFME2 3c38116b6e; BFME1 00c2ffbb23e9154fbe9970954afacb04e4943dd7;
published census c7845fd6e7, 2026-10-21 15:41.

Rva0054FD83Destroy.cpp was held out by its non-retail out-of-line
operator!=<PodPayload20> copy. The rowed provider is retail 0x00169C80
in stlport_deque_destroy_pod.cpp. Both compare only the iterator current
pointer; no element type identity or application layout is newly inferred.
The established dllimport forceinline specialization retains that comparison
inside the native range loop and suppresses its losing COMDAT copy. The
import-ref gate finds zero named imports. A declaration-only trial instead
added an external call and exceeded the 33-byte range-loop row; it was replaced,
not landed. No row extent or baseline was changed.

Legacy link_check before: 0 -> 0 B, sole iterator comparison blocker.
After: 0 -> 118 B, LINKS, same frozen index. A search of the saved census
blockers finds no other unit with this name as a blocker.

./build.sh: 4/4 rows exact; string, float and import gates pass.
find_declared_unmatched.py: all definitions matched.
link_check.py --prepare-current: strict receipt preparation and byte gate pass.
This is a legacy preview gain; no closed-strict or full link-cycle gain claimed.
