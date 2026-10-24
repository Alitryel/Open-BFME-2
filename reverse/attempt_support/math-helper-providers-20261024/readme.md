# Math and inline helper provider ownership

Move six existing rows out of blocked units into currently linking exact providers. Retain the source rows needed for valid source ownership and retail COMDAT selection.

6 existing rows move to existing consumer units already emitting the same
complete named retail body and resolved relocations. No source, flags, pins,
aliases, class names, ABI or layout changes. Original identities and uncertainty
remain as recorded. The receiving copy establishes no new donor identity.
BFME1 review reuses verified f5140c1cff6a58e16276fd6de6788186286953d4 and the
provider survey in link_library_providers_20261023; inputs are unchanged.

Paired refreshed legacy link_check: **65,566 -> 65,823 B, +257 B
linked availability**; 9/15 units clean before/after. Index 11b3872700
(2026-10-23 23:06, retail-truth-4). Inherited gains against the frozen index
are excluded. No unique C++, self-strict, closed-strict or full-image census
gain claimed. No census or full link cycle run.

Preflight: complete bytes/relocations exact, zero unresolved and zero wrong
allowed-symbol bindings for every moved row. Functions: OK 257/257 matched across 15 source file(s). Strings, floats and
imports pass. EH verify: 16 row(s) with EH data (EXACT 16); 0 not exact, 0 in baseline; 0 row(s) without an object; 0.2s
Shadow identity findings unchanged (paired logs); frozen definitions, CSV
and whitespace pass. No baseline edited. Commands: link_check.py --refresh
--paths-from before/after; build.sh on touched units; eh_verify.py --sources-from;
code_identity_gate.check; find_declared_unmatched.py; check_csv.py; git diff --check.
Rows, exact paths and measurements accompany this note.

Excluded transfers (original owners restored and claims released):

- Scale at 0x00074643/133 B would leave shattersystem.cpp with no matched
  row. Preserve the substantial reference source and its remaining row.
- SphereClass constructor at 0x0006A52F/36 B is dynamesh.cpp's first RVA.
  Moving it changes link order and keeps wrong shattersystem copies of
  MaterialInfoClass::Add_Vertex_Material, DynamicVectorClass<VertexMaterial*>::Add
  and MeshMatDescClass::Peek_Single_Material.
- Matrix3D constructor at 0x0004C91A/101 B is JetAIUpdate.cpp's first RVA.
  Moving it selects FlightDeckBehavior's wrong Thing::isAboveTerrain.

These bodies already match; the ownership moves need prerequisites. Rejected
identity diagnostics are retained. The final six-row move has exactly the same
27 shadow identity findings as its baseline. Restore operations were byte-
verified through add_match; corresponding log entries retain their chronology.
