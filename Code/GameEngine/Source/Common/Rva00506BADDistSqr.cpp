// cl: /O1 /MD
// ?Rva00506BADDistSqr@@YAMPBURva00506BADCoord@@0@Z retail 0x00506BAD (47 B,
// cdecl): squared distance between two float triples, kept on the x87 stack.
// Unreferenced in the image; the name is address-derived. The sum is spelled
// (x*x + z*z) + y*y: retail evaluates the rightmost term first and then the
// left group, which this parenthesization reproduces.
struct Rva00506BADCoord
{
	float x, y, z;
};

float Rva00506BADDistSqr(const Rva00506BADCoord *lhs, const Rva00506BADCoord *rhs)
{
	Rva00506BADCoord d;
	d.x = lhs->x - rhs->x;
	d.y = lhs->y - rhs->y;
	d.z = lhs->z - rhs->z;
	return (d.x * d.x + d.z * d.z) + d.y * d.y;
}
