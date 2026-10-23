# SubTitleWindow shared exception handler

The whole owner is Code/GameEngine/Source/GameClient/SubTitleWindowDestructor.cpp. Its existing 471-byte constructor at 0x00260865 and 154-byte destructor at 0x00260A3C both pass normal byte verification and complete EH verification. Existing target constructor callers, the 0x6C allocation, field accesses and the WorldBuilder DA4FD0 destructor name supply the lifetime identity; this addition makes no new class-layout or donor-name claim.

Both native prologues install handler 0x00772D1B and FuncInfo 0x00919880. The single unwind state selects the already owned 11-byte action at 0x00772D10, which loads the receiver from EBP-10, adds 8 and jumps to the record-vector destructor at 0x00260826. Both emitted parent graphs reproduce that action and every relocation exactly. Their compiler labels differ, but their native graph is shared.

The handler is exactly 10 bytes, 0x00772D1B..0x00772D25: MOV EAX,0x00D19880 followed by JMP to the CxxFrameHandler thunk at 0x00629182. The next independent cleanup starts at 0x00772D25. Each compiler-emitted handler is also exactly 10 bytes, with DIR32 at offset 1 naming its parent's FuncInfo and REL32 at offset 6 naming ___CxxFrameHandler. The ledger uses the destructor's emitted handler name as the single owner; no second folded name, pin or alias is added.

Whole-file placement search found no further bodies. The published 10:38 census preview reports existing unresolved g_bfmeEndKA and STLport COMDAT conflicts, so exact bytes do not establish that this unit links. The source and its dependencies are unchanged by this handler admission. Native/object proof is retained in ignored build/next-batch-oct19d/subtitle-proof.txt. Model: gpt-6.1-sol.
