// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W3DShrubBuffer method at retail 0x000E7140 (371 bytes, ret 0x14): moves the shrub record of a drawable key to a new
// position and transform and rebuilds its bounding sphere from the type. Open-BFME-1 twin:
// W3DShrubBufferRva00733000.cpp (0x00733000). BFME2 layout read from retail: 2000 records of 0xA0 at +0x1958
// (count +0x4FB58, changed byte +0x4FB5C), 64 types of 0x5C at +0x4FB70. Opaque identity.
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;

struct Rva000E7140Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    void *key;
    unsigned char reserved5c[0x44];
};

struct Rva000E7140Type
{
    unsigned char reserved00[0x10];
    SphereClass bounds;
    unsigned char reserved20[0x3c];
};

// The record and type arrays are spelled as W3DShrubBuffer.cpp's own view spells them (opaque element storage);
// this body reads them through its local element views above.
class Rva000E9C1DRecord
{
public:
	Rva000E9C1DRecord();
private:
	unsigned char m_storage[0xA0];
};

class Rva000E9C1DType
{
public:
	Rva000E9C1DType();
	~Rva000E9C1DType();
private:
	unsigned char m_storage[0x5C];
};

class W3DShrubBuffer
{
public:
    char rva000E7140(void *key, Vector3 position, const Matrix3D *transform);

private:
	Rva000E7140Record &record7140(Int i) { return reinterpret_cast<Rva000E7140Record *>(m_records)[i]; }
	Rva000E7140Type *types7140() { return reinterpret_cast<Rva000E7140Type *>(m_types); }
	unsigned char m_pad000[0x1958];
	Rva000E9C1DRecord m_records[2000];
	Int m_count;
	unsigned char m_4fb5c;
	unsigned char m_pad4fb5d[0x4fb70 - 0x4fb5d];
	Rva000E9C1DType m_types[64];
};

char W3DShrubBuffer::rva000E7140(void *key, Vector3 position,
    const Matrix3D *transform)
{
    for (Int index = 0; index < m_count; ++index)
    {
        if (record7140(index).key == key)
        {
            record7140(index).position = position;
            record7140(index).transform = *transform;

            Rva000E7140Type *type = types7140() + record7140(index).type;
            record7140(index).bounds = type->bounds;
            Real scale = record7140(index).scale;
            record7140(index).bounds.Center *= scale;
            record7140(index).bounds.Radius *= record7140(index).scale;
            record7140(index).bounds.Center += record7140(index).position;

            m_4fb5c = 1;
            return 1;
        }
    }
    return 0;
}
