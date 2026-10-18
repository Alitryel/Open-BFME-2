# Pointer deque allocator ownership

At BFME2 7e14760d55, census c2c5ac8c27 reports the pointer deque O1 unit blocked only by allocator<void*> destructor and allocate competing copies. Plain declaration-only specializations change the rowed deque destructor and push-back bytes because those workers must remain available for inlining. TU-scoped imported inline specializations preserve the existing bfmealloc header bodies and suppress the competing emissions. The allocation helper keeps its established raw-byte allocator call; its existing row owner is 0x00620180 in stlport_hash_map_int.cpp. No target identity, layout, pin, range or shared header changes.

Before link_check: blocked, 0/713 linked bytes. After: LINKS, 713/713 linked bytes. These are legacy census-preview bytes with self-strict touched-object receipts, not closed-strict gains. Unreferenced proxy destructor differences remain diagnostics under retail-truth-2 and were not suppressed. A cause sweep found the other ranked allocator consumers also require independent vector/base/proxy reconciliation; this commit claims no improvement there.

Acceptance: ./build.sh passes all 20 matched rows plus string, float and import checks. link_check.py --prepare-current passes the same rows and produces a reusable strict receipt; link_check.py reports LINKS. find_declared_unmatched reports all definitions matched.

Donor inputs remain the verified BFME1 pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5. The inlined bodies come from BFME2 reference/shims/bfmealloc/stl/_alloc.h; the optimization/ownership adaptation was checked against BFME2 retail. BFME1 master d348fca17814122303884ebe194cbc877a2c0bb0 remains a separately pending freshness update; no unverified donor pointer is adopted here.
