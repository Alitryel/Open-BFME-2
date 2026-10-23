# BfmeRecord0040B61A assignment link attempt

Current assignment186B is blocked by a non-retail __uninitialized_copy helper.
Declaring that helper alone changes the parent to a stack-local result and
register allocation (extra push ECX). Mirroring the allocate-copy sibling's
explicit copy-constructor declaration preserves the complete186B parent, but
leaves the new copy constructor unresolved and the scanner still non-retail.
Paired legacy preview with the allocate-copy provider drops138->0B; no gain.
The provider alone still links138B. No pin or new class-identity claim added.
Original restored and byte verified. A future repair needs the actual element
copy provider (native scanner4B2FD), not another body-less constructor declaration.
