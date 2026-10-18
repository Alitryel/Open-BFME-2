# AsciiString list sentinel constructor linkage

The current-provider baseline finds the shared `_List_base<AsciiString>` constructor wrongly selected in all twelve current emitting units. Its existing pin names RVA 4EC36C, the existing 41-byte physical `_List_base<int>` owner. The first GameSpyLoginPreferences copy instead calls its private allocator-proxy allocation wrapper. Rva0054F434Vslot1 emits a second non-retail copy.

The complete native constructor initializes the allocator proxy through 14F3C4, allocates a 12-byte list sentinel through 307F0, makes the next/previous links self-referential and installs the sentinel pointer. The existing canonical byte allocator is a verified 22-byte provider in stlport_byte_allocator.cpp. Its existing BucketAlloc::allocate binding reaches the same implementation; no pin or alias directive is added.

The GameSpy specialization preserves STLport 4.5.3's allocator-proxy initialization and sentinel construction, using the target-proven byte allocator. Its complete 41 bytes and resolved relocations equal the physical owner. The existing AsciiString constructor pin and independently matched callers establish that this is a fold, not a second address. A declaration suppresses the unused competing constructor in Rva0054F434Vslot1.

A plain specialization declaration and an explicit-instantiation declaration were both refused by the byte gate: the 237-byte email getter's frame grew from 14h to 18h and its cleanup graphs no longer matched. Keeping the real corrected constructor visible preserves compiler analysis and all existing matched caller bytes. No nonmatching trial remains in Code.

Reference review used verified BFME1 revision 64d369b90170b7e9ec917d646f020b11f13eb0d5. The GameSpyLoginPreferencesGetEmails donor establishes the returned list's ownership and traversal semantics, but uses different allocator settings and is not a direct allocation repair. The target's complete constructor and existing BFME2 allocator provider determine this adaptation. BFME1 ranked and near lanes and lift_lane were reviewed; no ready donor transfer was substituted for this linking repair.

The controlled comparison retains the pre-repair identity map and original constructor pin for both old and current objects. The new folded row is excluded only from that in-memory RetailTruth input: otherwise its shared-address fallback would stop disproving the old wrong constructor. All current rows independently pass normal verification.

proof.json records unchanged existing code and relocation sites, independently EXACT before/after parent EH graphs, and a controlled in-memory link comparison against one provider snapshot. It records the twelve cleared wrong selections separately from the units that become fully linkable. No measured census, full-game link or runtime result is claimed.

The accompanying cleanup receipt independently places the SplineEffect string-result cleanup using its actual parent's EXACT exception graph, checks all 25 bytes and the existing AsciiString destructor at48BA39, then retires its standalone MASM provider. No synthetic emitter or new symbol pin is introduced.
