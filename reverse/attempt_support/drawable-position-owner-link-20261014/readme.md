# Drawable position callee binding repair, 2026-10-14

At BFME 2 base 90693dc2ac93e87879a929570e941ba1473bab3d, two consumers
still requested BFMERopeDrawable::getPosition although the verified provider
and ledger own the getter as Drawable::getPosition. Declare the existing owner
in W3DViewRva0008C3AC.cpp and FormationTranslatorRva00431C9D.cpp, including
the corresponding pointer types. No layout, instructions, provider, pin,
alias or function ledger row changes.

## Target evidence

The W3DView::update row at RVA 0x0008C3AC and FormationTranslator handler
at 0x00431C9D call the same getter at 0x002763E6. Native REL32 fields are
0x0008C5AC, 0x0008CAEC and 0x00431D39. The provider's existing target identity
evidence relates the getter to Drawable::getTransformMatrix, the cached Thing
position and independently identified Drawable callers. The provider's layout
is not copied into these consumers; their existing member offsets are retained.

object-proof.json compares 39, 3 and 9 emitted COMDAT symbols in the two
consumers and provider respectively. Every COMDAT raw body is identical.
Relocation offsets and kinds are identical, and the only changed referents are
the three getter calls above. Each native displacement resolves to 0x002763E6.
The provider object is unchanged, including its SHA256. The comparison used
tools/link_census.py's COFF parser; the exploratory script and object snapshots
remain in ignored build/drawable-position-link-20261014/.

## Reference review

The clean, committed BFME 1 pointer remains
23b143233b5a8664a3bdf8572df6d905c310a5a1. Official master fetched to
a7c38d3b2597121f178ab5190b3062478823257d; another seat holds the submodule
file claim. No pointer advancement or freshness-success stamp was made here.
Reviewed fea964f85433012ec0c95a44a8d88f77b4c29af5's direct operator
new/delete binding repair and a7c38d3b2's sized-delete callback repair.
The ranked analogous direct-delete work is already inherited in relevant
BFME 2 units; the callback repair is inapplicable to this getter. The landed
getter itself preserves BFME 1 donor provenance (10af19f44a89ab7ecc23195bb9a842ceafbc02c9),
while its Drawable identity and target offsets are established separately by
BFME 2 evidence. No donor bytes or layout were imported by this repair.

## Acceptance and measured improvement

Discovery index: measurement 147cfae2cb, 2026-10-14 07:27; SHA256 recorded in
object-proof.json. The committed link_status measurement is older (67e1365aa9,
2026-10-13 16:47) and was not used as current acceptance evidence.

- link_check.py --prepare-current on the two claimed consumers plus their
  claimed provider passed ordinary byte, string, float and import gates for
  all six rows before and after, with strict reusable compiler receipts.
- ./build.sh on both changed units passed 2/2 rows, 33 float literals,
  and the source, string and import checks.
- class_gate.py, find_declared_unmatched.py, check_csv.py and diff --check pass.
- place_bodies.py on both changed units serves zero bodies and zero pins.
- The permitted local legacy link_check preview removes one unresolved getter
  dependency from each consumer (three native call sites total). The provider
  still links, 691 bytes. Both consumers retain unrelated blockers; the local
  linked-byte total remains 691 -> 691, with no new authored C++ coverage.

The strict receipts establish self byte evidence, not closed-strict placement
or dependency closure. No closed-strict gain, new census result or fully linked
consumer is claimed. No full link cycle, census build, nightly or boot runner
was started. The discovery index remained unchanged.

## Remaining work

W3DView still has CameraShakerSystem/TheWaterRenderObj data bindings and
STL allocation/vector COMDAT selection blockers. FormationTranslator still
has TheGameClient, two address-named data references, and a conflicting
Restart definition. Exact remaining local diagnostics are in link-after.txt.

The additional W3DRopeDraw.cpp consumer under Drawable/ uses a ZH-derived
Drawable/Thing header and an explicit BFMERopeDrawable cast. It requires
reconciling the inherited getter declaration/header behavior before replacing
that cast; it cannot use the private declaration rename applied here without
redefining its already included Drawable class. It was inspected, not edited.
Keep this as a class/dependency follow-up rather than adding a callee alias.

All three file claims are released after committing. Full closure and the
reference-pointer update remain with their respective authorized owners.
