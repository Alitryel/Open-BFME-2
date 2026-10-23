# Terrain shroud accessor link repair

At BFME 2 8a7962f1ae00b1bbe55229d0206df133b4f7d115, the prop and
scene render consumers each emit an unused seven-byte
BaseHeightMapRenderObjClass::getShroud COMDAT, digest 2b13140fc9ac.
Their callers already inline the +0x3878 field access. Mark the two getters
imported forceinline, following W3DRadarSetShroudLevel.cpp's existing
same-field accessor. Only the surplus external definitions disappear.
No new import reference, layout, identity, ABI, flags, header, ledger, pin,
alias or baseline is introduced.

The target basis remains the existing matched bodies: W3DPropBuffer::drawProps
at 0x000EE452 (976 bytes) and RTS3DScene::renderOneObject at 0x0006FB59
(2550 bytes). The ledger preserves their ZH donor and target evidence.
This repair makes no additional donor identity or target-layout assertion.
The other indexed getter copy, in W3DPropBuffer.cpp, has digest a2ac82ffd074;
this change does not judge or alter that copy.

Discovery used repair_queue.py link, link_rank.py and the published index,
followed by strict current-object checks. Both files were claimed before
editing and passed find_declared_unmatched.

## Paired evidence

index-meta.json pins the unchanged index SHA256 and measurement 825b86983f,
2026-10-15 12:37, derived from census 5986a99448 at 04:52. The before and
after previews refresh exactly the same two objects in memory. Each unit's
findings drop from seven to six: fourteen to twelve overall. Only the getter
conflict disappears; all other findings are identical. The affected units
cover 3513 existing nonpadding bytes, but neither becomes clean. Authored
C++ growth and predicted linked-byte gain are both zero.

These are legacy local previews with self-strict current receipts for the
edited consumers. External-provider closure is not proven closed-strict.
No actual linker placement, closed-strict gain or fresh census is claimed.

Acceptance:

- Bounded link_check.py --prepare-current before and after and independent
  ./build.sh: 2/2 rows exact, eight float literals verified, zero string
  baselines/skips and zero named imports.
- object-proof.json: precisely two seven-byte helper COMDATs removed, all
  63 retained COMDATs unchanged. All retained nondebug sections, bytes,
  flags, definitions and normalized relocations agree, including EH tables
  and directives. Neither removed helper has an incoming nondebug relocation.
  No new COMDAT variant is introduced.
- EH: 2/2 EXACT, no baseline or missing object. Frozen definitions, class,
  new-variants admission, CSV and whitespace checks pass. Placement resweep
  finds zero bodies and zero pins.
- Enforced converged-data check: two sources, eight addresses, zero second
  names or unjudged rows. All before/after data-reference facts agree.
  The optional enforced shadow-data probe still refuses four existing
  outside-baseline wrong-name findings: DX8Wrapper::FogEnable in each
  consumer, FogColor in props, and LODTextureReduction in the scene.
  These are reported unchanged, not suppressed or described as passing.

Original sources, COFF objects and strict dependency receipts remain in ignored
build/terrain-shroud-getter-link-20261015/before. The comparison script is
build/terrain-shroud-getter-link-20261015/proof.py. Reproduce by preparing the
two sources from sources.json at the base revision, saving sources/objects/
receipts and index metadata, applying this patch, preparing again and running
proof.py. It checks retained sections, paired findings and data references
without changing the index.

## Reference review and remaining dependencies

BFME 1 verified checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Review of donor repair
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo constructor emission)
and 66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocator emission)
supports the imported-forceinline mechanism. Their types, layouts and bodies
are unrelated and were not imported. The prior dedicated donor sweep is
reused; unchanged blocked donors were not retried.

Official master was fetched at c3c5a59620585b5752df5861abfd7979010f485b.
The reference directory still has another worker's live file claim, and
the comparative full-gate blocker in ../unicode-comparator-link-20261014/readme.md
is unresolved. Preserve the verified pointer; no freshness-success stamp
is written.

The prop consumer still has unresolved fog data and the shroud rendering-method
helper, the duplicate/selected drawProps owner, and Matrix3D::Set selection.
The scene consumer still has unresolved FogEnable and the shroud helper,
LightEnvironmentClass ambient selection, and Drawable shroud-frame helper
conflicts. link-after.txt records the precise names. These independent
dependencies remain for later repair. No census build/measure/history,
full link cycle, nightly, boot runner or shadow publisher was started.
