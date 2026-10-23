# String constructor cause sweep, 2026-10-22

Parent 455205ef67; published legacy index 08160bc2c9 (2026-10-22 17:08),
verified BFME1 inputs 37c3022de1. No donor source or pointer changes.

Current-object baseline: StandingWaterAreaLoadPCA.cpp 0/2362 B,
rva0060D2E9Rva0060D2E9Farm.cpp 0/341 B,
PeerThreadStats_PackStatKey.cpp 0/295 B, PingThread_Pinger_getPing.cpp 0/172 B.
Each emits a referenced competing narrow-string C-string constructor and
_String_base<char> destructor. The Horde model-state unit has the same
constructor blocker but was not retried: prior log entry at 0x0007A847 already
records two failed visibility trials.

Trial one: declaration-only specialization of the C-string constructor plus
imported force-inline base destructor with vendor _M_deallocate_block() body
and throw() contract, following the verified BuddyThread repair. Trial two:
replace only the constructor declaration with extern-template instantiation,
keeping the base destructor. The two variants compile identical mismatches:
StandingWater LoadPCA frame 0x240 -> 0x244; XferSave frame 0x20 -> 0x24;
Pinger getPing frame 0x14 -> 0x18. PackStatKey remains 102 B but its first
allocator temporary address changes [ebp+0x0b] -> [ebp+0x0f] at byte +0x14. Parent and/or
cleanup rows fail full-byte verification. Link previews consequently reject
the changed parent bodies; gain is zero. These are combined visibility trials,
not proof that either helper alone causes every frame difference.

After two failed byte builds per unit, all four sources restored and the normal
byte gate passes all 40/40 original rows. Diagnostic
patch preserves trial two; trial one substitutes template <> for extern template
on its constructor declaration. No nonmatching reconstruction, pin or alias
was retained. A future attempt needs a distinct explanation for allocator
escape/lifetime packing or independent provider reconciliation, rather than
repeating these declarations. Original code, compiler flags and includes remain
in the parent commit. Local diagnostic logs: build/seat-string-{before,after2}.log,
build/seat-string-gate{1,2}-[0-3].log. No closed-strict gain or full link cycle.
