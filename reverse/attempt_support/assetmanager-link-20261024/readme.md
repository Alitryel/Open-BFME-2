# assetmanager_impl.cpp link repair (4,059 B held), 2026-10-24

Blockers from `link_check.py --refresh` on master 00ddfa0eb4:

1. `vector<unsigned>::_M_insert_overflow`: ours (TU-end state) is 232 B,
   retail 0x002DFCF6 is 140 B.
   - `overflow-gsy.patch` (an explicit specialization in a `gsy` region with
     `auto_inline(off)`, no `inline`, plus a declaration-only `fill_n<unsigned*>`
     replacing the TU-end forceinline one) keeps the unit 29/29 and stays a COMDAT.
     It gives 153 B, because the proxy forceinline `allocate` inlines
     `allocator<unsigned>::allocate`. Retail calls 0x00068E15 out of line.
   - The declaration-only `allocator<unsigned>::allocate(size_t,const void*)`
     specialization closes the overflow to 140/140 exact. On its own, even
     without the overflow specialization, it changes the register allocation in
     `retain`/`subtract` (0x0061FAA0/0x0061F910, +12 B). Placing it after the
     proxy specializations gives C2908.
   - `inline_depth(1)` does not stop the nested inline.
   - Untried: `inline_depth(0)` with a hand-expanded size/max/_M_clear/_M_set
     and a direct `allocator<unsigned>::allocate(n,0)` call.
2. `_Rb_tree<Rva001408C0Target*>::_M_create_node`: the kept copies (index 1600+,
   for example `Rva0006C995Insert.cpp`) are bfmealloc-shaped:
   `push 0; push 0x14; call allocator<char>::allocate (static)`. Ours calls the
   declaration-only `_STLP_alloc_proxy<node>::allocate(1)` out of line. A match
   needs the bfmealloc allocator, meaning the TU moves to
   `/Ireference/shims/bfmealloc`, with every allocator spec in it revisited.
3. `_Hashtable_iterator<pair<const int,Q1ReceiverHashPayload*>>::_M_skip_to_next`
   pinned at 0x00054DC7 (symbols.csv):
   - The pin is harvested from the Q1 `??E` row at 0x00055532 (a masked
     placement).
   - Retail's Q1 bodies (0x00621A00, 0x00621B10) inline the int-key find and
     ++ with a direct `div`. 0x00054DC7/0x00055532 are the AudioRequest
     pointer-hash iterator (0x00053EA8 -> 0x00051B89 dereferences key+8).
   - Dropping the pin makes the 0x00055532 Q1 row fail (unresolved callee). The
     row identity has to be re-homed to the AudioRequest name (already pinned
     at 0x00055532 with fold-proof MilesAudioManager.cpp) first.
