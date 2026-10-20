Filter base emitter repair, 2026-10-20

At starting revision 09046e92f8, PartitionFilterAllowSlots.cpp has 12 matched rows
and 460 nonpadding authored bytes, but its deleting wrapper for Rva000421C8
is not retail. The real base constructor/destructor providers are already rowed
at 0x000421C8/0x000421D5 and 0x0049C38A. The target class identity, layouts and
address-derived names remain as recorded in the existing ledger; no new donor
identity is claimed. BFME1 verified donor revision reviewed this session:
4483e88da1c2f3b9a273f779baac7458bd8bb891, including emitter repair 51b97cd796.

Mark the abstract base novtable, and keep its initialization available only for
inlining through an imported forceinline constructor. The derived constructor
at 0x0057377E still installs the native derived vtable and clears the chain link.
Novtable alone passed all bytes but emitted a shortened, non-retail base ctor;
the combined form removes that unused body too. No import call is emitted.

All 12 rows pass the normal byte, literal and import gates. The strict preparation
receipt is current for this source, EH has no applicable rows, and the converged
data and declared-definition checks pass. The before/after proof replaces this
one object in the same frozen census index, and verifies every retained nondebug
section, definition, flag and relocation is identical; only three unused base
COMDAT sections disappear. The current census ranking reports no other unit
with this same sole deleting-wrapper blocker, so no same-cause peers were edited.

Result: paired legacy prediction 0 -> 460 linked nonpadding bytes. Self-strict
provider preparation passes. Closed-strict gain is unmeasured; no full link
cycle/census was run. proof.json records the index and object hashes. To rerun
proof.py, retain the old object at build/filter-base-link/before.obj (or rebuild
its source from the starting revision in an isolated trial) and byte-verify the
new source through build.sh and link_check.py --prepare-current first.
