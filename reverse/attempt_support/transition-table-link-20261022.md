# Transition parser table ownership and constructor binding

At BFME2 025f02303e, both parser units fail the legacy current-object
preview: Rva0059D1F0AttackNuggetFactory.cpp (126 B) lacks its field table;
Rva0059EE10AttackNuggetFactory_Rva0035D48A.cpp (81 B) lacks an integer
vtable spelling and an empty field-table spelling. The published comparison
index is 08160bc2c9, 2026-10-22 17:08. These are current-object before/after
predictions, not the stale ranked census counts.

Retail factory 35D35D passes C164B0 to INI::initFromINI. That complete
64-byte table has StartFrame / parseInt / 0 / 10, EndFrame / parseInt / 0 / 14,
FadeInUnfrozenSounds / parseBool / 0 / 18, followed by a null record. Native
string pointers, callback identities (2EF56 / 2E850), offsets, extent and
sentinel are independently verified. Retain the pre-existing neutral table
identifier with its corrected array type; record its actual array symbol
in data_rows. Original derived-class identity remains unresolved. Donor
factory source is semantic provenance only, not proof of the native table.

Native factory 35D48A calls constructor 35D45A and passes the null table
C6BB18. Both already have real row owners: Rva0035D47B::Rva0035D47B and
g_emptyFieldParseTable[4]. Use those declarations directly; the class view
matches Rva0035D47BCtor.cpp's 16-byte base and virtual destructor. This
removes the duplicate S4Built constructor and undefined integer-vtable
reference rather than introducing a pin or another data owner. No row or
existing symbol is renamed. The historical pinned S4Built spelling remains
untouched for other consumers.

Each parser passes its byte gate (4/4 and 3/3, including emitted EH bodies).
The 64-byte table passes data_rows --verify, including string and code
relocations. find_declared_unmatched and check_csv pass. link_check
--prepare-current supplies strict reusable source receipts for both units.
Legacy paired prediction improves 0/207 to 207/207 B. Including unchanged
constructor and empty-table providers, the cohort improves 50 to 257 B,
4/4 linking. The 50 control bytes and EH bodies are not counted as new gains.
Self-strict byte verification is established; closed-strict link closure
was not measured. No full census or maintainer-only runner was started.
