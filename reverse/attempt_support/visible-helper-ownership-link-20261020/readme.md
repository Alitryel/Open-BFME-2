# Visible helper ownership (+277 B linked after rebase)

Baseline: BFME2 74eb0e2dab, published legacy census e7a7769fe5 (2026-10-20 18:36). Explicit-source before/after checks use the same frozen index. The measured counts exclude padding. No authored C++ coverage gain, census rewrite, full link cycle or closed-strict closure claim.

VectorAngleRva00363B4B becomes an inline, noinline-emitted owner, matching the consumer ownership in PathRva00365309. The consumer needs a visible definition for its optimizer summary; historical attempts to remove it changed caller bytes. The owner retains its exact 124-byte row, and now links 122 nonpadding bytes. The untouched caller loses the duplicate blocker but still needs Coord3D::scale and Path::rva00364AA2.

ConnectionManagerCtor and ConnectionManagerInit2 both become inline, noinline-emitted constructors. Both must change: a remaining strong definition still conflicts with a selectany copy. Small absent-from-retail call sites retain emission of the visible definitions. This preserves every one of the 15 existing rows, including six graph-resolved renumbered EH labels, while the constructor provider now links 277 nonpadding bytes. Init2 is the necessary second half of the ownership repair, not a claimed extra byte gain; its non-retail constructor copy and pair destructor still block its own 463 bytes. Earlier declaration-only attempts changed cleanup/EH bodies; retaining definitions avoids that failure.

Acceptance: ordinary byte gates 16/16 across the three changed units, float/string/import reference checks, strict reusable compiler receipts for those same units, new-variant check, class gate and declared-unmatched check. The link gains are legacy-index predictions with self-strict compiled providers; dependency closure was not measured. See paired logs and strict receipts here.

Reference review: clean verified BFME1 4483e88da1c2f3b9a273f779baac7458bd8bb891, including ownership repairs a411b334c, 3313189ad and c54305633. Inline ownership is a donor repair pattern only. BFME2 identity, row extents, call relationships and byte preservation are established by the existing target rows and fresh gates; no donor layout or name is newly asserted.

Publication reconciliation: upstream595955cc30 independently adopted the same angle ownership repair while this batch was publishing. Retain its source and exclude the122B angle gain from this commit. Angle logs above are historical measurements at74eb0e2dab, not new gain over the rebased parent. Final batch: ConnectionManager277B plus Transport735B =1012B. Upstream also recovered Path364AA2, so that old Path prerequisite is resolved.

Rebased acceptance: ordinary gate17/17, self-strict receipts3/3 units, paired frozen-index prediction0->1012B (2/3 units link). See rebased-{gate,after,strict}.txt. ConnectionManagerInit2 remains a prerequisite and does not link. No closed-strict gain is claimed.
