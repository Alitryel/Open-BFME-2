// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ??0Rva00052B3D@@QAE@XZ @0x00052B3D 22B.
// Vector-ctor-iterator init of 2x4-byte elements at +0 via rowed ??_H and a
// user ctor (push 4 push 2 pattern like retail; ctor push is reloc). Neighbours
// are MilesAudioManager TUs; owner has no vtable (array at +0) so honest
// Rva name. Callers 0x0005C892 0x000626A7.
struct Elem4
{
	int m_x;
	Elem4();
};

class Rva00052B3D
{
public:
	Rva00052B3D();
private:
	Elem4 m_arr[2];
};

// ??0Elem4@@QAE@XZ present-unmatched
Elem4::Elem4() : m_x(0)
{
}

Rva00052B3D::Rva00052B3D()
{
}
