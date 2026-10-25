# Debug console consolidation prerequisite, 2026-10-25

Seat codexb, Libraries pool. The normal debug_io_con.cpp dry run rejected
DebugIOConDestructorThunk.cpp because its private FreeConsole declaration
returned void, conflicting with the SDK's BOOL declaration in the seed.
Replace that prototype with <windows.h>. The standalone build preserves all
five rows (destructor, deleting destructor, byte predicate and two EH rows),
the named FreeConsole import and exact exception data. The declared-unmatched
check passes. No function body or compiler flag changes.

The scoped Microsoft-header audit now finds no private Microsoft names in
this source. Its owning refresh_queue API removes the old FreeConsole:abi
queue entry, preserving all unrelated records. No code/data identity debt
is retired, no source file is removed and no retail byte coverage is added.

## Remaining merge boundary

The after dry run reports seed plus destructor accepted, seven rows, but
prints the literal `compile` instead of composed source on its final retry.
Do not apply that result. The before dry run accepted no pair. A tooling
handoff was recorded with re_log.py for 0x00040860. Reading Verifier.matched
shows that failed compile-cache hits do not restore all_errors, while
attempt() uses that mutable field to choose declaration removals. This is a
likely explanation for the inconsistent retry; it needs a separate tooling
repair and regression test, not a workaround in this prerequisite.

The Common bfmeWriteQN donor still has a conflicting WriteFile declaration;
its source is outside this pool. The factory donor still has private
placement operations and a conflicting DebugIOCon view. The constructor is
protected-register keyed. None was edited. Receipts:
build/sol-debug-dry.txt, build/sol-debug-dtor-build.txt and
build/sol-debug-dtor-after.txt.

## Outgoing batch audit

Thread's constructor prerequisite and this SDK prerequisite change no source
paths. The complete local outgoing range from its merge base with fetched
origin/master plus this staged change contains no moves or absorbed donors;
there are no consumers to repoint. Historical paths remain untouched.

Both sources in the Thread prerequisite and this destructor were rescanned
through the Microsoft-header owner; none has local Microsoft declarations.
The Thread rows have no header queue entries to transfer. No source in the
batch is keyed in the code-identity or data-identity debt registers, and all
ledger owners remain unchanged. The code-identity scan checks affected
providers/consumers and selected COMDAT definitions; ordinary byte/import,
data and EH checks verify the emitted bindings. No binding change or new
identity debt is claimed. This is prerequisite work, not an applied
composition; Luna must repeat the destination checks when it moves rows.

Keep the Thread source/constructor, debug destructor and handoff file claims,
plus RVAs 0x00610430, 0x00040860 and 0x000408C0, until publication is confirmed.
Release them after landing; these existing-row claims may require explicit
release if --landed reports none.
