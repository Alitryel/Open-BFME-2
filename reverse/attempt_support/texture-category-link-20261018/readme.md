Texture-category member and callback reconciliation, 2026-10-18

Paired current-provider legacy link_check: 12,225 -> 12,460 matched bytes (+235 B). Providers MeshModelClassCopyCtor.cpp, Rva00144690Dtor.cpp and fxshadernamespacesas.cpp are identical in both measurements. The already repaired opaque list provider contributes 175 B before and after and is excluded from this gain. Census c2c5ac8c27; self-strict receipts only, no closed-strict claim.

The native category constructor installs vtable BD34E0 for its +1C member; its unwind cleanup at 76627E reaches existing rowed destructor 144690. That provider retains the opaque Rva00144690 name. The consumer now uses this provider's class instead of leaving the speculative MultiListClass<DX8PolygonRendererClass> destructor unresolved. This does not establish the original member type name. Existing native constructor/layout and EH proof remain unchanged.

As in the provider, novtable keeps this derived-only GenericMultiListClass view from emitting its non-retail base table/deleting destructor. Its imported forceinline constructor preserves the native inline node/head initialization without a competing base-constructor body. The texture RefCountPtr default callback uses the same explicit size-optimized specialization proven in the migration unit; complete six-byte body 8BC1832000C3, zero relocations, at target 326BE6. No pins, aliases or baselines added.

Acceptance: 5/5 code rows exact including all three unwind funclets; 1 EH record EXACT; data_check --enforce zero findings; converged 9 addresses, zero second names/unjudged rows; find_declared_unmatched passes. Self-strict reusable current receipts prepared without closure expansion.
