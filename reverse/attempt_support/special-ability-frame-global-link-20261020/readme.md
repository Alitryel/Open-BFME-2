SpecialAbilityUpdate frame global binding, 2026-10-20

The 20 matched rows in SpecialAbilityUpdate.cpp pass their complete byte and
reference gates before and after declaring g_00E033D0 as int. The existing
provider Rva007ABC6FFrameRateInits.cpp and data row at RVA 0x00A033D0 already
own the signed spelling ?g_00E033D0@@3HA. The consumer alone declared unsigned,
producing unresolved ?g_00E033D0@@3IA. SpecialAbilityUpdateRun.cpp already uses
the signed provider. A whole-Code search found no further unsigned consumer.
No layout, global identity, data definition or pin is added.

Paired current-object link_check against published index e7a7769fe5
(2026-10-20 18:36): consumer 0 -> 5,211 nonpadding matched bytes; provider
467 -> 467. Before, the unsigned global was the sole blocker; afterwards
both units have no blockers. Both were prepared with strict reusable
receipts, and the consumer was re-prepared after the change. This is a legacy
index preview with self-strict objects; closed-strict closure, census gains
and executable placement are unmeasured. Authored C++ byte growth is zero.

Checks: ./build.sh consumer 20/20 rows, strings/floats/imports; strict
prepare-current provider+consumer 51/51 rows and 12 data rows; after-change
strict consumer 20/20; link_check before/after; new-variants; class_gate;
find_declared_unmatched; data_check --converged; git diff --check.

Donor review: BFME1 4483e88da1c2 recent linking repairs a411b334c,
3313189ad and c54305633 support existing-provider ownership, not target
addresses or layouts. The prior shared-node-allocator-link-20261020 donor
scan and verified pointer migration remain applicable; newer b0af542b7,
7b534cb1f and bc79c8fef concern ILT/data/vftable ownership and supply no
additional change here. This repair follows independently rowed BFME2 data.
t=8 model=gpt-6.1-sol.
