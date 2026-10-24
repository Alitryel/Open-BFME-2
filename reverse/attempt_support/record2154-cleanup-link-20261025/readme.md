# Correct the record's existing string-cleanup binding

The construction repair exposed an unchanged code-identity warning in the
same unit's 53-byte record destructor at 2154BE. Its call at body+36 reaches
36410 in retail, the 133-byte StringBase<char>::releaseBuffer provider in
StringBaseWideReleaseBuffer.cpp. The old BFME_ASCII_DTOR_DECL switch instead
calls the real AsciiString destructor name, whose owner is the five-byte
tail-jump at 48BA39. A historical pin at 36410 hid that distinction from
masked byte checks. No pin is changed in this repair.

Drop only that per-unit switch. The existing shared AsciiString destructor
then expands normally and calls the actual releaseBuffer owner. A private
trial leaves all 14 ordinary matched bodies raw-identical and changes only
this one relocation name. Production independently decodes its native REL32
target as 36410. It keeps the existing four construction-provider bindings
from the preceding committed repair and introduces no private class view.

The prior PlayerAITypeSet attempt 65649 already found the same cleanup
correction in another view of this record, but its separate class-name
collision prevented linking. This unit has no such prerequisite. Earlier
AudioFileCache and Rva005C3A37Elem repairs 61558 and 64278 also establish the
supported shared-header switch behavior. Reference string semantics remain
at the already verified BFME1 pointer 0bf534ea7ccde110c456edb9cd2dd5dae823c953;
the actual target and provider addresses above come from retail/ledger evidence.

Normal byte checks pass 22/22 rows across consumer and actual release provider,
including six named imports. The consumer's two EH graphs are EXACT, its
frozen-file check passes, and the link preview still accepts it. Two unkept
AsciiString range-cleanup COMDAT copies differ only in relocation names and
are reported as unreferenced diagnostics, not selected providers. No extra
linking or recovered-C++ byte credit is claimed for this semantic repair.
