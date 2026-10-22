# Link-repair handoff, 2026-10-22

BFME2 base 896b220f7d; verified repair b68575f39f. Published index
08160bc2c9 (2026-10-22 17:08), BFME1 retained at verified gitlink
37c3022de1ab944c7ffe536440d637dc8199091c. Donor mechanism reviewed:
2483354a, canonical row-call binding; no donor layout was imported.

## Verified improvement

Rva000834CERva000834CE.cpp now calls the rowed
RenderableStandingWaterArea::AllocateAndFillBuffers at 0x8304A instead of
the old Rva0008304A view. The complete native caller 834CE..83547 establishes
the same thiscall target and ABI. Paired current-object legacy preview with
W3DWater.cpp changes the caller from 0 to 121 linked bytes. Its byte gate and
commit hooks pass. W3DWater.cpp still has independent duplicate cache helpers;
this is not a closed-strict or full-link placement claim. A preview against
the old index without the explicit provider still reports the new name as
unresolved. No new authored C++ coverage is claimed.

## Restored attempts

The five failed units are unchanged and all their claims released:

- StandingWaterAreaLoadPCA.cpp: constructor/base-destructor visibility changes
  parent stack allocation and EH cleanup identity. See
  pca-link-20261022/readme.md and its diagnostic patch.
- W3DHordeModelDrawSetModelState.cpp: declaration-only and visible imported
  vendor constructor both change stack slots and cleanup grouping. See
  horde-link-20261022/readme.md and its diagnostic patch.
- PeerThreadNickError.cpp, MainMenuUtils_hasWriteAccess.cpp and
  stlport_money_put_long_double.cpp: plain and extern-template constructor
  declarations fail the parent/EH gates. See string-ctor-link-20261022.md.

After restoration the combined byte gate passes 64/64 rows, resolves 49
funclet pins and two STL folds, and passes literal/float/import checks.
Do not repeat the same suppressions without a new compiler-visibility or
provider-selection explanation. Attempt log entries record each boundary.

## Queue audit and prerequisites

link_rank --top 30, --near 2, class_views --blockers and repair_queue link
were reviewed. Live probes of approximately 150 unheld near-link units found
many inherited fixes; none were credited to this session. In particular,
both quick-match option units already link (4869 B combined), as do the
current SlowDeath parser and ocean-water units. The old ranking is a lead,
not a before measurement.

The Rva00204BB8 heap provider lead is still refuted: the pin at 21D375 belongs
to the Rva0021B68D comparator family and calls 21C878, not this family's
206D33 adjust helper. Prior evidence remains valid; no edit or new attempt
was made. The word-vector resize blocker likewise retains the recorded
load-bearing Thai consumer dependency. Unrowed FESL/Miles callees remain
unrowed and their existing banks should be preserved.

name_globals --dry-run finds zero eligible edits. rehome_rows cannot inspect
placements because build/link_census/census.log is absent from the fetched
artifact; no census was rebuilt and this failure is not queue exhaustion.
No matching data-back measurement artifact was available. Large remaining
class contracts and unrowed callees need separate substantive work.

BFME1 freshness remains due: official fetched master was 704af04c, while
file:reference/open-bfme-1 was held by codex-bce2-01a11b23-root. The retained
verified pointer and previous freshness stamp were not advanced. Coordinate
that update through claims and comparative full-byte verification. This
session does not establish that all eligible link work is exhausted.
