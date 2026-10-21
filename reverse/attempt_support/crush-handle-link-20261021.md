# CrushDie counted-handle callback repair

At HEAD 5edfccaa91 with the published e20daa4e78 index (2026-10-21 21:42),
CrushDieModuleDataCtor.cpp failed the legacy preview only on undefined
AudioEventRTS::AudioEventRTS(). Its private four-byte declaration was stale:
the old 0x79514/0x793FA bodies are now identified as ShadowTypeInfo, not
AudioEventRTS. No AudioEventRTS default constructor is rowed under that name.

Target facts: the complete 82-byte constructor 0x2539B3 passes 4 as array
stride and 4 as count, with initializer VA 0x726BE6 (RVA 0x326BE6) and
cleanup VA 0x50F149 (RVA 0x10F149). These are the existing Rva0010F149Handle
callbacks used by other counted-reference fields. Its existing provider in
BfmeObject476Copy emits the whole six-byte initializer 8BC1832000C3 and
12-byte destructor 8B0985C97405E9........C3; the destructor relocation names
the rowed OpaqueRefCounted::Release_Ref at 0x50ED3. Those are the native
whole bodies and relocation target. This establishes the shared four-byte
lifetime/ABI, not the original referent type or an original class name.
The donor field name m_crushSounds is carried only as donor provenance.

Repair: use that existing opaque handle declaration for the four elements.
No callback implementation, pin, row, layout, optimization or gate changes.
Declaration-only callbacks preserve the native external-call EH behavior.

Acceptance: build.sh all 3/3 rows; eh_verify EXACT 2/2; frozen-source check
passes; prepare-current issues a strict reusable receipt for all three
rows. Paired legacy link_check previews: 0/168 -> 168/168 linked bytes.
This is +168 nonpadding bytes in the legacy preview, with self-strict
source verification. No closed-strict closure or measured census gain is
claimed. Other AudioEventRTS default-constructor consumers were inspected;
they use larger event layouts and do not share this four-byte callback
cause, so they are not part of this repair.
