# Deferred Drawable node factory binding

The 351 B callback at 30F14C is byte-exact but fails legacy link preview against
2967eab33e on its node factory and selected malloc allocator. Declaration-only
factory specialization loses compiler visibility and changes caller register
allocation. An inline-only vendor factory specialization restores exact caller
bytes but moves the conflicting copy into list::insert and keeps the selected
allocator blocker. Extern-template suppression also changes caller allocation.
Two byte-failing attempts end this investigation. All source is restored and
its 1/1 strict-current byte check passes. No linking improvement is claimed.
The next repair needs compiler evidence that preserves partial inlining while
binding external helpers, rather than repeating these variants.
