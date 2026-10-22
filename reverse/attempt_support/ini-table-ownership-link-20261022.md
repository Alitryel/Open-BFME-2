# Thin INI parser linkage, 2026-10-22

Input b72af045b4; frozen census 08160bc2c9, 2026-10-22 17:08.
Paired current-object link_check of INIThinFieldParsers4_Rva001DFBC7Parse:
legacy 0 -> 214 linked bytes, four blockers -> none. Authored code coverage
and existing function boundaries are unchanged. No closed-strict gain is claimed.

Three pre-existing undefined global names now own their native data:

- VA BDD0B4: seven LookupListRec pairs (SUBTLE through CINE_INSANE and
  the null pair), 56 B, referenced by parser RVA1DFBC7.
- VA BDD1D0: eleven pairs (SCORCH_1 through SCORCH_9, RANDOM=-1 and
  null), 88 B, referenced by parser RVA1DFC09.
- VA DCAE84: five weather pointers, 20 B, referenced by RVA492F6A.
  Committed BFME 1 revision 42bba2ddbd5cb895d99293583891d3b7315fa49e,
  game/GameEngine/Source/GameLogic/System/WeatherData.cpp, independently
  supports the five-entry non-terminated array extent. Retail values are
  NONE, CLOUDY, RAINY, CLOUDYRAINY, SUNNY; adjacent pointers are excluded.

All values and pointer targets come from BFME 2 game.dat, not inferred
names. The data ledger's previously unowned inferred spans are not used as
array sizes. New data_rows entries verify each compiled extent and every
literal relocation against retail. Existing global spellings are preserved.

The stance parser's original StanceType push_back pin refers to the folded
ScienceType vector body at RVA2E01C6. Use the existing rowed ScienceType call
view, with identical four-byte enum representation and three-pointer vector
layout. This asserts only call ABI and relocation equivalence; no application
type identity is inferred. It adds no fold alias or pin.

Normal byte/data gate passes all four function rows and all three data rows;
find_declared_unmatched passes. Explicit strict provider preparation verifies
the consumer; LINK closure remains unmeasured. The unsplit sibling has only
unused extern declarations of these tables and already links; no sweep gain
is credited to it.
