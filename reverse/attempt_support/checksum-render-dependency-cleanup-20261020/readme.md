# CRC and hash rendering-dependency cleanup

BFME2 base24bc709a, BFME1 reference92f6bbe8. The pinned WWLib crc.cpp, realcrc.cpp and hash.cpp donors contain neither render-object includes nor synthetic VCI anchors. Independently decoded owned native bodies have no call to array-constructor iterator1423. CRC buffers and lookup tables hold primitive values; HashTable allocates an array of pointers, so none needs class element construction.

Remove the unused rendobj include and synthetic iterator block from all three units. Actual algorithms, tables, implementation bodies, compiler flags, identities and imports remain unchanged. In particular, hash.cpp keeps its established _OPERATOR_NEW_DEFINED_ guard and scalar new/delete behavior inherited from BFME1 e04d5580 and separately proven against native constructor/destructor calls.

Normal whole-file checks pass20/20 rows,1058 claimed bytes. Every resolved native row hash is identical before and after; all three frozen object pairs link cleanly against the same index. Both EH checks find0 owned graphs and0 missing objects. The only removed external name is each unit's redundant iterator copy; no name is added, and canonical providers remain. Focused placement finds0 bodies/0 pins. This removes three synthetic anchors, six pragma-optimize directives and three unused rendering includes. Zero new unique bytes and zero new linked bytes are claimed.

The paired record includes source/object SHA256 hashes, each native row hash, symbol inventories and link verdicts. The native/donor packet and other-provider witnesses are included. Frozen actual objects, dependency receipts and original source copies remain under ignored build/checksum-anchor in the writer checkout. No header, baseline, pin, alias or verifier changed.

Agent: Codex (runtime model not exposed).
