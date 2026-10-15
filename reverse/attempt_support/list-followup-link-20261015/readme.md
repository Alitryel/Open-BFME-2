# Six more list-comparison link repairs

Continue the supported comparator repair from list-comparison-link-20261015.
Six consumers emitted the same unused, incorrect 18-byte external
`_List_iterator_base::operator!=`. A static typed overload keeps their native
inline comparisons and suppresses that external copy. No layout, ABI, compiler
setting, ledger, pin, data binding or shared header changes.

The consumers are Rva0004D47DParticleRender, PlayerUpdate,
AIFollowPathAndEvacuateStateUpdate, SelectionXlatTranslateGameMessage,
HordeContainIface11CSlots and AptOnlineQuickMatchOptions. All six files and
the canonical stlport_list_int provider were claimed before preparation;
all six passed find_declared_unmatched before editing.

## Verification

context.json records the base, original source hashes and frozen index hash.
The index measures a2839ea429 at 2026-10-15 13:35, derived from census
5986a99448 at 04:52. Fetch-index retained this equally current local index
and imported published objects. The committed repair queue's status CSV
measures 4b7e7091c4 separately and was used only for discovery.

- Strict bounded preparation passes 166/166 matched rows across seven units.
  The ordinary ./build.sh gate also passes 166/166. String references (25
  literals and five empty strings), 36 float literals and seven imports pass.
  Existing renumbered funclets are verified through their parent EH graphs.
- EH verification passes 18 EXACT graphs, zero nonexact, missing or baselined.
- proof.py proves all 1,635 retained external COMDAT bodies, extents and
  relocation digests unchanged. All other existing nondebug sections,
  normalized relocations, external bindings and directives are unchanged.
  Only the six unreferenced wrong comparator sections disappear. MSVC emits
  16 internal typed comparator copies of 12 bytes each; each has static COFF
  storage and no incoming nondebug relocation. They cannot affect external
  COMDAT selection. The canonical provider's complete object is unchanged;
  its 22-byte comparator at 0x006CFE40 matches retail, including relocations.
- Paired previews refresh only these seven explicit objects into independent
  copies of the same frozen index. Consumer findings change as follows:

  | Consumer | Before | After |
  | --- | ---: | ---: |
  | Particle render | 17 | 16 |
  | Player update | 10 | 9 |
  | Evacuate state | 13 | 12 |
  | Selection translation | 37 | 36 |
  | Horde interface slots | 45 | 44 |
  | Online quick-match options | 44 | 43 |

  Each difference is exactly the removed comparator conflict. All other
  findings are identical; the provider stays at 46 independent findings.
  Ordinary local link checking agrees: none of these units links completely,
  and legacy LINKED bytes remain 0 -> 0. Authored coverage grows by zero.
- Paired identity-shadow findings remain 61 -> 61, with no new findings.
  Class, declared-definition, new-variant and enforced converged-data checks
  pass. Explicit enforced data checking reports five existing wrong-name
  findings; paired data-proof.py proves all data facts and findings identical.
  The normal shadow data gate passes with these five unchanged findings.
  An initial --sources-from invocation of ordinary data checking did not
  select these files; acceptance.json records the explicit-source rerun.
  Placement resweeps find zero additional bodies and zero pins.
  No verifier, baseline or whitelist changes.

These are legacy local link predictions using strict-current compiler inputs.
No self-strict executable-placement gain, closed-strict gain, new census or
runtime result is claimed. Maintainer-only runners were not started.
The proof scripts replay using ignored before-object snapshots under
build/list-followup-link-20261015 and the unchanged index; JSON preserves
the measured results. They are evidence, not portable acceptance gates.

## Scope and remaining blockers

sweep.json accounts for all comparator definers in this index. Three consumers
were repaired in the previous batch and six in this batch. MapCache's recorded
branch-codegen blocker and the two recorded audio orphan-funclet false rejects
were not retried. The two provider copies are retail. No untrialled consumer
remains for this supported comparator cause in the frozen index.

Remaining consumer findings include vector/allocator/template disagreements,
duplicate state helpers, Pathfinder dependencies, pooled-list provider
selection, and quick-match dependencies. proof.json preserves the exact
partitions. Resolving them requires separate evidence; the unchanged provider
also has independent debt. The retained unrowed SelectionXlat parent makes no
new recovery claim.

The five unchanged data findings concern WW3D::AreStaticSortListsEnabled,
the quick-match TheLadderList and g_00DB9198 bindings, and two HordeContain
local-static flags. Their original data facts, including inferred names,
are preserved; this comparator repair does not resolve their identity debt.

Original target/donor identity and layout provenance remains unchanged in each
source. Reuse the prior reviewed BFME 1 c1315665 suppression principle and the
existing BFME 2 NetPacket/W3DFXParticleSystem overload pattern; no donor source
or layout is imported. Official BFME 1 master was fetched at e082760734795655f086939df77b393f4b728375.
The verified clean checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
The live foreign file:reference/open-bfme-1 claim still owns the overdue
comparative verification. No pointer update or freshness-success stamp was made.

Model: gpt-6.1-sol.
