# Seven getter data bindings

Seven existing six-byte getters move from ConstIntGetters5Addr.cpp back into
ConstIntGetters5.cpp. Each returned immediate is the address of an already
byte-verified data table. Its new DIR32 reference names that exact owner:

| Getter RVA | Existing table owner |
| --- | --- |
| 001DAF77 | g_00C15468 (CommandButton table) |
| 001DCC3F | DrawGroupInfo::s_fieldParseTable |
| 002009F5 | TerrainType::m_terrainTypeFieldParseTable |
| 0026EDB1 | g_00BFA6E8 (UpgradeCenter table) |
| 002C8E5A | g_00C00B48 (WeaponTemplate table) |
| 00309E1E | GlowEffect::m_fieldParseTable |
| 0035C959 | CrateTemplate::TheCrateTemplateFieldParseTable |

The data ledger and the defining units supply the provider names; native leaf
bytes independently supply the returned addresses. The original getter names,
classes and integer-versus-pointer return types remain unknown. Existing opaque
names and integer ABIs stay unchanged. Static-data-only declarations assert no
instance layouts. Three providers retain their existing address-derived global
names; this change neither adds another datum nor renames an existing owner.
No pins, alternatenames, code/data extents or verification exceptions are added.

Normal add_match replacement verified every existing row. All 87 rows in the
two family files pass the complete byte gate. A bounded strict preparation also
verified 121 bodies across both consumers and nine candidate table providers,
plus all 25 declared data rows in those units. No other source was compiled by
that preparation and it wrote no census status.

Two initially considered bindings were rejected: getter0040C344's C18D18
provider has pre-existing duplicate/retail-wrong selected data definitions;
getter0041F71A's ArmyDefinition provider has an unresolved destructor and other
COMDAT blockers. Their original literal bodies remain in the split unit.
These independent provider failures do not affect the other seven tables.

The final link preview refreshes both sides of the move and all seven retained
providers together against the published census at d5ae1ce9c2. The getter home
and all seven providers say LINKS. Home's linked bytes rise360 to402 (+42).
The split unit retains20 unrelated raw addresses and remains nonlinking; that
expected residual is why the nine-unit diagnostic exits1. Omitting the split
peer from a preview would leave stale duplicate getter definitions in the
index, so the paired result is the authoritative comparison here.

This is linking repair, with zero new C++ coverage. No claim is made about a
new global census or whole-program closure. The published census/index/status
are untouched. Bindings and before/after reports are preserved alongside this
note; successful publication is required before releasing the seven claims.
