# Link-repair handoff, 2026-10-18

Baseline master: 0153acb61d. Published index: c2c5ac8c27, 2026-10-18 11:36,
retail-truth-2. No source, pin, data, header or verifier changes retained.
No new authored or linked bytes claimed; all link_check results below are legacy
previews, not closed-strict measurements.

## Texture diagnostics: explicit destructor linkage is blocked

INIStatsRecordTextures.cpp currently has two findings: the implicit
DynamicVectorClass<StringClass> destructor and VectorClass<StringClass>'s
scalar deleting destructor differ from the retained providers. Added one explicit
`__declspec(dllimport) __forceinline virtual ~DynamicVectorClass() {}`
inside the existing per-unit class view. The normal byte gate still passed both
rows, literals and imports. The current link preview instead gained an undefined
`__imp_??1?$DynamicVectorClass@VStringClass@@@@UAE@XZ` from the EH cleanup,
and the base deleting-destructor conflict remained. No improvement. Restored
the complete original source and reverified it. Native cleanup 0x007945AF targets
0x00121E20; no matched named derived-destructor provider exists. This needs real
provider/class reconciliation, not an import alias. The before, after and byte
logs are included. File and both RVA claims released.

## False rejection: an RGB color is treated as an image address

Rva0059675ACtor.cpp defines the matched 125-byte FadeInTextRender constructor at
0x005966DD. Its unsigned field +0x28 is initialized by `color(0xDCF0FA)`.
The current link preview has only the hard-coded-address finding on this scalar
constant. No source rewrite or checker change attempted. A tooling seat should
reproduce and add a regression distinguishing immediate color data from pointer
access before changing the classifier. File claim released.

## Lanes checked and remaining scope

- link_rank.py --top 30 and --near 2: high-return missing bodies and class/ABI
  conflicts remain. Existing deferrals for moveAllies, getPortTransform,
  Rva006D07E0Key destructor, Object vector-base lifetime and StringBase<char>
  suppression are unchanged; no new evidence justified repeating their trials.
- class_views.py --blockers: MilesAudioManager, DX8Wrapper, Apt, Pathfinder and
  private render views dominate; they need broader class/provider work.
- repair_queue.py link: agrees with those missing-body dependencies.
- Current-object previews sampled over 100 units from small blocker cohorts.
  Several index findings disappear with already-landed code. Supplying current
  providers clears StaticSortListClass vtable (461 bytes), MeshClassRender
  (1,427 bytes) and INIParseFXListVec (303 bytes), without any source edit here.
  These are baseline freshness corrections, not gains from this session.
- name_globals.py --dry-run: zero rewrites kept.
- rehome_rows.py dry-run: 110 census candidates; inspected the candidate list
  against current blockers. Only six split/home pairs with blocked split and
  at most one home blocker remain, all below 100 bytes (5--93). Initial byte
  probes refused 12 pairs; the one exact 29-byte entry constructor already
  links, while its home has unrelated range/destroy blockers. Stopped the
  broader dry-run after this bounded scope assessment; did not apply it.
- No matching link-cycle data-back artifact is available; no data-back ranking
  manufactured. No census build/measure/history or maintainer runner started.
- BFME1 official master fetched to 8619c4c56d73cfeb7beb7d7dd87e4fbde47b01da;
  clean verified checkout/gitlink remains 64d369b90170b7e9ec917d646f020b11f13eb0d5.
  Existing update-verification blocker is the PrimaryBase DIR32 inconsistency
  documented in ../link-reconciliation-20261018/readme.md. No successful
  freshness stamp written and no unverified pointer advanced.

check_csv passed; progress.py origin/master reported zero byte deltas.
