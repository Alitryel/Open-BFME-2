# STL helper bindings, 2026-10-22

At BFME 2 80b1c0b8ca, using the published census index from 08160bc2c9
(2026-10-22 17:08), both current original objects failed the link preview:

| Unit | Before | After | Authored nonpadding gain |
| --- | --- | --- | --- |
| SelectionXlatTranslateGameMessage.cpp | 0 | 4,145 | 4,145 B |
| Rva002E0298.cpp | 0 | 195 | 195 B |

The const void-pointer vector subscript and the two hash bucket helpers retain
their exact STLport header definitions for inlining, while `dllimport` suppresses
the conflicting external copies. The science-vector `push_back` instead uses a
declaration-only specialization: its callers must retain their existing call,
and forcing that definition inline changed both matched bodies. The kept
external providers resolve all referenced names in the resulting objects.
The remaining `bucket_count` diagnostic in Rva002E0298 is unreferenced and is
not a blocker under the current census rules.

Semantic reference: verified BFME 1 donor 37c3022de1ab944c7ffe536440d637dc8199091c,
`inputs/vendor/stlport/stl/_vector.h` and `_hashtable.h`. These definitions do
not establish new application identities or layouts. The helper annotations
declare unpinned source definitions, rather than new matched retail bodies.

Acceptance: `./build.sh` passes 3/3 and 2/2 existing rows respectively;
`link_check.py --prepare-current` verifies all five rows with strict reusable
self receipts, including string, float and import references. The ordinary
two-unit `link_check.py` preview changes 0 to 4,340 B with no blockers. This is
a same-index current-object legacy link prediction, not a closed-strict or
actual-placement measurement. Frozen-source and CSV checks pass.

Cause sweep: ArmorStoreParse already links in its current object, so it is not
credited. GameLogicDoXfer retains independent duplicate and unresolved class
blockers; no zero-gain change was retained there. The second unit above is the
only additional compatible hash-helper repair found in the reviewed rank.

Other trials were restored and logged: W3DHordeModelDraw's string constructor
binding changes parent/EH bytes; AssetManager refresh's allocator constructor
bindings change the parent; CreateAHeroData's virtual declarations preserve
bytes but expose unresolved CreateAHeroHero ownership and its fifth Update
slot. Those require separate compiler/class prerequisites. Their claims were
released.

Publication reconciliation: origin/master b589abb5fa landed an independent
SelectionTranslator repair during this session. Rebase brought equivalent
specializations into that unit, and the push hook correctly refused duplicate
definitions. Drop this seat's Selection additions and retain upstream's; the
remaining repair credited to this seat is **195 B** in Rva002E0298.cpp.
The original 4,145 B experiment is historical evidence only, not an additional
gain over the rebased master. Reverification preserves all five exact rows and
the two-unit link preview; only the independent science-vector gain is claimed.
