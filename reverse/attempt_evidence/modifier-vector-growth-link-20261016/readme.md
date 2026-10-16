# Modifier vector growth linking trial

The verified source remains in Code/GameEngine/Source/GameLogic/System/AttributeModifierStore.cpp. This is an unsuccessful linking alternative for the already matched replaceModifier body at RVA 0x00214BB0 (158 bytes), not new recovery.

The unit emits conflicting vector<const ModuleData *> growth and allocator copies. The known growth provider is 0x002DFCF6, 140 bytes, in ModuleFactory.cpp. Declaring its specialization suppresses the private implementation but changes replaceModifier register allocation because the original pointer argument may be modified across the call. A separate retired-pointer copy restores the principal register shape, but allocates an extra DWORD: the call takes EBP-0x10 instead of retail EBP+8 and the EH scratch slot moves by four bytes. Explicit reuse of the index parameter instead spills the saved index and changes the register shape again.

The text archive `214bb0.cpp.txt` preserves the closest separate-pointer-copy trial. Copy it to the owning source path before building; its relative includes are those of that source. No row, pin, baseline, or gate change admits this alternative. The committed source was restored and verified after these trials. Static-STLport mode alone also preserved the matched rows but replaced imported allocator failures with COMDAT conflicts; it is not a solution.

Native evidence: the existing complete 158-byte owner calls the 49-byte pointer push_back at 0x004DFCB0. Its shared growth dependency is rowed at 0x002DFCF6. The target keeps the old modifier in ESI and uses its exhausted index argument slot at EBP+8 for the pointer argument. Original application identity of the ModuleData pointer spelling remains unproven; only four-byte retired slots are established.
