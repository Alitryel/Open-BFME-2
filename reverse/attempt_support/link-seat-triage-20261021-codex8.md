Link-repair triage, codex8, 2026-10-21

No source changes or new linked bytes. HEAD before this note was 002d21139a;
the fetched published index measures 03035cf02c, 2026-10-20 22:09 UTC.
Do not count census-to-current differences as a new repair. No claims were
acquired and no reconstruction or preparation backup needs restoring.

Selection and checks

- Pulled master; check_csv passed (97,651 function rows, 15,929 pins, 1,136
  data rows). Fetched the published index and its objects successfully.
- Ran link_rank --top 30, --near 2 and an expanded one-blocker list;
  class_views --blockers; repair_queue.py link. Checked current objects for
  100 one-blocker sources and smaller independent leads. Twelve of those
  sources already link (6,173 nonpadding bytes); that is existing progress.
  Current ScoreRowSort also already supplies both comparator instantiations,
  and the three old BfmeLess callers already use operator< in source.
- Existing handoffs cover vector<Object*> destructor cleanup, sequential
  constructor funclet ambiguity, Apt vector/key ownership, Float4 construction,
  Coord3D length, deque POD identity, String erase and scalar-deleting wrappers.
  Unchanged blocked compiler campaigns were not repeated. See the cause-specific
  handoffs referenced by link-seat-wrap-20261020b/readme.md and
  link-seat-triage-20261020-codex2.md.
- Current HLodUpdateObjSpaceBoundingVolumes has nine blockers, including bounds,
  sphere, matrix, Vector3 and destructor helpers. MaterialCollectorCollectMaterials
  has a duplicate Find_Shader plus four helper conflicts. Their indexed shared
  math conflicts do not constitute independent single-name repairs.
- name_globals.py --dry-run: zero files/edits. rehome_rows.py --limit 15 cannot
  rank candidates because build/link_census/census.log is missing. No matching
  link-cycle/data-fold artifact is available for data_back_rank. No census,
  full link cycle, nightly or boot runner was started.
- BFME1 official master fetched as fac83b23cd95fbdda4707902837018822e831146;
  verified checkout remains 68c5ce2789e974f36b6c742d57437d157bc159e9. Reviewed
  intervening linking repair leads, including 93a40127's gate-callback ILT
  ownership. The freshness receipt is absent: the prior comparative full-gate
  SDK failure remains unresolved, so no pointer update or success stamp is
  claimed. Preserve the verified inputs until that comparison can complete.

Additional shader-table evidence

Rva00066A9ABody.cpp remains blocked on g_Va00DB43A4 and g_Va00DB43AC
(W3DShaderManager::init, RVA 00077F80, 316 bytes; unit 371 nonpadding bytes).
This extends the read-only root-table evidence in re_attempts.log entry 77486.
Retail PE pointer walks give the following complete null-terminated lists (VAs):

    DB439C -> DB5A34, 0
    DB4348 -> DB5BD4, 0
    DB4364 -> DB5B54, DB5B5C, 0
    DB4350 -> DEC1F0, 0
    DB4394 -> DB5A64, 0
    DB4370 -> DEC140, DEC174, 0
    DB437C -> DEC0E0, 0
    DB4358 -> DEC1CC, DEC1DC, 0
    DB4384 -> DEC080, 0
    DB438C -> DEC018, 0

The shader root is {DB439C,0}; the filter root is
{DB4348,DB4364,DB4350,DB4394,DB4370,DB437C,DB4358,DB4384,DB438C,0}.
Neither the roots nor nested lists have data-row providers. The initialized
DB5A34/DB5BD4/DB5B54/DB5B5C/DB5A64 objects and DEC1F0 also lack data-row
owners. Several other DECxxx addresses have existing address-derived globals
in Rva007B6880Thunks.cpp; preserve their names rather than creating aliases.
The data ledger's DB43AC extent of 196 is inventory spacing, not proof of a
196-byte root: its null-terminated root occupies 40 bytes.

BFME1/ZH MasterShaderList and MasterFilterList establish the iteration purpose
only; BFME2's one shader list and nine filter lists differ from those donors.
Defining the roots alone would introduce unresolved object providers and free
no unit. Resume with evidence-backed object/vtable ownership reconstruction,
not casts of fixed addresses or donor identity assumptions. No source trial.

progress.py origin/master reports +0 authored C++ bytes and +0 linked bytes.
Resume with refreshed measurements, missing artifact availability, newly landed
providers or a substantive class-reconciliation assignment. This note does not
claim that all possible reconciliation work is exhausted.
