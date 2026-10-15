# Remove competing incidental WWMath::Clamp bodies

Four units used the donor's inline float Clamp and also emitted an unused
external copy that differs from retail's owner at RVA 0x0011F680 in
lightenvironment.cpp. The tactic, height-map and vehicle-curve callers now
spell out that same comparison expression. CameraShakeSystemClass discarded
all three return values: its calls were already optimized away, so removing
them preserves its existing behavior. No header, compiler setting, ledger,
pin, data binding or baseline changes.

## Controlled comparison

Base checkout cba7c2e8f3f9d2201d58ace3036124dcb42f075a. Both preview phases use
deep copies of the same runner index, refreshed in memory with just these four
objects. context.json records its SHA256. The index measures update commit
825b86983f (2026-10-15 12:37); its underlying census is 5986a99448 (04:52).
The committed link-status queue measures 4b7e7091c4 and served selection only.
No census, index or status was rewritten.

| Consumer | Existing authored bytes | Legacy findings | Identical retained COMDATs |
| --- | ---: | ---: | ---: |
| Rva00506B74Tactic.cpp | 1,613 | 3 -> 1 | 87 |
| vehiclecurve.cpp | 178 | 15 -> 13 | 80 |
| HeightMap.cpp | 439 | 72 -> 70 | 240 |
| camerashakesystem_shaker.cpp | 868 | 11 -> 9 | 47 |

Each loses precisely the wrong-COMDAT and wrong-selected findings for
`?Clamp@WWMath@@SAMMMM@Z`. Legacy LINKED remains 0 -> 0 across these 3,098
existing authored bytes; new authored C++ bytes are zero. There is no claimed
self-strict, closed-strict, census or executable-link gain. Strict reusable
consumer receipts establish currency, not provider closure.

object-proof.json proves all 454 retained COMDATs identical in bytes and
normalized relocation digests, including the unclaimed vehicle Evaluate body.
All other nondebug sections, external bindings and directives are identical.
The only removed definitions are the four unreferenced Clamp copies; no new
definition, import, external binding or local helper is emitted. Neither the
symbol nor its section had a nondebug caller relocation in any original.
The retail Clamp copies in render2d/lightenvironment are unchanged.

Original source/object snapshots remain in ignored
build/tactic-clamp-link-20261015. The evidence scripts expect those snapshots
and the recorded index; they do not replace the normal gates.

## Acceptance

- ./build.sh and bounded strict preparation: 47/47 matched rows, 13 float
  literals, no skipped/baselined strings or import findings.
- All seven EH-bearing rows EXACT; no baselined or missing-object cases.
- Enforced data checks: zero findings. Converged-data: eight addresses, zero
  second names or unjudged rows. Class, declared-definition, new-variant,
  check_csv and whitespace checks pass.
- Paired link-check results remove exactly the eight findings above; other
  findings are unchanged. The normal local preview still exits 1 for those
  remaining blockers. No maintainer-only runner was used.
- Placement resweep: zero bodies or pins. All eight existing shadow identity
  diagnostics are unchanged (AIBaseBuilder's base-destructor binding and seven
  unrelated vector/matrix definitions). This check is not reported as clean.
  Exact EH and object evidence establish preservation despite funclet-label
  renumbering; no baseline was changed.

## Remaining work and donor review

The tactic still needs AIBase::rva005AD99C's vector-of-hit provider. Vehicle
still needs PersistFactoryClass lifecycle and SaveLoadSystem pointer
registration providers plus unrelated math/vector reconciliation. HeightMap
still has missing terrain/rendering providers and RenderObj/Shader COMDAT
conflicts. Camera-shaker still needs its CameraShaker destructor provider and
pool/list/critical-section reconciliation. These require separate evidence;
the complete unchanged findings are in link-proof.json.

The pass started with repair_queue.py link and link_rank.py. BFME1 repairs
fea964f85433012ec0c95a44a8d88f77b4c29af5 (true allocation bindings) and
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (remove competing incidental
constructors) were reviewed. Their ownership principle applies; their types,
addresses and layouts do not. Target COFF references, retail owner verdicts,
donor Clamp's comparisons and the controlled target-object comparison support
this repair. No donor identity or layout is inferred from byte equality.

Official BFME1 master was fetched to e08276073. Its clean verified checkout
and committed pointer a7c38d3b2597121f178ab5190b3062478823257d are retained:
another worker holds file:reference/open-bfme-1. The previously documented
old/new dependency verification blocker is not retried unchanged. No pointer
advancement or freshness-success stamp was made.
