# AptPlayer GameText singleton binding repair

BFME2 base: 07a4c16b6a8cd387cace77c72237b05fe7a26125.
The link queue and ranked census identify AptPlayer.cpp's only blocker as
`?TheGameText@@3PAVGameText@@A`. Nothing defines that spelling. The data ledger
and GameTextStringLookUpLess.cpp already own the singleton with the
`GameTextInterface *` type. Declare that global and cast its value to the
existing local virtual-slot view at the tooltip call. No new global, alias,
pin, matched row, class layout or compiler setting is introduced.

Target evidence: the 199-byte tooltip body at RVA 0x002238E6 ends at
0x002239AD with RET4. Its DIR32 operand at RVA 0x0022393A reaches VA
0x00DFF0BC (data RVA 0x009FF0BC). The existing data ledger names this address
`?TheGameText@@3PAVGameTextInterface@@A`, defined once as zero-filled data in
the unchanged provider. The call still uses virtual offset 0x38. Original
tooltip provenance and naming uncertainty remain as recorded in the ledger;
this repair establishes global ownership, not a new application identity.

## Paired acceptance evidence

The runner index measures ac77c85054 at 2026-10-15 14:25, SHA256
a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3.
proof.py refreshes exactly the same two prepared objects into independent
in-memory copies before and after. The sole unresolved name disappears;
all other findings stay identical. Clean units increase 1/2 to 2/2 and
existing nonpadding linked retail bytes increase 153 to 3286 (+3133).
The prescribed link_check also reports both units LINKS.

Both objects have self-strict current compiler receipts. The improvement is
a legacy local link preview; no closed-strict gain or new census measurement
is claimed. New authored C++ bytes: zero. The census index, status and history
are untouched.

proof.json records object/receipt hashes and verifies every complete nondebug
section's bytes, size, flags, definitions and symbolic relocations modulo
exactly the intended global name. The provider object is byte-identical.
Data facts are identical after normalizing that one name; its wrong-name
finding drops from one to zero, with no unread matched rows.

- Strict preparation before/after: 43/43 rows; 11 literals and four empty
  string references, one float and five imports verified; none skipped.
- Separate normal byte gate: AptPlayer 40/40 rows.
- EH: 13 EXACT, zero missing/nonexact rows or baseline exceptions.
- Data enforcement: zero findings. Converged enforcement: eight addresses,
  zero second names and zero unjudged rows.
- Frozen-definition, class and new-variant admission checks pass.
- Affected-unit placement resweep: zero bodies, zero pins.
- CSV, whitespace and normal commit/publish hooks are required as well.

The saved before sources, objects and receipts remain under ignored
build/aptplayer-gametext-link-20261015/before. To reproduce elsewhere, prepare
the two sources at the recorded base with --prepare-current, save their
objects and receipts there, retain the matching index, apply the source
change, prepare again and run proof.py from the repository root.

## Reference review and remaining work

Reviewed BFME1 repair 92a8d854746f059994f8ab370c133f3ba71eec24: bind debug-cell
consumers to the existing data owner through a local cast. Its ownership
principle applies; BFME2 retail operands, data ledger and compiled provider
independently prove this repair. No donor type layout, address or code is
imported. The prior dedicated donor review is reused; unchanged deferred
codegen candidates were not retried.

Clean verified BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched at
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Another worker's live reference-file
claim and the previously recorded controlled full-byte comparison blocker
still prevent the overdue update. No success stamp or pointer is advanced.

The same-cause search finds AptPlayer as the only Code unit declaring
`extern GameText *TheGameText`; no further consumer edit is needed. Both
touched-cohort units are locally clean. Broader closure remains unmeasured;
no maintainer-only census build/measurement, link cycle, nightly or boot runner
was invoked. Unrelated untracked dump/sweep files are preserved.
