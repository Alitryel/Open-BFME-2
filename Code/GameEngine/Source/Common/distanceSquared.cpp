// cl: /O1 /MD
// ?distanceSquared@@YAMPBURva00506BADCoord@@0@Z retail 0x00506BAD (47 B,
// cdecl): squared distance between two float triples, kept on the x87 stack.
// Unreferenced in the image; the name is address-derived. The sum is spelled
// (x*x + z*z) + y*y: retail evaluates the rightmost term first and then the
// left group, which this parenthesization reproduces.
struct Rva00506BADCoord
{
	float x, y, z;
};

float distanceSquared(const Rva00506BADCoord *lhs, const Rva00506BADCoord *rhs)
{
	Rva00506BADCoord delta;
	delta.x = lhs->x - rhs->x;
	delta.y = lhs->y - rhs->y;
	delta.z = lhs->z - rhs->z;
	return (delta.x * delta.x + delta.z * delta.z) + delta.y * delta.y;
}
