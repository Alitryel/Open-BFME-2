Int-key mapped-node ownership repair, 2026-10-20

Pathfinder's Rva002F1DA1Mapped tree instantiated STLport's generic node factory.
The link kept that wrong copy before the rowed pool-backed 002EF239 factory,
blocking StlportIntMapInsertFamily. Declare the factory specialization in
Pathfinder, matching the existing declaration in the insertion family. The
callee remains the same ledger name; it now binds to the existing verified
provider and its DBD4B0 pool, not the generic allocator. No address, layout,
alias or pin added. Rva002EF239CreateNode's pair<const int,int> _Construct also
had strong ownership despite competing copies. Mark its unchanged noinline
body inline so matching COMDAT selection handles shared ownership.

Paired published e7a7769fe5 (2026-10-20 18:36) legacy preview:
StlportIntMapInsertFamily 0 -> 4,898 nonpadding bytes; factory provider 0 -> 57;
combined +4,955. Pathfinder retains independent blockers, so none of its 49,548
bytes are counted. All retained COMDAT bytes/relocation digests are unchanged
in all three units. Insertion-family whole object is unchanged. Only the
wrong factory copy disappears from Pathfinder and the construction helper's
ownership changes in the provider.

Strict before preparation 156/156 rows across three units. Normal after gate:
Pathfinder 111/111 plus two data rows, provider 2/2. Strict after preparation
113/113 across the two edited sources; 125 string refs, 92 floats, 18 named
imports pass. New-variants, class gate, declared definitions, converged data,
diff and commit hooks pass. Self-strict object receipts with a legacy-index
preview; no closed-strict closure, census rerun or executable result claimed.
Authored C++ bytes +0.

Donor linking review remains 4483e88da1c2, with existing name/ownership repairs
as recorded in special-ability-frame-global-link-20261020. This repair uses the
already byte-proven BFME2 factory; no BFME1 layouts or values transplanted.
Same blocking factory has only two emitted copies in the index (Pathfinder
wrong, provider retail); one declaration removes its only competing cause.
t=9 model=gpt-6.1-sol.
