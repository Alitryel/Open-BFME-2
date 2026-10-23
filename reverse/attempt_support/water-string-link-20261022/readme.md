# Water loader string-provider trial, 2026-10-22

Current legacy preview: 0/2362 bytes on differing unowned narrow string-base
destructor and const-char constructor copies. Apply the proven BuddyThread
inline-only destructor plus declaration-only cstr constructor. The 2306-byte
LoadPCAFile stays the same length, but frame grows 0x240 -> 0x244 and several
local slots move; two rowed funclets also differ. Saved patch and first-difference
report allow reproduction. This confirms the shared caller-temporary wall seen
in PeerThreadStats_PackStatKey, so do not repeat the identical suppression on
other units without a compiler-visibility hypothesis. Original restored and
25/25 byte verification rerun. No source or pins landed. Inputs BFME2 66c176bd18,
BFME1 37c3022de1ab944c7ffe536440d637dc8199091c, census 08160bc2c9; flags unchanged.
