# String range-initializer provider repair

At BFME 2 parent faaeb851fb with census 08160bc2c9 (retail-truth-4),
wide_money_put_string.cpp emitted strong definitions for both the char* and
const char* two-argument basic_string<char>::_M_range_initialize overloads.
The ledger's retail owner is stlport_narrow_string_range_init_2arg.cpp.

Mark both specializations inline, retaining __declspec(noinline): their
bodies and the formatter's call boundaries stay the same, while their
emitted definitions become selectable COMDAT copies. This follows the earlier
narrow money formatter's provider repair. No pin or ledger entry changes.
A search of WWLib found no other remaining specialization with this exact
strong-definition pattern.

Paired legacy link_check.py calls explicitly included the wide formatter,
narrow range-initializer owner and locale_global.cpp. Before: only the locale
unit linked (364 B). After: the narrow range unit also links (465 B total).
The gain is **101 B**; the inherited locale gain is excluded. The wide
formatter itself remains blocked by unrelated providers/facet IDs.

./build.sh verifies all ten formatter rows, including eight EH funclets whose
compiler labels are relocated using the parent EH graph, and both narrow
range-owner rows. --prepare-current verifies the formatter's self-strict
compiler receipt. This is a legacy provider-preview improvement, not a claim
of closed-strict gain. find_declared_unmatched reports no undeclared bodies.

Local logs: build/link-wide-inst-{before,after,byte,strict}.txt and
build/link-wide-consumer-byte.txt. The original formatter is preserved locally
as build/link-wide-original.cpp.txt; the source diff is two inline specifiers.

Independent read-only triage: Rva00541EB8Dtor.cpp still passes all five byte
rows but calls a differently rowed narrow-record destructor after linking.
Retail's two calls go to 0x541E77; the named owner resolves to 0x41A200.
The 0x541E77 gen-alias has a different EH handler, so it is not an admitted
whole-body relocation twin. No alias workaround or source edit was made;
the blocker is recorded in re_attempts.log.
