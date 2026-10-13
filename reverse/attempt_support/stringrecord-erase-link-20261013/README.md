# String-record range erase provider repair

Base checkout: 68a2d9a2f3. Local census index: cb660e4d97, 2026-10-13
04:02 (SHA256 in index.json). The committed link-status queue measures
67e1365aa9 at 16:47; it is discovery evidence, not the preview baseline.

The allocate-copy and clear units instantiated a non-retail range erase
for vector<BfmeStringRecord005DDD40>. Both now declare that specialization,
using the existing verified 51-byte provider at 0x00381B1F instead. No method
body, layout, compiler flag, header, ledger row, name, pin or baseline changes.
The exact provider remains unchanged and independently byte-verified.

Existing BFME2 precedent: stlport_vector_asciistring_copy_backward.cpp declares
its verified range-erase specialization before explicit vector instantiation.
Target support here is the existing native 0x00381B1F extent, all relocations
of its verified provider, and the native call from the 30-byte clear body.
The record's application identity remains unresolved; no donor-derived naming
or layout claim is added.

BFME1 donor linking scan reviewed d4ab8b980fe916fe70e137b2c2d2d04bceda8c9a:
its five WWVegas array-allocation repairs concern a different dependency and
are inapplicable to this conflict. No donor source or pin was imported.
The clean committed donor pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Freshness fetch found a5cc7fd46 upstream; the earlier comparative full-gate
blocker (FontCharsClassGdiState_Ctor.cpp/profile_highlevel.cpp compile stalls)
remains documented in build/reference-update-blocker.txt. This repair neither
advances the pointer nor records a successful freshness stamp. Comparative
verification of the updated donor remains outstanding.

Acceptance and scope:

- Bounded --prepare-current before/after: all 16/16 rows across the two edited
  sources and exact erase provider byte-verify with strict reusable receipts.
- Read-only GameStats consumer: 15/15 rows, 39 strings and three float references
  byte-verify with a strict reusable receipt. All 31 existing rows preserved.
- Two associated EH graphs EXACT, no baseline; frozen-definition and class
  gates pass; converged-data check: eight addresses, zero second names/unjudged
  rows. The ordinary ./build.sh check is saved separately.
- Thirteen COMDATs disappear: the wrong erase from both consumers and eleven
  helpers only needed by clear's discarded erase. No COMDATs added; all 93
  retained COMDAT byte-and-normalized-relocation hashes are unchanged, including
  the complete exact provider. Details in comdat-diff.json.
- Same-index legacy preview: allocate-copy findings 8->6, clear 3->1,
  erase provider 4->3, GameStats 4->3: total 19->13. The wrong selected erase
  finding disappears from all four units. Before uses strict pre-edit object
  snapshots retaining their original object basenames, refreshed only in memory
  through link_check's normal refresh/check_object/report routines; GameStats
  is unchanged. After uses the ordinary link_check.py command on the cohort.
- Every unit still has independent blockers. No locally linked-byte, measured
  census, closed-strict or authored-byte gain is claimed. The census's stored
  2,283 GameStats bytes are an older baseline, not a regression caused here.

Remaining blockers: allocate-copy's record/UnicodeString cleanup and insertion
COMDAT selection; clear's g_00E022F8; erase provider's mismatched __copy_ptrs and
unresolved two-template-argument __copy spelling; GameStats' newer AddStat/Max/
MinGameLength providers are absent under those names from this old index.
Provider/callee reconciliation must preserve all existing bytes. A new authorized
measurement is needed for closed-strict credit. No full census, link cycle,
nightly, boot or scheduler operation ran.
