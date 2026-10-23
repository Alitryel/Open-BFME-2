# Science-vector hash resize link blocker

Baseline legacy-index preview: stlport_hash_map_int_vector_sciencetype.cpp
(244 bytes) and its _subscript.cpp sibling (189 bytes) both fail solely on
their identical, non-retail hashtable::resize COMDAT and selected provider.
The existing pin is 0x53F1EC, the 184-byte Armor map resize owner. Neither
unit has a resize ledger row. These are unchanged sources at 0cbe358230,
using BFME1 a2c8039e61ad4dfb20c095d8eafe048248d31f25 and MSVC 7.1.

The normal compiled resize is 222 bytes and has EH-prolog/frame cleanup;
native 53F1EC..53F2A4 is 184 bytes with a normal frame. Both use the same
bucket construction, next-size, allocator and swap calls, but native frees
the temporary storage directly at 0x30830. The emitted value uses no
ScienceType-specific element operation, consistent with the existing pin's
structural bucket-relink identity; exact folding remains unproved here.

Tried the import-inline vector<void*> destructor and _Vector_base destructor
bodies from the verified FXListStoreParse provider. Moving allocator<void*>'s
declaration before the inline base destructor is necessary to avoid C2908.
Then made allocator and allocator-proxy destruction inline empty, as their
reference definitions are empty. With the actual unit's /O1 /G7 /arch:SSE
flags, the best diagnostic still emits 215 bytes and __EH_prolog; it is not
a repair. The adjacent patch preserves that diagnostic only. Initial scratch
288/271-byte results used /O2 and are not comparable to the real unit.

No tracked game source was changed. No alias, pin or exception contract was
added. Remaining independent lead: the declaration-only vector<void*>::swap
leaves a potentially throwing call after temporary construction, unlike an
inline visible reference body. An evidence-backed provider/exception-visibility
repair is needed; do not merely suppress resize without a real provider.
Local logs: build/hash-science-before.txt, build/hash-resize-diff.txt and
build/hash-science-variant{3,4}.txt. File/RVA claims released after recording.
