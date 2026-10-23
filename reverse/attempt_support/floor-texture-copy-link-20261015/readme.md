# Floor texture argument-copy emission repair

The private `RefCountPtr<TextureClass>` specialization in Rva000E473F.cpp
emitted an unused standalone copy constructor that lost the census's COMDAT
selection. Mark its existing inline constructor imported and force-inline,
following the established BFME 2 consumer pattern. The argument copies retain
their existing AssetReference constructor calls at 0x000424BB. No ABI, layout,
ownership behavior, compiler flags, shared headers, pins or ledger rows change.

The specialization and its target-specific AssetReference semantics were
already established by the matched drawFloors caller. This change makes no new
claim about the original template identity and does not reconcile the other
private texture-handle views. In particular, the ordinary ZH reference-counted
pointer implementation is not substituted for this target's asset handle.

Base checkout: c5d60ae1d0982fbadff6c0498a6dc88a03b5276d.
Unchanged census: 28269d8e8d, 2026-10-15 09:31 UTC; index SHA-256
6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.
The published-index fetch retained this same index and restored its objects.

## Measured local improvement

The same-index legacy local preview changes the floor-buffer consumer from
one COMDAT blocker to LINKS: **0 -> 2,241 existing matched bytes**. This is
one repaired blocker and **zero new authored bytes**. It is not a new census,
an executed link.exe placement, or a closed-strict closure result.

Both before and after consumer objects have self-strict reusable receipts.
The complete retained-object comparison shows exactly one removed COMDAT:
`??0?$RefCountPtr@VTextureClass@@@@QAE@ABV0@@Z`. All 63 retained COMDATs,
complete nondebug section bytes/extents and symbolic relocations are identical.
External bindings, undefined symbols and weak externals are unchanged, and no
retained section references the removed constructor. SafeSEH symbol indices
are compared by binding; local relocation destinations include section bytes,
extent, flags and offset. Debug sections are excluded.

The census's retail-proven constructor copy is in WorldHeightMapGetFlatTexture.
It remains present. That provider also passes strict reusable preparation and
its 285-byte row and string check. The paired provider/consumer preview leaves
the consumer clean; the provider retains its independent unresolved
TerrainTextureClass::updateFlat dependency. No provider source was edited and
no provider LINKED gain is claimed.

## Acceptance and limits

- Consumer strict preparation before/after and explicit ./build.sh pass all
  15 matched rows; string, float and import checks pass.
- EH verifier: 5/5 EXACT; no missing objects or baseline discrepancies.
- Local link preview and new-variants admission pass for the changed consumer.
- Enforced data check: zero findings. Converged-data check: eight addresses,
  zero second names or unjudged rows. Canonical-class and frozen-file checks pass.
- Placement rescan: zero new bodies or pins. CSV and whitespace checks pass.
- Identity shadow reports two existing addFloor list push_back/push_front
  bindings at 0x0005548F and 0x00392076. The saved original and current caller
  objects produce the same two findings against the same provider context.
  All retained relocation bindings are independently unchanged. No identity
  baseline was altered. Those findings require separate repair.

Before objects, original source, receipts and comparison scripts remain in
ignored build/floor-texture-copy-link-20261015. The committed object proof and
paired identity findings record the controlled comparisons. Verification used
model gpt-6.1-sol. No census build/measure/history, full link cycle, nightly or
boot runner was started; broader verification remains outstanding.

## Reference review

Retained clean BFME 1 gitlink/checkout:
a7c38d3b2597121f178ab5190b3062478823257d. Reused the unchanged dedicated donor
review in link-inline-emitters-20261014/readme.md: removing surplus inline
definitions is applicable; donor layouts and addresses are not imported.
The GeneralsMD ref_ptr.h documents the ordinary reference-counted semantics,
which do not replace the already verified BFME 2 AssetReference specialization.

Official master was fetched and resolved to
75ff0c1485a68eafb10344670711edbee8679b62. The submodule still has a foreign
file claim; its verified inputs were preserved. Updating the pointer remains
blocked on that claim and comparative full verification documented by earlier
sessions. No freshness-success stamp was written.
