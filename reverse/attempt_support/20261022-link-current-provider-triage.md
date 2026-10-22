Link-repair current-provider triage (2026-10-22)
================================================

At fd690dd12e, with the published 08160bc2c9 census (2026-10-22 17:08),
this pass made no source changes and claims no new linked bytes. Preserve
the incoming verified relation-map, audio-cache and pod-map repair commits
(a33a07d59d, eb981995c5, fd690dd12e): their recorded legacy gain is 1,113 B.
They were already complete on entry; this pass does not count them again.

Queue checks
------------
link_rank.py --top 30 / --near 2 and class_views.py --blockers were checked,
followed by current-object previews of more than 100 ranked units. Many
ranked blockers are stale. In particular these unchanged cohorts now link:

* Render2DClassAddQuadColor + Render2DSentenceDrawBFME2: 4,372 B total;
  the sentence's 2,392 B are an existing repair, not this pass's gain.
* BfmeConv932 + SidesListDataChunks: the native MapObject getter provider
  resolves the stale selection blocker; SidesList contributes 6,726 B.
* colmathsphere.cpp: 251 B. c03ded03bc already replaced the rotation
  constructor with default construction followed by the native Matrix3 Set.
* ProductionPrerequisite add/parse consumers, locale_global with its current
  wide-money provider, W3DAptAux draw/flush and PingThread getResponse also
  have their previously reported prerequisite repairs already present.

name_globals.py --dry-run: zero files, zero edits. rehome_rows.py --limit 12
completed all 103 split candidates and found three exact home placements:
Rva004F6318EntryCtor -> LivingWorldAutoResolveBattle, W3DView_Rva0008BB27 ->
View, and RvaTreeInsertUniqueGenP12pod009282C0 -> RvaMapIndexGenP12pod00928690.
The six-file current-object cohort already links 4,432 -> 4,432 B, so moving
these rows is not a linking repair. No rows were moved.

repair_queue.py link still serves missing-body and class/provider prerequisites
covered by prior attempts. In particular LineGroup Set_Transform visibility,
CreateAHeroData's vtable contract, HordeContain's pooled-list allocator,
CollisionManager's 7586F0 body, and the narrow append allocator ABI remain
unresolved. Their existing banks and evidence were retained; no unchanged
source trial was repeated. Class-view rankings require class contracts rather
than another private view or unsupported vtable suppression.

Shader prerequisite
-------------------
Claimed and released Rva00066A9ABody.cpp and RVAs 66A9A / 77F80 after reading
the earlier root-array blocker. Retail DB43A4[2] and DB43AC[10] require ten
leaf lists at DB4348..DB43A4 and thirteen singleton data targets. Only DEC1F0
has a data row. The unrowed DB5A34 declaration is char, whereas the native
singleton has an initialized vptr. Defining only the roots cannot close their
relocations. Coherent singleton/vtable/data ownership recovery is required;
no speculative data definitions or source edits were left. re_attempts.log
records this audit against W3DShaderManager::init (77F80, 316 B).

Reference and verification limits
---------------------------------
Official BFME1 master was fetched at aef2f1687742cdc91db274993cd41c3d036860ad;
the initial clean verified checkout/pointer was 37c3022de1ab944c7ffe536440d637dc8199091c.
Another worker holds file:reference/open-bfme-1. Prior reviewed linking donors
(string destruction, TerrainRefCount, battleplan, EAString, Profile and
Subsystem) supplied no new bounded transfer with the required BFME2 proof.

An optional global link_check.py --refresh was interrupted after slow stale
compiles; it returned no prediction and was not used to exhaust a queue.
Completed explicit provider/consumer previews above are legacy checks only.
No self-strict or closed-strict gain is claimed. No full link cycle, census,
nightly or boot runner was started. check_csv.py passes: 98,064 function,
15,855 symbol and 2,128 data rows. All claims acquired by this pass are released.

Final integration
------------------
Rebased onto the newer origin/master before closing. This incorporated the
upstream verified BFME1 pointer 42bba2ddbd5cb895d99293583891d3b7315fa49e and
the 32050 allocator, Miles 5BE59 and AptTimeLine repairs. Their gains belong
to upstream. The unwanted recursive donor rebase was aborted, preserving the
old checkout, then the clean donor was checked out at the committed pointer.
The upstream freshness handoff proves full old/new byte gates and unchanged
header/toolchain inputs at that update. The fetched official master is newer
still; this pass did not advance the pointer further or write a success stamp.

The incoming repair commits are now e04dc86f9d, 2d89baf609 and 49c7118443.
Their integrated four-source byte gate passes 26/26 rows, including EH and
literal/import checks. The same four-source legacy preview links relation-map
577 B, audio-cache 360 B and pod-map subscript 176 B: 1,113 B total. The
remaining pod-map helper owner still does not link; no gain is claimed for
its 249 B. This revalidation preserves the incoming batch's measured gain;
it is not another 1,113 B improvement. No new source trial remains unfinished.
