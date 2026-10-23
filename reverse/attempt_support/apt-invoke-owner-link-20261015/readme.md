Independent Apt callback provider ownership verification

Rebase handoff: upstream d9f026ec39 independently landed the same provider
repair while this seat worked from its older pulled base. The final commit
keeps upstream source and its sole ledger row, and records only this seat's
independent paired verification. The +941 result below is against the saved
base, not an incremental gain over updated origin/master. No duplicate row or
new progress claim is retained.

Base commit: 3fab4cc2cc0aa7eb18bf0ef1613c1a8cbba41306.
Frozen runner census: ac77c85054, 2026-10-15 14:25 UTC. context.json records
its SHA256. The committed census supplies discovery, not a new measurement;
no per-row data-back artifact was available or used for ranking.

AptInvokeWrappers.cpp defined an unused exclusive 149-byte unsigned/int
callback beside the identical select-any emitter required by BannerUIUpdate.
Move its existing 0x0021639A row with add_match --replace-existing to that
emitter, and remove the unused definition. No name, ABI, layout, extent,
compiler flag, pin, alias, allowance or header changes. Identity remains the
existing address-derived callback name; this repair establishes ownership,
not a newly recovered semantic identity.

Local proof and acceptance

Before and after strict preparation verifies 13/13 rows across the two units,
11 string literals, one compiler float and zero named imports. Both resulting
objects have self-strict reusable receipts. The complete native 149-byte twin
has the same relocation digest in both original objects. The surviving Banner
object is identical except for its COFF timestamp. All 17 retained wrapper
COMDATs and 33 Banner COMDATs retain their bytes, extents and relocations.
Normalized nondebug sections change only by removal of the unused callback,
its 26-byte EH handler/unwind section, its 44-byte EH data, and its safe-SEH
entry. Directives and all other sections remain identical; the only external
binding change is removal of that callback definition.

proof.py uses ignored before snapshots under build/apt-invoke-owner-link-20261015,
current objects and independent copies of the same frozen index. It refreshes
both units together, and records exact paired findings in proof.json. The
shared index, census and committed link_status.csv are not modified.

Local legacy prediction: AptInvokeWrappers moves from one duplicate to zero
findings, recovering 941 existing matched bytes. Banner loses that duplicate
and retains five unresolved names plus its separate Rva00216332Call duplicate.
Combined legacy predicted linked bytes: 0 -> 941. New authored unique C++
coverage is zero. This has self-strict object currency; it is not closed-strict,
a fresh census, executable placement or runtime evidence. The ordinary two-unit
link_check CLI exits 1 because Banner retains independent findings.

The declared-definition, class, no-new-variants, CSV and whitespace checks pass.
EH: eight EXACT, zero nonexact, zero baseline, zero missing objects.
Data facts are unchanged: one pre-existing baselined wrong-name binding for
TheRva00222A8BTarget at 0x009FE4CC, zero outside-baseline findings. Converged
checks cover eight addresses with no second names or unjudged rows. The
wrong-name finding needs a separate canonical-global repair; local legacy
LINKS does not prove data closure. Placement resweep: zero bodies, zero pins.
acceptance.txt and link-after.txt record the checks. Hooks repeat the required
checks. Both files and the retail RVA were claimed before editing.

Reference review and handoff

BFME1 repair d5043e1658bdf46d39281a2e975e9e0145221555 removes unused exclusive
Coord3D definitions and rehomes their rows to identical inline emitters. Its
ownership repair applies directly; b66f793f3d886b07b8698ff04aa5ce9707eb896a
also preserves existing consumer COMDATs while converging providers. No donor
source, layout or ABI is imported.

Verified BFME1 gitlink/checkout stays a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched as 9f335a9ec9ff012c5103195540fa82ccc3e7877e. Its
foreign-claimed freshness update still needs the controlled old/new full-byte
comparison and layout reconciliation. A prior unchanged old-input baseline
left 2806 of 2982 stale TUs after 21 minutes; it is not repeated here and no
freshness success stamp is written.

Banner's remaining unresolved names: GetStateString, ControlBar::bfmeShowDN,
and GameLogicFwd rva0023D075/rva0023D096/rva0023D0AC. The separate callback
duplicate and pre-existing data name remain independent follow-up work.
No full census, link cycle, nightly, boot or scheduler runner was invoked.
Model: gpt-6.1-sol.
