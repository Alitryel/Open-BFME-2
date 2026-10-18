Four vector<bool> units lose solely on their emitted `_Bvector_base<allocator<bool> >::_M_deallocate` copies. The helper has no retail address, but surviving callers reference it; the published first copy therefore governs. This is a live blocker under retail-truth-2.

Each TU now uses a dllimport forceinline specialization of the unchanged STLport 4.5.3 helper from vendor/stlport/stl/_bvector.h:246. It preserves allocator access, null check and element count, inlines every call in these units, and emits neither a conflicting helper nor an unresolved imported call. No shared vendor input changes.

Same-index local preview: 0/4 units and 0 B before; 4/4 and 1,057 B after (209 + 392 + 147 + 309). This is a legacy link projection with strict self-byte receipts for all four inputs on both sides. It is not a closed-strict link result or additional authored C++ coverage. Full scope gate passes 5/5 matched rows, two strings and all reference checks. The index is unchanged.
