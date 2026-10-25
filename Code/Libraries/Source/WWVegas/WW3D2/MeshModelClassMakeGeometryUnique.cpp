// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// MeshModelClass::Make_Geometry_Unique at 0x00172070.
//
// Gives the model private copies of its shared geometry buffers: two vertex
// arrays always, the second pair only when both exist, and the Vector4 array,
// each cloned with NEW_REF and swapped in with REF_PTR_SET / REF_PTR_RELEASE.
// This is the body Open-BFME-1 recovered; BFME 2 packs the members differently,
// with the second pair at +0x38/+0x3C rather than +0x40/+0x44 and the Vector4
// buffer at +0x48 rather than +0x50, so the reduced model below is laid out by
// BFME 2's own offsets.  /G7 is the unit's tell.

#include <new>
#include <stddef.h>

class Vector3;
class Vector4;

// The existing shared-buffer body uses only count-at-4 and Delete_This slot 0.
// Its element classes are template identities here; no element layout is used.
class RefCountClass
{
public:
    virtual void Delete_This();
    virtual ~RefCountClass();
    void Add_Ref() { NumRefs++; }
    void Release_Ref() { if (--NumRefs == 0) Delete_This(); }

private:
    int NumRefs;
};

template <class T> class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);
protected:
	T *RawBuffer;
	T *Array;
	int Count;
	int Alignment;
};

// Body-specific buffer view: offsets are the existing BFME 2 target facts above.
struct Rva00172070Buffers
{
    unsigned char m_padding00[0x30];
    ShareBufferClass<Vector3> *m_buffer30;
    ShareBufferClass<Vector3> *m_buffer34;
    ShareBufferClass<Vector3> *m_buffer38;
    ShareBufferClass<Vector3> *m_buffer3C;
    unsigned char m_padding40[8];
    ShareBufferClass<Vector4> *m_buffer48;
};

class MeshModelClass
{
public:
    void Make_Geometry_Unique();
};

void MeshModelClass::Make_Geometry_Unique()
{
	Rva00172070Buffers *buffers = reinterpret_cast<Rva00172070Buffers *>(this);
	ShareBufferClass<Vector3> *buffer30 =
		new ShareBufferClass<Vector3>(*buffers->m_buffer30);
	{ if (buffer30) buffer30->Add_Ref();
		if (buffers->m_buffer30) buffers->m_buffer30->Release_Ref();
		buffers->m_buffer30 = buffer30; }
	{ if (buffer30) { buffer30->Release_Ref(); buffer30 = NULL; } }

	ShareBufferClass<Vector3> *buffer38 =
		new ShareBufferClass<Vector3>(*buffers->m_buffer38);
	{ if (buffer38) buffer38->Add_Ref();
		if (buffers->m_buffer38) buffers->m_buffer38->Release_Ref();
		buffers->m_buffer38 = buffer38; }
	{ if (buffer38) { buffer38->Release_Ref(); buffer38 = NULL; } }

	if (buffers->m_buffer34 != 0 && buffers->m_buffer3C != 0) {
		ShareBufferClass<Vector3> *buffer34 =
			new ShareBufferClass<Vector3>(*buffers->m_buffer34);
		{ if (buffer34) buffer34->Add_Ref();
		if (buffers->m_buffer34) buffers->m_buffer34->Release_Ref();
		buffers->m_buffer34 = buffer34; }
		{ if (buffer34) { buffer34->Release_Ref(); buffer34 = NULL; } }

		ShareBufferClass<Vector3> *buffer3C =
			new ShareBufferClass<Vector3>(*buffers->m_buffer3C);
		{ if (buffer3C) buffer3C->Add_Ref();
		if (buffers->m_buffer3C) buffers->m_buffer3C->Release_Ref();
		buffers->m_buffer3C = buffer3C; }
		{ if (buffer3C) { buffer3C->Release_Ref(); buffer3C = NULL; } }
	}

	ShareBufferClass<Vector4> *buffer48 =
		new ShareBufferClass<Vector4>(*buffers->m_buffer48);
	{ if (buffer48) buffer48->Add_Ref();
		if (buffers->m_buffer48) buffers->m_buffer48->Release_Ref();
		buffers->m_buffer48 = buffer48; }
	{ if (buffer48) { buffer48->Release_Ref(); buffer48 = NULL; } }
}
