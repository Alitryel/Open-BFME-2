# Asset-reader link repair stopped at address false reject

At BFME2 88457d2ee5, declaring the existing pointer-set constructor specialization
without a local body removes the only COMDAT conflict. All three existing rows
(1081B parent, 10B handler, 8B unwind) pass build.sh; unwind label is resolved
through the unchanged parent EH graph. No pins or ledger changes are needed.

The current-object link preview still reports zero linked bytes because
link_debt.addresses classifies two switch constants as hard-coded image
addresses: 0x544558 (TEX) and 0x424F58 (BOX). The source switch tests the file's
asset-kind integer against these format tags; neither is dereferenced or cast
to a pointer. The full native parent already verifies those immediates. This
is a concrete false reject, not a missing data-global repair. Do not rewrite
the constants to evade the detector. Patch and verification output are banked;
production source restored. Reapply after a separate verifier repair with a
regression test. No linked improvement is claimed for this attempt.

The same set-constructor cause appears in AssetManagerImplCtor and
Rva00622290CollectKeys, but current previews show many other independent
container conflicts; BaseHeightMapInitHeightData has further blockers too.

The diagnostic patch has zero context; use `git apply --unidiff-zero`.
