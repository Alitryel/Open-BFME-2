# GameSpy list-map link repair, 2026-10-18

Base: 78329b8e0c; census c2c5ac8c27 (2026-10-18 11:36), retail-truth-2.

The tree unit used an opaque class derived from list<AsciiString>. Its implicit
copy is an 18-byte thunk, incorrectly pinned as the actual 88-byte list copy at
0x54D800. Replace the wrapper with the actual list type and rename the existing
rows, removing six obsolete pins. Declaration-only specializations make the
pair/subscript and preferences consumers use the rowed tree providers.

Identity evidence: native GameSpyLoginPreferences nick/clan maps and the existing
list-map subscript at 0x5CAC49 establish the mapped list type. The tree's retail
pair copy calls AsciiString copy at 0x365F0 and list copy at 0x54D800; its node
allocates 24 bytes, constructing the eight-byte pair at +16. Whole-body bytes,
relocations and EH data verify the canonical instantiations. Existing neutral
address-based typedef labels remain; no new source identity is inferred from
byte placement alone. STLport remains the semantic source.

Paired legacy prediction uses the same four current providers, in this order:

- Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_hint_005ca999.cpp
- Code/Libraries/Source/WWVegas/WWLib/stlport_string_list_pair_construct.cpp
- Code/GameEngine/Source/Common/GameSpyLoginPreferences.cpp
- Code/Libraries/Source/WWVegas/WWLib/stlport_list_asciistring_insert.cpp

Original sources and ledgers: 1/4 link, 222 bytes. Final: 3/4 link, 1,369 bytes.
Gain: 1,147 bytes (tree 931, pair/subscript 216). The unchanged list provider's
222 bytes already link with current preferences and are excluded from the gain.
The preferences declaration is a verified prerequisite for these two units;
preferences itself still has independent tree destructor/erase/allocator blockers.

Self-strict preparation verifies 66/66 rows, string/import/float references;
EH verification is 18 EXACT, zero exceptions. Ordinary builds pass 10/10, 4/4,
52/52. find_declared_unmatched, check_csv, pin_consistency --check and diff checks
pass. This is a legacy link prediction with self-strict receipts, not a measured
closed-strict result. No full link cycle or census was run. No authored C++ byte
growth or new rows is claimed. The existing funclet parent/object-symbol follows
the canonical instantiation and its verified EH graph.

BFME1 linking donor review: verified pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5,
upstream reviewed through 8619c4c56d73cfeb7beb7d7dd87e4fbde47b01da. Reviewed native
helper/type reconciliation in 67f4eab2, 4040498c, af83a425, 991da24d, 21c98eb4,
81dc7af4, 5aace43d, c42f040f, 0ee8de1e, 4b285d7b, df1e180d, e6200339 and 9f0d845f.
Existing matching repairs are inherited or inapplicable to remaining BFME2
blockers. This repair applies the supported native-type/provider pattern locally,
without importing BFME1 layout or addresses. No donor pointer update: freshness
remains blocked by the previously documented DIR32/PrimaryBase failures in
reverse/attempt_support/bfme1-freshness-20261018/readme.md.
