PeerResponse helper-copy blocker, 2026-10-20

BFME2 2c5c1dfc73, BFME1 0dc8a26a9c60; published retail-truth-2 index b73720bed9. MSVC 7.1 /GX /MD and the original source flags in the diagnostic patch.

OwnedRecord840Copy.cpp currently owns 984 nonpadding bytes, with competing char/wide _String_base destructors and vector<AsciiString> copy constructor. Baseline link_check remains nonlinking; no improvement is claimed.

Trial 1: declaration-only char/wide basic_string destructors plus vector copy constructor. Native PeerResponse destructor 0x38A063 inlines each string cleanup to test start and free; trial changes those to basic_string destructor calls, changing body and scoped EH locations. Trial 2 (attached): restore basic_string visibility, specialize char/wide _String_base destructors as dllimport forceinline with their original _M_deallocate_block bodies, retain vector-copy declaration. This still changes the PeerResponse destructor in the same way and loses exact scoped EH parent evidence. Two byte-gate failures; do not repeat these unchanged variants. No usable partial recovered body was produced.

Next prerequisite: preserve the original string destructor inlining/lifetime analysis while suppressing only emitted competing copies, then establish an actual kept retail provider for the wide base destructor. A nothrow-specific variant was not tested. All production source restored and original byte gate rerun before handoff. Claims released. No ledger/pin/verifier changes.
