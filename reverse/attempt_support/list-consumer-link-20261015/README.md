# Particle/giant-bird list comparison repair, 2026-10-15

At BFME2 base `42cc2c5532`, give W3DFXParticleSystem.cpp and
GiantBirdAIUpdate.cpp TU-local typed list-iterator comparisons. This is the
existing NetPacket.cpp/InGameUI.cpp recipe: the comparison is exactly the
STLport `_M_node != other._M_node` operation. Their /O1 /G7 compilations
otherwise emit an incompatible external `_List_iterator_base::operator!=`.
No game body, compiler setting, ABI, layout, identity, data binding, retail
extent or ledger row is changed.

## Controlled result

Both phases refresh the two genuine current objects together in independent
in-memory copies of the same runner-provided index: update commit
`19a2565407`, census commit `5986a99448`, index SHA-256
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
Original objects were saved only after strict byte preparation with the
original sources/current dependencies. The index and census status are not
rewritten. link-proof.json records the exact before/after findings:

- W3DFXParticleSystem.cpp: 2 -> 1 findings; unresolved
  `?g_bfmeVal991@@3HA` remains (1,710 existing authored bytes).
- GiantBirdAIUpdate.cpp: 2 -> 1 findings; unresolved
  `?consume@Rva003909FAObj@@QAEXPAXHH@Z` remains (649 existing authored bytes).

Each removed finding is the non-retail list-base comparison. Legacy local
LINKED is **0 -> 0 bytes**. New authored matched bytes: zero. This establishes
two fewer COMDAT blockers across 2,359 existing authored bytes, not new
self-strict placement, closed-strict gains, a new census, or executable linkage.
Maintainer-only broader verification remains outstanding.

object-proof.json proves all 35 retained particle-unit COMDATs and all 31
retained giant-bird-unit COMDATs have identical bytes and relocation digests.
Each unused external 18-byte comparison is replaced with one unused local
12-byte comparison. No nondebug code/data relocation references any removed
or added helper. The only external-binding change is removal of the rejected
helper; all other normalized nondebug sections, relocations and directives are
identical. Automatic local labels, section indices and .sxdata symbol indices
are normalized by their actual targets.

identity-proof.json independently compares the genuine baseline and changed
objects using upstream's shadow checker: all three pre-existing findings are
identical (GiantBird consume binding is unowned, Object getBodyModule/getContain
have divergent definitions). This repair leaves that identity debt unresolved.
Existing target-derived and donor-derived source evidence is preserved.

## Acceptance

- Original and repaired `link_check.py --prepare-current` for the two owned
  sources: strict reusable receipts, 4/4 matched rows; string, float and import
  checks pass. No other sources prepared.
- `./build.sh` both sources: 4/4 matched, reference checks pass.
- Ordinary `link_check.py` both sources: exactly the remaining unresolved
  names above; expected exit 1. Paired proof: each findings count 2 -> 1.
- `link_check.py --new-variants` both sources: pass.
- `eh_verify.py` both sources: 3/3 EXACT, zero baselined or missing objects.
- `data_check.py --enforce`: zero findings; `--converged`: eight addresses,
  zero second names or unjudged rows.
- `find_declared_unmatched.py`, `class_gate.py`, `git diff --check`: pass.
- `place_bodies.py` both sources: zero bodies, zero pins.
- Session-start `check_csv.py`: pass (91,177 function rows).

Proof scripts run from repository root using saved original objects in
build/list-consumer-link-20261015; scratch binaries are not committed.

## Queue and reference review

Started with `repair_queue.py link` and the current `link_rank.py` workflow.
`link_check.py --fetch-index` retained the newer local index and fetched the
published object store. Current local checks show six served candidates are
already link-clean: AIAttackApproachTargetStateOnExit.cpp,
Rva000C4069PristineQuery.cpp, ParticleSystemDebugDisplayBody.cpp (also claimed
by another worker), AIIdleStateUpdate.cpp, AptMpGameSetupRefreshMapList.cpp,
and TerrainLogicWaypointLookups.cpp. They were not edited or claimed.
Rva000B8F5AMapErase.cpp has six current findings (tree comparison plus separate
allocator/less/erase issues); its inspection claim was released without edits.
Rva00525ABFXfer.cpp has an already recorded vcall-thunk DIR32 false reject;
no retry or source workaround. Rva00082EF5Ctor.cpp additionally needs shared
BfmeE16 vector/allocator reconciliation; not edited or claimed.

Reuse the preceding Horde comparison donor review at committed BFME1 pointer
`a7c38d3b2597121f178ab5190b3062478823257d`. No donor source, ABI or layout is
imported: library-helper ownership is the applicable principle, and local
BFME2 recipes plus object/byte evidence justify this change. Official master
was fetched; tip `75ff0c1485a68eafb10344670711edbee8679b62`. The new linking-related
commits since the preceding reviewed tip `e27a65cb6` are blocked attempt logs
(`75ff0c148`, `752d1260d`), with no new repair to transfer. The submodule stays
clean at the committed pointer. Another worker still owns
file:reference/open-bfme-1. Full old/new reference verification remains blocked
on previously recorded stale/missing inputs and a stalled MSVC baseline; no
unchanged full attempt repeated and no freshness-success timestamp written.
