# AptPlayer search binding, 2026-10-20

Input: 040ab04fc7. Census b73720bed9, 2026-10-20 05:34,
retail-truth-2 legacy predictor. Same-index current object checks change
AptPlayer.cpp from zero to 4,005 linked matched bytes. The census's stale
source-byte total differs; 4,005 is the actual checked unit's result.

Retail HandleOverButtons (633 bytes at 0x00224F6C) calls the rowed
StringBase<char>::find(char) const at 0x0002C459 from 0x0022508E. The
shared AsciiString header's find wrapper delegates through exactly that
one-pointer StringBase view. Express that direct call at the existing
movie-path dot search. This removes the callable AsciiString::find copy
whose selected implementation was not retail's. There is no new layout,
method identity, pin, alias, compiler flag or header change.

This sweeps the supported GameInfoSetMap repair documented in
reverse/attempt_support/gameinfo-find-20261010/README.md. The underlying
BFME 1 provider-binding lead (5f05cce4e52a5f69608af60cc2bfa2a8e78d9187)
is applicable; the target call above independently establishes the actual
provider. Current donor pointer remains a2c8039e61ad4dfb20c095d8eafe048248d31f25.
PeerThread is the other census consumer of this name and has 93 blockers;
changing its one wrapper alone would not constitute a measured repair.

Original and final bounded preparations pass 50/50 full-byte rows with
strict reusable compiler/include receipts, including the six compiler
funclets resolved through their complete parent EH graphs. The final staged
code-identity gate finds zero new issues; EH is EXACT 16/16. Frozen-file and
normal commit gates pass. This is a legacy predictor gain backed by strict
byte evidence for the changed unit, not closed-strict closure or additional
authored C++ coverage. No full link cycle or census was run.
