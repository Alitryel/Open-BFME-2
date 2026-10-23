GeometryRecord allocator link repair
====================================

Three node-allocator copies of allocator<GeometryRecord>::deallocate competed with the verified malloc-backed copy in GeometryInfoDtor.cpp. The existing symbols.csv fold-proof binds this name to retail RVA 0x46264A, the rowed allocator<char>::deallocate body. Declaration-only specializations remove all three wrong implementations and select the verified provider. No allocator ABI, target layout or retail data changes.

Paired legacy previews refresh these same four current objects against the same index. Before: 0/4 clean, 0 linked bytes. After: GeometryInfoDtor.cpp links, 1/4 clean, 260 linked bytes (+260). Both sides pass 17/17 byte checks with strict reusable receipts. This is a legacy selection-preview gain with self-strict byte checks, not closed-strict or a full link-cycle result. The three provider units retain unrelated private-view and helper conflicts.
