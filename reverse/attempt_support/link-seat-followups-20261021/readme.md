Link repair follow-ups, 2026-10-21

Inputs: BFME2 d317a046cd plus Floor repair 593972c277; BFME1 verified
cea1e9734dc0c5355613b61226fe3cc2faab4aa4; published legacy index e20daa4e78.
All attempted source changes below were restored. All claims were released.

SceneSpatialRescale_Unresolved.cpp (197B parent 141F90, 10B EH handler,
8B cleanup): current paired preview remains 0/207B. Its only legacy blocker
is _Slist_base<int>::~_Slist_base. A member extern-template declaration
suppresses native inline cleanup and fails the parent byte gate. A class
extern-template declaration retains 3/3 exact rows but still emits the same
conflicting destructor, so it makes no linking improvement. The existing
retail 9B destructor at 6FB50 uses /O1 /Ob0; this optimized caller also needs
inline erase. A real provider reconciliation must preserve both behaviors.
The restored source passed 3/3 again. No candidate body was worth banking.

Rva001499D0Cluster.cpp: consider moving only the 64B single-array forwarder
149A10, which still needs unrowed 16B680, so the 50B two-array forwarder1499D0
and standalone 57B149BB0 can link through newly rowed16BF40. This remains a
hypothesis, not a measured repair. The published index lacks the new provider
Rva0016BF40DeformedVertices.cpp, and the paired preview refuses to measure it.
refresh --current-ledger refuses 10,951 providers without current compiler
evidence. No edits were made. Fetching the index returned the same publication;
retry after a new published index instead of rebuilding the census.

Local diagnostics: build/link-seat-scene/{before,gate1,gate2,after,restored}.txt
and build/link-seat-mesh-{before,current}.txt. The facts above suffice to avoid
repeating these trials if the local artifacts are unavailable.
