AIUpdate guard-order kind-mask link repair

AIUpdateInterfacePrivateGuardObject.cpp and AIUpdateInterfacePrivateGuardPosition.cpp
emitted unused private Thing::isKindOf (40B, d08f3bed52e8) and
ThingTemplate::isKindOf (41B, 659973b635dc) outlines. These competed with the
existing providers, producing a duplicate, two losing copies and a selected
wrong helper in each unit. Add dllimport to the existing forceinline definitions
to suppress the unused outlines. The guard bodies remain fully inlined, with
no new import reference or external binding. Established identity, layouts,
semantics and the original donor uncertainty remain unchanged.

Discovery used repair_queue.py link and link_rank.py. The committed link status
measurement ac77c85054 (2026-10-15 14:25) differs from the runner index. All paired
claims here use the unchanged index a2839ea429 (2026-10-15 13:35), based on census
5986a99448 (04:52). Its complete metadata and SHA256 are in object-proof.json.
No census/index/status/history, ledger, header, flags, pins, aliases, markers or
baseline changed.

Acceptance:

- Before and after strict reusable preparation pass both complete retail rows:
  privateGuardObject 0x00264D0E..0x00264D81 (115B) and privateGuardPosition
  0x00264BC2..0x00264CBB (249B). ./build.sh passes 2/2 and all literal/import
  checks, with nothing skipped.
- All five retained COMDATs and every retained nondebug section's bytes,
  characteristics, definitions and symbolic relocations are identical. The
  deleted helper sections have no incoming retained relocation. External/weak
  bindings and data facts are equal, and there are no new harmful variants.
  Remaining helper providers retain the same selection facts and loss decisions.
- Object.cpp (testStatus), Rva002907A1Finish.cpp (isMobile) and region.cpp are
  independently strict-current and byte-verified: 69/69 rows, 18 strings,
  four empty strings and one float. All five units link in the ordinary local
  preview. These providers have identical findings in the paired before/after
  preview using their current objects on both sides.
- Paired current-object consumer findings fall from four each to zero. LEGACY
  linked bytes increase 0 -> 364 for the two consumers, and 5,830 -> 6,194 for
  the five-unit cohort. These are self-strict receipts and a legacy local link
  prediction. No closed-strict closure, link.exe placement, full-game runtime
  result or new authored C++ byte gain is claimed.
- Enforced data and converged-data checks pass with zero findings/second names
  and zero unjudged rows. Declared-definition, class and whitespace checks pass.
  EH verification finds no EH-bearing row. Placement finds zero bodies or pins.

The existing BFME1 pointer a7c38d3b and repair 66b19a8e95 were reviewed. That Apt
allocation repair demonstrates the compiler emission mechanism; BFME2 object
and target evidence establish this repair. No donor identity or layout was
imported. Read-only fetch confirms official master at 95eeb3be. Another owner
holds the submodule claim; freshness verification remains pending under that
owner, with the last verified pointer retained and no success stamp written.

The AIUpdateInterface privateGuard units are the complete same-name local
forceinline family found by the scoped search. AutoHeal's shared-header family
has different flags and many separate dependencies; no acceptance for it is
inferred here. The earlier AIGroup iterator-signature blocker remains separate.
No maintainer-only runner was started. Before snapshots and the proof script
remain in ignored build scratch; reproduce.json identifies them. Source parents
and committed results preserve the repair and checked evidence.
