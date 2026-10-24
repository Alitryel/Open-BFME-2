# String range insertion provider

Move the existing 0x28820 insertion row into BfmeConv1461.cpp, whose recovered counted-insertion caller already emits it exactly. The earlier identity and full twelve-relocation receipt remain in string28820-recovery-20261020 and string-insert-callers-20261020/v21.md. Both compiler contexts reproduce the whole row; the original replacement owner retains its separate erase/replaceBase blockers. Current retail-truth-4 checks show the receiver links; earlier evidence of mutable-copy link failure predates that rule. No identities, constness claims, code or compiler settings change.

1 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **149 -> 886 B, +737 B
linked availability**; 1/2 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 3/3 matched across 2 source file(s). Strings, floats and
imports pass. EH verify: 0 row(s) with EH data (); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.
