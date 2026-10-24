# FX particle template assignment providers

Sixteen existing 18-byte ConcreteModuleTemplate assignment rows move from
FXParticleSystemModules.cpp to FXParticleSystem.cpp, which already emits the
same complete named bodies and relocations. No source, flags, names, pins,
class views or ABI changes. Existing Open-BFME5 provenance is preserved;
this establishes no new donor identity or layout. The separate folded 5-byte
destructor aliases stay at their original owner.

Paired refreshed legacy link_check at index 11b3872700 (retail-truth-4):
5,061 -> 5,349 B, **+288 B linked availability**; 1/2 units clean before/after.
The wrapper unit retains independent constructor/deleting-destructor COMDAT
and selected-provider blockers. No unique C++, self-strict, closed-strict or
full-image census gain is claimed. BFME1 donor review reuses verified
f5140c1cff6a58e16276fd6de6788186286953d4 and the provider survey documented in
link_library_providers_20261023; no donor inputs have changed.

Acceptance: all sixteen complete bodies/relocations exact, zero unresolved
relocations and zero wrong allowed-symbol bindings. Scoped build.sh 584/584;
strings, floats and imports pass. EH: zero EH-bearing rows in these units.
Five existing shadow identity findings unchanged. Frozen definitions, CSV
and whitespace pass. No baseline edited or census/full link cycle started.
Commands: link_check.py --refresh --paths-from, build.sh on both units,
eh_verify.py --sources-from, code_identity_gate.check, find_declared_unmatched.py,
check_csv.py and git diff --check. Exact rows and paired logs accompany this note.
