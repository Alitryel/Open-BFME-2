# Existing provider binding repairs

At BFME 2 base be9e8b7b79ee, correct two consumer bindings without changing
retail behavior, layouts, pins or ledger rows.

- PlaceEventTranslator declares the existing voice response provider as bool.
  Both native calls reach 0x004DAAFD. Every initialized non-debug COFF section
  is unchanged; only the two relocation referents change from void to bool.
  The provider itself is unchanged. One unresolved symbol disappears.
- ObjectCreationList replaces an absolute IAT call with the real C import
  pointer. C identifier `_imp___strcmpi` emits `__imp___strcmpi`; the retail PE
  identifies msvcr71.dll `_strcmpi` at VA 0x00BBA518. The native 73-byte body
  at 0x001F07B8 retains FF15 at +14 and its DIR32 operand at +16. All 23 rows
  pass, including named-import verification. One address finding disappears.

Donor review: verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d
declares the bool voice ABI. Earlier BFME 2 voice-response-abi-link-20261014
already repaired the other consumers. BFME 1 0835ab92 supplies the real-owner
binding principle; import identity here comes from BFME 2's PE, not the donor.

These units remain blocked by unrelated dependencies: zero new linked or
authored bytes are claimed. Both source gates pass. The campaign's final
eight-source strict preparation verifies 174/174 rows; see the companion
link-inline-emitters-20261014 evidence for the combined receipts. Converged
data enforcement passes. The two existing PlaceEventTranslator static-data
wrong-name findings remain unchanged, as proven by its object comparison.

No full census, linker, boot runner or gate change was used.
