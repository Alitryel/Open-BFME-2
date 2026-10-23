# Terrain cap donor removal, 2026-10-23

At d4fa46f19a, retail-truth-4 index refreshed from b711de3634, the current
W3DTerrainTracks.cpp object loses its pinned addCapEdgeToTrack donor copy:
the Zero Hour view does not reproduce BFME's complete 793-byte native body.
That body is already rowed and byte-verified as
Rva00084206Track::addCapEdgeToTrack in W3DTerrainTracksBind.cpp. Both native
callers (W3DModelDrawReactToTransformChange and W3DModelDraw_setHidden)
already call that rowed owner. This change removes only the incompatible
unrowed donor definition and its present-unmatched annotation. The donor
source remains available in the reference checkout and git history.

Bounded legacy preview before: terrain 0/202 nonpadding bytes; both callers
and provider link 4240/4240 bytes. After: all four link 4442/4442, gain 202 B.
These are current-object legacy results, not self-strict or closed-strict
cycle measurements. No new C++ coverage, pin, alias or vtable claim is made.
The normal byte gate passes 7/7 functions and the one data row, including
renumbered parent-bound EH cleanup. Strings, floats and imports pass.
Frozen-definition check and check_csv pass; strict reusable receipt preparation
re-verifies the same 7/7 rows and data row. New-variant admission passes.
