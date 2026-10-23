# Caller-domain and copy-topology reassessment

Continuation at BFME2 eba848189d95832f39eb8aeb74399690a33cc957, unchanged
BFME1 138757e9b74645fbcbb7724a7af2764e34931e11, same retail image and
isolated OrbStack BUILD_POOL=1 runtime as readme.md. No external decoder
source consulted. Existing candidate.cpp.txt remains the best semantic bank.

## Independently checked retail caller evidence

AnyRatio_2D_Scale at RVA 001BACA0 loads the last-band callback from VA
00E22FC0 at 001BAD6D, stores it at stack +18 at 001BAD7B, and calls the
saved pointer at 001BAEE1. It pushes EDI (destination width), ESI (pitch),
EBX (band) at 001BAEDE..001BAEE0. The destination width is not range-checked
by this function; its earlier horizontal call also receives it unchanged.
AnyRatioFrameScale loads the post-processor expanded width at +70 at
001BAF3A. ChangePostProcConfiguration copies 14 caller-supplied dwords into
post-processor +40 with REP MOVSD at 001B67F6, including expanded width
at +70. The approved specs 001baca0, 001baf30, 001b67e0, 001b9410 and
001b56f0 agree with the configuration flow.

The stream header provides a concrete narrower path: at 001BD19C it calls
the eight-bit reader, MOVZX ECX,AL at 001BD1A1, doubles ECX at 001BD1AD,
then LEA EDX,[ECX*8] at 001BD207 and stores it to decoder +1E0 at
001BD20E. Thus that assignment produces width 0..4080, not a general
positive-width invariant. VP6_InitFrameDetails passes the configuration
at decoder +1B0 to ChangePostProcConfiguration, so +1E0 maps to +70.
This proves the bounded stream-derived assignment but does not prove all
configurations accepted through the separate caller-supplied configuration
path are bounded. No signed-overflow assumption or new domain guard was
introduced. Signed native SUB/JG fusion remains an open hypothesis only if
the full valid-input contract can be independently established.

## New whole-function expression trials

All trials use the original unsigned ABI and safe pre-subtraction comparison,
direct intrinsic vector assignment, /O2 /Oy-, no EMMS and no helper calls.

- Vector-pointer cursor, separately sequenced store and increment: 39 bytes.
  Band EAX is loaded before width EDX (unlike the old bank), pitch remains
  ESI, the preserved-width CMP and three-byte loop alignment remain.
  Bytes: 558bec8b45088b5510568b750c8d49000f6f008bca0f7f043083c00883ea0883f9087fec5e5dc3
- Independent source/destination byte cursors: 41 bytes. Band ECX,
  destination EAX, width ESI; two pointer ADDs remain, with separate CMP.
  Bytes: 558bec8b4d088b450c568b751003c1900f6f018bd60f7f0083c00883c10883ee0883fa087fea5e5dc3

An initial postincrement expression was discarded on language review because
it modified and read the cursor without sequencing; only the separately
sequenced trial above is eligible evidence. It produced the same bytes.

These are independent allocation/topology findings, not a claim every C++
expression has been exhausted. The MMX operations are already intrinsic and
the retail body has no callees; hidden callee visibility cannot account for
the mismatch. The current concrete blockers are the unrestricted-width
predicate contract and compiler register/flags scheduling, rather than an
unavailable MMX move. Original 31-byte production source restored unchanged.
Next candidate is the fixed eight-row CopyBlockMMX: no variable-width
countdown and a different four-load/four-store intrinsic topology.
