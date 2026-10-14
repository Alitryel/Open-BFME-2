# O1 wide-string append max link repair

Base checkout 7a6ab992f147187ba8c9990cbbd9f9bbfe502db4. File scope claimed
before editing stlport_wide_string_append_O1.cpp. The unchanged runner index
measures 147cfae2cb, 2026-10-14 07:27; object-proof.json records its hash.
The newer committed de7bb30890 link_status measurement is discovery only.
No census, full link cycle, nightly or boot runner was started.

Make the existing TU-only max template static. All growth callers already
inline it. The sixteen-byte external unsigned-max COMDAT differs from retail's
provider; its replacement is an eight-byte private helper with no relocations.
There are no retained calls to the removed external helper, no new external
bindings, and no edits to providers, shared headers, flags, layouts, rows,
pins, aliases, markers or baselines.

The existing native append 0x001EF83A (212 bytes), wrapper 0x001EFC58 (22)
and assign 0x001EFC6E (105) remain the boundary and identity basis. STLport
4.5.3 supplies the template semantics; existing neutral rva001EF83A names
preserve the distinction from the separately rowed O2 append. This repair
makes no new application-name or layout claims.

Acceptance:

- Ordinary byte gate: all three rows match; zero baselined or skipped literal,
  float or import references. Strict preparation passes before and after.
  The consumer plus unchanged canonical unsigned-max provider
  stlport_basic_ios_init.cpp pass the cohort preparation with strict receipts
  (see cohort-prepare.txt for the full row count).
- Whole-object comparison preserves all twelve retained nondebug sections and
  eleven COMDATs, including data and linker directives: bytes, extents, flags,
  definitions and normalized relocation targets are identical. Only the
  rejected max section is removed and the private helper added. Original
  objects, source and executable comparison script remain under ignored
  build/wide-append-max-link-20261014.
- EH verification has zero applicable parents, zero nonexact, baselined or
  missing objects. Declared-function, class, CSV, whitespace and new-variant
  admission checks pass. Shadow data has zero findings; converged data has
  eight protected addresses, zero second names and zero unjudged rows.
- Placement resweep finds zero additional bodies or pins.

Both local previews use the same index, explicitly refreshing the consumer
in memory. Legacy findings decrease 5 -> 4 across 337 existing authored bytes;
LINKED stays 0 -> 0. Three unchanged COMDAT disagreements remain (wide
char_traits::assign, _M_construct_null, allocator-proxy deallocate), plus the
selected nonretail basic_string wide assign provider. The 339 ledger bytes
include padding; the local preview counts 337. This is link-debt reduction
with zero new authored C++ coverage. Strict receipts establish current
compilation; no self-strict or closed-strict LINK gain, census gain or runtime
result is claimed. Current-ledger closure refuses judgment with 22,109 missing
objects (closed-after.txt).

Related-cause review: the O2 stlport_wide_string_append.cpp sibling has no
unsigned-max blocker; its allocator and selected-append conflicts are distinct.
Other max consumers were inspected through the index and current source;
most already have the prior repairs. PeerDefsGameOptions.cpp was tried with
both a local overload and a declaration-only specialization. Each changes
native local-home/register scheduling in setGameOptions. Its source was
restored, the ordinary byte gate passed again, the blocked evidence was
recorded in re_attempts.log and its claim was released.

Donor review at retained verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d
covered de59a7e9f891 (COMDAT convergence), d003077f0b7c (existing provider
ownership) and fea964f85433 (direct canonical allocation calls). The first
principle applies here; no donor bodies or types are imported. BFME 2's prior
vector-growth repairs supply the local-helper pattern; exact target bytes
and unchanged relocation targets establish its application here.

Official BFME 1 master was fetched at
4b2a6f64aa83cd66e01cd83574cc64cc366a440e. Retain the clean verified a7c38d3
checkout/gitlink: prior old-input baseline comparison required 2,982 stale
TUs and remains incomplete. No unchanged multi-hour rebuild was repeated,
inputs advanced, headers substituted or freshness success stamp written.
