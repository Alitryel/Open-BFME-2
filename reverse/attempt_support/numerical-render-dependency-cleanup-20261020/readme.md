# Numerical-library rendering-dependency cleanup

BFME2 base24bc709a, BFME1 reference92f6bbe8. The pinned WWLib random.cpp, mpmath.cpp and pk.cpp donors contain neither render-object includes nor synthetic vector-constructor iterator anchors. Independently decoded owned native bodies have no call to iterator1423. The current emitted code has no relocation to that iterator.

Remove the unused rendobj include and synthetic iterator block from these three units. Keep every arithmetic function, table, random state, static bignum definition, allocation macro and compiler setting unchanged. The random state arrays contain primitive int/unsigned values; mpmath's digit is unsigned long. Although pk.cpp includes RandomStraw's real Random3Class[32] member and the Gcd template's T[3] local, its current object emits neither constructor/template machinery nor a call to the iterator. This conclusion comes from the whole object, not merely the owned native rows.

Normal whole-file checks pass107/107 rows,13458 claimed bytes. Every resolved native row hash is identical before and after; all three frozen object pairs link cleanly against the same index. Both EH checks find0 owned graphs and0 missing objects. The only removed external name is each unit's redundant iterator copy; no name is added, and other providers including the canonical ATL owner remain. Focused placement finds0 bodies/0 pins, and the three explicit current providers have strict reusable verification receipts.

This removes three synthetic anchors, six pragma-optimize directives and three unused rendering includes. Zero new unique bytes and zero new linked bytes are claimed. No header, baseline, pin, alias or verifier changed.

The paired record contains source/object SHA256 hashes, each resolved native row hash, symbol inventories, compiler flag comments and link verdicts. The independent native/donor packet and other-provider witnesses are included. Frozen actual objects, dependency receipts and original source copies remain under ignored build/numerical-anchor in the writer checkout. This is the final compatible cleanup cohort for this batch.

Agent: Codex (runtime model not exposed).
