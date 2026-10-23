# Random-force provider linkage

`ApplyRandomForceNugget::create` at `0x001F01F1` still called an address-named
declaration although the existing `ObjectCreationList.cpp` owner already
recovers `calcRandomForce` at `0x001F0247`.

Native call site `0x001F022B` targets `0x001F0247`. It passes four floats and
the address of a 12-byte stack vector, then releases 20 bytes of arguments.
This agrees with the existing provider's cdecl signature and the canonical
12-byte `Coord3D` layout. The caller now uses that canonical type and function
name. The provider's body is unchanged; removing `static` makes its existing
implementation available to the separately recovered caller.

COFF inspection confirms the provider changes from storage class 3 (local)
to class 2 (external), and the caller references the same external symbol.
No alias, pin, new provider body, or shared-header edit is introduced.

At BFME2 `54a521e4`, pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`:

- Whole-unit verification passes all 24 existing rows across both sources,
  including the 86-byte caller and 422-byte provider.
- All four checked exception graphs remain exact, with no baseline debt.
- Paired actual-object link checks against published index `5366c4f808`
  change 0 to 86 linkable bytes. The provider unit's 1,494 bytes retain their
  21 independent existing findings; no gain is credited for that unit.
- Placement scans of both affected sources find no new bodies or pins.

This is an 86-byte linking repair, with no new recovered retail coverage.
