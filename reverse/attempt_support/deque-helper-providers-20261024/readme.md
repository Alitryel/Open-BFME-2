# Deque helper providers

Move a 40-byte-element iterator difference and E12 deque constructor helpers to existing linking consumers. Three rows cover 143 extent bytes, including a pre-existing 20-byte gen-alias excluded by the linked-byte metric. The baseline already includes 135 bytes beyond the frozen census; inherited gains are excluded. Four unchanged typed-callee blockers at 20A227, 7A7AA, 5F97BC and 54FEC8 were read in the attempt log, excluded without retries, and released.

3 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **736 -> 859 B, +123 B
linked availability**; 2/4 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 36/36 matched across 4 source file(s). Strings, floats and
imports pass. EH verify: 1 row(s) with EH data (EXACT 1); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.
