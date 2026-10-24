# Audio request-set allocator constructor link repair

BFME2 input 9ce3e39c2b, published census 268f876e3b (retail-truth-4).
Verified BFME1 pointer 32774ab03393 remains current; no donor change or new
application identity is introduced. This follows the request-set identity
repair and the rejected suppression trials in audio-request-proxy-link-20261023.md.

StlSweepW4Rva00056BFE.cpp's /Oy- context emitted the referenced
`_STLP_alloc_proxy<void **, void *, allocator<void *> >` constructor as
`558bec8bc18b4d0c89085dc20800` (14 bytes). The kept provider and 70 other
indexed copies emit `8bc18b4c24088908c20800` (11 bytes). Both simply store the
second argument in the stateless allocator proxy and return the receiver.
There is no retail address for this constructor; this is copy reconciliation,
not a new retail attribution.

An ordinary inline specialization keeps the original base construction and
pointer store visible. A scoped optimize("y", on) supplies the shared frame
omission only for this definition; the TU's flags resume immediately afterward.
Unlike the prior declaration-only and imported-forceinline trials, resize
remains the complete exact 197-byte body at 0x00056BFE.

Paired current-object checks, with the same published index:

- Before: 0/197 bytes link, solely the referenced constructor copy conflict.
- After: 197/197 bytes link. This is **+197 legacy scoped predicted linked
  bytes**, not a fresh census or closed-strict gain.
- Both states pass build.sh and prepare-current: 1/1 body and all reference
  checks; strict reusable compiler receipts establish self evidence only.
- All 25 named code definitions remain. Only this constructor's bytes change;
  its relocations are empty in both states. The other 24 definitions have
  identical complete bytes and relocations. No new import or alias appears.
- The indexed cause sweep finds 72 copies: this was the sole differing copy.
  The resulting constructor matches the other 71 copies, including the kept
  Rva0002C7FD.cpp provider. EH verification finds no EH-bearing row.

Scratch paired logs, original source and object comparison are under
build/audio-request-proxy-seat/. No full link or census runner was invoked.

Separate read-only handoff: assetmanager_impl.cpp still holds 4059 nonpadding
bytes. Its integer-map iterator skip pin at 0x54DC7 reaches the audio request
pointer-key bucket helper 0x53EA8, which dereferences a key and then its +8
field. The current integer-map helper uses the integer key directly (59 bytes
versus native 47). Suppression would conceal the container-identity problem;
reconcile the iterator and its callers first. Its claim was released.
