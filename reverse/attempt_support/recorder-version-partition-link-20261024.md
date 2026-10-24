# Recorder version-check ownership

Input BFME2 7ffc6dcd9c; frozen published census a9f880ad06,
retail-truth-4. BFME1 verified input 32774ab03393 remains fresh.
Reviewed its RecorderHandleCRCMessage and RecorderReadReplayHeader donors.
Their sequence is already represented in the target source; target offsets,
Unicode filename, CRC view and class identities remain unchanged.

The recorder's version check (0x0037D0EF, 247 B) has no dependency on the
constructor's vtable emission or the CRC dispatcher's opaque queue methods.
Move those two definitions and all five associated EH rows unchanged into
Rva0037BCC4DeferredCtorCRC.cpp. Retain the version check and its three EH
rows in Rva0037BCC4_Unresolved.cpp. Compiler flags and ABI declarations stay
the same. No pins, aliases, data values or function bodies change.

Paired scoped current-object `link_check.py Rva0037BCC4_Unresolved.cpp`
changes from 0 to 247 linked authored bytes against the same index.
This is a legacy preview, not a closed-strict result or census measurement.
The new deferred unit has no index position and earns no gain.
Both units pass all 11 byte checks, two exact EH graphs, frozen definitions
and strict reusable receipt preparation through the normal byte gate.

Remaining deferred prerequisites: the native CRC queue push/pop contract
currently spelled Rva0037D097CRCView::rva0037D097/rva0037BD64, and the
constructor's private Rva0037BBED vtable against the kept definition. Do not
rename CRC storage to FXList merely because the existing wrappers fold.
