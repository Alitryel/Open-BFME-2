Registration table ownership, 2026-10-21

At BFME2 f2d6dacea8, against published legacy census d08db10acb, the
Rva007B4874Registrations unit was held out solely by four undefined
address-derived table names. Each initializer already installed that
name at the recorded retail table address.

Target evidence: native C63398/C745A0/C74698/C7475C contain two pointers.
The following object vtables start at C633A0/C745A8/C746A0/C74764,
independently evidenced by Rva005C4758Dtor, Rva005C4403Ctor,
Rva005C45B6Ctor and Rva005C4986Ctor and the existing data ledger. All
slot-zero pointers are the existing deleting destructor 005C43E7.
Slot-one factories are respectively 004FAC99/0052B58F/0052B5C6/0052B5FD.
Definitions reference those existing COFF code owners with __identifier,
as in TextureAssetGet and the existing data-only vtable repairs.
No new pins, aliases or class identities are introduced. The original
registration/factory class relationships remain unknown.

Verification: byte gate passes all 12 code rows, their EH graphs and all
eight table relocations (four 8-byte data rows). Four literal references
are exact. Current legacy preview changes 0 to 388 linked bytes.
prepare-current issues a self-strict reusable provider receipt; this is
not a closed-strict link measurement. Data-check has zero findings and
converged data has no second names. Authored C++ byte coverage is unchanged.
