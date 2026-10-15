# Overridable inline-walk link repair

Four private BFME 2 views emitted the same 15-byte non-retail
`Overridable::getFinalOverride` COMDAT. Each existing inline implementation
checks the +4 next pointer and calls the rowed nonconst
`friend_getFinalOverride` at RVA `0x001E35DF`. Keep those bodies visible but
mark them imported and force-inline, suppressing only their unused outlines.
The retail provider remains the 14-byte recursive loop in
`ThingFactoryNewOverride.cpp`, digest `3b5ad65048a5`; its strict preparation
passes 4/4 rows and judges that helper retail.

Consumers: `CrateSystemNewCrateTemplate.cpp`, `LocomotorCtor.cpp`,
`Rva0030C1FCOwnerCtor.cpp`, and `INIParseWeatherDefinition.cpp`. Identity,
layout and donor uncertainty remain as documented in their existing source
and ledger. No type, layout, semantics, pin, alias, flags or shared-header
change. BFME 1 revision `a7c38d3b2597121f178ab5190b3062478823257d` and repair
`66b19a8e95a4add525ef808fcea088e306798e2b` were reviewed for the inline-import
compiler mechanism; its Apt repair is a technique lead, not target identity
or layout proof. The BFME 1 override views were also surveyed; no donor body
was imported.

## Acceptance

- Strict reusable preparation before/after: all 18/18 consumer rows. Ordinary
  `./build.sh` also passes 18/18, five strings and six float references.
- EH before/after: 8/8 EXACT, no baseline or missing object.
- Paired current-object local previews against unchanged index `a2839ea429`
  (2026-10-15 13:35, original census `5986a99448`): crate 3->2 findings,
  locomotor 3->2, river owner 6->5, weather 2->1. Exactly four wrong helper
  COMDAT findings removed, with no new finding or selection change.
- All 61 retained COMDATs and all retained nondebug section bytes, flags,
  definitions, symbolic relocations, external/weak bindings and data facts
  are identical. No retained relocation addresses a removed helper. The
  admitted variant sets do not grow. The removed copies share digest
  `40e2e656e50a`; provider selection for all remaining copies is unchanged.
- Enforced data and converged-data checks pass; class and declared-definition
  checks pass; placement sweep finds zero new bodies or pins.
- Provider and all four consumers were checked together. Each has a reusable
  self-strict receipt, which does not establish closed-strict closure. The
  legacy preview still links none of the five units. New authored bytes and
  linked-byte gain are both zero. No full census, link.exe, closed-strict gain
  or whole-game verification is claimed.

## Remaining blockers and scope

The crate unit still needs `Rva0031AB1ENode`'s constructor and the crate-pointer
vector push_back. The locomotor needs its destructor and a correct selected
xfer provider. The river owner needs four virtual callees and its deleting
destructor COMDAT reconciled. Weather needs the field table `g_00BE2C10`.
The provider unit retains a wrong selected ThingTemplate assignment provider.
Exact decorated names are in `link-all-after.txt` and the paired proof.

The same-name family was swept: ThingFactory/InGameUI/AIUpdate reach shared
header views, requiring separate shared-dependency work; W3DSnow uses a
recursive inline body with a previously recorded failed declaration-only
trial, rather than these four one-hop wrappers. They were not edited or
retried on unchanged evidence.

BFME 1 freshness remains pending under another worker's live
`file:reference/open-bfme-1` claim. Retained verified pointer `a7c38d3b`;
official fetched master `95eeb3be`. No success timestamp or pointer update was
made. Evidence JSON records the measurement hash and source/object hashes;
before snapshots and the one-off proof remain under the scratch path in
`reproduce.json`. No protected baseline or verifier was changed.
