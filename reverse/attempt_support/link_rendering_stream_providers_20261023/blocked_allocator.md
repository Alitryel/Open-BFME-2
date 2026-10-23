# Existing allocator ownership move refused

At BFME 2 2d93ad8839, the existing BfmeE12 allocator row at
0x00395928 has extent 28 and lives in stlport_deque_e12_o1.cpp.
GPUParticleStorageConstructor.cpp emits its complete same-named body with
exact bytes and relocations, no unresolved relocation (byte_preflight.txt).
The source and declarations require no change.

add_match --replace-existing refuses before compilation because a second
existing allocator<vector<BfmeE8>> row also occupies 0x00395928 in
SidesListCastleBuildLists.cpp. No new name, row, pin or alias was requested.
This is a suspected false rejection of a pure existing-row ownership move;
do not delete the competing row, add an alias or bypass admission. Both rows
remain unchanged. A tooling seat should reproduce with the two existing
rows and decide whether existing-row replacement needs a regression fix or
the old folded identities first require canonical reconciliation.

The independent rendering/deque/stream moves proceed without this 28-byte
candidate. Its RVA and unused provider-file claims are released.
