# Pod264 hash search link repair

Base 70288b2283; published census 08160bc2c9 (2026-10-22 17:08).
Paired legacy preview of stlport_hash_map_int_list_pod264.cpp and its
_subscript companion initially links 0/425 bytes. Both instantiate a key-only
_M_find<int> with an existing fold pin at 2888D4. Declaration-only const
vector bucket access made the emitted search 53 bytes instead of retail's 47.
The subscript unit also forced vector::size out of line.

Imported forceinline specializations preserve the existing vector layout and
compile both complete searches to exactly retail's 47 bytes, with no relocations.
All 12 rowed bodies (8 provider, 4 subscript), literals, imports and frozen-file
checks pass. Paired legacy preview now links the subscript's 176 bytes; the
provider remains blocked on resize. This is not a closed-strict gain. The
provider edit is a verified prerequisite: without it the kept search copy is
wrong and the companion does not link. The saved census blocker map lists only
these two units for this search/resize family. No pins or aliases were added.

A declaration-only _M_find specialization hit MSVC C1001 at _hashtable.h:488.
An independent resize declaration preserved all eight provider rows, but changed
its blocker from wrong selected body to unresolved: its old 53F1EC pin has no
same-name provider. That trial was removed. A future provider repair must either
reproduce the existing canonical bucket resize or make _M_insert call that
real provider by its actual name while preserving bytes and ABI. A pin alone
does not provide a definition. The one-byte unreferenced _Destroy<BfmePod264>
diagnostic does not block linking and was left alone.
