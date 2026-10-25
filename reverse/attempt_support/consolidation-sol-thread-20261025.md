# Thread consolidation prerequisite, 2026-10-25

Seat: codexb. Target: `Code/Libraries/Source/WWVegas/WWLib/thread.cpp`.

The before dry-run rejected ThreadClassCtor.cpp with C2511: the seed included
Zero Hour's two-argument constructor declaration, while the existing matched
BFME 2 body takes one name argument. The seed now declares the same existing
BFME 2 prefix and virtual interface as that constructor and the independently
matched lifecycle donor: name at +4, thread ID +44, handle +48, priority +4C;
destructor, Execute, Thread_Function in the three virtual slots. The shared
Zero Hour header remains available to its other consumers. Both participating
local views declare the seed's existing nonvirtual/static methods as well.
No new identity, data binding, virtual slot, hatch or original name is inferred.

Acceptance: ./build.sh thread.cpp ThreadClassCtor.cpp passes 4/4 code rows,
2 data rows, 2 strings and 5 named imports. Declared-unmatched passes (the
seed's existing Sleep_Ms marker remains). The normal merge dry-run changes
from no accepted pair/C2511 to seed plus constructor, four exact rows and no
rejection. Local receipts: build/sol-thread-before.txt,
build/sol-thread-prereq-build.txt and build/sol-thread-after.txt.

The constructor pair is ready for Luna. Lifecycle and BFMEPoolYield are still
protected-register keyed; neither was edited or moved. No merge is applied,
no source file is removed, no C++ bytes are recovered and no identity debt is
retired. The prepublication consumer audit has no pending source-path changes
(origin/master..HEAD empty before this prerequisite), so no repointing is
needed. Keep seed, constructor and 0x00610430 claims until publication.
