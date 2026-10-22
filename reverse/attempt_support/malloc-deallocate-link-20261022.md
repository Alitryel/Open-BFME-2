Allocator keeper repair, 2026-10-22, gpt-6.1-sol

At a3deb0d4e5, the published census (08160bc2c9, retail-truth-4) has only two
COMDAT providers of __malloc_alloc<0>::deallocate: the correct 18-byte owner
STLMallocAlloc0Deallocate.cpp at 23A70, and the earlier incompatible copy in
stlport_wide_money_put_string.cpp. Its direct, throwing C++ free declaration
is required by that formatter's inlined expansions. It is not the owner's
unoptimized dllimport-C free context.

Make the formatter's specialization dllimport/forceinline, retaining the
vendor body free((char *)p) and its existing local declaration context.
The formatter's 10 matched rows remain exact; its object no longer defines
the conflicting allocator symbol. No new pin, global, source alias or retail
identity is asserted.

Legacy current-object link_check, same three explicit units before and after:

* STLMallocAlloc0Deallocate.cpp: 0 -> 18 B LINKS.
* stlport_construct_deque_string.cpp: 0 -> 100 B LINKS.
* stlport_wide_money_put_string.cpp: 0 -> 0 B, independent existing blockers
  remain (facet ids, duplicate definitions, other STL copies).

Total +118 B linked, measured with the changed provider included so its old
definition is removed from the in-memory index. The published census/status
is unchanged. This is not a closed-strict link-cycle claim. prepare-current
byte-verifies the one changed provider with strict reusable receipts; the
normal byte/ref gate passes all 10 rows, and the EH graph is checked too.
Unchanged newly enabled units are byte-checked separately.

An accidental --refresh invocation was interrupted during stale-source
inspection, before any compiler process was started. Measurements above use
only explicit paths, without --refresh. Registry vector destructor visibility
trials in the same evidence batch are separately banked and reverted.

Publication reconciliation: upstream 2040751dcb independently landed this
same specialization before this batch rebased. Retain its source. This
commit preserves the independent measurement and Registry handoff; the
118-byte result adds nothing over the updated origin/master.
