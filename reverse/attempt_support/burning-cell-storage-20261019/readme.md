# BurningCell singleton storage repair: blocked

The existing matched 136-byte getter at RVA 002862C9 is unchanged. This is a
data-identity repair attempt, not a new recovery. Native code constructs the
12-byte vector at VA DFEC74 through 1F81BF, guards it with bit 0 of DFEC80,
registers 7B7810 (destruction through 3ED94F), adds BurningCell once using the
byte at DFEC70, and returns that same DFEC74 object. Previous log entry 36781
already identified the duplicate-data hazard; 54067/54068 recorded the natural
source return mismatch before 54099 landed an external-global return.

Current C++ instead allocates a one-byte function-static class, passes it to
the twelve-byte constructor, and returns a distinct four-byte global in the
broad thunk TU. The isolated baseline COFF confirms the one-byte allocation.
The native twelve-byte extent is also bounded by the independent guard at +12.
The BFME1 donor at the recorded revision supplies bfmeAddKey only, not this getter.

The candidate supplies three actual vector-base pointers and returns its own
function-static object. It emits 136 bytes, but saves and materializes ESI only
after construction, then returns ESI. Native saves/materializes ESI before the
guard branch, uses it for construction and registration, and returns an
immediate object address. This is not exact. Keeping the incorrect external
return with the corrected size instead emits 135 bytes without ESI.

Ruled out: pointer-array and void-pointer return casts; empty-base plus derived
pointer fields; opaque byte/word storage with and without explicit alignment;
external constructor declaration versus visible implementation; /GX, /Ob0 and
/Ob1; /Og- (153 bytes). Making LargeGroupAudioKeyMap the actual base eliminates
the proven allocator constructor call and is not a valid repair. Direct zero
stores similarly lose the proven constructor call. No production source, pin,
ledger row or generated source changed.

Before a future landing, reconcile the generated atexit callback with 7B7810,
the exception guard clearer at 773EB8 with GlobalFlagClearers_DFECxx.cpp, and
the singleton data allocation/return. The normal data-row sizeof probe cannot
name this function-local aggregate (recorded in evidence.json); this is a
separate tooling limitation, not a demonstrated false rejection of exact code.
Do not restore the second global to force a byte match. Existing banks remain
untouched. candidate.cpp.txt and the raw unrelocated disassembly preserve the
best semantically corrected trial; all flags and input revisions are recorded.
