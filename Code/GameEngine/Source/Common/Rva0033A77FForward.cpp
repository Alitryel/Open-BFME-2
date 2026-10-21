// cl: /O1 /Oy- /DNDEBUG /MD
//
// ?rva0033A77F@Rva0033A77F@@QAEXHHHHH@Z @0x0033A77F 35B.
// Forwarder: passes its five stack arguments plus a trailing 0 to the member
// object at +0xA0 (thiscall, ret 0x14), calling 0x006BEF80, the rowed
// GeometryInfo::getBestContactPoint (GeometryInfoCollidesWith.cpp).
// Retail keeps a frame pointer here (push ebp / mov ebp,esp), hence /Oy-.
// The owner and its own argument types are unknown; dwords are the measured
// ABI view, handed on as the callee's declared types.

struct Coord3D;
class GeometryInfo
{
public:
	bool getBestContactPoint(Coord3D *result, const Coord3D *from, const char *trace, int a, int b, bool flag) const;
};

class Rva0033A77F
{
public:
	void rva0033A77F(int a, int b, int c, int d, int e);

private:
	char unknown00[0xA0];
	GeometryInfo mA0;
};

void Rva0033A77F::rva0033A77F(int a, int b, int c, int d, int e)
{
	mA0.getBestContactPoint((Coord3D *)a, (const Coord3D *)b, (const char *)c, d, e, false);
}
