# FX parameter vector linkage handoff

Current base8ea8de9596, BFME1 pointer92f6bbe8. Narrowing the whole-class
instantiation in stlport_vector_rva0007bb16_destroy.cpp to its rowed clear,
Construct and uninitialized_fill_n helpers preserves all7 rows, including EH
and the renumbered cleanup label (142B). It removes local default/erase/growth
losers, but links0B. Assignment1522CF (206B) also remains blocked.

The published index identifies fxshadersetup.cpp as the wrong kept provider of
allocate_and_copy151DCB and uninitialized_fill_n151E15; GrowthFootprints and
the cleanup unit supply retail copies. Declaration-only specializations in the
caller trigger MSVC7.1 C1001 P2 internal compiler error at _vector.c50 (reserve's
allocate_and_copy call), both before and after the record layout is complete.
Two failed builds; no further variants attempted. The caller patch and exact
cleanup candidate are evidence only. Production files are restored.

Independent hypotheses remaining: preserve caller inline visibility with a
scoped import declaration, or reconstruct reserve's native call visibility
without the member-template specialization. Verify the whole caller and EH;
do not suppress unrelated unused COMDATs or claim the zero-gain cleanup alone.
No identities, pins, headers or ledger rows changed. Claims released.
