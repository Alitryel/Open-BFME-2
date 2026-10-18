# Link-repair seat handoff, 2026-10-18

Two verified repairs change the legacy preview by **+371 bytes / five units**:
native constructor cleanup +314 bytes / four units, and the unsigned-vector
base binding +57 bytes / one unit. Their paired measurements, byte gates,
EH checks, self-strict preparation and identity evidence are in
`../native-cleanup-link-20261018/` and `../vector-cleanup-link-20261018/`.
Provider closure remains incomplete; these are not closed-strict gains.

Later independent trials were restored, with blocked verdicts in the attempt
log. ChatWindowsOnlineRoom's declaration-only overflow binding changes its
408-byte parent. W3DLightDrawConstructor's novtable DrawModule base preserves
the 287-byte parent and exact EH but exposes a conflicting ordinary destructor.
An imported forceinline destructor still preserves the parent, but adds an
unresolved import in the exception cleanup and changes five bytes at 7627D8.
Neither trial is retained. Both candidate file/RVA claims were released.

The link ranking and private-class blocker ranking were refreshed, and
`repair_queue.py link` was checked. Many published-census blockers already link
with current sources: the Coord3D allocator sweep is 8/8 clean (2,387 bytes),
ProductionUpdateQueue is clean (8,298 bytes), and PolygonTriggerParserParse
and StrategicInGameUIArmyDetailsCreateIcon are clean (587 bytes together).
These are pre-existing repairs and are excluded from this seat's improvement.
No census, index, link_status, baseline or verifier was changed.

Remaining leads require new evidence or class/provider work: DrawModule's
destructor contract; Script's banked 177-byte loop-scheduling mismatch; the
canonical APT base vtable; and the still-unrecovered ActionManager location
check. Rva0059A85CCtor has a further identity lead: native C70DE4 slot 1 is
59AC6E, rowed as nonvirtual Rva0059AC4D::update. Its unresolved inherited v0
needs reconciliation of that class and its providers, not another address pin.
The unchanged BFME1 freshness blocker is documented separately; the last
verified submodule pointer was retained.

`python3 tools/progress.py origin/master` reports +0 C++ coverage and +0
committed-census linked bytes, as expected for repairs with no fresh census.
The measured +371 bytes above comes only from paired local previews.
Publication is delegated to the runner when the batch threshold is not met.
The verified 211E58 fold-provider claim stays queued until its commit lands.
