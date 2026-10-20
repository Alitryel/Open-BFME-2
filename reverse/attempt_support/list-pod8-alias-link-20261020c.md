Rva004E4F82Finish link handoff, 2026-10-20

Inputs: BFME2 413ecd9e74; BFME1 92f6bbe8; retail-truth-2 index
5366c4f808. No Code changes retained. The three rows (144-byte constructor,
10-byte handler, 11-byte funclet) still byte-match in the original source.

Sole blocker is the 41-byte _List_base<Pod8,allocator<Pod8> > constructor.
Its /Ow copy writes this->_M_node before initializing the allocated node's
links; rowed owner stlport_pod_list_bodies.cpp initializes links first, then
stores this->_M_node. Calls and relocations otherwise agree.

Trials:
- Explicit declaration of the constructor suppresses its conflicting COMDAT,
  but the parent allocator call changes from retail F3 to F2 (one-byte mismatch).
- Scoped #pragma optimize("w",off) around <list>, then restoring it: 3/3 rows
  pass, but the helper's store ordering is unchanged and linked bytes stay zero.
- An explicit visible specialization under the same pragma also passes 3/3,
  but produces the same non-retail ordering. Body tested:

```cpp
namespace _STL {
template <> _List_base<Pod8, allocator<Pod8> >::_List_base(const allocator<Pod8>& a)
    : _M_node(0, a) {
    _M_node._M_data = _M_get_node();
    _M_node._M_data->_M_next = _M_node._M_data;
    _M_node._M_data->_M_prev = _M_node._M_data;
}
}
```

No flags, pins or headers retained. Needs compiler/alias visibility reconciliation;
repeating suppression or the scoped /Ow pragma alone will not link this unit.
Legacy link_check stays 0 linked bytes; no self-strict/closed-strict gain claimed.
Scratch diagnostics: build/link-seat-20261020c/list/{gate,gate2,gate3,after,after3}.txt.
