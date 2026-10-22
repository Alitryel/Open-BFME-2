# Link helper emission handoff, 2026-10-22

Inputs: BFME2 791c389ce0, retained BFME1 37c3022de1ab944c7ffe536440d637dc8199091c,
published census ae3b3e68e2 (11:05 UTC). No reference inputs or compiler settings
changed. The BFME1 pointer refresh remains claimed by another seat; the stale
freshness stamp was not advanced. Both attempts below were fully reverted and
all claims released. Original matched sources are the best candidates.

## FVF declaration builder

`Code/Libraries/Source/WWVegas/WW3D2/BfmeFVFDescriptorVertexDeclaration.cpp`,
retail 0x1818C0..0x181F69 (1705 B), plus EH handler 0x768488 (10 B).
The current legacy preview holds 1715 B out on the mutable
`__uninitialized_copy<ICoord2D*>` copy and the selected vector overflow copy.
The overflow owner is 0x181770 in MapUtil.cpp; the mutable copy pin is 0x4C3121,
with wrong providers in PartitionManager, WorldHeightMap, MapUtil and this unit.

The original /O2 /G7 /EHs /Ob2 /arch:SSE /Op, malloc/static-STLport setup has a
force-inlined push_back. Trial 1 hid both overflow and mutable uninitialized-copy
with declaration-only specializations. Trial 2 hid only the copy. Both failed
the 1705 B parent byte gate (EH row still passed). Hiding overflow makes the
compiler initialize its empty false_type argument. Even copy-only suppression
changes register and frame allocation: retail begins `55 8b ec 83 e4 f8`
and reserves 0x24 bytes, whereas the trial has a different EH prologue and
reserves 0x30. The original body visibility supplies compiler summaries needed
by the matched caller. This is not evidence that the verifier is wrong.

Next prerequisite: reconcile the actual kept providers while retaining the
caller-visible body information, or prove an inline-only emission mechanism.
Do not repeat declaration-only suppression or reconstruct the matched parent.

## String-key hashtable resize

`Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva00056BFE.cpp`,
retail 0x56BFE..0x56CC3 (197 B), /O1 /G7 /Oy- /EHsc and its existing
no-exceptions/static-STLport flags. Its private hash<string> is the first-kept
wrong copy; it also blocks stlport_hash_map_string_uint_resize.cpp (382 B). Other active
blockers include __stl_string_hash, the bucket helper at 0x51B89, and the
allocator-proxy constructor. The string-uint and XferBlockWriter providers
have retail-proven hash<string> copies in the frozen index.

Trial 1 used declaration-only hash<string>::operator(), __stl_string_hash,
the element hashtable's _M_bkt_num_key, and the alloc_proxy<void**> constructor.
This introduced an EH frame. Trial 2 added throw() to those declarations;
the EH disappeared, but register allocation and loop scheduling still changed.
Retail reserves 0x1c bytes, keeps buckets in EBX and the old count in EDI;
the trial reserves 0x18 bytes, exchanges those registers and rotates the loop.
Both full-byte gates failed. Neither is a useful replacement for the exact
original source. The compact target/trial diagnostic below preserves the
remaining mismatch; no partial C++ body is banked.

A future repair needs compiler-visible inline bodies without competing emitted
copies, or a reconciliation of the first-kept provider that passes every
consumer. Do not repeat the two declaration-only variants unchanged.

## Session result and remaining leads

4680dc89b1 isolated the already blocked Pod900 operations: +2174 B legacy linked.
791c389ce0 removed competing selection-translator helper emissions: +4145 B
legacy linked. All 44 moved/remaining Pod rows and all three selection rows
passed their normal byte gates. Total measured improvement: +6319 B legacy;
no self-strict, closed-strict or new authored-C++ growth is asserted.

Current-object checks found many stale failures already repaired upstream,
including the fallback-texture 0x13331A unit and list assignment 0x289FBC.
They received no credit. name_globals dry-run found no edits. rehome_rows could
not use a missing census.log; no census was rebuilt. Larger unresolved families
(MilesAudioManager, StreakRenderer, GameLogicDoXfer, MeshGeometryGetEdges) need
separate ABI/provider work. BridgeBehavior's secondary UpdateModule vtable has
an incompatible private base view; merely changing a slot is insufficient.
The locale-global and ShareBuffer vector2 candidates were held by other seats.
