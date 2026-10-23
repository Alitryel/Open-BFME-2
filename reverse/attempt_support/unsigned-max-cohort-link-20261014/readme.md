# Unsigned max ownership repair, 2026-10-14

Two consumers no longer emit a nonretail external unsigned `_STL::max`
COMDAT. A TU-local overload preserves their already inlined comparison. The
verified 17-byte provider at 0x00013740 in stlport_basic_ios_init.cpp is unchanged.
No symbols, ledger rows, baselines, vendor headers or verifier rules change.

## Controlled result

Base checkout 7a79608ff3; runner census index measured at 147cfae2cb,
2026-10-14 07:27. Its SHA-256 and complete metadata are in context.json.
The committed link_status.csv is a different measurement (de7bb30890) and
was used only for discovery. The paired preview deep-copies the same runner
index and replaces only the three explicit current objects in memory.

| Consumer | Retained identical COMDATs | Paired legacy findings | Legacy linked bytes |
| --- | ---: | ---: | ---: |
| StrategicInGameUIArmyDetailsPopulate.cpp | 45 | 6 -> 5 | 0 -> 0 |
| stlport_wide_string_append_O1.cpp | 11 | 5 -> 4 | 0 -> 0 |

Every retained body and relocation digest, external binding, link directive
and other nondebug section is identical. The only external symbol removed is
`??$max@I@_STL@@YAABIABI0@Z`; each replacement helper is static, has no
relocations, and has no nondebug caller relocations. The provider's entire
COFF object is identical. Object hashes and the comparisons are in
object-proof.json. No authored-C++ growth or self-strict/closed-strict linked
byte gain is claimed. Strict compilation receipts prove these explicit
objects current, not the closure of their other dependencies.

Populate retains four vector/allocator COMDAT disagreements and one
wrong-selected vector-base destructor. Wide append retains char_traits assign,
construct-null and allocator deallocation disagreements plus wrong-selected
wide-string assign. The provider also has existing unrelated iostream blockers.
link-proof.json lists the complete before/after findings, with every finding
other than the two unsigned-max entries unchanged. No broader census or link
cycle was started.

## Acceptance checks

- Before preparation: 31/31 rows across the original five-TU candidate cohort.
- Accepted strict preparation: 25/25 rows across the two consumers and provider;
  source claims, complete byte/string/float/import verification passed.
- EH verifier: 2/2 exact, no baseline entries or missing objects.
- Data enforcement: zero findings; converged globals: zero second names.
- Class gate, declared-definition gate and new-COMDAT-variant check passed.
- Placement resweep: zero additional bodies or pins.
- Prescribed local link_check returns 1 for the remaining legacy blockers;
  the controlled paired check verifies exactly two findings removed.
- Restored deferred sources: ordinary byte gate passes 6/6 rows.
- check_csv and git diff --check passed. Normal commit/push hooks remain required.

The scripts reproduce the object and paired-preview comparisons from the
ignored scratch directory build/unsigned-max-cohort-link-20261014. Before
objects and dependency receipts were saved after strict preparation; their
hashes are recorded. Raw objects and preparation backups are not published.

## Deferred members and false reject

PeerDefsGameOptions.cpp: two careful shapes (definition before includes;
forward declaration before includes and definition after the parent) remove
the max emitter but change the matched parent's a4/a8/b0 stack/register
schedule. Both byte gates fail. Source restored and file claim released.
Do not repeat these shapes without new codegen evidence.

SidesListTeamsInfoRecAddTeam.cpp: both shapes preserve all retained COMDAT
bytes and relocation digests, including the parent and catch body, and all
other nondebug sections. The generated catch label nevertheless moves from
$L4413 to $L4417 (first shape) / $L4420 (second shape). The existing row pins
object-symbol=$L4413, so the gate refuses an unavailable label. The second
shape's section comparison and identical 20-byte handler are recorded in
false-reject-proof.json. Recorded as a false reject; no ledger workaround or
verifier edit. Source restored and file claim released. A tooling seat should
reproduce stable EH-handler resolution with a regression test; current gate
exploit refusals must remain intact.

## Donor review and freshness

Reviewed BFME1 d3f9000fe08615a100e844adfff57fa4a39cd615, which suppresses
an incidental competing TileData constructor without changing its verified
consumer. This is a supported ownership pattern, not target-byte proof.
The exact unsigned overload and independent full-object comparisons follow
the already verified BFME2 FX-list repair at 7a79608ff3. Target comparisons,
not the donor result, establish this repair's byte and relocation preservation.

Clean BFME1 checkout/gitlink a7c38d3b2597121f178ab5190b3062478823257d
was retained after fetching official master 4b2a6f64aa83cd66e01cd83574cc64cc366a440e.
The previously documented comparative full-gate update requires thousands
of stale TU rebuilds (2806 remained after its 21-minute baseline attempt);
this bounded link-repair seat did not repeat that unresolved work, advance
the pointer or record a successful freshness stamp.
