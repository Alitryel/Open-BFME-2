# ModuleFactory provider recheck

Input 3c6c4f6651; legacy published index 11b3872700 still ranks ModuleFactory
blocked. Current-object link_check instead reports all ten candidate units
link-clean, including ModuleFactory's existing 2,393 B. Rehoming twelve exact
helpers would move ownership without adding linked bytes; nothing was changed.

The thirteenth proposed transfer, ObjectCreationList pointer-vector allocator
constructor 0x004F710A (18 B) into RubbleRiseUpdateModuleDataCtor.cpp, reproduces
complete bytes and resolved relocations but fails allowed_symbols: its
_Vector_base<const ObjectCreationList*> call at offset8 binds to 0x00211E58
without an admitted identity. It stays in its original home. This is a blocked
transfer, not a blocked implementation or an assertion of verifier error.

BFME1 f5140c1c ModuleFactory reviewed: container roles apply, donor interface
mask layout differs (+C against the vendored +8 view), so no layout imported.
All 23 RVA/file claims released. No authored or linked-byte gain claimed.
