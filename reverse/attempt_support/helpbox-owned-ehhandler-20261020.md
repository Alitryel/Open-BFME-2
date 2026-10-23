# Help-box content EH handler

The existing real C++ owner ControlBarPopupDescription.cpp implements
OldSchoolHelpBoxContentSource::createContent at retail 00405E3D, 3287 bytes.
The WorldBuilder twin 01078070 and native vtable 00838970 slot 3 establish
its identity. No source change or new parent identity is needed.

Strict current-object verification confirms the entire parent body and its
associated EH graph EXACT. The native parent's DIR32 handler reference binds
the genuine emitted __ehhandler$?createContent symbol to 0078504C and its
FuncInfo to 009316D4. The whole ten-byte handler loads that FuncInfo address
and jumps to the existing CxxFrameHandler at 00629182. Its full bytes verify,
and neither its name nor retail range has an existing owner.

The normal gate verifies both rows, 26 string literals plus the empty-string
reference, and the parent EH data. No pin, alias, source scaffold or assembly
was added. Result: ten additional unique retail bytes from the real owner.
