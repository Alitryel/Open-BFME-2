// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// GeometryRecord value assignment at retail 0x0004E512 (36 bytes).
// The record is three scalar fields followed by an AsciiString name at +0x0C;
// the vector<GeometryRecord> copy path calls this operator through the
// rowed __copy body at 0x000635F8. The name assignment reaches the folded
// AsciiString copy-assignment pin at 0x000366F0.

extern "C" void *__cdecl memcpy( void *dst, const void *src, unsigned int count );
#pragma intrinsic( memcpy )

#include "ascii_string.h"

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;

	GeometryRecord &operator=( const GeometryRecord &other );
};

inline GeometryRecord &GeometryRecord::operator=( const GeometryRecord &other )
{
	memcpy( this, &other, sizeof( int ) * 3 );
	m_name = other.m_name;
	return *this;
}

#pragma inline_depth(0)
// ?bfmeEmitGeometryRecordAssign@@YAXPAUGeometryRecord@@ABU1@@Z present-unmatched
void bfmeEmitGeometryRecordAssign(GeometryRecord *geometryRecord, const GeometryRecord &other)
{
	*geometryRecord = other;
}
#pragma inline_depth()
