AI enemy-search player-name emitter repair

AIClosestEnemySearch.cpp's existing Player::getPlayerName inline definition
now uses imported forceinline emission, preserving its member access at +0x4C
while suppressing a surplus four-byte standalone COMDAT. The matched caller
already inlines that accessor. No import reference, external dependency, pin,
alias, compiler option, header or ledger row is added.

Target evidence remains the existing native enemy-search worker at
0x002FF07B..0x002FF8DD (2146 bytes, RET 28), its named filter relationships
and WorldBuilder twin. Its call to getControllingPlayer followed by the
name-field comparison is preserved by complete byte and relocation checks.
The original source/ledger distinguish target facts from ZH AI::findClosestEnemy
semantics. This change makes no new standalone getter identity or layout claim.

Measurement: base checkout 8add80fe9f222932e835abbd296859fac944c015;
runner index commit 4b7e7091c4, 2026-10-15 12:36 UTC. measurement.json records
the index hash. Both strictly current original and repaired objects were
independently refreshed into copies of that same index. The one COMDAT finding
becomes zero; no new finding appears. Ordinary link_check.py changes from
0/1 to 1/1 clean and predicts 0 -> 2,142 existing authored bytes, excluding
padding. Census status and history are unchanged.

proof.json records object/source/receipt hashes. All 59 retained COMDAT bodies,
extents and relocation digests are identical. Every other nondebug section,
symbolic relocation target, external binding, weak external and linker directive
is unchanged; SafeSEH indices compare by symbol name. No retained relocation
targets the removed accessor. Saved original and repaired sources, objects,
receipts and the executable comparison remain in ignored
build/ai-player-name-link-20261015.

Acceptance:
- Bounded link_check.py --prepare-current before and after: strict reusable
  compiler receipts and 4/4 complete rows exact, including three funclets
  resolved through the unchanged parent EH graph despite local label changes.
- Independent ./build.sh: 4/4, two strings and five compiler float literals;
  no skipped/baselined references or named imports. EH verify: one row EXACT,
  zero nonexact, baselined or missing objects.
- Frozen-definition and class gates pass. New-variants admission passes.
- Converged-data enforcement: eight addresses, zero second names or unjudged
  rows. Shadow data check retains one wrong-name finding for the existing
  compiler static guard at 0x009FF108. The optional --enforce check exits 1
  both before and after, with exactly the same unbaselined finding; no data
  binding changed. This independent data-owner debt is not repaired here.
- place_bodies.py: zero additional bodies or pins. CSV and whitespace checks
  pass.

This is a legacy local link-preview improvement with strict compiler-currency
and full byte evidence. New authored C++ bytes: zero. Placed self-strict gain,
closed-strict closure and whole-game linkage are unmeasured. No full census,
link cycle, nightly, boot or scheduler runner was started. The index contains
two copies of this getter; this is its only losing consumer. Other current
definitions require their own evidence and are unchanged. Since no dependency
or provider edge changes, the paired section proof also preserves other
consumers' definitions and references.

Donor review: retain verified clean BFME1 gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed upstream repair
66b19a8e95a4add525ef808fcea088e306798e2b and its verification message:
imported forceinline removes surplus competing emitters without adding import
references. That mechanism applies; its Apt identities, addresses, layouts and
byte-gain measurement do not. This repair imports no donor code. Official
master fetched at 3a5eb7a27d25a9192ca16872ae5446a5cde592f1; another seat's live
file:reference/open-bfme-1 claim still prevents advancing donor inputs.
Comparative full verification and affected donor refresh remain outstanding;
no pointer advance or successful freshness stamp is claimed.

Discovery: repair_queue.py link, link_rank.py help/top/near/file and a current
object check. File and parent RVA were claimed before editing. No per-row
data-back artifact or manufactured ranking was used.
