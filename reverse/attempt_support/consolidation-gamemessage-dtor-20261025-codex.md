# GameMessage destructor donor prerequisite

The approved MessageStream.cpp plan and scoped Common planner retain this
GameMessage.cpp donor. The ordinary baseline composition rejects its destructor
because the destination header has m_list and m_argList rather than the private
m_listener and m_nodes names. Original-path alternatives remain hints; routing
approval comes from the current in-memory TU map, not those hints.

The donor now uses the existing header's two field names and pointer types.
Explicit casts retain its original argument-node cleanup prefix and list callback
view, including the +4 next link, flag-zero virtual call, separate global free
and owning-list slot 0x40. No call target, offset, traversal or store changes;
this does not assert recovery of the complete argument or list class layout.

Official ./build.sh before and after preserves both rows: destructor 59 bytes
at 0x0030F4AF and scalar deleting destructor 28 bytes at 0x0030F8E3.
Declared-unmatched passes before and after. Scratch receipts:
build/codex-gamemessage-dtor-{before,after,dryrun}.txt.

The normal merge dry run now accepts MessageStream.cpp, GameMessage.cpp and
GameMessageIntWideArgs.cpp together, preserving 16 non-alias rows (previously
14 without this donor). Remaining rejected donors retain their separate
layout, duplicate-declaration and protected-register prerequisites.

No source path, ledger owner, compiler flag, protected register, header queue,
data/identity debt key or hatch changes. The complete outgoing path audit is
empty: tools, hooks, workflows, includes, build inputs and registries need no
consumer transfer. Keep the donor claim until publication; the accepted donor
is ready for Luna's mechanical consolidation.
