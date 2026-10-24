# Do not report unmeasured units as linked

Reproduced at BFME2 `605cde0e4a`, using the published provider index updated
2026-10-24 10:28 at `2fbdec0868`. Its recorded blockers still belong to the
measured census of 2026-10-24 02:54 at `268f876e3b`.

`tools/link_rank.py --file Code/GameEngine/Source/GameLogic/AI/AIPlayerQueueSupplyTruck.cpp`
reported `1595 matched bytes, links`. The unit is absent from that census:
the ordinary `link_check.py` correctly refuses to preview it. The ranker used
`found.get(path, ())`, treating a missing entry like a measured empty blocker
set. A typo had the same false-success path. Owner-gap mode also silently
substituted an empty set for an absent requested file.

The ranker now requires a requested file to exist in the recorded blocker
map before any report mode runs. Absence prints an unknown link state and
returns 2. A known empty blocker set remains a successful historical result.
The normal ranking also counts current matched units missing from the census;
139 were missing in this checkout. Their absence creates no inferred blocker
list or link success in the JSON export.

All report modes identify the measured census separately from later provider
index updates. Blocker maps, diagnostics and metadata are read from the same
loaded snapshot. The existing owner-gap JSON schema and ordinary rank JSON
map are unchanged. This changes discovery reporting, not retail-truth rules,
compiler evidence, link admission or census records.

The stale-date distinction matters in practice: current normal checks showed
wide_ifstream, the LightningDraw constructor, ScriptEngine destructor,
MapCache clearUnseenMaps, GeometryInfo constructors and AptScriptFunction
constructors already linking despite their recorded blockers. No gain for
those existing repairs is attributed to this change. The narrow_num_put
candidate still fails on the documented narrow range-initializer name bound
to wide RVA 0xBF90 (prior attempts 82778 and 83115); no suppression or native
source change was retained.

Validation: the new regression file fails 7 tests and passes 1 on the original
ranker. After repair, all 112 tests across the snapshot, owner-gap, link-check
and unreferenced-diagnostic suites pass. The live new-unit example now returns
2 and reports unknown, while a normal ranking shows both timestamps. The
unreferenced-diagnostic test now supplies a complete in-memory snapshot, so it
does not accidentally read the host's real census.

No new C++ bytes or linked-byte improvement is claimed. No pin, alias,
baseline, shared header or verification rule is changed.
