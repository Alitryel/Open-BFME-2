# Existing string-record helper providers, 2026-10-24

Ten existing STLport helper rows now belong to nine existing consumer units that already emit the same named complete retail-exact bodies. Source, flags, identity and layout claims, pins and annotations are unchanged. The Bfme record names remain emitter views with the source/ledger's existing uncertainty; no new application identity or complete layout is inferred. This ownership repair reuses existing BFME2 providers; the BFME1 donor revision reviewed remains f5140c1cff6a58e16276fd6de6788186286953d4.

Paired refreshed link_check on these ten units: **4,388 -> 4,720 B, +332 B legacy linked availability**, nine of ten units clean before/after. Row extents total 333 B; link_check's existing non-0xCC accounting excludes the one 0xCC byte at 0x361657+25. No new C++, unique bytes, self-strict or closed-strict gain is claimed. Index: 11b3872700, 2026-10-23 23:06; no census or full link cycle run.

Each preflight checks complete body bytes/relocations, zero unresolved relocations and zero wrong allowed-symbol binding. Scoped build.sh passes 191/191 with literal/import/reference checks; EH passes 29/29 exact. Frozen checks, check_csv and diff --check pass. Scoped shadow identity findings are the same eighteen before/after (paired logs included). The original collector remains blocked by unrelated selected COMDATs, listed in both measurements.

Commands: tools/link_check.py --refresh --paths-from build/link-ascii-record-providers-paths.txt before/after; build.sh on those paths; tools/eh_verify.py --sources-from; code_identity_gate.check; tools/find_declared_unmatched.py per path; tools/check_csv.py; git diff --check. Rows and exact paths are in rows.json and measurement logs.
