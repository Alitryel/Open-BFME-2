# Blocked integer-list identity correction

At BFME 2 revision 326ff40928, the 20-byte row at 0x00079E8D was
`list<int>::push_back()` in stlport_list_int_o1.cpp. Retail's complete
79E8D..79EA1 body loads the sentinel, supplies the iterator return slot,
and calls 0x00079CB6 (REL32 at 79E9A), then pops ECX and returns.

The callee is independently recovered as the 94-byte default insert of
list<vector<unsigned int>> in stlport_list_create_node_vecuint.cpp:
its vector-base constructor, typed value insert and exception cleanup
establish that family. See the row and attempts for 0x00079CB6. An int
insert cannot reproduce that complete body; the old pin merely concealed
the caller's wrong element type. Proposed repair: retract the caller row and its stale
list<int>::insert(iterator) pin together. Do not invent an int alias at
79CB6. The native STLport vector-list push_back() is the supported next
identity to verify at 79E8D; no application-level element meaning follows.

Scoped legacy link_check before: integer-list unit 0/687 B and vector-list
provider 0/175 B. Tentative retraction preview: integer-list unit 667/667 B. The other
provider's separate vector<unsigned> constructor conflict remains; its
previous attempts on 2026-10-18 already tested declaration-only and
force-inline alternatives. No closed-strict link gain is asserted.

The retraction did NOT land: the commit hook reverified 161 dependent units
and refused one of 2,355 functions. ProcessGroup in
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DHordeModelDrawProcessGroup.cpp
actually calls the wrongly named push_back and loses its call target.
All original ledger entries and pins were restored. The next repair must
coordinate the true wrapper ownership with that consumer and pass its gate;
add_match requires a real-claim retraction in its own commit. The patch
records only the proposed two-row retraction, not verified progress.
Inputs: MSVC7.1 native TU flags; BFME2 326ff40928.
