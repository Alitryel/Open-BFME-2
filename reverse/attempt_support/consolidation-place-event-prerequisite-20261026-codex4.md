# PlaceEventTranslator composition prerequisite, 2026-10-26

Allocated family A shard 1/2 destination:
`Code/GameEngine/Source/GameClient/MessageStream/PlaceEventTranslator.cpp`.
No merge applied; leave the accepted pair for Luna.

## Target facts and repair

The current upstream plan approves constructor 0x0043216D (29 bytes) from
`Common/PlaceEventTranslator.cpp` and translateGameMessage 0x0043218A
(1701 bytes) in the destination. Its two EH companion rows add 18 bytes.
The scoped planner reports the same destination as a ZH spelling hint, with
macro context, internal linkage and quoted-include review prerequisites;
that hint does not grant placement. The upstream plan rebuilds the stale TU
map in memory and is the routing authority. No TU map was written.

Before repair, normal `tu_skeleton.py --merge TU --dry-run` accepted nothing:
the seed failed C2059/C2146 after composition hoisted the V/V10 macros and
#undef directives ahead of their uses. Expand those declaration macros into
the identical ordinary virtual declarations, preserving all slot spellings.
This alone passes the seed but exposes the donor's C2600: the chosen receiver
view lacks a constructor declaration. Share the already modeled receiver in
`PlaceEventTranslatorView.h` with both sources. The retail constructor and
existing translator accesses agree on the +4/+8 pixel, +C/+10 frames and
+14/+15 byte fields. Constructor assignments follow the original store order.
Value initialization was rejected because MSVC emitted stos; no failed body
is retained. No virtual slots or global identities were added or renamed.
The existing second-slot modeling limitation stays documented in the ctor.

After repair, the same upstream dry-run accepts BOTH sources, rejects none,
and verifies all four existing rows / 1748 bytes. This demonstrates an unblock,
not an applied consolidation or a confirmed subsequent Luna landing.

## Verification and composition evidence

- Fresh scoped `name_lane.py consolidate --under
  Code/GameEngine/Source/GameClient/MessageStream/` and snapshot currency check.
- `./build.sh` on both sources: 4/4 byte-exact, including the 1701-byte parent,
  ctor, cleanup and handler; four string literals and one float literal pass.
- `find_declared_unmatched.py` on both sources: all definitions matched.
- Normal `tu_skeleton.py --merge TU --dry-run`: accepted both, four rows,
  no rejected donor. Local report: `build/codex4-place-prereq/shared-trial.txt`.
- Supported COFF/data primitives (`allowed_symbols._object_defs`, `Obj`,
  `link_census._comdat_selections`, `data_check.object_facts`) compare saved
  original objects, repaired standalone objects and the normal dry-run object.
  Both standalone objects retain all code/data definitions, digests, sizes,
  exclusivity, COMDAT selection and undefined references. Composition equals
  their union: 35 code definitions, six external data definitions and 35
  unresolved references after internal resolution. All four row DIR32 data
  binding sets agree before/after and in composition. No changed provider or
  consumer binding requires a broader trial. Local executable proof:
  `build/codex4-place-prereq/proof.py`.
- `allowed_symbols.py --source TU Common/PlaceEventTranslator.cpp`: 34 refs,
  29 owner, two alias, two fold, one EH; zero wrong bindings.
- `data_check.py --converged` on both: ten addresses, zero second names or
  unjudged rows. `eh_verify.py`: one EXACT EH row, zero missing objects.
- `check_csv.py`: 98252 function / 15683 symbol / 2215 data rows, OK.

No code/data identity baseline or header/MS-header queue key names either
source. No debt retired, files removed or newly recovered C++ bytes.
MessageStream's maintainer-owned global identity decision is untouched.

## Publication compatibility audit

Audited HEAD plus this staged prerequisite and all locally pending commits;
the inherited split-tooling commit 58dd60a46e is confirmed on origin/master
and its five old file claims were released before this task. There are no
pending source moves/renames/deletions. The only added source dependency is the
private header, included by the two intended consumers, verified together.
Combined searches of tools, hooks, workflows, Code includes, build inputs,
source registries and reverse registers find no consumer requiring repointing.
Existing ledger, link-status and naming-path entries retain their current paths;
historical attempt/reference records remain historical. Protected registers
are unchanged. Local search receipt: build/codex4-place-prereq/path-audit.txt.

Luna must still apply the merge through the upstream tool, audit its actual
path deletion and refresh path-keyed queues/registers in that batch. Keep the
current approved ownership and all existing identity debt. A successful byte
trial does not establish a new census or image ownership result.
