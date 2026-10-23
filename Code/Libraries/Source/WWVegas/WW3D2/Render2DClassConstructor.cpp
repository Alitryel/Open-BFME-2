// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// BFME's Render2D layout predates the later vendored class. Keep the retail
// layout and its 0x74-byte batch element local to this translation unit.

class ShaderState
{
public:
	ShaderState() : Value(2) {}
	int Value;
};

#include "../../../../../reference/shims/wwmath/Vector2.h"

class Render2DRawArray
{
public:
	Render2DRawArray() : Data(0), Size(0), Count(0), GrowthStep(16) {}
	~Render2DRawArray();

	void *Data;
	int Size;
	int Count;
	int GrowthStep;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	StringClass() : Buffer(0) {}
	char *Buffer;
};

class Matrix3D
{
public:
	float Row[3][4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/proxy.h
class ProxyClass
{
public:
	ProxyClass();
	~ProxyClass();

	StringClass Name;
	Matrix3D Transform;
	unsigned char UnreconstructedTail[0x74 - 0x34];
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
  DynamicVectorClass(int size = 0, T const *array = 0);
  virtual ~DynamicVectorClass();
  virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *);
	virtual int ID(T const &);

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(int size, T const *array) :
	VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

class TextureRef
{
public:
	__declspec(dllimport) __forceinline TextureRef() : Pointer(0) {}
	~TextureRef();

	void *Pointer;
};

extern int g_bfmeFirstEB;
extern int g_bfmeSecondEB;
extern int g_bfmeThirdEB;
extern int g_bfmeFourthEB;
extern int g_bfmeFifthEB;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	Render2DClass();
	void Reset();

private:
	ShaderState Shader;
	Vector2 CoordinateScale;
	Vector2 CoordinateOffset;
	Render2DRawArray ArrayA;
	Render2DRawArray ArrayB;
	DynamicVectorClass<ProxyClass> Batches;
	TextureRef Texture;
	int CurrentBatch;
	bool IsDirty;
	unsigned char tail[3];
};

// The Render2DClass constructor itself is rowed (retail 0x0011C0F0) in
// Rva0011C0F0Finish.cpp; this unit only needs Render2DRawArray's inline
// constructor (retail 0x00118D60) emitted, so construct one in place.
inline void *operator new(unsigned int, void *where) { return where; }
// ?bfmeAnchorRender2DRawArray absent-from-retail
void bfmeAnchorRender2DRawArray(void *where)
{
	new (where) Render2DRawArray;
}
