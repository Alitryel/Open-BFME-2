# Eye Tower helper-emission link repair

At source base 4e8d225d939b100e61d0b8515e82e5671c692dc0, the already
matched 941-byte LivingWorldEyeTower::rva003F962F body inlines its Matrix3
initialization and Z rotations correctly, but its unused standalone copies
lose the local link census's COMDAT rules. Matrix3(bool) differs from the
first copy; both Create_Z_Rotation_Matrix3 overloads differ from their retail
owners. The existing WWMath U4RotateYMatrix3 unit owns the two rotation rows
at 0x003F946D (113 bytes) and 0x003F94DE (135 bytes).

Declare the three existing forceinline definitions dllimport to suppress their
standalone emission. This removes six unused COMDATs, including the dependent
Matrix3 copy constructor, index helper and vector Set helper. It introduces no
import reference or replacement body. All 13 retained COMDAT sections have
identical whole bytes, extents and complete relocation targets/content. All
16 retained nondebug sections, strong/undefined/weak bindings, COMMON data and
linker alias directives are unchanged. No field, compiler flag, dependency,
row, pin or baseline changes. This is an emission/dependency repair; the
existing neutral method spelling and target/donor identity uncertainty remain.

Target evidence remains the complete native 0x003F962F..0x003F99DC boundary,
processFrame caller, WB transform graph, nine-float matrix access and existing
callee rows recorded in the source. It establishes this caller's behavior and
layout independently of the donor semantic leads. No new original target name
or layout is asserted.

Measurement uses the runner's unchanged index at 147cfae2cb, 2026-10-14 07:27,
SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Committed link_status.csv at 67e1365aa9 is discovery evidence only.
The saved strict-current before consumer and final strict-current after
consumer are each substituted into that same index in memory alongside the
same three current providers: Rva000B3649Fetch, ParticleControlCtorFamily and
U4RotateYMatrix3. Paired legacy preview findings fall 12 -> 9, consumer
findings 3 -> 0, clean units 1/4 -> 2/4, and linked existing bytes
613 -> 1554 (+941). Every provider's findings remain exactly unchanged.
The standalone four-source link_check agrees; its exit 1 reflects the nine
documented independent provider findings. Index/status/history are untouched.

Acceptance checks:

- Strict bounded preparation passes 20/20 cohort rows; final consumer strict
  preparation and independent build.sh pass 1/1. Literal checks: no skipped
  or baselined strings, five consumer float constants exact, no named imports.
- Object comparison checks all retained sections, bytes, relocations and
  external bindings. Removed section names, digests and lengths and paired
  before/after results are in object-proof.json. No undefined name is added.
- Cohort EH: 4/4 EXACT, zero baseline, zero missing objects. Consumer has no EH.
- Frozen definitions, class gate, new-COMDAT admission, CSV and whitespace
  checks pass. Converged data covers eight addresses with zero second names
  or unjudged rows; consumer data shadow has zero findings.
- Affected-unit placement resweep returns zero bodies and zero pins.

Compiler currency is self-strict for the bounded explicit cohort. The gain is
a legacy local prediction, not measured closed-strict closure, link.exe
placement or a fresh full census. New authored C++ coverage: zero. Remaining
providers: fetch selects a nonretail OBBoxClass::Transform; particle control
has three unresolved virtual functions and five unrelated Matrix3 rotation /
AsciiString allocator/vector COMDAT conflicts. They do not block this local
consumer gain and were not retried.

Reference review: retained verified BFME1 checkout/gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1; official master fetched at
bc990782485c4111aa72d4fb8f8d00bb82e12f5b. Reviewed donor linking repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583: its competing-incidental-COMDAT
principle applies; its Apt layouts and expressions do not. Also reviewed
92a8d854746f059994f8ab370c133f3ba71eec24's canonical-global repair; no
eligible owned-global rewrite was found by name_globals --dry-run. No donor
source or new input is imported. BFME1 freshness remains due: the previously
recorded old-input baseline required 2982 stale units and was interrupted after
21 minutes with 2806 left. That unchanged bounded-seat blocker is recorded
in re_attempts.log's bfme1-reference-freshness entry and the existing
unicode-comparator-link-20261014 evidence. No update or success stamp is claimed.

Discovery checked repair_queue link, link_rank top/near and name_globals.
rehome_rows was unavailable because build/link_census/census.log is missing;
this is a tool/artifact blocker, not queue exhaustion. The earlier validateTeam
candidate was already repaired upstream: refreshing its four current peers
confirmed LINKS 712, and its rejected consumer trial was fully reverted.
No maintainer-only verification runner was started. Scratch before source and
object, reproducible proof script and gate logs remain under
build/eye-tower-link-20261014; no scratch code is compiled as project source.
