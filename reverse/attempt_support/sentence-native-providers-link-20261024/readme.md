# Sentence record helpers use their native providers

The newer target-derived PendingSurfaceStruct provider implements the complete
native constructor at `156A10`, assignment at `1568E0`, vector Resize at
`157780` and Add at `157060`. Its 28-byte record has surface storage at zero
and a 24-byte renderer vector at four. The constructor, assignment, Resize and
Add sources document their independent native calls, field accesses and array
callbacks; these established bodies and their identities are unchanged here.

The older `render2dsentence.cpp` donor view emitted implicit record construction
and pointer/vector assignment, plus its own Resize/Add. They were selected
before the verified providers, and their bytes were not native. The isolated
declaration trial removed those four definitions; every remaining ordinary
matched body was unchanged. Declaring the native special members removed an
accidental renderer-vector instantiation path too. Explicit assignment and
constructor instantiations retain the four existing renderer-vector rows,
including the virtual destructor and deleting wrapper, without a new anchor.

`Render2DSentenceDonorView.h` carries the complete BFME1 donor header from
`32774ab03393709a7f14331ba8d98d281a55ffd9`, retaining its license and attribution.
Only the pending record becomes accessible for legal external template
specialization, and its existing native constructor/assignment are declared.
No fields, sizes, virtual slots or other class access levels change. An initial
private-type specialization failed C2248; friendship alone still failed on the
qualified parameter type, so only that nested type was exposed. These access
changes do not alter its ABI. This is a TU-scoped donor view, not a new claim
that all donor fields or renderer element identities have been established.
No submodule, shared tool, pin, ledger row or verification baseline changes.

## Evidence and validation

`link-proof.json` compares the original HEAD donor source and repaired source
against the same current follower index at `c3d347cf53`. The original compiles
in an isolated directory with the original source's compiler command; the
normal current object supplies the repaired side. Only that provider object
is replaced in each in-memory index. No census or link runner is started.

The PendingSurfaceStructResize unit has four wrong-selected helpers before and
none after. Its **542 existing matched nonpadding bytes** now link. The donor
unit remains blocked on surface Lock/Unlock, FontCharsClass::Store_GDI_Char and
renderer-vector destruction; these are not credited as gains. Other sentence
consumers retain their integer-vector lifetime blockers.

The normal scoped byte gate passes all 35 existing rows in both units. The
two compiler cleanup labels are renumbered, and the normal gate verifies their
placement from the unchanged parent EH graph. `body-proof.json` additionally
checks every ordinary matched body in both units strictly with alias notes
cleared; EH and cleanup rows are checked by the normal gates. No new recovery
or unique-byte gain is claimed.
