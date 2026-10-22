Asset refresh constructor suppression, 2026-10-22
================================================

At 71e7f85a0c, AssetManagerImplRefresh.cpp remains 0/3252 B linked because
its pointer-set _Rb_tree_base and compare/allocator tree constructors
conflict with kept copies. The refresh body itself is exact.

Tried same-body dllimport forceinline specializations. A first trial used
_M_get_node, which belongs to the derived tree rather than this base;
replaced it with _M_header.allocate(1). Placing the specializations before
existing allocator/dtor declarations gives C2908; placing them at the file
footer compiles but changes parent expansion. The latter introduces calls
to _STLP_alloc_proxy's allocator/pointer constructor and _M_empty_initialize
that retail refresh inlines. The parent byte gate fails (1/2), so no repair
was retained. Source was restored. Future work needs to preserve helper
inline visibility as well as suppressing the two external constructor
copies; do not repeat constructor-only suppression unchanged.

The exact failed footer specialization is preserved in the adjacent patch.
Flags and all dependencies are those of the unchanged source at the base
revision. No new provider pin or guessed helper identity is justified.
