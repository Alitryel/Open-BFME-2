# Reconcile independently landed link repairs

Publication fetched origin/master `4719955641` after the shared cooldown.
Three independently landed repairs overlapped this session's unpublished
changes: pointer-vector accessors (`af6384ec15`), scalar/diagnostic definitions
(`2b105dafb9`), and the XML entity table (`b24fdfd515`). Git merged the separate
insertion locations without diagnosing duplicate C++ definitions. Keep the
overlapping upstream source definitions, removing the duplicate local insertions.

Their historical paired legacy gains total 764 B (283 + 385 + 96), already
present upstream. Retain the independent proofs with explicit overlap notes;
claim no incremental gain for them. Keep the three new byte-verified data rows:
four-byte native scalar, 32-byte diagnostic allocation, and 40-byte XML table.
The diagnostic includes 29 string bytes through NUL and three padding zeros;
the data gate required updating our row to upstream's full allocation extent.

This reconciliation is a publication prerequisite for the virtual-base
repair (+1,019 B legacy prediction across three newly clean units), and for
retained earlier archive-directory (+246 B) and prerequisite-vector work.
Upstream also independently landed Coord3D allocation changes (+2,387 B) and
prerequisite size helpers (592 B of the original local 729 B experiment);
keep their source spelling without counting those gains again. Push-back
still has a selected-copy blocker after upstream's size fix. Retain only the
local narrow instantiation, measuring its remaining 137 B against the actual
upstream object. The full gate exposed the duplicate push-back size
specialization (C2995); remove it, retaining upstream's existing definition.

The frozen census is c2c5ac8c27. Self-strict receipts establish object currency;
legacy predictions do not establish closed-strict closure or executable linking.
No census or maintainer-only verification runner is used. Local preparation,
full byte-gate output, and final measurements are under
`build/link-reconciliation-20261018/`; final results are recorded separately.

Final bounded acceptance: 101/101 code rows and three data rows (76 B) pass;
all 23 providers have strict reusable receipts. After retaining the narrow
push-back instantiation, reverify its cohort: 7/7 rows. `push-proof.py` compares
upstream's current strict object against this final source: 64 incidental
COMDATs removed, 19 retained exactly, no added or changed COMDAT, all retained
nondebug bytes/flags/definitions/symbolic relocations identical, every reachable
removed name's kept provider unchanged. Paired legacy prediction: 0 to 137 B.
The 23-unit CLI preview moves 20/23 clean and 5,075 B to 21/23 and 5,212 B.
The two archive units retain their recorded independent STL blockers.
The virtual-base paired proof also reruns successfully at +1,019 B.

Class, declared-unmatched, new-variant, converged-data, CSV, path-case and diff
checks pass. Enforcing shadow data identity reports the same three vbtable
wrong-name findings proved unchanged by the virtual-base before/after objects.
No closed-strict gain is claimed.

Full gate: all 96,606/96,606 code rows pass, plus 30,794 literals, 2,137 empty
string references, 8,081 float literals, and 6,182 named imports. Cross-source
DIR32 consistency refuses `??_7Rva005E394EPrimaryBase@@6B@` at three bases:
0xBC6F20, 0xC77BE8 and 0xC7A630. `dir32-upstream.json` records seven relocation
witnesses and proves the six units, their canonical header and the code ledger
are unchanged from origin/master. No check, whitelist or class source is
modified to hide it. After that known failure the unrelated full data phase was
interrupted (exit 130); the full gate is NOT recorded as passing. The earlier
Apt missing-object report disappeared once the duplicate helper compile error
was fixed and the complete code compile finished. The blocker is recorded with
re_log.py for subsequent class repair.

`progress.py origin/master` reports +0 authored C++ bytes and unchanged census
metrics; these link repairs do not update the published census. Frozen-index
legacy predictions and the exact code/data checks above are the evidence.
