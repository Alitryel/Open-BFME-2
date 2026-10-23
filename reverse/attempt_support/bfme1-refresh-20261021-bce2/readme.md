# Verified BFME1 reference refresh

At fixed BFME2 revision `b8aeb288fed788258a3000fb9a2e382e29a70a92`, compare previous verified reference
`68c5ce2789e974f36b6c742d57437d157bc159e9` with fetched official Open-BFME/Open-BFME-1 master
`01d0e9e4fc149c12c138360ca341686f75906a63`. The reference checkout was clean and its scope was claimed.
No dirty or unpublished donor work was discarded. Existing game/ and
inputs/reference/ layout resolution remains applicable; every donor trial's
resolved include directory was checked to exist. No header changed.

Both ordinary full build.sh runs exited0: all97,918 bodies across23,427
sources and all1,143 data rows passed, as did baseline, string, float,
import, DIR32, pin, module, source-claim and no-op-patch checks. Of24,834
dependency receipts, zero use a changed donor compile input. The old gate
rebuilt4,484 units and restored4,088 more; the candidate gate reused all23,426
compiled TUs as current. Source, header and ledger state was held fixed for
the comparison; the later callback experiment remained in build/ only.

Separate complete EH checks also exited0. Their11,867-entry verdict maps
are exactly identical:11,841 EXACT,25 bytes_differ and1 retail_only.
The latter26 are existing keyed baseline entries, unchanged by this update;
there are no new EH failures and no missing objects. verification.json names
the exact input revisions, counts and full-log/JSON hashes. Full diagnostic
logs remain under ignored build/resume-eh-local/.

The refresh changes261 donor paths. Both14 new clean donor units' original
and BFME2-family settings were compiled in isolated trials:28 objects,
1,032 emitted code symbols, zero placements and zero pins. Their source,
flags, profiles and object hashes are retained in donor-trials.json. These
were leads only; no external donor path was admitted as a target source.
Fresh ranked and near sweeps both return zero; the lift lane now reports150
bodies,104 servable. No lane was silently skipped. Pointer advancement
recovers zero BFME2 C++ bytes and does not establish link or runtime progress.

## Publication reconciliation

While this batch waited to publish, BFME2 master commit `03a959c2a83`
advanced the reference to `3f00bbbe9b0c477c2182782b7401aa4fa8b1aa80`.
Official donor history confirms our verified `01d0e9e4fc` is its ancestor.
The intervening changes touch two game C++ sources and game-specific ledger
and evidence files, with no shared header, toolchain or imported tool changes.
The rebase retains upstream's newer pointer; this commit preserves the paired
verification evidence rather than downgrading the reference. The historical
verification counts above remain tied to their recorded revisions.
