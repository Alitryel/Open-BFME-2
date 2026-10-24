# Scalar deleting destructor providers, B04 and B14

Twenty complete scalar deleting wrappers and an existing destructor leave blocked B04/B14 aggregates for eighteen already-linking units. Four foreign-claimed rows were excluded. Candidate 0x005C4A75 was omitted: proposed provider Rva005C4A91Ctor.cpp emits it, but Rva005C4A91Dtor.cpp already links a distinct row over the same address; duplicate ownership needs separate identity reconciliation. Candidate 0x005AE76E was omitted: upstream 883172301f renamed its provider Rva005AE66BDtor.cpp to Common/AptMessengerOnline.cpp, which legacy link_check --refresh refuses as absent from published index 11b3872700. No index or source workaround was made. Both omitted claims were released and verdicts recorded; independent providers were remeasured with the corrected explicit scope.

20 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **7,909 -> 8,448 B, +539 B
linked availability**; 18/20 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 264/264 matched across 20 source file(s). Strings, floats and
imports pass. EH verify: 70 row(s) with EH data (EXACT 70); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.
