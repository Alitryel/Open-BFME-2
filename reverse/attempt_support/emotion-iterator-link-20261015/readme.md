# Snapshot and INI iterator emission repair

BFME2 base: `97b6eebb8086bb75212d2d8ce0d52aa841bce573`.
The two affected consumers are `Code/GameEngine/Source/Common/Rva004DD489Xfer.cpp`
and `Code/GameEngine/Source/Common/Rva00423FD8Parse.cpp`.
A TU-local typed tree-iterator inequality preserves the existing node comparison
and suppresses each consumer's conflicting external base-iterator COMDAT.
No flags, layout, class declarations, data owners, headers, pins or ledger
claims change. The established target identity evidence remains unchanged;
this emission repair establishes no new identity or layout.

## Evidence and measurement

All 89 retained COMDATs in the snapshot and 71 in the parser have identical
bodies, extents and relocation digests. The removed shared comparisons are
unreferenced by nondebug code. The only added sections are respectively two
and one unreferenced, private 12-byte typed comparisons. All other normalized
nondebug sections, external bindings, linker directives and data facts are
identical. This includes the parser's EH and unwind sections, normalizing
COFF symbol indices and local labels by their actual targets.

Paired previews refresh the saved old and current objects into independent
copies of one frozen published index. Receipt: `825b86983f`, 2026-10-15 12:37;
underlying census: `5986a99448`, 04:52. SHA256:
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
The discovery status at `28269d8e8d` is older and is not credited as a new
measurement. No index, census or committed status was rewritten.

Current-object local findings decrease **29 to 28** for the snapshot and
**17 to 16** for the parser. Paired JSON asserts exactly the removal of each
base-iterator comparison finding, with no other finding change. Their existing
nonpadding authored bytes are 399 and 426. Legacy predicted LINKED stays
**0 to 0**. New authored C++ bytes: **0**. Strict object receipts and byte checks
do not establish self-strict or closed-strict placement gains. No full census,
link cycle, nightly or boot runner was invoked.

## Acceptance

- Before/after bounded `link_check.py --prepare-current`: 1/1 snapshot and 2/2
  parser rows exact, strict reusable receipts. No dependency expansion.
- Normal `./build.sh` on both sources passes 3/3 rows, four string literals and
  two empty references; zero float and import discrepancies. The parser's
  existing parent EH record correctly resolves unwind label $L7968 to $L7981.
- `eh_verify.py`: parser EXACT 1, no baseline exception; snapshot has no EH.
- `data_check.py --enforce`: zero findings in either consumer. Converged checks:
  eight addresses, zero second names and unjudged rows. Paired data facts equal.
- Default local `link_check.py` exits 1 as expected with remaining blockers;
  paired comparison proves the reduction. New-variant checks pass for both.
- Class gate, declared-definition checks, whitespace check and `check_csv.py`
  pass. Affected-unit placement rescans return zero bodies and zero pins.

The snapshot still has other losing iterator, pair, allocator and map helpers,
and five wrong-selected providers. The parser retains five unresolved imported
STLport functions, ten COMDAT conflicts and one wrong-selected provider. These
providers and their other consumers are unchanged. Exact remaining names are
in link-after.txt and link-proof.json; they need separate supported repairs.

## Blocked trial and donor review

MapCacheWriteCacheINI.cpp was claimed and tested first. A typed tree/list
comparison trial and then a tree-only trial both changed native yes/no pointer
branch selection in the 1503-byte writer at offsets 0x20C, 0x228 and 0x244.
The failed tree-only gate is saved here. Source was fully restored, bounded
strict preparation passed again, the blocker was logged, and the claim was
released. No false reject is asserted. Do not retry without a supported
compiler-shape explanation. MilesAudioCache has an existing unresolved
funclet-label false reject; it was inspected but not claimed or retried.

Reviewed BFME1 repair `66b19a8e95a4add525ef808fcea088e306798e2b` and current
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` (inline/import suppression).
The local typed comparison pattern is already verified in other BFME2 units;
this patch independently proves it for both affected consumers and imports no
donor layout, source or address. Official donor master was fetched at
`c3c5a59620585b5752df5861abfd7979010f485b`. The verified clean checkout/gitlink
remains `a7c38d3b2597121f178ab5190b3062478823257d`. Another worker owns its
reference scope. The stale successful-check stamp was not advanced: prior
old-input full verification needed 2982 stale TUs and remained incomplete with
2806 after 21 minutes. That unchanged verification blocker prevents the pointer
update; a bounded local repair uses the last verified inputs.

Lane discovery ran repair_queue.py link, link_rank.py (rank, near and per-file),
then fetched the published index. Several tree-comparison entries already have
local overloads, so were not retried. Unrelated reverse/zh_sweep work is preserved.

Proof scripts are saved evidence, not production tools. Run from the root in
object, link, data order while scratch build/emotion-iterator-link-20261015
old objects and this frozen index remain available. JSON/logs preserve the
results without committing objects. Both file claims are released on completion.
