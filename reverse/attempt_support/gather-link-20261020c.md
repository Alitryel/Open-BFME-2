GatherWorldInformation link handoff, 2026-10-20

Inputs: BFME2 413ecd9e74; BFME1 verified pointer 92f6bbe8; published
retail-truth-2 index 5366c4f808 (2026-10-20 12:21). No Code changes retained.
Parent 0x0050366B/1706 and handler 0x00793EAD/10 remain matched.

Two declarations added just before PlayerInfoMap::_Rep_type::clear remove
non-retail player helper copies without changing either row (build.sh 2/2):

```cpp
template <> _Rb_tree_node<PlayerInfoMap::value_type> *PlayerInfoMap::_Rep_type::_M_create_node(const PlayerInfoMap::value_type &);
template <> pair<PlayerInfoMap::iterator, bool> PlayerInfoMap::_Rep_type::insert_unique(const PlayerInfoMap::value_type &);
```

Legacy link_check findings fall from three to one but linked bytes stay zero.
Remaining helper is IntIntTree::insert_unique(iterator,const value_type&),
retail 0x00422EC0. Suppressing it through a declaration changes parent frame
0x1D8 to 0x1DC and many stack offsets despite retaining its native call.
Both declaration placements (after PlayerInfoMap typedef and before IntIntMap
 typedef) fail identically. No header/flag/pin changes were tested. Do not
repeat those declarations alone: remaining work needs body visibility and
external-emission reconciliation. No closed-strict or linked-byte gain.
Scratch diagnostic logs: build/link-seat-20261020c/gather/{trial1,trial2,trial3,mid-link}.txt.
