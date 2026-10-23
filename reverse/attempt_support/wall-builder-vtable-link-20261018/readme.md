# Wall-builder lifetime table reconciliation

Parent: 71cc64ea98. Published census: c2c5ac8c27. Current paired-object legacy
preview: 42 -> 147 matched bytes link (+105 B); constructor remains 42 B and
destructor unit gains its 77 B complete destructor and 28 B scalar wrapper.
This is not a closed-strict gain. Strict current-object receipts cover 4/4 rows;
closure was not checked. No authored C++ byte increase is claimed.

Target evidence: constructor/destructor vptr stores identify VA C62874. The
whole 12-byte native table is three DIR32 entries: 8E9F52 (scalar destructor),
8E9FB2 (update), and 8E9B70 (cleanup). Both object tables now reproduce all
three entries, including the compiler's weak vector-to-scalar deleting-destructor
fallback. table.txt records the object relocations and reconstructed bytes.
The last two workers take an unadjusted this; the complete destructor already
calls cleanup. Existing ledger names remain their owners. The opaque class is
not renamed from this table evidence alone.

The constructor had modeled the deleting destructor as a normal inherited
virtual, omitted cleanup, and aliased the base class's slot names. Its view now
has the actual virtual destructor and derived slot declarations. novtable and
the imported forceinline constructor-only base cleanup prevent emission of an
empty base destructor in place of the separately rowed 506B28 body. The dtor
view gains the same two remaining virtual slots. Derived slot aliases target
existing row names; no pins, ledger extents, or baseline entries are changed.

Acceptance: four byte-exact rows; one exact EH record; zero converged-data
second names/unjudged addresses; no shadow data findings; all definitions
rowed; all three native table entries checked in both objects. Link prediction
checks both units together against the same frozen index before and after.
The first two constructor aliases are replaced, and two aliases are added to
the destructor view; this existing hatch is not counted as authored recovery.
