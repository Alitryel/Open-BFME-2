# Diagnostic data ownership repair

At BFME 2 parent 3e633a1a53 the three current consumer objects failed the
legacy link preview solely on undefined diagnostic data. The current-object
baseline in before.txt excludes unrelated improvements since census c2c5ac8c27.
After the repair the same three units link: 66 + 67 + 57 = 190 matched bytes.
This is a legacy preview gain, with self-strict reusable receipts for the three
changed units; no closed-strict or full-link result is claimed.

Retail RVA 009A71A8 has 27 relocated pointers. Each points to the complete,
NUL-terminated diagnostic string at BBD9EC down through BBD480. The reference
STLport 4.6 inputs/vendor/stlport/stl/debug/_debug.c and _debug.h at verified
BFME 1 revision 64d369b90170b7e9ec917d646f020b11f13eb0d5 define exactly these
27 strings in this order and independently establish _StlMsg_MAX = 27.
The target indexed-error and verbose-assertion consumers select slots 0 and 2
respectively, with their indexed message arguments. These relationships establish
the table's diagnostic purpose and extent; they do not establish the original
template argument or identifier. The existing data-ledger donor placeholder
name g_bfmeTableSWA is retained. BfmeConv1304 now refers to that same global,
rather than declaring a second symbol for the address.

The data row verifies sizeof(table) = 108, all 27 pointer relocations and each
complete literal against retail. /GF pools the literals into compiler-named
COMDATs that the normal relocation verifier can place. Without pooling /Od
emits TU-local $SG names whose addresses the data verifier correctly refuses
to infer. All five existing code rows retain their full bytes.

Retail RVA 0086ABF4 is the complete string "challenge". BfmeConv1279 uses that
literal directly, as it already does for the adjacent "ticket" field. The
ordinary string-reference gate verifies both complete literals.

Acceptance: link_check --prepare-current (5/5 functions, 1 data row, both code
literals, import and float gates); link_check on all three units before and
after; check_csv; data_check on all three units reports zero findings. No
census, linker cycle or maintainer-only runner was launched.

Donor linking review: official BFME 1 HEAD 67f4eab2437e8a7ab3f22d3b3f9bf1eac91e081b
was fetched. Its ownership repairs (4040498c15/06a23066c and bit-count-table
21c98eb41) support checking a complete table and canonicalizing consumers;
no donor address or ABI was transplanted. The unchanged prior BFME 1 freshness
blocker remains recorded in bfme1-freshness-20261018: the old verified pointer
is preserved rather than accepting the known unrelated DIR32 inconsistency.
