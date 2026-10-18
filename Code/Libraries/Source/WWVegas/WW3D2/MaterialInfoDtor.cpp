// cl: /DNDEBUG /MD /EHsc
// BFME MaterialInfoClass destructor at 0x00930F60 / 175 bytes.
// Layout/vtable identities follow MaterialInfoClassCtor.cpp. Free releases
// materials first, then owned texture cells and vertex-pointer storage unwind.
// Nonthrowing array deallocation removes the spurious EH state before the
// final POD vector cleanup; TextureClass::Release_Ref can still unwind.

class VertexMaterialClass;
void __cdecl operator delete[](void *) throw();

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
 	RefCountPtr() : Referent(0) {}
 	~RefCountPtr();

private:
 	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

// The compiler-generated array deleting destructor takes the flags of its
// first use. Instantiate retail's /O1 helper in an unemitted static function,
// following TextureHandleAssignment.cpp, before the native vector cleanup.
#pragma optimize("gsy", on)
static void materialTextureDeleteAnchor(TextureVectorCell *cells) { delete[] cells; }
#pragma optimize("", on)

class TextureVectorBaseCtorShim
{
public:
 	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
 	virtual ~TextureVectorBaseCtorShim() {
  if(Vector && IsAllocated) { delete[] Vector; Vector=0; }
  IsAllocated=false;
  VectorMax=0;
 }
 	TextureVectorBaseCtorShim &operator=(const TextureVectorBaseCtorShim &);

private:
 	TextureVectorCell *Vector;
 	int VectorMax;
 	bool IsValid;
 	bool IsAllocated;
 	bool VectorClassPad[2];
};

// VectorClass<VertexMaterialClass *>'s vtable (retail 0x00BD4628, installed by the
// matched MaterialCollectorClass dtor too). Bind the provider's real name directly,
// following BFME1's ac2f5d9fd324 repair; BFME2's retail reference proves the slot.
extern "C" const unsigned char __identifier("??_7?$VectorClass@PAVVertexMaterialClass@@@@6B@")[];

class MaterialVector {
public:
 ~MaterialVector() {
  Vtable=(unsigned)__identifier("??_7?$VectorClass@PAVVertexMaterialClass@@@@6B@");
  if(Vector && IsAllocated) { delete[] Vector; Vector=0; }
  IsAllocated=false;
  VectorMax=0;
 }
private:
 unsigned Vtable; VertexMaterialClass **Vector; int VectorMax;
 bool IsValid, IsAllocated; char pad[2]; int ActiveCount, GrowthStep;
};

class TextureVector : public TextureVectorBaseCtorShim
{
public:
private:
	int ActiveCount, GrowthStep;
};

#pragma optimize("gsy", on)
class RefCountClass
{
public:
	RefCountClass() : Count(1) {}
	virtual void Delete_This() { delete this; }

protected:
	virtual ~RefCountClass() {}

private:
	int Count;
};

#pragma optimize("", on)

class MaterialInfoClass : public RefCountClass
{
public:
	MaterialInfoClass(const MaterialInfoClass &);
private:
 void Free();
public:
	virtual ~MaterialInfoClass();

private:
	MaterialVector VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::~MaterialInfoClass()
{
 Free();
}

void Force_MaterialInfoClass_Deleting_Destructor(MaterialInfoClass *material_info)
{
	delete material_info;
}
