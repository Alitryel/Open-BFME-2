// cl: /Ireference/shims/bfmerendobj /O1 /G7 /MD /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Clean BFME1 donor 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/Libraries/Source/WWVegas/WWMath/matrix3d.h four-vector constructor.
// Lead: vehiclecurve.cpp with original header directory first, O1/G7/SSE/MD.
// Target Ghidra 147B at 7B890, RET16: copies four 12B input vectors into
// three 16B rows, each row receiving one component from each input.
// First constructs three 16B entries through the existing iterator 1423;
// callback 47A6A9 is the complete 3B return-this body shared by empty ctors.
// No E8/E9 callers found; original class/method names and reachability unknown.
// Target iterator arguments prove three16B entries starting at this; stores
// prove all twelve component offsets. This address-labelled48B prefix uses
// shared Vector4/Vector3 types; original/full object layout is unknown.
// No Matrix3D identity or new helper byte credit is claimed.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
#include "vector3.h"
#include "vector4.h"
class Rva0007B890MatrixBasisCtor
{
public:
 Rva0007B890MatrixBasisCtor(const Vector3 &x, const Vector3 &y,
                          const Vector3 &z, const Vector3 &position);
private:
 Vector4 Row[3];
};
// ?store_row absent-from-retail
// TU-local inline equivalent of donor Vector4::Set: evaluate all input
// components before writing the row, without emitting its wrong SSE COMDAT.
static __forceinline void store_row(Vector4 &row, float a, float b, float c, float d)
{
 row.X = a; row.Y = b; row.Z = c; row.W = d;
}
Rva0007B890MatrixBasisCtor::Rva0007B890MatrixBasisCtor(
 const Vector3 &x, const Vector3 &y, const Vector3 &z, const Vector3 &position)
{
 store_row(Row[0], x.X, y.X, z.X, position.X);
 store_row(Row[1], x.Y, y.Y, z.Y, position.Y);
 store_row(Row[2], x.Z, y.Z, z.Z, position.Z);
}
