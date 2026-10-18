Terrain parser data ownership, 2026-10-18

At BFME2 43cabf5c60, census c2c5ac8c27 (retail-truth-2), current INITerrain.cpp
has only unresolved TerrainType::m_terrainTypeFieldParseTable. Paired preview
uses the identical explicit unit and unchanged index: legacy LINKED 0 -> 333
nonpadding C++ bytes. No new C++ bodies, pins, aliases or optimization changes.

Target evidence: parseTerrainDefinition 200A65 passes C0C3A8 to initFromINI.
The native table has five16-byte entries and one16-byte zero terminator,96B,
ending at C0C408 where the next bytes start the TerrainObject string. The coarse
unowned data_ledger extent644 includes subsequent strings and is not a proof of
the array size. Field offsets8,C,10,1C,0 and all callbacks come from retail.

Class entry passes DBE340 to the rowed browser/index-list parser. Its complete
47 string pointers and trailing null occupy192B, ending at DBE400. All strings
are reproduced through their terminators; no source enum identities inferred.
The neutral BfmeTerrainClassNames name preserves that uncertainty. Writable
pointer storage follows retail .data. Existing static TerrainType member name
is independently established by the native INI caller and ZH table role.

Donor guide: BFME1 verified revision64d369b90170, inputs/reference/.../Common/
TerrainTypes.cpp provides the established Texture/BlendEdges/Class/
RestrictConstruction table role. Target adds TerrainObject and uses its own
layout and expanded classification list. No donor table bytes assumed.

Acceptance: strict reusable receipts before and after; code2/2, data2/2
(96+192B and all pointer destinations), EH EXACT2/2; declared-unmatched clean,
converged-data zero second names, check_csv clean. These are self-strict object
checks and a paired legacy preview, not closed-strict closure or actual link.exe.

Recovery reconciliation: upstream e6fae26dd3 independently landed the same
terrain tables. Keep its typed callbacks and terrainTypeNames definition;
the new explicit data row follows that existing name at DBE340. The +333B
preview above is historical evidence, not a further gain over that upstream
commit. Do not introduce BfmeTerrainClassNames as a second global.
