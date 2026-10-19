GameInfo slot-provider consolidation, 2026-10-18

Paired current-object legacy preview against the same published census
(2d2ca9cd35, 2026-10-18 18:45, retail-truth-2): four blocked units, 0 linked
bytes, become one clean unit containing 6,983 nonpadding retail bytes. This is
not a closed-strict closure or a link.exe/full-game result.

The three existing getConstSlot definitions include two compiler-visible
copies needed for MSVC register preservation. getSlot has the same problem.
Plain inline coalescing loses that information and breaks callers. Consolidate
the matched slot-query operations and their callers into GameSlotApparent.cpp,
retaining exactly one visible strong native provider of each accessor. The
complete target slot/GameInfo layouts come from the already verified views;
the original apparent accesses and all target offsets remain unchanged.
The obsolete donor unit's two matched operations use these target views;
its unmatched ZH-layout providers and duplicate singleton definition retire.
TheGameInfo's existing data-ledger source moves with its actual definition.

Three STL cleanup conflicts then remain. TU-local imported forceinline
specializations preserve the unchanged STLport 4.5.3 cleanup implementations
and call-side analysis without emitting competing external copies. Declaration
only fails the two serializers; that trial was restored. With the visible
bodies, all 42 complete rows, four entire native EH graphs, 32 literals,
14 empty-string references and 22 imports verify. The current object has no
unresolved, duplicate, losing-COMDAT, wrong-selected or address findings.
Existing compiler-local label notes are re-derived from exact parent EH graphs.

Strict reusable receipts cover 40/40 old rows in three units and all 42/42
rows in the merged unit. The retired donor's include inventory is uncacheable;
its two rows pass the ordinary full byte gate, so no strict before/after
closure claim is made. Retired exports were checked against the same-index
reference graph: no newly missing matched foreign callers. Data enforcement
and converged-global checks report zero findings. No verifier, baseline,
shared header, symbol pin, alias, or generated source is changed.

Reference lanes refreshed at BFME1 91c5204c276f44faa1251ca03b52a11a19d43e51:
byte-identical queue empty; one previously attempted 25-byte fade lead;
lift lane reviewed; ZH cache inputs unchanged, match/packets refreshed with
no packets. Existing BFME1/native slot-query semantics are retained, rather
than treating donor layouts as target evidence. The native byte/relocation
and EH gates establish the final integration.
