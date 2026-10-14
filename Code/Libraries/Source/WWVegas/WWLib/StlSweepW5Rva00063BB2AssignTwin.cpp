// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ICF twin of ??4GeometryShape@@QAEAAU0@ABU0@@Z (0x00063627,
// GeometryShapeAssign.cpp): the element of the STLport sweep at 0x00063BB2
// is the same 0x24-byte shape record, and its assignment is that body.
// Same flags and layout as the owner.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva00063BB2Element
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	Coord3D m_offset;
	AsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_byte21;

	Rva00063BB2Element &operator=(const Rva00063BB2Element &other);
};

Rva00063BB2Element &Rva00063BB2Element::operator=(const Rva00063BB2Element &other)
{
	m_type = other.m_type;
	m_height = other.m_height;
	m_majorRadius = other.m_majorRadius;
	m_minorRadius = other.m_minorRadius;
	m_offset = other.m_offset;
	m_name = other.m_name;
	m_enabled = other.m_enabled;
	m_byte21 = other.m_byte21;
	return *this;
}
