# DrawableXfer unused max copy repair

Base: effed3af699047291e08dff4daaf3d27963536ad. Paired measurement index:
ac77c85054, 2026-10-15 14:25, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
The consumer DrawableXfer.cpp and unchanged stlport_basic_ios_init.cpp provider
were file-claimed. No ledger, pin, baseline, shared header, index or census
status changed.

DrawableXfer emits an unused 16-byte max<unsigned int> COMDAT
(`8b4424048b108b4c24083b110f42c1c3`, digest 733af3e58f87). It conflicts with
the native 17-byte provider at 0x00013740 in stlport_basic_ios_init.cpp
(`8b4424048b4c24088b103b1173028bc1c3`, digest 4e112da03a19).
No nondebug relocation refers to the removed body or its section.

A TU-local dllimport/forceinline specialization keeps vector's comparison
inline and suppresses the unused external definition. All 26 retained
COMDATs and all other nondebug sections/relocations, external bindings and
directives are unchanged after normalizing compiler-local symbol numbering.
There are no replacement imports. The provider's whole object is unchanged.
The existing Drawable::createEmbeddedPortals identity and layout are preserved;
this repair introduces no target identity or donor layout assertion.

The emission technique was reviewed in BFME1 commits
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo constructor) and
66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation). Current BFME2
bytes and relocations independently establish applicability. No donor source
or layout was imported.

## Acceptance and measured improvement

proof.py refreshes the explicit consumer/provider pair into two in-memory
copies of the same index. The original byte-verified objects and final
strict-receipt objects produce:

| Unit | Findings before | After | Local legacy linked bytes |
| --- | ---: | ---: | ---: |
| DrawableXfer.cpp | 1 COMDAT | 0 | 0 -> 506 |
| stlport_basic_ios_init.cpp | 27 | 27 | 0 -> 0 |

proof.json contains complete paired findings, object hashes, emitted bytes,
relocations, strict-current checks and zero data findings in both phases.
The 513-byte authored row contains 506 nonpadding bytes. Authored C++ byte
growth is zero. This is a legacy local link preview with byte-strict current
objects; no closed-strict, full-link, census or runtime gain is asserted.

- Bounded --prepare-current passes 22/22 matched rows across both sources,
  one literal plus one empty-string reference and two named imports, with
  strict reusable receipts. Both original and final preparation logs are saved.
- EH verification: 2 EXACT, zero nonexact or missing objects.
- Enforced data check: zero findings. Converged data: eight addresses,
  zero second names or unjudged rows.
- New-variants admission, class gate, declared-definition check, ledger check
  (91526 function / 15479 symbol / 464 data rows) and diff whitespace pass.
- Placement rescan: zero bodies, zero pins.
- Local link_check reports the consumer LINKS, 0 -> 506 bytes. Its exit 1
  reflects the unchanged provider's unresolved/COMDAT/selected debt; the paired
  proof confirms every provider finding is identical.

Original sources and objects remain in ignored
build/drawable-max-link-20261015, with the provider's original receipt.
The original consumer's strict preparation is logged; its old receipt was
not copied. Reproduction needs the frozen index, original objects compiled
from the base revision, and final build.sh/--prepare-current receipts.
proof.py reads those snapshots and leaves shared caches and the index intact.

## Remaining work and freshness

The native provider still has scan_not unresolved, competing stream/string
COMDATs and selected-definition debt. This repair does not close its dependency
graph. PlayerAddScience was inspected as another max consumer; it also needs
a retained vector-base destructor repair, so it was not edited or credited.
Ground path work was held by another file claimant and was left untouched.
Top-ranked EAString, WorldToCell and the LightClass/WeaponRange repairs were
already locally repaired; no gain was credited for them.

BFME1 checkout and committed pointer remain
a7c38d3b2597121f178ab5190b3062478823257d. The freshness fetch found upstream
95eeb3bef370a7cd730b0ad5f228c317c8756e72. The live
file:reference/open-bfme-1 claimant owns the update and comparative full-gate
work. This seat preserved those inputs and did not stamp a successful check.
Full verification runners remain maintainer-only.
