# AIGroup chain iterator link repair

Base checkout: 11559f8d90. Census index: 147cfae2cb, 2026-10-14
07:27; SHA256 recorded in object-proof.json. The committed link_status.csv
measures 67e1365aa9 and was used only for discovery. No index, census status,
ledger rows, pins, headers, baselines or data owners changed.

AIGroupChain00472B54.cpp emitted a 17-byte int-map iterator prefix-increment
COMDAT, judged wrong against the standalone 20-byte retail body at 0x00169ED0.
The existing provider is stlport_map_int_int.cpp, digest 4efff003592f. The
matched 314-byte chain parent already inlines the header's increment expression
and calls the established _Rb_global<bool>::_M_increment implementation.
An explicit dllimport/forceinline specialization preserves that expression while
suppressing the unused standalone wrapper. There is no new import reference:
all strong, undefined and weak bindings are identical as sets. The annotation
names the already-rowed real template specialization, not a new identity.

Target basis: existing parent row and its named call relocations, complete
provider row at 0x00169ED0 and its byte verification. The expression comes from
the existing STLport 4.5.3 dependency; no layout or identity is inferred from
similar bytes alone. The parent's map layout and behavior are unchanged.

Reference review: verified clean BFME 1 gitlink 23b143233b5a8664a3bdf8572df6d905c310a5a1.
Donor d2e21369067f2f2c762c1c7ec2792c75f1ecf53d removes non-retail forwarding
constructors; de59a7e9f891b3ed2d4221d151ca881f4b75a583 reconciles private helper
COMDATs without changing matched callers. Those are technique leads; this
local repair uses BFME 2's own template/provider evidence. No donor code imported.
Official master fetch now resolves to bc990782485c4111aa72d4fb8f8d00bb82e12f5b.
The old-input comparative full-gate baseline remains incomplete (recorded
CPU-bound MSVC stalls in build/bfme1-freshness-blocker.txt and
build/runner-bfme1-freshness-blocked.txt); preserve the verified pointer pending
complete comparison. No new freshness-success stamp or pointer update.

Acceptance:

- Ordinary byte gate: 2/2 source rows exact. Explicit bounded prepare-current
  for consumer and existing provider: 21/21 rows, strict reusable receipts;
  zero skipped/baselined string, float or import checks. Final annotated
  consumer repeats 2/2 with strict currency.
- Before/after snapshots: one 17-byte COMDAT removed, none added; all 37
  retained COMDAT raw bodies, sizes and relocation digests identical.
  All 43 retained nondebug sections agree after normalizing local labels by
  target section bytes and symbol offsets, and .sxdata symbol-table indices
  by handler names. Strong, undefined and weak binding sets unchanged.
  Scratch proof script and object snapshots: build/link-seat-current/ai-proof.py.
- EH graph: 1/1 EXACT. Frozen-source, class gate, new-variants admission,
  converged-data check (eight addresses, no second names/unjudged rows),
  shadow data check (zero findings), CSV and whitespace checks pass.
- Placement resweep: zero bodies, zero pins.
- Paired same-index bounded legacy preview, with the current retail provider
  included on both sides: consumer goes one wrong-COMDAT finding -> zero;
  LINKS 0 -> 324 existing authored bytes, including its 10-byte EH handler.
  The unchanged provider retains independent allocator/map helper blockers;
  it is not counted as newly linkable. No dependency changes are claimed.

New authored C++ bytes: zero. Self-strict object currency is verified;
closed-strict dependency closure, actual link.exe placement and a fresh census
were not measured. No maintainer-only verification runner was started.

Triage handoff: TerrainLogicWaypointLookups' remaining _M_find conflict is the
already-recorded C1001/context blocker (re_attempts.log entry 51909); release
without retry. ReinforcementEntryParser's pair constructor suppression was
already refused (entry 50255), so no edit or repeat trial. Multiple higher-ranked
blockers are already repaired in the refreshed objects. All triage claims released.
