Render2D constructor cleanup repair (2026-10-21)
==============================================

Paired legacy link_check.py previews against census c7845fd6e7,
2026-10-21 15:41, using current objects:

- Rva0011C0F0Finish.cpp: 0 -> 211 linked bytes. Before, the only blocker was
  undefined BatchVector::~BatchVector. After, the unit links cleanly.
- Render2DClassReset.cpp: 2,495 -> 2,495 bytes, still clean.
- Render2DClassDestructor.cpp: 122 -> 122 bytes, still clean.

The constructor's native stores prove the vector header at +0x34. The
already-byte-verified Reset and complete destructor independently establish
vector<BfmeRender2DBatch> there, stride 0x74 and its destructor at 0x00119C00.
Replace the private BatchVector cleanup type with that existing STLport
specialization, declared out of line. The element view records only its
proven extent; this constructor never accesses an element. No new target
name, symbol pin or data address is claimed.

Use the provider's native allocator shim/static STLport settings. Without
those settings the vector base emits an imported node allocator and a
conflicting base cleanup. Forwarding the old private destructor with
forceinline/dllimport also leaves an undefined import in the funclet;
neither intermediate was retained. The successful source preserves both
ledger rows (202-byte constructor and 10-byte EH handler), and all checked
relocations/literals. No ledger range, baseline or gate changed.

Acceptance: build.sh passed 2/2 rows; eh_verify.py EXACT 1; frozen-file check
passed. link_check.py --prepare-current on constructor, Reset and complete
destructor passed all 29 rows and made strict reusable receipts. The three
current-object legacy previews are clean, total 2,617 -> 2,828 bytes.
Self-strict preparation is not closed-strict closure or a full link cycle;
no closed-strict gain is claimed and census/status are unchanged.

BFME1 linking guidance was reviewed at donor 00c2ffbb23e9154fbe9970954afacb04e4943dd7
(including bf91f4be's single Buffer cleanup provider). This local repair
uses BFME2's existing providers and layouts, not a transplanted donor layout.
The newer BFME1 pointer remains another seat's claimed update; existing
verified inputs were preserved and no freshness success stamp was written.
