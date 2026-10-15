# Melee squish Object predicate binding

AIAttackApproachTargetStateOnEnter.cpp called native RVA 0x0028CECF through
Rva0028CECFOwner, an unresolved stand-in. ObjectRva0028CECF.cpp already owns
that 104-byte predicate as Object::rva0028CECF. Declare it on the consumer's
existing Object view and use that declaration at all three calls. Remove the
unused stand-in declaration and its obsolete symbols.csv pin. Existing other
callers already use Object; remaining stand-in type occurrences are unused
declarations or parameter types, not references to the removed method pin.
No new row, alias, class layout, compiler flag or header is introduced.

## Evidence and scope

Base commit ec4c8af08ea4f084e572c73c9c2248e61c74b1bc. The affected 629-byte
AIAttackMeleeSquishState::rva0034D98B at 0x0034D98B has REL32 operands at
0x0034D9D0, 0x0034DB3E and 0x0034DB76. All three independently target
0x0028CECF in retail. The original and canonical declarations have identical
thiscall bool() ABI; the receiver was already an Object pointer. The provider
walks the +0x274 containment chain and checks its existing template/holder
fields. Identity and field evidence remain those documented by the matched
provider; this repair adds no donor-derived name or layout assertion.

Consumer and provider were file-claimed before preparation. The frozen local
index records update a2839ea429 at 2026-10-15 13:35, census 5986a99448 at
04:52; its SHA256 is in index-meta.json. Published-index fetch retained this
snapshot. Committed status 4b7e7091c4 served only discovery. No per-row data-back
artifact was available or used, and no ranking was invented from missing data.

The dedicated reference review inspected BFME 1 COMDAT repair c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
and searched its Object binding/canonical repair history. Constructor emission
suppression is inapplicable to these direct calls. This local name repair is
proved by BFME 2 operands and the existing matched provider. The verified
BFME 1 gitlink a7c38d3b2597121f178ab5190b3062478823257d was retained; official
master fetched as 95eeb3bef370a7cd730b0ad5f228c317c8756e72. The overdue update
is owned by the foreign live file:reference/open-bfme-1 claim. No successful
freshness stamp or pointer update is claimed.

## Acceptance and measured effect

- Bounded strict preparation before and after and ./build.sh pass 30/30 rows,
  38 string literals and 14 compiler float literals, with no skipped references.
  EH verification: five EXACT rows, zero nonexact/missing/baseline use.
- proof.py compares all retained nondebug section bytes, flags, definitions,
  directives, symbolic relocations and external bindings after normalizing only
  the old predicate name. Everything agrees. It separately verifies all three
  retail branch targets. The provider object is byte-for-byte unchanged.
- Paired in-memory link previews replace only these two objects in separate
  copies of the same frozen index. Consumer findings fall 10 -> 9, solely by
  removing the unresolved stand-in. Provider stays LINKS with no findings.
  Existing variant findings are identical; none is added. Index hash unchanged.
- Ordinary local link_check exits 1 for the remaining consumer blockers and
  reports the provider LINKS. Legacy LINKED bytes stay 104 -> 104; consumer's
  existing 10,101 nonpadding bytes remain blocked. Authored C++ gain is zero.
  Self-strict receipts prove input currency; closed-strict and executable
  placement gains are unmeasured. No full link, census, nightly or boot run.
- Data facts are identical before/after. data_check --enforce exits 1 for the
  pre-existing wrong-name static at RVA 0x00A01DF4, outside its baseline:
  ?$S1@?N@??update@AIAttackMeleeHordeWaitPathState@@UAE?AW4StateReturnType@@XZ@4IA.
  No data finding is added or suppressed. Enforced converged-data check passes
  all eight addresses with zero second names or unjudged rows.
- Class gate, declared-definition check, pin consistency, CSV consistency and
  whitespace checks pass. Placement resweep: zero bodies, zero pins. No verifier,
  baseline or whitelist change. Hook checks remain mandatory.

Remaining consumer blockers: chooseVictim unresolved; three duplicate bodies
(onEnter, rva00340F25 and rva003430A3); two competing PartitionFilter destructors
and their vtables; selected StateMachine::isInAttackState is not retail's.
The exact names and unchanged variant findings are in object-proof.json and
link-after.txt. These need independent provider/class reconciliation.

Run proof.py from the repository root using saved original objects under
ignored build/object-container-predicate-link-20261015/before and current
strict objects. Recreating them requires the base commit and identical verified
inputs. The JSON is durable session evidence; this proof is not a portable gate.
