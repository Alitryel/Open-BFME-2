# Rva005D4C61 vtable reconciliation

Base: `a06317b34346aad1ebcd774de1943539ce00bc7c`.
Frozen local index SHA256:
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
Its measurement is `a2839ea429`, 2026-10-15 13:35; underlying census
`5986a99448`, 2026-10-15 04:52. The committed status CSV is discovery evidence
only. No census, full link cycle, index publication or status rewrite was run.

## Target evidence and repair

Retail VA `0x00C75AAC` has two slots, `0x009D4E06, 0x009D4C48`, followed
by the string `_OnPosChanged` rather than another slot. These are the existing
matched deleting destructor and float callback of `Rva005D4C61`.
`Rva005D4C61Dtor.cpp` already declares both virtuals; its matched constructor
stores this table. `OpaqueScalarDeletingDtorsB16.cpp` declared only the virtual
destructor and emitted a competing one-slot table. Add the existing callback's
declaration to that view. The address-derived identity and callback signature
are inherited from the matched BFME 2 provider and target access evidence;
no donor identity or layout is promoted to a target fact.

The paired COFF proof checks both objects against the same index, before and
after. Only B16's table changes: four zero bytes and one DIR32 relocation become
eight zero bytes with a second DIR32 relocation to the existing callback.
All code COMDATs, other nondebug sections, symbolic relocations, weak externals
and existing external bindings remain identical. The provider object is
unchanged. The two emitted tables now agree in bytes and relocations.
No body, pin, alias, import, baseline entry or data claim is added.

## Acceptance and result

Before and after `link_check.py --prepare-current` passes 26/26 rows for the
two explicitly owned sources and supplies strict reusable current receipts.
`./build.sh` also passes 26/26 with string, float and import-reference checks.
The ordinary local preview and paired in-memory refresh agree: B16 loses its
only conflicting COMDAT and goes from local legacy LINKED 0 to 441 nonpadding
owned bytes. The provider stays LINKED 0 with its same unresolved
`?cb@DummyCb1@@QAEXPAX@Z`; its 247 owned bytes are not counted as a gain.
The two-source ordinary preview exits 1 for that preserved finding.

Self-strict byte verification and current receipts are established. Self-strict
executable placement and closed-strict closure are unmeasured. This is a local
legacy improvement, not a new census or closed-strict gain. New authored C++
bytes: zero.

Other checks: `find_declared_unmatched.py` and `class_gate.py` pass;
`link_check.py --new-variants` passes (the paired proof admits no new variant);
`eh_verify.py` reports two EXACT EH rows, none nonexact or missing;
`data_check.py --enforce` has zero findings; `--converged` checks eight addresses
with no second names or unjudged rows; `place_bodies.py` finds zero bodies and
pins; `check_csv.py` and `git diff --check` pass.

## Reference review and remaining work

Reviewed BFME 1 repair `9af805d8ed9f679b0b93f04ba1b7d7ff67119b62` (vtable
identity reconciliation). Its ownership principle applies; its rename, class,
addresses and ledger changes do not. Also reviewed incidental-emission repair
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9`; no suppression was used here.
Official master was fetched at `95eeb3be`; the verified checkout/gitlink stays
`a7c38d3b2597121f178ab5190b3062478823257d` while another seat owns the
reference update. No freshness-success stamp was written.

`proof.json` records the exact hashes and paired findings. `proof.py` requires
the ignored `build/listener-vtable-link-20261015/context.json` and before object
snapshots plus the frozen index and current objects. The base revision and
hashes identify inputs for an independent reconstruction. The unresolved dummy
callback needs independent target-backed identification; no alias or pin is
invented for it. B16's pre-existing Rva005DA7F5 variant is unchanged. Broader
link validation remains outstanding.
