Link-repair seat handoff, 2026-10-20

Five published repairs measured against the unchanged published e7a7769fe5
legacy index (2026-10-20 18:36), using current touched objects on both sides:

- SpecialAbilityUpdate frame-global type: +5,211 bytes.
- String-record and control-bar inline owners: +8,190 bytes.
- Two object-vector destructor consumers: +381 bytes.
- Int-map pool-backed node factory ownership: +4,955 bytes.
- Materials function/global provider declarations: +10,934 bytes.

Total +29,671 nonpadding matched bytes newly link in paired legacy previews.
The individual directories special-ability-frame-global-link-20261020,
inline-owner-link-20261020, object-vector-dtor-link-20261020,
int-map-node-link-20261020 and material-provider-link-20261020 contain the
measurements and proofs. Self-strict receipts were obtained for the touched
units. Publication's byte gate passed 269/269 rows and 63/63 EH graphs EXACT.
No closed-strict closure, full census, link cycle or executable result claimed.
Authored C++ coverage +0; no new body recovery in this dedicated linking pass.

Final probes, without source edits:
- W3DVolumetricShadowConstructVolume has two strong duplicates; both target
  bodies and owner/consumer files are held by another worker. The appended
  attempt log records the claim conflict; partial claims were released.
- InGameUIPostDraw already links after refreshing both explicit current
  sources; its previous strong duplicate was removed upstream. No credit.
- ScoreRowSort still depends on the unrowed 005EC52E comparator. Read its
  existing bank and handoffs before any new conversion attempt.
- DX8WrapperMatrix3DTransform still has the previously documented wrong
  selected Set_Transform provider plus Vector4 assignment copy. Existing
  dx-transform-copy-link-20261020 handoff is the starting point; do not repeat
  assignment-only edits while the earlier providers remain unreconciled.
- Rva0020479E constructor is claimed by another worker.
- name_globals --dry-run on ConstIntGettersAddr, ConstIntGetters2Addr,
  ConstIntGetters5Addr and Rva0059675ACtor found zero edits.
- Apt key-cleanup and float4 blockers are recorded in the earlier commits;
  those trials were restored. No unfinished source change or owned claim.

progress.py origin/master after publication reports delta +0, because this
batch is already on origin/master. Published linking totals are still based
on the earlier census, so the paired previews above are the repair evidence.
End this long session at the context reassessment boundary; eligible work has
not been declared exhausted. Next seat should rerank current units and claims.
