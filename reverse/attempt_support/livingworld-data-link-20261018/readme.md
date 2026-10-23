# LivingWorld parser data and replay extension

At parent 343ab60169 the three current objects failed only on the undefined
data named in before.txt. Defining their actual inputs makes all three link:
72 + 18 + 26 = 116 matched bytes in the legacy link preview. The four code rows
and the data definitions have self-strict reusable receipts. This does not
claim closed-strict closure or a full-link result.

Native VA C39AF8 has two 16-byte FieldParse entries: "Sides", callback
6E2612 (RVA 2E2612), offset 0; "Bonus", callback 8138C7 (RVA 4138C7),
offset 0C; then a complete zero entry. The existing callbacks independently
establish the vector of sides and science-bonus store. Their named code and
full table relocations are verified, without adding pins. The old ctor view
uses the ModuleFactory::ModuleTemplate POD as an emitter; this repair does not
promote that view to the semantic identity of the LivingWorld data.

Native VA C39D54 is one FieldParse with null name and callback 813C02,
zero userData and offset. Rowed findFieldParse at RVA 2BC27 establishes that
this null-name entry ends traversal and supplies an unmatched token as the
callback's fourth argument. No extra zero padding is claimed as a sentinel.
The callback's row and WB evidence already identify reinforcement scheduling.

Native RVA 81875C is the complete UTF-16 ".BfME2Replay" filename extension.
Returning UnicodeString from the wide literal removes its undefined datum;
the normal string-reference gate verifies the complete literal and terminator.

Acceptance: link_check before and after, --prepare-current (four function
rows; sizeof and all relocations of 48-byte and 16-byte data definitions;
string, float and import checks), check_csv and frozen-source checks.
The converged-data and code-identity checks also run in the commit hooks.

The shadow data check reports one old-ledger type mismatch: C39AF8 was
recorded from an incomplete scalar extern, whereas the sole definition is now
a const three-element array. No other source declares either old or new
symbol there. C39D54 retains its exact scalar spelling. The generated broad
data ledger was inspected via build/field-data-link-seat/data_ledger.csv,
not replaced with unrelated current-tree changes; no baseline was expanded.

This repair uses native table bytes and already established callback identities.
It imports no BFME 1 layouts or addresses. The reference revision reviewed in
the preceding diagnostic-table repair remains unchanged.
