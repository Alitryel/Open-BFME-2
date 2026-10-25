# Mesh material I/O: current provider check and obsolete hatch removal

Inspected BFME 2 `d7fa8a31bf3`, with the unchanged committed BFME 1 pointer
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. The picker served the whole
`Code/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp` unit at `0x00188020`.
All eleven rows, totaling 352 bytes, remain at their existing addresses and
owners. No names, pins, layout, ABI, compiler flags or source paths change.

## Current linking evidence

The published index is `f995f30157`, 2026-10-25 21:36 UTC. Checking only
meshmdlio still reports the historical wrong selected
`DynamicVectorClass<VertexMaterialClass *>::Add`. Checking its current object
together with the current shattersystem object clears that blocker and previews
meshmdlio as LINKS, both before and after this change. This confirms the
consumer scope of the earlier `69e0157d1a8` repair (LINK-012); it is inherited
repair, not a new 352-byte gain from this commit.

Shattersystem itself remains blocked: Add_Texture, Get_Vertex_Normal_Array and
Set_Single_Texture are unresolved; Get_Z_Vector and ShaderClass copy conflict;
the selected Add_Vertex_Material and Peek_Single_Material are wrong. Those
seven findings are identical in the paired controls. No whole-family, strict
closure, executable or new census claim is made.

## Cleanup and rejected trial

Remove the old un-emitted `BfmeVciAnchorElem`/`bfmeVciAnchor` construction anchor
and its `#pragma optimize("gsy", on)` / reset pair. It is no longer needed to
preserve any of the eleven full bodies or this unit's ordinary linking result.
Remove the stale `present-unmatched` marker from MeshSaveContextClass's
destructor: its existing eight-byte row at `0x00188390` is exact.

An independent trial also removed the RefCountClass size-optimization pair.
The eleven rows still matched, but this introduced an unreferenced Add_Ref
diagnostic (five emitted bytes instead of the retained four-byte copy). That
trial was rejected and the RefCount optimization restored. Do not repeat it
as an unconditional pragma cleanup. The final source has only the proven
anchor/marker removals.

`hatch_counters.py --update` generated the register changes. Only this unit's
generated hunks are retained: two optimization occurrences and one stale
present-unmatched occurrence are retired. Unrelated pre-existing register
slack is left alone. No admission, allow override or gate relaxation is used.

## Verification

- Normal `./build.sh` passes 11/11 complete bodies, strings, floats and imports
  after each trial and after restoring the RefCount optimization.
- `find_declared_unmatched.py` passes with all definitions declared.
- The paired ordinary link previews retain the same 352-byte clean consumer
  scope and the same seven provider blockers.
- `place_bodies.py` on the final file finds zero bodies and zero pins.
- Reference refresh: BFME 1 ranked and near queues are empty; lift pass read
  140 bodies as leads; forced Zero Hour compile builds 919/987 with 68 donor
  refusals, then match/packets produce no free candidate packet. No donor
  import, original-name inference or new byte coverage is claimed here.

The retired hatch count is the new result. Linking headline changes await a
maintainer census; runtime exit requirements remain unchanged.
