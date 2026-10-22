APT renderer owner repair, 2026-10-22

At BFME2 21387ea4c9, bind the flush, render wrapper and singleton cleanup to
W3DAptAux::s_renderer (VA DE6170). The existing PreDraw owner defines its
BfmeHub982 pointer; no second datum or address alias is needed. Cleanup had
owned an extra g_00DE6170, and BfmeConv982 had an /alternatename to that copy.
The flush now calls the rowed AptShapeContainer::render at A9F98, the exact
callee of its former cleanup spelling (existing pin and retail call evidence).
Renderer method views remain casts at their uses. No pin or ledger edit.

Paired current-object LEGACY preview, same four-unit cohort, published census
2026-10-22 11:05 / ae3b3e68e2:
- before: flush excluded by old callee and renderer names; 3/4 units link,
  3551 nonpadding authored bytes included;
- after: 4/4 units link, 3650 bytes included; attributable gain +99 B.
The cohort is the three changed units plus current W3DAptAux.cpp, whose
matched render definition is newer than that census. Its pre-existing 10-byte
census delta is present on both sides and is not credited to this repair.

./build.sh on all three changed units: 3/3 matched, source claims, strings,
floats and import references pass. find_declared_unmatched passes all three.
link_check.py --prepare-current supplies strict reusable byte receipts for
these explicit providers. The link preview is LEGACY, not closed-strict; no
full link cycle, census rebuild or closed-strict gain is claimed.
Ignored paired logs: build/link-seat-current/renderer-cohort-before.log and
renderer-link-after.log; source gate renderer-gate.log; strict provider byte
preparation renderer-prepare-final.log. BFME1 inputs remain 37c3022d; its
freshness update is claimed by another worker.
