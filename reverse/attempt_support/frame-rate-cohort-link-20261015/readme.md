Frame-rate owner binding repair, 2026-10-15

BFME 2 base 6c7f854d192bf33d174b324c82b253c582d83ba3. Seven consumers still declared g_00DBA4E4 or g_Va00DBA4E4 rather than the existing sole data owner BfmeLogicFramesPerSecond. Bind each to that existing int; no definition, pin, layout, compiler flag, baseline or function ledger changes. sources.txt lists the seven edited consumers followed by the unchanged ColdGlobalDwordGetters provider. All eight files were claimed and passed the frozen-source check before editing.

Target evidence and scope

The matched data row owns all four bytes at RVA 0x009BA4E4, initial value 5; its independently verified provenance is reverse/attempt_support/frame-rate-owner-link-20261014/readme.md. The identifier is descriptive, not an original debug symbol. Eleven native DIR32 operands in the seven matched consumers independently reach VA 0x00DBA4E4 (object-proof.json records caller, RVA and operand offset). Full non-debug COFF section bytes, flags, extents, definitions and all other relocations are identical before/after. Only the data relocation name changes. Strict reusable receipts are current at each snapshot. The provider's complete object and receipt hashes remain identical. Class identity/layout claims in these sources are preserved, including the provisional constructor class spelling and historical home-unit reconciliation note.

Same-index paired link preview

The runner index is updated at 19a2565407, 2026-10-15 09:33, from census 5986a99448, 04:52. SHA256 a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3. The committed link_status snapshot belongs to another measurement and serves discovery only. No per-row data-back artifact or sole_bytes ranking is used.

Only the constructor, RTS3DSceneRenderOneObject and unchanged provider are present in this index. Paired checks use the saved before objects and current after objects, refreshing only these definitions in memory. Exactly one old unresolved name disappears from each previewed consumer; every other finding is identical. The constructor at 0x001E4ABE becomes clean, predicting 752 existing authored bytes linked (754-byte extent includes two padding bytes). Cohort clean files increase 1/3 to 2/3 and predicted bytes 511 to 1263. The renderer remains blocked by two unresolved names, four losing COMDATs and one wrong-selected definition, all listed in link-delta.json.

BannerUIUpdate, DynamicPortalBehaviourCreateWaypoints, both horde attack-position consumers and ScriptEngineRva0020A586 are absent from the index. The official local checker refuses their link preview; no fabricated positions or rankings were used. Their byte-exact owner bindings remove five verified wrong-name data findings, but no link closure or linked-byte gain is claimed for them. All objects are self-strict; the available link results are legacy local previews. Closed-strict closure and link.exe placement remain unmeasured. New authored C++ bytes: zero.

Acceptance

prepare-current before and after plus final ./build.sh pass 45/45 function rows and the unchanged provider's data row. Eight literals, one empty-string reference and 35 float literals verify, with no skipped references. EH is 3/3 EXACT. New-variant admission, class and frozen-source checks pass. The same-cause placement resweep yields zero incidental bodies or pins.

Explicit eight-source data checking falls from 19 findings (11 outside baseline) to 12 (4 outside baseline), removing exactly seven consumer wrong-name findings. Six edited consumers pass --enforce with zero findings. The renderer retains its pre-existing FogEnable and LODTextureReduction wrong-name findings; the provider retains its pre-existing RVA 0x009BD0F0 and 0x00A063EC findings. Existing baselined findings are preserved. The enforced converged-data check covers all eight sources and eight protected addresses with zero second names and zero unjudged rows. No baseline is changed. Normal data_check ignores --sources-from outside its converged mode, so data-before.log, data-after.log and data-clean-consumers.log were produced with explicit positional sources. CSV integrity and diff checks pass. No census/index/status/history files or maintainer-only runners were used.

Donor review and outstanding freshness

Reviewed clean verified BFME 1 pointer a7c38d3b2597121f178ab5190b3062478823257d and its repair 92a8d854746f059994f8ab370c133f3ba71eec24: bind consumers to the existing data_rows owner, rather than inventing another datum. This principle applies directly; no donor type, address or layout is imported. BFME 2's verified frame-rate provider and native operands independently establish this change.

The latest observed official origin/master after the session fetches is newer, 0dbe7e53e56a3e319104c52f9d59c13668158374. The prior handoff already records the outstanding same-revision old/new full-verification comparison (the old baseline had thousands of stale units), and another worker holds file:reference/open-bfme-1. Preserve the verified pointer and existing inputs; no freshness success stamp is written. Pointer advancement and its full comparative gate remain outstanding.

Queue review and reproduction

repair_queue.py link and link_rank's unresolved, address and COMDAT ranks were checked. Several top rows already pass the local checker. Previously recorded FireWeapon secondary-vtable dependency and WeaponTemplate literal false rejection remain unresolved and were not retried. After this supported shared owner fix, broader renderer/class/data debt is left to its own repair cohort; no queue exhaustion is asserted.

At the base revision, prepare-current sources.txt, then run proof.py before to snapshot strict objects and receipts into build/frame-rate-cohort-link-20261015. Apply the seven source name substitutions, prepare-current again, run proof.py after and link-proof.py, and run official link_check.py with preview-sources.txt. The scripts do not write a census or mutate the index. Tracked logs/JSON preserve the result; scratch objects and receipts remain untracked build artifacts. Re-run normal data_check with explicit paths, and converged checking with a NUL source list. The provider must remain last in sources.txt and preview-sources.txt.
