# FXListStore constructor link prerequisite, 2026-10-25

BFME2 input 22fcf20ea9; published retail-truth-4 census aa9aee26b4
(2026-10-25 06:47); verified BFME1 input
0bf534ea7ccde110c456edb9cd2dd5dae823c953. No donor pointer or header changed.

Current-object `link_check.py Code/GameEngine/Source/GameClient/FXListStoreCtor.cpp`
reports 0/109 linked authored bytes. The sole cause is the emitted FXList
hashtable bucket constructor selected against retail RVA 0x001E2F8E, 64 B.
Both COMDAT and selected-definition checks reject its actual non-retail body.
The three owned rows (0x001E3386, 0x001E33A5, 0x00769F7E) already match.

Two evidence-backed trials kept all three owned rows byte-exact but gained
zero linked bytes:

1. Add `/O1`, following the native size-optimized constructor provider.
2. Also expose the ordinary vector<void*> allocator constructor and its base
   constructor by removing their two explicit-specialization declarations.
   `visible-vector.patch` preserves this trial relative to the original TU.

The second trial emits 72 B rather than retail's complete 64 B.
`hashtable-diff.txt` records the exact comparison. Retail calls the native
vector allocator constructor at 0x00025100 and uses the dead argument slot
at EBP+0x0B. The trial inlines three vector stores, adds EDI/frame space,
calls the allocator destructor at 0x00023A40, uses EBP-0x0D, and leaves the
typed `_M_initialize_buckets` unresolved (native call 0x00148DDF).
This is a real code-generation/dependency mismatch, not a false rejection.
The native 64 B owner is StlSweepW5Rva001E2F8E.cpp; its neutral element type
does not independently prove the FXList map value's identity or layout.
Do not alias those template names merely to silence the link check.

The production source was restored exactly; its normal byte gate passes
3/3 again. No source/ledger/pin change, new authored bytes, linked-byte gain,
self-strict gain, or closed-strict gain is claimed. Claims were released.
Resume only with new evidence for the vector-constructor visibility and
allocator temporary lifetime, or a supported reconciliation of this map's
value and initialization-helper identities.

Other scoped checks: name_globals dry runs on ConstIntGettersAddr.cpp and
ConstIntGetters2Addr.cpp offer zero rewrites. Refreshed-object previews show
the audio, vector-destruction, tracer constructor and basis-matrix repairs
already link upstream; their stale rank entries are not new gains. The
Rva001ECF66Finish.cpp empty allocator helper is a possible independent lead,
but claiming its 0x0021983A body was refused as held by another worker;
its file/parent claims were released without editing it.

The secondary `repair_queue.py link --limit 8` and
`link_rank.py --owner-gaps --near 2 --top 8` searches return the same stale
or prerequisite-bound leads above. Current previews leave the special-power
module blocked by three private vtables (222 B), LivingWorldBuildingCtor by
three missing class methods (298 B), HRawAnim constructor by two animation
vtables (149 B), and BW filter init by two missing object definitions (101 B).
Those filter tables also contain separately neutral-named owners, so adding
small partial class definitions would not establish correct native storage.
`class_views.py --blockers` likewise prioritizes already-repaired providers,
known string-emission failures, unrowed MemoryPool/INI methods and larger
class reconciliation. No unchanged deferred source trial was repeated.
`data_back_rank.py --bundle build/cycle_bundles --top 5` reports unavailable;
there is no matching published link-cycle bundle here. No census, full link
cycle or maintainer-only runner was started.

The complete read-only `rehome_rows.py --limit 30` search finishes with four
movable units: Rva004F6318EntryCtor, View_getPosition,
W3DBridgeGetModelVertices and RvaTreeInsertUniqueGenP12pod009282C0. All four
and their home units already link in the published census. Current paired
source previews additionally confirm the View, bridge and tree pairs still
link (3,624 B and 1,143 B respectively), so no zero-gain row moves were made.
`check_csv.py` passes (98,244 functions, 15,735 symbols, 2,208 data rows).
