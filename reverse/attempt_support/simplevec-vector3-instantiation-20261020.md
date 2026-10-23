# Vector3 vector owner emission

`simplevec_vector3_dtor.cpp` previously emitted the 23-byte artificial
`bfmeEmitsimplevec_vector3_dtor` function solely to force copies of its real
`SimpleDynVecClass<Vector3>` constructor and `Resize`.

Explicit instantiations after the existing inline definitions emit the same
select-any methods directly. The artificial function, its `present-unmatched`
marker, and its `inline_depth` pragmas are removed.

At BFME2 `24bc709a164cff181a32062b16b3d663aa82a933`, with pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`:

- All seven existing rows, totaling 227 retail bytes, remain exact.
- Every real COMDAT has identical bytes and relocation digest. This includes
  both vtables, both deleting destructors, and the constructor/Resize copies.
- The only removed definition is the artificial 23-byte helper; there are no
  new strong definitions. Undefined references, including the separately
  owned base `Resize` and `Uninitialised_Grow`, are unchanged.
- The unit has no exception graphs, and the placement scan finds no additional
  bodies or pins.
- Frozen before/after object checks against published index `144ed0ccab`
  both have no linking findings.

This is source and emission cleanup, with no new recovered coverage.
