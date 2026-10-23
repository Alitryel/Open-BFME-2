# Sun-ray initializer provider repair, 2026-10-23

The existing 1984-byte initializer at 0009CD9B reads two values apiece into
DE5E0C/14/1C/24 and later selects entry 0 or 1. Four extern-only arrays had no
compiled providers. Define those existing two-float symbols in their consumer,
and row their complete eight-byte zero-initialized retail ranges (32 data bytes).
These ranges do not overlap an existing data row; original names remain unknown.
The target accesses establish their layout and role, independently of any donor.

The texture call already passes the address of the owning handle. Its RefCountPtr
reference spelling is pinned to 0015E250 but has no emitted provider. Use the
existing rowed TextureClass-pointer spelling and pass the same handle address,
as W3DProjectileStreamDrawModule and W3DWaypointBufferDestructor already do.
The existing thunk adds DC to this and jumps to 001911E0, whose read-through and
reference count behavior establish this handle ABI. No alias or pin was added.
The historical pointer spelling is preserved; no new class identity is asserted.

Paired current-object legacy link checks against index d4fa46f19a, census
2026-10-23 19:41 (retail-truth-4), change the consumer from 0/1978 to 1978/1978
nonpadding bytes. Unchanged segline.cpp and seglinerenderer.cpp providers remain
23068/23068. Total bounded preview: 23068 -> 25046, **+1978 existing bytes linked**.
This is not a self-strict or closed-strict census gain or a link.exe placement.

Acceptance: normal build 3/3 function rows and 4/4 data rows, string/float/import
references pass; frozen-definition and check_csv checks pass; data_check reports
zero findings; strict receipt preparation and new-COMDAT-variant checks pass.
Normal hooks run without bypass. EH cleanup label renumbers from L2515 to L2516
and is independently located through the exact parent EH graph. No baseline,
verifier, census history, link status or pin edit. Raw local logs are under
build/link-seat-sun/. Other uses of the old setter alias were searched; the two
existing caller units already use the rowed pointer spelling.

The same commit records a read-only rejected prerequisite-assignment candidate:
2D0C44/564CD4/565668 confuse a single-string record and vector<int> with native
two-string/record providers. No speculative source change from that probe remains.

Shadow-check limitation: code_identity_gate reports one new binding finding for
uw_0076061c, naming the RefCountPtr<TextureClass> destructor at retail 0002FD60
(operator delete). Its scanner takes the stale ledger object-symbol L2515; the
normal byte gate and strict receipt instead follow the exact parent EH graph,
which locates this row at the renumbered L2516. Thus the shadow finding appears
to inspect the neighboring delete cleanup against this row's retail bytes.
This was reproduced with code_identity_gate.check on this source. The commit
was accepted normally; no baseline or verifier workaround was made. A tooling
seat should reconcile identity scanning with the byte gate's EH-label resolver.
