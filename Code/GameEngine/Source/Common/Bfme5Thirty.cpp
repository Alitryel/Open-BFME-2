// Ported from Open-BFME-1's game/GameEngine/Source/Common/Bfme5Thirty.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) via tools/bfme1_sweep.py.
//
// The donor must be carried in pieces: it defines functions the sweep never
// placed and .githooks/pre-commit's find_declared_unmatched refuses a source with
// any definition the ledger lacks. This TU carries ONLY the body that places:
// the donor's plane/vector dot product (donor b1 0x006E18F0, 32B -> game.dat
// 0x00094B67, 32B).
//
// The name is address-derived, not the donor's: lotrbfme.exe folded this body
// across eight addresses, so `?bfmeDot@@YAMPBVBfmePlaneCX@@PBVBfmeVec3CX@@@Z` is
// one of the twins the sweep cannot tell apart, and AGENTS.md forbids spending a
// guessed name on a folded address. The BYTES are not in doubt -- the sweep
// placed the 32 masked bytes uniquely at 0x00094B67, 0x00094B66 (`ret`) is the
// instruction immediately before it, and retail there is a whole function whose
// operand order fixes the expression:
//
//   fld  [eax+8] / fmul [ecx+8]     ; z first
//   fld  [eax+4] / fmul [ecx+4] / faddp
//   fld  [eax]   / fmul [ecx]   / faddp
//   fadd dword ptr [eax+0xc]        ; + w
//
// i.e. (x*x + (y*y + z*z)) + w with the plane's four floats read from +0..+0xc
// and the vector's three from +0..+0x8. No call and no global, so no
// reverse/symbols.csv pin is needed.

class Rva00094B67Plane
{
public:
	float m_x;								// +0x00
	float m_y;								// +0x04
	float m_z;								// +0x08
	float m_w;								// +0x0c
};

class Rva00094B67Vec3
{
public:
	float m_x;								// +0x00
	float m_y;								// +0x04
	float m_z;								// +0x08
};

float __cdecl Rva00094B67Dot( const Rva00094B67Plane *plane, const Rva00094B67Vec3 *point )
{
	return plane->m_x * point->m_x + plane->m_y * point->m_y + plane->m_z * point->m_z + plane->m_w;
}
