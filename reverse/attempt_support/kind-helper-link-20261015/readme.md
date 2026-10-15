# Remove unused competing KindOf helpers

Base: 318028c9781ce6b1470d6fda394a599152db2708. The local index measures
commit a2839ea429 (2026-10-15 13:35), underlying census 5986a99448 (04:52).
Index SHA256: c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37.
The committed link-status measurement differs; no index, census or status was
rewritten. Both edited files and the clear provider were claimed.

The two private BitFlags<116> views emit the same nonretail 14-byte clear
copy (digest abe257faeb2e), calling memset. The native clear at 0x00666E80
is owned by SupplyTruckAIUpdate.cpp and its whole 14-byte body verifies
(digest cd02e976ed1c). ScriptConditions_evaluateTeamStateIs.cpp additionally
emits an unused 18-byte ThingTemplate::isKindOf(int) wrapper (8ef3c75c1173);
SupplyTruckStateMachineOnEnter.cpp emits an unused 20-byte BitFlags<116>
constructor (a330e1fa3cdf). These are incidental copies, not ledger bodies.

TU-local dllimport/forceinline annotations retain the original inline code
while suppressing those external copies. No retained code or data changes,
replacement imports, pins, aliases, class views, ledger or baseline edits.
The compiler-emission technique follows BFME1 repairs reviewed at
66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation copies) and
c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo constructor copies).
No donor identity, behavior or layout was newly imported; target bytes and
object relocations establish this repair's applicability.

## Paired local evidence

proof.py refreshes only both explicit consumers and the unchanged provider
in two copies of the same index, using saved original and current objects.
Script findings fall 5 -> 2 (two losing COMDATs and one wrong-selected finding
removed). Supply-truck state-machine findings fall 3 -> 0 (two losing COMDATs
and one wrong-selected finding removed). Its 439 existing nonpadding retail
bytes become locally linkable; script's 9907 remain blocked by the unchanged
TransportStatus destructor and ObjectTypes::prepForPlayerCounting references.
The native provider's other link findings remain identical, including its
wrong-selected clear from other units. No provider closure gain is claimed.

All 170 script and 12 supply-truck retained COMDATs are byte-and-relocation
identical. Every other nondebug section, external binding and directive is
unchanged. None of the four removed bodies has a retained nondebug relocation
caller, and no replacement import reference appears. The exact removed bytes,
digests, object hashes, before/after findings and unchanged provider findings
are recorded in proof.json. Original objects, source snapshots and strict
receipts remain under build/script-kind-helpers-link-20261015 and
build/supply-kind-clear-link-20261015; the proof uses these ignored snapshots
without modifying the shared object cache or index.

./build.sh passes both edited files (50/50 and 1/1). Final bounded preparation
of both consumers and native provider passes 52/52 rows with strict reusable
receipts, 3 string literals, 9 compiler float literals and 0 named imports.
EH verification: 22 EXACT, 0 nonexact, 0 missing objects. Converged data:
8 addresses, 0 second names, 0 unjudged rows. New-variants admission,
declared-definition checks, check_csv (91512 functions / 15481 symbols /
464 data rows) and diff whitespace pass. Placement rescan: 0 bodies, 0 pins.

The data-name shadow check reports two pre-existing static guard-name findings
at 0x00A02E28 and 0x00A02E30 in the script unit. The existing data-check reader
was run against saved original and current objects: both findings are identical
(proof.json). No data baseline change or new data finding.

These are strict byte receipts and a legacy local link preview: 0 -> 439
locally linked bytes, six fewer findings, zero new authored C++ bytes.
No closed-strict closure, actual link placement, full census, nightly or boot
result is claimed. Full runners require a maintainer. The script's two missing
providers and the native provider's other blockers remain follow-up work.

## Scope and handoff

The indexed same-clear-digest sweep found these two consumers; other emitters
(DumbProjectileBehavior, ThingTemplate, WeaponSet, HordeUpdate and Player)
have a different nonretail clear digest and need their own evidence. Do not
apply the annotation blindly to required out-of-line callers. The particle
DebugDisplayBody ranked item was already byte-exact and locally linkable
without an edit, so no improvement is credited there. The BFME1 submodule
freshness update remains with the worker holding file:reference/open-bfme-1;
this seat preserved the last verified pointer and did not stamp freshness.
