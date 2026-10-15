# Horde slot tree-iterator emission repair

BFME2 base: `e509b3d01c4b7708cada7e23b294322412fca7ce`.
Affected consumer:
`Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva00474483ConfigureSlots.cpp`.
A TU-local typed tree-iterator inequality preserves the node comparison and
suppresses the conflicting external base-iterator comparison. No compiler
flags, headers, layouts, identities, data bindings, pins or ledger extents change.

## Paired evidence

All 142 retained COMDATs have identical bodies, sizes and relocation digests.
The removed 18-byte shared comparison has no incoming nondebug relocations.
The only added section is an unreferenced private 12-byte typed comparison.
Every other normalized nondebug section, including EH data and unwind code,
external binding and linker directive is identical. Local labels are compared
by their actual target sections and offsets; `.sxdata` indices by symbol name.
Paired data facts and findings are identical, with zero data findings.

The before and after objects are refreshed independently into copies of one
frozen runner index. Index receipt: `825b86983f`, 2026-10-15 12:37;
underlying census: `5986a99448`, 04:52. Index SHA256:
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
The older committed link-status queue is discovery evidence, not a new
measurement. No index, census or committed status is rewritten.

Current-object local findings decrease **22 to 21**, exactly the removed
base-iterator COMDAT conflict. The paired JSON asserts no other finding change.
Legacy predicted LINKED remains **0 to 0** for this unit's 969 nonpadding bytes.
New authored C++ bytes: **0**. Strict reusable object receipts and byte gates
do not prove self-strict or closed-strict placement gains. No full census,
link cycle, nightly or boot runner was started.

## Acceptance

- Before/after `link_check.py --prepare-current`: eight rows byte-exact,
  strict reusable receipts, one explicit provider and no dependency expansion.
- `./build.sh` passes all eight rows, two string literals, zero float/import
  discrepancies. The parent EH record verifies the renumbered unwind label
  `$L12314` at retail `0x0078B267` (ledger label `$L12310`).
- `eh_verify.py`: EXACT 1, zero baseline exceptions.
- `data_check.py --enforce`: zero findings; converged check: eight addresses,
  zero second names and zero unjudged rows.
- Default local `link_check.py` exits 1 with the remaining blockers below;
  paired previews prove the single-finding reduction. `--new-variants` passes.
- Class gate, declared-definition check, `check_csv.py` and whitespace check
  pass. The affected-unit placement rescan returns zero bodies and zero pins.

The consumer still has one unresolved provider (`Rva004693D9::rva004693D9`),
16 other COMDAT conflicts and four wrong-selected providers. Exact names are
saved in `link-after.txt` and `link-proof.json`. Those providers and their other
consumers are unchanged and require separate evidence-backed repairs.

## Donor review and handoff

Reviewed BFME1 master `6974867b784ad2e651a2e167853246afcb18e3b5`, especially
`de59a7e9f891b3ed2d4221d151ca881f4b75a583` (shared inline identity) and
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` (nonretail constructor suppression).
The typed-iterator remedy is already supported by BFME2's snapshot/INI and
other local repairs; this unit is independently verified. No donor body,
layout or identity was imported. The verified clean checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`.

Another worker holds the reference-update file claim. The stale freshness
stamp is not advanced: the prior old-input full verification was incomplete
with 2806 stale TUs after 21 minutes (2982 initially). Retain the verified
inputs until that separate update is verified.

Discovery used `repair_queue.py link`, `link_rank.py` rank/near/per-file views,
and the fetched published index (the newer local runner index was retained).
Already-repaired queue entries and unchanged recorded blockers were skipped.
Unrelated untracked assembly and ZH sweep work is preserved.

Proof scripts are evidence, not production tools. Run them from the root in
object/link/data order while scratch `build/horde-slots-iterator-link-20261015`
snapshots and the frozen index are available. Saved JSON and receipt hashes
retain the measurement without committing object files. The file claim is
released after completion.
