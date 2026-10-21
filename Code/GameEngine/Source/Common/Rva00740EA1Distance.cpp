// cl: /MD
// ?Rva00740EA1DistanceSquared@@YAHPBE0@Z, retail 0x00740EA1, 77 bytes.
// Squared distance between two 4-byte vectors via movzx sub imul add.
// Evidence: caller at 0x00741459; no callees; reads 4 bytes each.
typedef unsigned char Byte;
int __cdecl Rva00740EA1DistanceSquared(const Byte *lhs, const Byte *rhs)
{
	int d0 = (int)rhs[0] - (int)lhs[0];
	int d1 = (int)rhs[1] - (int)lhs[1];
	int d2 = (int)rhs[2] - (int)lhs[2];
	int d3 = (int)rhs[3] - (int)lhs[3];
	return d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3;
}
