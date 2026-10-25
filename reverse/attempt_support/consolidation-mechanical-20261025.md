# Mechanical consolidation handoff, 2026-10-25

Shard 3/5; trials restored and claims released.

## AssaultTransportAIUpdate

`--merge --dry-run` accepted no whole donor. It rejected
`AssaultTransportAIUpdateHelper.cpp` with C2039 (`Rva0048F365Helper` is not a
member of `AssaultTransportAIUpdate`), `AssaultTransportAIUpdateXfer.cpp` with
C2011 (`Xfer` redefinition), `AssaultTransportAIUpdateCheck.cpp` with C2065
(`m_object08` undeclared), `Rva0048F64EFinish.cpp` with C2039
(`rva0048F64E` is not a member of `AssaultTransportAIUpdate`),
`AssaultTransportAIUpdateCommandHelper.cpp` with C2011 (`GameLogic`
redefinition), and both `AssaultTransportAIUpdateDispatch.cpp` and
`AssaultTransportAIUpdateUpdate.cpp` with C2039 (helper/member absent from the
class view). Three other donors are keyed in protected path registers.

The mixed-file trial carving `0x0048F456` from `ModuleNameGetters.cpp` passed
its split dry run and 72/72 scoped byte checks. Composition review then found
four new shadow code-identity divergences in the destination:
`AICommandInterface::aiAttackMoveToPosition`, `AICommandInterface::aiEnter`,
`Object::getBodyModule`, and `Object::isContained`. Current provider selection
could not be refreshed: `link_check --refresh --current-ledger` refused 47
missing object receipts. The split was restored; do not apply until Sol resolves
the identity findings and current binding evidence is available.

The other mixed paths were inspected: carving `0x0048F3E0` from
`Rva0026E836Derived.cpp` is blocked because a hatch count would grow; carving
`0x0048F46D` from `VslotSmallBodiesAJ.cpp` matches alone but the seed rejects
it with C2011 (`GameLogic` redefinition in
`GameLogicObjectLookupView.h(57)`); carving `0x0048F828` from
`AssaultTransportAIUpdateUpdate.cpp` is unsupported because a namespace block
defines something.

## RepairDockUpdate

The unchanged `RepairDockUpdateBehaviorCtor.cpp` donor passed the dry run and
scoped 1/1 byte build. `RepairDockUpdateXfer.cpp` was rejected with C2061,
`Snapshot` syntax error in `BfmeXfer.h`; `RepairDockUpdateAction.cpp` was
rejected with C2511, no matching
`RepairDockUpdate(Thing *, const ModuleData *)` member declaration. Three
additional donors are keyed in protected path registers. The staged merge had
zero new code-identity findings, but current provider selection could not be
refreshed because `link_check --refresh --current-ledger` reported 47 missing
objects. The merge was restored; re-evaluate after receipt coverage is repaired.

The mixed `ConstIntGetters4.cpp` split trial for `0x004A11CE` passed its dry run
(1/1 carved row; residual keeps 267 rows), but it was not applied because the
same current-provider blocker prevents composition verification. The
`Rva0058A0F4Derived.cpp` split for `0x004A11D4` is blocked because a hatch count
would grow. The full shard listing contains 25 unheld candidates; later
destinations remain eligible by allocation, but any accepted composition still
needs the missing current-ledger receipts before it can be published.
