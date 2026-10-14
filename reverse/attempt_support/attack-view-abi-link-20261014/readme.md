Bind attack-path consumers to the verified Pathfinder query

Base de546401389634e1006f7dfe3f7692e5297cb937. Two current consumers declared
Pathfinder::isAttackViewBlockedByObstacle with coordinate pointers. The real
544-byte provider at 0x002F314A uses coordinate references. Reconcile each
active declaration and dereference its position arguments. MSVC emits exactly
the same instruction/data sections and argument addresses; only the external
relocation name changes to the existing provider. No new wrapper, alias, pin,
layout, compiler setting, header or ledger extent is introduced.

Target evidence is independent of the donor: the existing provider passes the
byte gate, and the consumer REL32 operands at 0x00266B92 (computeAttackPath)
and 0x00348888 (updateInternal) both decode to 0x002F314A. object-proof.json
records the parent rows, offsets, current receipts and full before/after
non-debug section comparison. All section bytes, flags, extents, strong/weak
definitions and other relocation names/destinations remain identical. Hatch
counts are unchanged. The provider object is unchanged.

The whole-source sweep finds these two active pointer-overload calls. Three
other units retain unused declarations without calls: AIStates.cpp,
AIAttackApproachComputePath.cpp and AIUpdateInterface_doPathfind.cpp. They need
no binding repair. The two forwarding bodies already use the correct references.

Donor linking review at the committed checkout
 a7c38d3b2597121f178ab5190b3062478823257d reuses the earlier same-revision scan.
Reviewed d003077f0b7ce97622adb7a53f1fe76653433c5c: its direct binding to a
matched provider is applicable; its stream types, addresses and wrapper removal
are unrelated and not imported. The existing donor Pathfinder query also uses
reference parameters. BFME2's verified provider and native caller operands
establish this repair; no donor layout claim is added. The freshness stamp is
under 24 hours old; the committed donor pointer and checkout agree. No donor
inputs or success stamp are changed.

Acceptance:
- Ordinary ./build.sh on both consumers and provider: 32/32 matched rows;
  all 39 strings and 22 float literals verified; no baselines/skipped checks.
- Bounded link_check.py --prepare-current before and after: all three explicit
  sources have strict reusable compiler receipts and pass the normal byte gate.
  These establish self-strict compilation, not strict LINK placement/closure.
- Six EH rows EXACT; no baseline exceptions or missing objects.
- New-variants admission, class gate, declared-definition check, pin consistency,
  check_csv, whitespace and enforced converged-data check pass (eight protected
  addresses, zero second names/unjudged rows).
- Shadow data check retains one existing wrong-name issue: update's static
  ?$S1@?N@??update@AIAttackMeleeHordeWaitPathState@@UAE?AW4StateReturnType@@XZ@4IA
  at 0x00A01DF4. Full section/relocation identity proves its binding unchanged.
- Placement resweep of the three units: zero bodies, zero pins.

Paired local preview uses the same index for both versions: measurement
147cfae2cb, 2026-10-14 07:27, SHA256 in index.json. The committed link status
at de7bb30890 is discovery evidence only, not the before/after baseline.
The provider postdates this index and is absent from it. Therefore the legacy
preview replaces two unresolved pointer-overload names with the correct names,
without reducing counts: 19 findings across two consumers before and after,
zero LINKED bytes. All other findings are unchanged. The provider's actual
current definition and the two correct consumer bindings are independently
verified, but no preview or closed-strict linking gain is claimed.

Permitted --refresh --current-ledger preview refuses 731 missing objects.
current-ledger-after.txt retains the exact refusal. It does not start a
whole-tree compile. No census build/measure/history, full link cycle, nightly,
boot or publisher verification runner was started. Census/index/status files
are unchanged. New authored coverage is zero; two verified binding repairs
are the improvement.

Remaining consumer blockers are enumerated in paired-link-after.txt:
updateInternal's unit has two other unresolved names, three duplicate names,
seven COMDAT findings and two selected-body findings; computeAttackPath has
moveAllies, Object::rva0028CE7B and selected computeApproachTarget. Current
provider closure and actual placement await runner census/compiler evidence.
Saved objects/source backups and reproducible proof.py remain under ignored
build/attack-view-link-20261014. This attempt adds no banked reconstruction.
