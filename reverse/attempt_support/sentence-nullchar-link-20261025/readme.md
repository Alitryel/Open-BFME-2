# Bind the sentence renderer to the existing string terminator

The renderer unit Rva00155AD0.cpp declared a private StringClass::m_LeadByte
that nobody defines. Its inline constructor reads that byte once in the
2821-byte Render body. The source already uses the real m_EmptyString owner.

Target evidence, independent of the proposed name: the DIR32 relocation at
body offset 1764 resolves to VA 00E08C18, after subtracting its object addend.
The matched data_rows.csv entry owns that exact one-byte address as
StringClass::m_NullChar in wwstring.cpp. That provider defines the zero byte
and initializes m_EmptyString to its address. No second datum is introduced.

Reference evidence: BFME1 revision 0bf534ea7ccde110c456edb9cd2dd5dae823c953,
game/Libraries/Source/WWVegas/WWLib/wwstring.h lines 399-402 and wwstring.cpp
lines 20-21, declares and uses m_NullChar for this constructor. BFME2's
corresponding existing wwstring.h and wwstring.cpp agree. This donor was
already refreshed with paired full verification; no new reference update
was needed. Earlier local attempt 67114 concerned now-resolved global and
COMDAT blockers and did not establish a separate lead-byte datum.

Correct the consumer declaration and use to the existing provider. This is
a binding repair, not a rename of an owner, a new pin, an alias or a new
recovered function. Both the complete 2821-byte renderer and 47-byte caller
are raw-byte identical before/after. All their relocations are identical
except the single intended m_LeadByte -> m_NullChar binding. Compiler-local
cleanup labels renumber normally; the full parent EH graph remains EXACT.

Verification: normal source gate 7/7 existing rows, three float literals,
one strict reusable provider receipt, frozen-file check, and EH 1 EXACT
with no baseline or missing objects. The existing wwstring provider is
also checked by the normal byte/data gate. Paired current object previews
against the same published index keep wwstring at 626 linked bytes and
change this consumer from zero to 2877 nonpadding linked bytes. This is a
prediction for existing code, not new C++ coverage, a fresh census, or an
executable boot test. All kept-provider and COMDAT checks pass in scope.
