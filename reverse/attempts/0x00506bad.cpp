// ?Rva00506BADDistSqr@@YAMPBURva00506BADCoord@@0@Z
// partial score=0.9 date=2026-10-14
// cl: /O1 /MD
// ?Rva00506BADDistSqr@@YAMPBURva00506BADCoord@@0@Z, retail 0x00506BAD
// (47 bytes, cdecl): squared distance between two float triples, kept on
// the x87 stack (no SSE in this body). Unreferenced in the image; the name
// is address-derived.
struct Rva00506BADCoord { float x, y, z; };

float Rva00506BADDistSqr(const Rva00506BADCoord *a, const Rva00506BADCoord *b)
{
	Rva00506BADCoord d;
	d.x = a->x - b->x;
	d.y = a->y - b->y;
	d.z = a->z - b->z;
	return d.x * d.x + d.y * d.y + d.z * d.z;
}
