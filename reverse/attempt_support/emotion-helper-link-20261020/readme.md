# Local ForceEmotion conversion helper

At b7bccca1c1, published census b73720bed9 (2026-10-20 05:34),
EmotionTrackerUpdateRva004B0DAC.cpp was held by its competing external
fast_float2long_round body. The retail external owner remains AIUpdate.cpp,
RVA 0x0015F520, 13 bytes. ForceEmotion's existing inline x87 conversion
and semantics are unchanged; giving that helper internal linkage prevents
its unrelated out-of-line copy from competing with the owner.

Paired current link_check on consumer and owner: consumer 0 -> 115 bytes,
owner still blocked independently; total legacy preview 0 -> 115 bytes.
Both source units pass all 10 matched byte rows, literals and imports.
The consumer has a current self-strict receipt. No closed-strict placement,
full-link or runtime result is claimed.

Diagnostics: build/emotion-{link-before,link-after,byte,strict}.txt.
Also recorded the independent INIStatsRecordTextures 435-byte blocker:
imported forceinline DynamicVectorClass destructor preserved both rows but
created an unresolved EH import and retained the base deleting-destructor
conflict. The trial was restored and all its claims released.
