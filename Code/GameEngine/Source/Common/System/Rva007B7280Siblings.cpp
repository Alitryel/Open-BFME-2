// cl: /O2 /DNDEBUG /MD /EHsc /arch:SSE
//
// Six WWLib VectorClass<T> global teardowns at 0x007B7280, 0x007B72C0,
// 0x007B7300, 0x007B7340, 0x007B7380 and 0x007B7400 (59 bytes each).
//
// Retail's body is the TU-local atexit destructor MSVC emits for a
// namespace-scope VectorClass object: store the vtable pointer, then Clear()
// inlined -- delete[] Vector through operator delete[] at 0x0002FD80, zero
// Vector, IsAllocated and VectorMax. The object layout is the vendor vector.h
// layout: vptr +0, Vector +4, VectorMax +8, IsValid +0xC, IsAllocated +0xD.
//
// The six objects are pointgr.cpp's: the data ledger gives VA 0x00DF94D0,
// 0x00DF94B0, 0x00DB6488, 0x00DB6498 and 0x00DB64A8 to PointGroupClass's private
// compressed_loc/diffuse/size/orient/frame and 0x00DF708C to the global
// VertexLoc, and the vtables agree with those Ts (0x00BCEFAC for both Vector3
// vectors, one shared vtable for the two unsigned-char vectors). This unit
// reaches the defined objects through a layout view instead of defining
// second datums at their addresses. Each distinct vtable VA below is the
// target's own DIR32 operand, auto-patched from retail. The vtable data itself is not recovered --
// only its address is used -- hence the anchor blobs. The teardown bodies are
// reconstructed as the equivalent free functions (same recipe as the matched
// 40-byte chain cleanups in System/GlobalChainCleanup.cpp).
void __cdecl operator delete[](void *);

struct RvaVectorClass
{
	void *vptr;
	void *vector;
	int vectorMax;
	bool isValid;
	bool isAllocated;
};

class Vector3;
class Vector4;
template <class T> class VectorClass;

void rva007B7280();
void rva007B72C0();
void rva007B7300();
void rva007B7340();
void rva007B7380();

class PointGroupClass
{
	friend void rva007B7280();
	friend void rva007B72C0();
	friend void rva007B7300();
	friend void rva007B7340();
	friend void rva007B7380();
	static VectorClass<Vector3> compressed_loc;		// VA 0x00DF94D0, vtable 0x00BCEFAC
	static VectorClass<Vector4> compressed_diffuse;		// VA 0x00DF94B0, vtable 0x00BD4EB4
	static VectorClass<float> compressed_size;		// VA 0x00DB6488, vtable 0x00BD4ECC
	static VectorClass<unsigned char> compressed_orient;	// VA 0x00DB6498, vtable 0x00BD4E9C
	static VectorClass<unsigned char> compressed_frame;	// VA 0x00DB64A8, vtable 0x00BD4E9C
};
extern VectorClass<Vector3> VertexLoc;			// VA 0x00DF708C, vtable 0x00BCEFAC

// Vtable-address anchors, one per distinct target vtable VA. The slot contents
// are not recovered; the teardown only stores the anchor's address.
void *const RvaBcefacVtable[7] = { 0 };
void *const RvaBd4eb4Vtable[7] = { 0 };
void *const RvaBd4eccVtable[7] = { 0 };
void *const RvaBd4e9cVtable[7] = { 0 };

void rva007B7280()
{
	RvaVectorClass &v = *(RvaVectorClass *)&PointGroupClass::compressed_loc;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBcefacVtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}

void rva007B72C0()
{
	RvaVectorClass &v = *(RvaVectorClass *)&PointGroupClass::compressed_diffuse;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBd4eb4Vtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}

void rva007B7300()
{
	RvaVectorClass &v = *(RvaVectorClass *)&PointGroupClass::compressed_size;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBd4eccVtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}

void rva007B7340()
{
	RvaVectorClass &v = *(RvaVectorClass *)&PointGroupClass::compressed_orient;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBd4e9cVtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}

void rva007B7380()
{
	RvaVectorClass &v = *(RvaVectorClass *)&PointGroupClass::compressed_frame;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBd4e9cVtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}

void rva007B7400()
{
	RvaVectorClass &v = *(RvaVectorClass *)&VertexLoc;
	void *vec = v.vector;
	v.vptr = (void *)&RvaBcefacVtable;
	if (vec != 0 && v.isAllocated) {
		operator delete[](vec);
		v.vector = 0;
	}
	v.isAllocated = false;
	v.vectorMax = 0;
}
