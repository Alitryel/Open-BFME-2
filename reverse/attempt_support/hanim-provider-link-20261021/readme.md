HAnim setter provider move: measurement blocked, 2026-10-21
==========================================================

At census c7845fd6e7 legacy previews, W3DMeshHolderHold.cpp (200 unique
nonpadding bytes) and HAnimComboDataSetHAnim.cpp (37) both fail duplicate
Set_HAnim. Camera holder units already link at 141 and 50; leave them alone.

Declaration-only Set_HAnim breaks both 90-byte mesh holder factories:
unknown alias effects reload the holder and select EAX instead of ECX,
producing longer bodies. OceanWater documents the same visible-body need;
it also has unrelated destructor/transform/flush blockers. Do not repeat
that declaration-only trial.

The better repair is to keep the visible noinline exact setter in
W3DMeshHolderHold.cpp, repoint its existing 0x001007B0 37-byte row there
with add_match --replace-existing, and delete the old standalone source.
This passed build.sh 11/11, eh_verify EXACT 2, frozen-file checking and
strict prepare-current. No new name or address, source shape or code bytes
are invented. Attached patch preserves this verified row/provider move;
apply with tools/add_match rather than manually mutating the ledger.

Cannot accept a measured gain yet: legacy link_check refreshes explicit
objects but retains the removed standalone unit and still reports its
old strong definition as duplicate. --refresh --current-ledger correctly
drops removed providers but refuses ten missing current-ledger objects
(including GameEngineMillisecondScale and BfmeThingClassNames). It performs
no tree compile. No maintainer-only cycle was attempted. Do not count an
expected +237 as verified linked bytes. Restore original row and source,
record blocker and release claims. Reopen when a current provider universe
is available or the legacy removed-unit preview limitation is fixed with
separate tooling evidence/tests. Existing source provenance and noinline
callee semantics remain intact; no source naming claim is changed.
