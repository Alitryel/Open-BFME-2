# Shader null sentinel trial superseded during recovery

Recovery on 2026-10-18 found upstream commit 13196d48f3 already registers
?NullShader@@3VShaderClass@@A at RVA 0x009F6F2C with its existing definition
in MeshMatDescDefaultCtor.cpp and a verified data_rows.csv entry.
That repair establishes the actual owner and already makes the 349-byte
reader link. The saved trial renamed the consumer and unowned ledger entry
to a donor class static without defining that member. Replaying that rename
would discard current ownership and introduce an unresolved class static.

Keep upstream's free global declaration and owned ledger entry unchanged.
The obsolete source/data rename from af378de39c is removed during rebase;
its original trial remains in refs/runner/preparation/1792331358981882686.
No additional linked-byte gain is credited to this evidence-only recovery.
The blocked GeometryInfo trial recorded by that commit remains preserved
in re_attempts.log; its nonmatching source was already restored.
