# Allocator-proxy swap provider selection

At 1d9f35562b, narrow-string and POD-vector instantiations emit non-retail
copies of the char allocator-proxy swap. The native 34-byte body at
0x00025AD0 is already emitted and fold-proven by stlport_vector_voidptr.cpp.
Declare that ordinary free-function specialization in the two library units
so their callers bind to the existing provider. No implementation, symbol,
pin, compiler flags or shared header changes.

Same-index paired legacy prediction (b73720bed9, 2026-10-20 05:34):
the four-file scope goes 0 -> 578 B. The voidptr provider newly links;
the other three retain independent blockers. No self-strict or closed-strict
link-cycle gain claimed. Exact scoped gate: 170/170; EH 11/11 EXACT;
find_declared_unmatched all definitions matched.

A third declaration trial in Rva00240000Load308050.cpp changed the matched
372-byte loader cleanup/control flow (one failure among 172 rows), so it
was fully reverted. Its competing swap copy remains a blocker for that
unit, but cannot displace the now-selected verified provider. Do not repeat
this declaration-only loader trial without addressing its escape-analysis
requirement. Existing matched loader source and bank remain untouched.

Target evidence is the existing native provider and relocations of verified
consumers. This changes link ownership, without inferring a new game class
or importing donor code. Current BFME1 donor linking review is recorded in
script-cleanup-link-20261020-codex3/readme.md.
