# W3DShadowMapManagerUpdateShadowCamera.cpp link repair (0x0007C8AE, 4,176 B) — blocked

Census c7845fd6e7 blockers: `__imp___assert` (from the unit's unreferenced
`Vector3::Cross_Product` copy, built without NDEBUG; it differs from the first
copy in link order) and `vector<BfmePod8>::erase` (not retail's body).

## Tried

- erase: retail calls stock STLport's out-of-line `__copy_ptrs(..., const __false_type &)`;
  the bfmealloc shim provides a by-value forceinline overload instead. Declaring a
  const-ref template overload and calling it through a typed function pointer
  (static_cast or local pointer) gives a 38 B copy with retail's callee and push order,
  but the tag sits at `[ebp+0xf]` (last byte of `__last`'s slot). Retail uses `[ebp+0xb]`.
  A `_TrivialAss()` temporary is value-initialised (xor/stosb, 47 B).
  Variant: build/shadowcam-erase-variant.cpp.txt (untracked); the core line is
  `__false_type __tag; pointer __i=static_cast<BfmePod8*(*)(BfmePod8*,BfmePod8*,BfmePod8*,const __false_type&)>(__copy_ptrs)(__last,this->_M_finish,__first,__tag);`
- Cross_Product: `/DNDEBUG` on the cl line, or NDEBUG around only vector3.h, removes
  `__imp___assert` and the copy, but UpdateShadowCamera then fails (xmm loads at
  0x7CD84 onwards use other stack slots). Removing erase's definition (declaration
  only) also breaks UpdateShadowCamera. Neither EH nor nothrow causes this
  (`throw()` and `__declspec(nothrow)` were both tried).

## Untried

- Find the source form that puts the empty tag in `__first`'s slot.
- Make Cross_Product dllimport-forceinline with the assert kept, so the inlined
  bodies are unchanged and no copy is emitted (needs a class-wide vector3 view).
