FadeInTextRender duplicate provider repair

The draw unit rva00596908Rva00596908Farm.cpp retained a second out-of-line
FadeInTextRender::LoadAssets definition from its reconstruction scaffold.
Rva0059675AInitialize.cpp already owns that virtual function at native
0x005967B3 (341 bytes). Remove the scaffold definition and its now-unused
address-named timing-global declaration, retaining the virtual declaration
and the draw body unchanged. The real provider uses the canonical
BfmeClientFramesPerSecond global. No layout or donor identity is inferred
from the link result; the existing WB slot and BFME 1 provenance remain.

Base checkout: 884f993895. Measurement: 2967eab33e, 2026-10-18 08:17 UTC.
object-proof.json records the index hash and paired findings with the same
two current objects substituted into that index on both sides. Before,
both units have a duplicate LoadAssets; the draw unit additionally has its
unresolved g_009BA4E8 and an unproven differing LoadAssets COMDAT. After,
both have zero findings. LEGACY local linked bytes improve 0 -> 822
(341 provider + 481 draw); no new authored C++ coverage is claimed.

Acceptance:
- link_check.py --prepare-current on both units passes 5/5 matched rows
  before and after, including all string, float and import checks. These
  are strict reusable compiler receipts, not a closed-strict link result.
- Ordinary paired local link_check.py reports both units LINKS after repair.
- All 11 retained external COMDATs have unchanged bytes, sizes and symbolic
  relocations; six unused COMDATs disappear and no COMDAT is added. The
  provider object is identical. Removed string/constants and AsciiString
  helpers belong to the deleted definition; the unchanged provider retains
  the corresponding dependencies. The native draw remains 481 bytes exact.
- eh_verify.py: both EH-bearing matched rows EXACT, no missing objects/debt.
- data_check.py --enforce and --converged: zero findings (nine converged
  addresses); frozen-file, class, CSV, new-variant and whitespace checks pass.
- place_bodies.py on both units: zero incidental bodies and zero pins.

Reproducer and strict before/after object/receipt snapshots are preserved
under ignored build/fade-load-assets-link. The census index/status, ledger
rows, pins, headers, flags, baselines and checks are unchanged. No full link,
closed-strict, placement or runtime improvement is claimed; no maintainer-only
runner was started.

Donor review: committed BFME 1 pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5.
Reviewed the donor's October 15 linking-transfer report and fetched official
master d348fca17814122303884ebe194cbc877a2c0bb0. Its latest ATL module-global
repair has no matching pair of BFME 2 units. This repair instead reconciles
two existing BFME 2 definitions directly. Another seat holds the reference
file claim, so the overdue verified pointer update remains outstanding; no
freshness success stamp was written.

Other triage: native bridge vertex-owner and tree-key range-vector/army-swapper
units already link with current objects despite their historical census
findings. Deleting the bridge donor helper changes both native caller bodies;
that trial was reverted, logged and released. MapMetaData, Script and GameInfo
families still have multiple live provider/dependency findings. The shared
ObjectID allocator repair overlaps other seats' live file claims.
