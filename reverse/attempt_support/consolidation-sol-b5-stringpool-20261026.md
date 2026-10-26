# StringPool declaration prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2; base 87cad06378, pending AptInput prerequisite
8fdd04e212. Allocated target Code/Libraries/Source/Apt/string/StringPool.cpp.
The Libraries-scoped planner was reviewed: target assertion paths, duplicate
private EAStringC views, compiler differences, data ownership, and mixed intern
and initialization files are distinct prerequisites, not merge approval.
Current --plan routing rebuilds the map in memory: three approved rows, two
whole donors and one mixed donor. No map or ledger is edited.

## Repair and demonstrated acceptance

The full normal --merge TU --dry-run initially accepts shutdown only (435 B).
Remove rejects C2039: EAStringC lacks rva006D2F40. The seed is selected from
Rva0070D9F0Shutdown.cpp; its private EAStringC declares other string methods
but not the remove donor's existing unsigned-short const hash accessor.
Add just that nonvirtual declaration to the seed donor. No body, virtual slot,
class size, flags, global, alias, hatch, source path or register changes.

After: the same normal dry-run accepts both whole donors, two matched rows,
840 retail bytes, no rejected donor. This demonstrates one newly compatible
405-byte row, not new authored/recovered bytes or a confirmed Luna landing.
Leave the verified merge to Luna. The mixed intern file stays behind; the
supported split lane must preserve its two other rows. Current planner hints
for StringPoolInitialize do not grant routing of its unapproved rows.

## Verification

Local receipts and saved objects use build/sol-b5-stringpool-*.

- ./build.sh both donors before/after: 2/2 matched, twelve literals, zero
  float/import failures. find_declared_unmatched.py passes for both, and
  class_gate.py on shutdown passes.
- build/sol-b5-stringpool-proof.py before/after asserts exact equality using
  allowed_symbols._object_defs, Obj, link_census._comdat_selections and
  data_check.object_facts: both external code definitions retain digests,
  sizes, exclusivity, COMDAT selection/flags and undefined symbols. All
  seventeen code references retain owner bindings; data definitions and
  data references are identical. Object paths and link order stay fixed,
  so no external consumer/provider acquires a new variant or binding.
- allowed_symbols.py --source: seventeen owner references, zero wrong bindings.
  data_check.py: one existing shadow finding, zero outside baseline.
  --converged: ten judged addresses, no second names or unjudged rows.
  eh_verify.py: zero EH rows, no missing or nonexact objects.
  ms_header_audit.py scan: no local Microsoft prototypes/conflicts/failures.
- Shutdown retains both existing data baseline keys (g_00E18650 and the old
  saConstantAtE18388 spelling). Neither source has code-identity/header/
  ms-header keys. No keys are retired, transferred or silently removed.
- Normal dry-run proposes two data-baseline transfers and three data-ledger
  transfers; those are future merge operations and are not applied here.
  Existing INT3 assertion blocks are untouched; no assembly conversion claimed.

## Batch audit and handoff

Pending range 87cad06378..8fdd04e212 plus this repair has no path moves,
changed includes, build inputs, tools, hooks, workflows or path-keyed registers.
Both commits modify declarations in place and add evidence. Historical EA
path strings stay intact. The Libraries planner is regenerated after the edit
and checked for currency before commit. git diff --check passes. Source-file
reduction, retired debt and new C++ bytes are each zero.

The AptInput prerequisite separately admits two rows/418 bytes; this one admits
one row/405 bytes. Neither is a linked-coverage gain or a downstream Luna
landing. BFME 1 freshness limitation is recorded in the AptInput handoff;
verified reference inputs are retained. No maintainer-only runner was started.

Keep file claims until publication: destination StringPool.cpp, both unchanged
remove and edited shutdown donors, and this handoff. Earlier AptInput claims
remain with its pending commit. Release file claims after confirmed landing;
settle RVA claims with claims.py release --landed (no RVAs moved here).
