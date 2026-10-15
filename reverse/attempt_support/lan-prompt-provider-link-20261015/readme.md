# LAN lobby prompt provider binding repair

BFME2 base: 78867b74343dab5920077a9f1d695c938fffd524.
Discovery: repair_queue.py link and link_rank.py serve the LAN lobby unit's
sole unresolved name, method@Rva0054D3D9Target. The existing 8-byte matched
provider is Rva0054D3E1Prompt::configure in Rva00437EDCFinish.cpp.
Bind the local caller to that provider, including its boolean return type
(the caller discards the result), and remove the obsolete pin. No matched
row, address, layout, compiler setting or replacement pin is added.

## Target evidence and provenance

Retail's 24-byte cdecl wrapper at 0x00437EAC calls 0x0054D3D9 with the same
receiver and three arguments. The 8-byte provider loads its child at +4
and tail-jumps to 0x0054D12A, the existing private configure method. The
independently matched AptMessageBox::Change consumer already uses this
provider spelling and boolean return type. proof.py verifies both native
REL32 destinations and the provider's child-load instruction and relocation.
The local wrapper's original identity remains unknown. This repair introduces
no additional donor identity or target layout assertion.

The same-cause search finds no other Code consumer of Rva0054D3D9Target.
The existing AptMessageBox caller needs no edit. Reference repair
 d003077f0b7ce97622adb7a53f1fe76653433c5c was reviewed: bind a caller directly
to the existing matched provider. Its ownership principle applies here;
its stream code, addresses and types do not. The earlier dedicated donor
review is reused; unchanged deferred reconstructions were not retried.

Clean verified BFME1 checkout/gitlink remains
 a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched as
 95eeb3bef370a7cd730b0ad5f228c317c8756e72. The live foreign claim on
reference/open-bfme-1 and the previously recorded incomplete comparative
full-byte verification still prevent the overdue reference update. No
freshness success stamp, pointer or donor input is advanced.

## Paired local acceptance

Index: ac77c85054, 2026-10-15 14:25; hash and BFME2 base in index-meta.json.
Both objects have current self-strict reusable compiler receipts. proof.py
refreshes exactly the same two prepared sources into separate in-memory
copies of the same index before and after. The sole unresolved finding
vanishes, with every other finding unchanged. Clean units rise 1/2 to 2/2;
existing nonpadding linked retail bytes rise 891 to 4134 (+3243). The
prescribed local link_check also reports both units LINKS. New authored
C++ bytes: zero. This is a legacy local preview, not a self-strict or
closed-strict census gain. No census index, status or history is changed.

The complete objects' nondebug section bytes, flags, definitions and symbolic
relocations are identical modulo exactly the intended callee name. The
provider object is byte-identical. No new variant or data finding; matched
rows' data bindings are identical. proof.json records all paired findings,
object and receipt hashes, target destinations and current receipt checks.

- Strict preparation before/after and ordinary byte gate: 42/42 rows;
  13 literals plus two empty-string references verified, none skipped.
- EH: 21 EXACT, zero nonexact/missing/baselined rows.
- Data enforcement: two sources, zero findings; converged enforcement:
  eight addresses, zero second names or unjudged rows.
- Local link, new variants, class, frozen-definition, pin consistency and
  whitespace checks pass. Affected-unit placement resweep: zero bodies/pins.
- CSV passes. Staged code identity runs in shadow mode and reports two
  existing findings: Rva00437E84 binding and the default TreeHintRef00217D4C
  constructor variant. Paired checks with the saved-before object reproduce
  exactly the same findings (identity.json); neither is introduced here.
  Ordinary commit/publish hooks remain required.

Saved original sources, objects and receipts remain under ignored
build/lan-prompt-provider-link-20261015/before. To reproduce, prepare the two
sources at the recorded base with --prepare-current and save their objects
and receipts there; retain the matching index, apply the repair, prepare
again and run proof.py from the repository root.

Broader closed-strict closure requires a new authorized measurement. No
maintainer-only census build/measurement, link cycle, nightly, boot or
scheduler operation was invoked. Unrelated untracked dump/sweep files stay
preserved.
