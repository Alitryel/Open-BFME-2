# Existing tag-slot providers complete the Vslot Q lookup

Paired current-object legacy previews against published census 17918792f6
(2026-10-21 09:22) change VslotSmallBodiesQ.cpp from 0/263 to 263/263
nonpadding matched bytes linked. StaticTagInitializers.cpp stays 1385/1385.
No authored function coverage grows. This is not a closed-strict closure result.

Target evidence: DD8320 contains exactly 35 pointers followed by null. Each
pointer names an existing Rva007F0210 global in StaticTagInitializers.cpp;
its byte-matched native initialization wrapper passes that object's address to
the rowed setter 65D090. The setter writes all three words (0,4,8), the existing
class is 12 bytes, and each complete span is loader-zero .data. New data rows
record those existing definitions, without creating another name or datum.
The lookup's existing 12-byte view reads the third word as the requested ID.
Table order and every initialized relocation are checked against retail.

DD8280 points to the complete errorCode literal CE315C; DD8288 points to the
complete decodedSize literal CE313C. DD8310 already belongs to g_bfmeWhatBKG
in BfmeConv482.cpp, so the ID reader uses that real global through a char cast.
No new alias, pin, hard-coded pointer, split body or compiler setting was added.
The prior vslot-q-link-20261020 handoff identified these missing complete object
providers; this repair resolves them while retaining the original lookup TU.

Donor review: verified BFME1 revision 5987fd1b has the same three-word slot
view but extern declarations in StaticTagInitializers.cpp. Its data rows for
errorCode and decodedSize support the pointer/literal ownership pattern only;
all addresses, 35 table entries, layouts and initial values above are BFME2
proof. Address-derived names retain existing identity uncertainty. Official
BFME1 master was fetched as 3f00bbbe; retained pointer is unchanged because a
comparative full byte gate is still required before adopting those inputs.

Acceptance: normal build verifies 72/72 code rows, 38/38 data rows and six
literal references across consumer and provider; check_csv, data_rows --check,
data_check --converged and find_declared_unmatched pass. link_check
--prepare-current accepts both units with strict reusable receipts and normal
byte gates. Legacy check says both units link, 1385 -> 1648 B. Census/index/status
are unchanged; no full census or maintainer-only runner was started.
