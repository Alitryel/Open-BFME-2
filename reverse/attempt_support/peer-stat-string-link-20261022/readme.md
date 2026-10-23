# Peer stat-key string providers

At BFME2 66c176bd18, current legacy preview rejects this 295 B unit on its differing unowned _String_base<char> destructor and non-retail const-char constructor. The successful BuddyThread destructor specialization (unchanged vendor body, dllimport forceinline, throw()) is insufficient without constructor emission control.

Trial 1 combines that cleanup with a declaration-only const-char constructor specialization. Seven of eight rows remain exact; packStatKey has a single allocator-temporary address mismatch: LEA [EBP+0F] instead of retail [EBP+0B] at offset 19. The call destination and cleanup body otherwise agree. Trial 2 uses extern explicit constructor instantiation to retain primary-template visibility; it produces the identical mismatch. No third trial.

The original is restored and build.sh passes 8/8 including references. No source change or linked-byte claim is retained. The trial patch is diagnostic only. A future attempt needs to preserve the allocator temporary location while eliminating the differing outlined constructor and destructor; the sibling visibility repair alone does not prove that. Verified BFME1 input remains 37c3022de1; no donor source imported. t=4 model=gpt-6.1-sol.
