# Existing narrow-string providers

BFME2 input 5f7faf02a3; published legacy index 11b3872700 (2026-10-23
23:06, retail-truth-4). Ten existing rows move from the blocked narrow-string
unit to five existing complete providers. No C++, settings, names, aliases,
pins, types or layouts change. The source keeps its independent compare,
mutable insertion and mutable initialization blockers; prior declaration-only
suppression attempts are not repeated.

Provenance remains in source: the main helper family uses STLport 4.5.3;
float_format carries its existing STLport 4.6.2 num_put_float source attribution
and archive hash, compiled against the existing compatible 4.5.3 ABI headers.
No donor layout or implementation is imported. Reviewed the current BFME1
f5140c1c provider scan recorded under link_library_providers_20261023; no
same-named donor TU supplies a new local repair. Target row identities and
callee relationships remain the existing library claims, independently checked
by whole body, resolved relocation and allowed-symbol preflight.

Paired current-object legacy preview: 6/7 units link, 12,239 -> 12,644 B,
**+405 B linked**. The 18 B already present against the frozen index is
excluded. Existing ICF twins remain; this measures ownership/availability,
not newly unique code. No self-strict, closed-strict or full-image census gain
is claimed. Acceptance: 233/233 byte gates, strings/floats/imports pass;
EH 16/16 EXACT, zero baseline; six code-identity findings unchanged;
frozen definitions, CSV and whitespace pass.

Rejected transfer: swap<char*> at 0x000357A0 is byte-exact in
Rva00240000Load308050.cpp, but moving that unit earlier makes its unrelated
vector<char>::_M_fill_insert COMDAT precede the certified retail provider.
The identity check correctly adds divergent debt (kept verdict unknown).
Its row stays at the original source; the rejected-order diagnostic is saved.
This blocks only the transfer, not the already matched implementation.

Retained rows (RVA, extent, receiver):

- 0x000179B0, 41 B, Code/Libraries/Source/WWVegas/WWLib/stlport_money_put_long_double.cpp
- 0x0001B320, 42 B, Code/Libraries/Source/WWVegas/WWLib/stlport_float_format.cpp
- 0x0001B4E0, 152 B, Code/Libraries/Source/WWVegas/WWLib/stlport_float_format.cpp
- 0x0001B790, 39 B, Code/Libraries/Source/WWVegas/WWLib/stlport_float_format.cpp
- 0x00689600, 37 B, Code/Libraries/Source/WWVegas/WWLib/stlport_money_put_long_double.cpp
- 0x00015E80, 13 B, Code/Libraries/Source/WWVegas/WWLib/stlport_float_format.cpp
- 0x000160D0, 23 B, Code/Libraries/Source/WWVegas/WWLib/stlport_float_format.cpp
- 0x000199E0, 17 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_insert_aux.cpp
- 0x0001DA50, 20 B, Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_filebuf.cpp
- 0x004598CC, 21 B, Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp
