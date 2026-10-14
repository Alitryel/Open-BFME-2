# Formation handler GameClient binding repair

Base: `e7a0806313c524852de5f3748d84d73eb1e67d4c`.
Available census index: `147cfae2cb`, 2026-10-14 07:27; its SHA256
is recorded in index-meta.json. The repair queue's committed status reports
`67e1365aa9`, 2026-10-13 16:47, and is used only for discovery.
No per-row data-back artifact ranking was used.

The formation second-button handler declared `TheGameClient` as a pointer
to its private `ClientFrameSubsystem` view. That spelling requires a different
linker datum from `GameClient *TheGameClient`, already defined by GameClient.cpp.
The consumer now declares the existing global's type and casts to its local
view at the slot-18 call. Neither the view layout nor the call changes.

## Target evidence

The 445-byte matched handler at RVA `0x00431C9D` has DIR32 relocations at
body offsets 144 and 162. Both retail operands address VA `0x00DFE77C`.
The existing provisional data row at RVA `0x009FE77C` assigns the slot to
`?TheGameClient@@3PAVGameClient@@A`, defined by the unchanged provider.
The consumer's former spelling was `?TheGameClient@@3PAVClientFrameSubsystem@@A`.
This repairs a binding to the existing inventory; it does not promote that
data row or establish another class identity or layout.

The before/after COFF witness checks every non-debug section's bytes, size,
flags and index, all relocation tuples after the intended name substitution,
and all external definitions and references. Consumer code is unchanged;
only those two data relocation names change. The provider's complete object
hash is unchanged. Both objects have current strict reusable self receipts.
The exact object and receipt hashes and retail reference witnesses are in
object-proof.json. The read-only proof scripts use scratch snapshots under
build/formation-gameclient-link-20261014; binary objects are not committed.

## Donor review and freshness

The clean BFME 1 checkout remains at the previously verified pointer
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. Official master was fetched at
`bc990782485c4111aa72d4fb8f8d00bb82e12f5b`. The overdue full byte comparison
and affected donor-cache refresh remain unfinished; neither pointer nor
freshness-success stamp was advanced by this repair.

BFME 1 donor `908413c254f83e1f402b991541d4cf68db48ea4e` changes Apt pool
externs to their existing owner types and casts at view accesses. That binding
repair principle applies here; none of its source, addresses or layouts was
imported. BFME 2 repair evidence in gameclient-global-link-20261013 already
establishes the same mismatch for PeerThread and ParticleBaseConstructor.
A same-cause sweep finds an unused declaration in RenderParticleConstructor.cpp;
it emits no corresponding reference or unresolved debt and is left alone.

## Acceptance and limits

Before and after, `link_check.py --prepare-current` on the explicit consumer
and provider passes all 4 function rows and 2 data rows, and issues strict
reusable self receipts. The final `./build.sh` passes those rows plus its
string, float and import checks. EH checking has zero EH rows and no failures.
Class, declared-definition, new-variant admission and whitespace checks pass.
`place_bodies.py` finds zero additional bodies and zero pins.

The paired same-index legacy preview (`link_check.py --refresh` on those two
sources) removes exactly one unresolved singleton name from the consumer:
3 unresolved names become 2. Its duplicate/COMDAT findings and every provider
finding remain identical; link-delta.json records all categories. The paired
snapshot proof overlays the before or current explicit objects in memory and
checks the index hash is unchanged. LINKED remains zero in both previews.
Self-strict object verification is established; closed-strict closure, a full
link/census measurement and new authored or linked bytes are not claimed.

The consumer/provider enforced data check falls from one wrong-name finding
to zero. Converged-data checking reports 8 addresses, no second names and
no unjudged rows. No pin, alias, hatch, baseline, header or data ledger changes.

Remaining consumer blockers are the address-named vtables `g_00C3C97C` and
`g_00C3C9A0`, plus duplicate/COMDAT ownership of
`WaitForSecondButtonDownStateHandler::Restart`. GameClient.cpp retains
independent unresolved, COMDAT and selected-provider debt. No maintainer-only
verification runner was started.
