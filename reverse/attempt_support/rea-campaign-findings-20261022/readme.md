# REA campaign findings and stop handoff, 2026-10-22

The user requested publication of the findings and termination of the work.
The implementation task for fresh natural FESL integration was cancelled before
any source changes or fresh compilation. No background continuation is intended.

## Accepted verifier repair, published as a patch

`accepted-static-verifier.patch` preserves the reviewed implementation. It was
committed and hook-checked locally as 8949f1eb3e, but is NOT installed by this
findings commit. Publication as active verifier code selects 23435 providers
through flag_delta_sources and requires a broad build, which the user excluded.
This evidence-only publication does not claim to satisfy or bypass that gate.
The patch SHA256 is
44afbc8f2fe6b02410b2ae45aff213f6088d9ac1a7587421f0abd32d89390a2f.

The separate verifier implementation admits explicit source-scoped static
data rows without exposing their names as global relocation targets. It checks
datum size/content, immutable object identity, exact static relocation identity,
whole contributing function extent, one consistent address, and a source/object
bound compilation receipt. Historical nine-column ledgers remain readable;
current ledgers add a trailing linkage column. Unverified local bindings remain
inconclusive in differential execution. No baseline or refusal was relaxed.

Independent core and consumer acceptance reports are included. Parent focused
tests: 126 passed, 1 skipped. The broader targeted suite on the upstream-based
checkout: 221 passed, 8 skipped, 14 subtests passed, one pre-existing failure.
That empty-ledger test reports 10 data-only source orphans against a baseline of
6 after deliberately hiding their data ledger; the identical failure reproduces
with the original unmodified tools. Normal current and staged ledger checks pass
(98083 function rows, 15851 symbol rows, 2138 data rows at the tested revision).
Normal commit hooks passed. No link/census/fullbuild/nightly/boot runner was run.

## FESL result and remaining boundary

`fesl-natural-static-owner.cpp.txt` preserves the natural static-separator
candidate. Independent archived-object verification found the complete
549-byte body at RVA 0x00655B90 exact: 220 instructions, 11 relocations, and
505 non-relocation bytes. The separator is 0x0A at VA 0x00DD7F45; the 256-byte
class table is at VA 0x00CE0E20. Its ordinary donor loop uses no volatile read
or duplicated labelled store. Original source linkage remains an inference.

The old verifier's external-only rule rejected this static owner. Deleting the
data row to evade that check was rejected and the integration rolled back.
The verifier repair is now accepted, but this candidate has NOT received a
fresh compilation/sizeof/receipt/scoped integration check under that repair.
It is preserved evidence, not a new installed implementation.

Upstream commit 0c91cd8750 independently published a different FESL recovery,
using an external separator, volatile read and duplicated labelled clear paths.
That implementation remains unchanged by this findings commit. The new natural
integration task was stopped during isolated environment preparation, before
editing the source. Its incomplete local submodule setup is not published.

## Other reviewed findings

- REA dossiers: raw coverage and records were confirmed, but several semantic
  interpretations were corrected. The included review distinguishes confirmed
  bytes from source/provenance and compiler hypotheses.
- Camera: corrected stack translation is EBP+k+0x78, not +0x74. The 4299-byte
  listing is usable; claimed liveness and seed/profile causation were unproved.
- AI occupancy: bounded source trials produced no improved match. The assertion
  that only one forbidden form obtains ECX zero was rejected.
- Compiler SSE route: class-6 descriptor commit was confirmed; descriptor +0x20
  is width in bits, not an established class mask. Folded probes do not establish
  whether allocation or scheduling caused the unresolved code shape.
- Upstream separately published weak VP6 de-ringing (6c7ec5dfe3, 1526 bytes) and
  additional recoveries during this campaign. Earlier reports here are historical
  snapshots, not a current outstanding-function inventory.

Included reports preserve their original evidence paths and confidence limits.
Those absolute scratch paths may be machine-local. The regression tests needed
to exercise the accepted verifier repair are included in the patch under tools/tests;
historical raw scratch trees, compiler outputs and REA stores are not bundled.
This handoff supersedes any earlier recommendation here to keep agents running.
