# Existing hash helper providers, 2026-10-24

Eight existing STLport helper rows (224 B) now belong to six existing consumer units that already emit the same named complete retail-exact bodies. Source, flags, identity and layout claims, pins and annotations are unchanged. The BfmePod names remain the existing emitter views, without new application identity/layout claims. This ownership repair reuses existing BFME2 providers; the BFME1 donor revision reviewed remains f5140c1cff6a58e16276fd6de6788186286953d4.

Paired refreshed link_check on these seven units: **2,518 -> 2,742 B, +224 B legacy linked availability**, six of seven units clean before/after. No inherited gain is counted. No new C++, unique bytes, self-strict or closed-strict gain is claimed. Index: 11b3872700, 2026-10-23 23:06; no census or full link cycle run.

Each preflight checks complete body bytes/relocations, zero unresolved relocations and zero wrong allowed-symbol binding. Scoped build.sh passes 56/56 with literal/import/reference checks; EH passes 10/10 exact. Frozen checks, check_csv and diff --check pass. Scoped shadow identity findings are the same seventeen before/after (paired logs included). The hash collector's remaining selected COMDAT blockers are listed in both measurements.

Commands: tools/link_check.py --refresh --paths-from build/link-hash-record-providers-paths.txt before/after; build.sh on those paths; tools/eh_verify.py --sources-from; code_identity_gate.check; tools/find_declared_unmatched.py per path; tools/check_csv.py; git diff --check. Rows and exact paths are in rows.json and measurement logs.

Handoff: the initially considered five rows from stlport_vector_stringrecord_5ddd40_allocate_copy.cpp were excluded because another worker holds that source claim. All five unused RVA claims and both unused destination file claims were released; that source was not edited. The existing insertion-overflow family callee-identity blockers remain as recorded in vector-existing-provider-link-20261023.md; no unchanged blocked trial was repeated.
