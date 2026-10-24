# AsciiString vector providers

Move the two existing vector<AsciiString> insertion and push-back rows from Upgrade.cpp to their complete retail-exact emission in XferAsciiStringVector.cpp. Genuine STLport operations and AsciiString cleanup retain their existing providers, ABI, layouts and compiler contexts. Upgrade keeps unrelated non-retail UpgradeCenter/UpgradeTemplate constructor blockers. The shared allocator-getter address was excluded before claiming, and the two independent deferred-destructor leads are foreign-claimed.

2 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **260 -> 493 B, +233 B
linked availability**; 1/2 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 16/16 matched across 2 source file(s). Strings, floats and
imports pass. EH verify: 4 row(s) with EH data (EXACT 4); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.
