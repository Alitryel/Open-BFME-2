# Sun-ray setup storage and setter binding

At BFME2 15c0f8e450, Rva0009CD9BSunRaysSetup.cpp has five unresolved
providers in the current-object legacy preview: four float arrays and
the RefCountPtr-reference spelling of SegmentedLineClass::Set_Texture.
The 0x0009CD9B native body proves each two-float extent: it writes indices
0 and 1 while loading livingworld.txt, then reads a mode-selected entry.
Retail VA 0x00DE5E0C, 0x00DE5E14, 0x00DE5E1C and 0x00DE5E24 each
hold eight initial zero bytes in .data. Give the existing extern names
zero-filled storage and four data rows; no other owner was found.

Native 0x0009D49D computes this+0x1D0 and 0x0009D4C8 pushes that slot
address into 0x0015E250. That eleven-byte provider adjusts this by 0xDC
and jumps to 0x001911E0, which dereferences the argument before updating
texture reference counts. Bind the consumer to the existing rowed
TextureClass-pointer spelling, passing the slot address explicitly; the
provider's pointer spelling does not establish a pointee semantic type.
The RefCountPtr storage and native argument value remain unchanged.
No aliases, pins or new class identity claims.

Same-index legacy preview (b711de3634, 2026-10-23 14:28), with both
current consumer and segline.cpp provider: consumer 0 -> 1978 authored
non-padding bytes; provider 4590 -> 4590, total 4590 -> 6568.
This is +1978 B legacy prediction, not measured LINK closure.
--prepare-current receipts verify current code without claiming
self-strict or closed-strict link gains.

Byte gate: 3/3 consumer rows and 72/72 joint provider rows; EH EXACT
1/1. Four data rows, six string references, seven
float literals and twelve imports pass. Frozen-definition, ledger and
diff checks pass. No other unit uses this unresolved setter spelling or
these four array names in the current census/source sweep. BFME1 donor
96c88c73a5cd was reviewed earlier this session; this repair uses target
bytes and existing BFME2 providers, without new donor source.

Post-rebase at upstream 778d2ec547, the same explicit current-provider
baseline and repair again give 4590 -> 6568 B. Refresh the unwind row's
object-symbol from $L2515 to $L2516: the exact parent EH graph independently
places the renumbered action at 0x0076061C. This removes a shadow binding
finding caused by the obsolete label selector; no native extent changes.
The earlier local terrain-track commit a34d6be94c was dropped because
upstream 5445be3c4b independently isolated the same obsolete body. Its
+202 B gain is inherited and is not credited to this session.
