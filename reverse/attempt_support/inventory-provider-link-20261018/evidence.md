# Control-bar inventory table provider consolidation

The current-provider baseline finds two strong definitions of ControlBarInventoryEntries: ControlBarCommand.cpp and its split update-context unit. The main unit owns the actual population callback and the split unit does not reference the table. Changing the split definition to an external declaration leaves one allocation and removes the duplicate from both units. The main unit becomes locally linkable; the split unit still needs the separately banked rva0031D230 provider.

Both views declare the same 32 entries, each containing a 32-bit window pointer and a 32-bit object ID. Native callback53B98C writes the pair through VA E05E20/E05E24; the whole256B target region is zero-filled. Other existing lookup and command-processing views use this same table. The descriptive global spelling is already established in BFME2 and is not presented as an original symbol identity. No data or code name, address pin, layout, alias or header is introduced.

Reference review used verified BFME1 revision64d369b90170b7e9ec917d646f020b11f13eb0d5. Its ControlBarCommandProcessing.cpp and ZH populateInvDataCallback establish the inventory window/ObjectID pairing and sharing between population and exit-container lookup. The donor uses m_containData; BFME2's absolute native references independently establish the existing global-table representation. No donor layout or original global name is inferred.

proof.json compares the original and current split objects against the same refreshed provider snapshot. Every existing row's code bytes and all relocation targets remain unchanged, and applicable parent EH graphs are independently EXACT before and after. Both sources pass normal complete byte verification. The record separates the newly linkable main unit from the split unit's remaining unrelated blocker. No measured census, actual executable link or runtime result is claimed.

The first investigated string-helper family was already largely repaired by newer pins than the published census. Current objects show no shared link gain from removing its earliest copies, so no string-family source edit was made and those file claims were released.

The separate Apt property-string result cleanup is recovered only from the actual existing C++ parent's independently EXACT EH graph. Its complete25B body and canonical EAStringC destructor call are verified before retiring the standalone MASM row. The source implementation and its EA donor provenance remain unchanged.
