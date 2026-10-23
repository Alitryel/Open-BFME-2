# Fade-transition parser: table and constructor ownership

Follow-up to transition-table-link-20261022.md, at BFME2 3c9c7ce84e.
Current legacy preview of S5ParseThenRegisterWide_Rva0035D0DC.cpp fails on
an unprovided BFME1-address vtable spelling and unprovided scalar FieldParse.
The matched native factory is 35D0DC..35D133 (87 bytes), not the donor's
59FB50 address or 157-byte extent still quoted in the old source macros.

The native call at 35D0FE reaches 35D097, whose existing row is the 58-byte
Rva0035D0D1 constructor. Its 0x28-byte allocation and complete provider view
establish the fields used by the factory. Reuse that exact class view and
call its existing constructor; no duplicate constructor or vtable datum is
needed. The original class name remains unresolved. Keep the factory's
existing identifier and ledger identity; no row/pin renaming was attempted.
The historical pinned donor constructor name remains untouched.

Native C16428..C16478 is the complete 80-byte table: StartFrame/parseInt/10,
EndFrame/parseInt/14, ViewsToFade/parseBitString32/18 with DBA1F8 user data,
LeaveSilent/parseBool/1C, and the null record. Native DBA1F8..DBA208 is
Tactical, World, Shell, null. The next pointer at DBA208 begins an unrelated
NONE/HOLD/KILL/SPAWN list and is excluded. All callback/string/data
relocations and both extents pass data_rows --verify. These identities,
offsets and extents come from retail, independently of the imported donor.

Byte gate passes 3/3 including EH artifacts; strict --prepare-current source
receipt, check_csv and find_declared_unmatched pass. Current legacy preview
against published 08160bc2c9 (2026-10-22 17:08) improves factory 0 to 87 B;
paired unchanged constructor/destructor providers retain 169 B, so cohort
169 to 256 B. The 169 control bytes and EH artifacts are not gains. This
small unit belongs to the same verified table-ownership sweep as the prior
207 B pair. Self-strict source verification is established; closed-strict
closure remains unmeasured. No full census or maintainer-only runner used.

Data identity shadow checks still carry the old scalar table spellings;
the new data_rows entries record the actual array symbols, exact native
extents and relocations. No baseline or verifier was changed.
