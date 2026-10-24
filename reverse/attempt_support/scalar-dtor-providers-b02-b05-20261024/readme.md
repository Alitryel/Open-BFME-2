# Scalar deleting destructor providers, B02 and B05

Seventeen scalar deleting wrappers and adjustment thunks leave blocked B02/B05 aggregate owners for thirteen already-linking class lifetime units. The independent wrapper at 0x003F4261 was excluded: its exact bytes still reference the locally unowned and uncertified Rva005FED52 destructor at an ICF-shared address. The preflight retains that wrong/unknown finding; its blocked verdict and claim release are recorded. Existing pins and aliases are unchanged.

17 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **3,900 -> 4,295 B, +395 B
linked availability**; 14/16 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 162/162 matched across 16 source file(s). Strings, floats and
imports pass. EH verify: 17 row(s) with EH data (EXACT 17); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.
