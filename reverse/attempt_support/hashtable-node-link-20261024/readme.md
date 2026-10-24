# Hashtable node creator link repair, 2026-10-24

Base c0e0d4ac2a; BFME 1 verified input 32774ab03393; published census
268f876e3b, 2026-10-24 02:54, retail-truth-4.

The two 112-byte insert_unique_noresize units at 000556AB and 005472F8
previously failed the current-object legacy preview: each emitted a wrong
_M_new_node and selected that wrong body. Their comparison/hash record views
expose only the first word, so generic node construction allocates too little.
The native callees already have complete C++ providers: 00054E8B allocates
12 bytes, zeros next, calls Construct at 00053FA4 with value at +4; 005472D3
allocates 20 bytes, zeros next, calls Construct at 00469C61 with value at +4.
These allocation sizes and call destinations are target facts. Opaque record
names and hashtable template spellings remain inferred, as in the existing rows.

Specialize the member creators with those same operations and existing typed
Construct declarations. Keep them out of line: retail passes the table in ECX.
A forceinline wrapper calling the existing stdcall providers removed the two
ECX setup bytes and shrank both parents to 110 bytes; that failed trial was
replaced, not landed. No pins, aliases, ledger identities or compiler flags
change. This is a two-unit sweep of the same allocation/calling-convention cause.

Paired current-object link_check: both 0/112 B before, both 112/112 B after;
**+224 B legacy availability**. Scoped byte/literal/float/import gates pass
2/2 rows. Frozen-definition checks pass. Explicit strict reusable compilation
receipts are also requested for the touched sources; these are compilation
receipts, not proof of whole-tree self-strict or closed-strict gain. No census,
full link cycle or closed-strict gain is claimed. Authored coverage is unchanged.

The same two opaque node creators are the only entries with this exact sole
blocker in the inspected near-3/150 ranking. Other existing new-node routes
already use their rowed native providers and are not counted as gains.
