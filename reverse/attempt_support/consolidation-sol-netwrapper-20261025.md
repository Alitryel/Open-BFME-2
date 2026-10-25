# NetCommandWrapperList pool-prefix prerequisite, 2026-10-25

The Luna GameNetwork handoff reported that normal composition hoisted the pool
macro before the BfmePoolGlue declaration. The baseline dry-run reproduced
C2653 in MessageStream.h for every merged flag set, including the seed alone.

Move the existing PreRTS include, namespace declaration and unchanged pool macro
into the local BfmeNetWrapperPoolPrefix.h, included at the same point. This keeps
the compiler environment ordered when the merger hoists includes. No function,
layout, symbol, ledger owner or escape-hatch count changes.

Acceptance: ./build.sh NetCommandWrapperList.cpp verifies all 13 existing rows;
find_declared_unmatched passes the source and header; diff --check passes. The
normal merge dry-run now compiles and verifies the seed, then rejects the donor
NetCommandWrapperList_getReadyCommands.cpp on C2248: class union selects a
protected NetCommandWrapperListNode constructor. The previous BfmePoolGlue
boundary is cleared, but this does not claim the full merge is compatible.
Receipts: build/sol-wrapper-before.txt, sol-wrapper-build.txt and
sol-wrapper-after.txt. The remaining donor needs its private declarations and
pool access reconciled with the seed header, preserving BFME's de-pooled
NetCommandRef layout and all three byte rows. No donor edit was retained.

No source file is removed and no code-identity debt is retired. One local
header is added. The scoped planner was refreshed after the repair at
build/consolidation/network; it remains evidence, not approval to merge.

Publication audit: outgoing commits 7b78ab72f7 and a1c245f8b2 plus this staged
repair contain no source moves or deleted source paths. Reviewed active tools,
hooks, workflows, source/header includes, build inputs, doxygen and protected
registries for GameInfo/GameSlotCtor/GameInfoSlotView and the wrapper/header.
No consumer needs repointing; all new quoted includes resolve beside their
sources. Existing provenance comments and EA paths remain historical evidence.
The prior GameSlot header acceptance is recorded in its separate handoff.
