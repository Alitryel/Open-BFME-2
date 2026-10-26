# HealContain prerequisite inspection, 2026-10-26

Seat codex family A shard 0/2; allocation check and scoped Contain planner/check
pass. Current --plan: seven approved rows, four sources, two mixed sources.
Ordinary --merge --dry-run accepts the ctor seed plus ModuleDataParse: two rows,
111 bytes. Pool key fails C2039 missing getModuleNameKey; xfer fails C2039 missing
xfer in HealContain/OpenContain. Receipts build/codex-healcontain-{planner,trial}.txt
and build/consolidation/codex-healcontain. Planner provides placement hints only;
current routing is rebuilt by the tool, no tu_map is committed.

The seed models vtable stores explicitly through nonvirtual OpenContain and
HealContain fields. Pool/xfer use virtual methods; adding those methods to the
seed introduces an implicit vptr and changes its accessed member placement.
A compatible repair therefore needs a proven reconciliation of that receiver and
its constructor-generated data, beyond adding member declarations. No source
attempt is retained and no merge or binding gain is claimed. Mixed ConstIntGetters4
and FlatMultiVptrDestructors remain; no split is attempted. ModuleDataParse is
already compile/byte compatible, not a newly authored prerequisite fix.

Blocked pool row 0x00466B88 recorded through re_log. The unchanged seed claim was
released; retain this handoff claim until publication. No file reduction, debt
retirement, recovered bytes or census measurement is claimed.
