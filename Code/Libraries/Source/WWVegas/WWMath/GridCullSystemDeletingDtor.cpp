// cl: /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.

// ??_GGridCullSystemClass, the scalar deleting destructor in vtable 0xCEFCB0
// slot 0 (retail 0x0071B170).  The class is declared locally only so its
// deleting destructor is emitted; the complete-destructor call resolves
// through that destructor's own row at 0x0071AD00.
class Vector3; class AABoxClass; class OBBoxClass; class FrustumClass; class CullableClass;
class ChunkLoadClass; class ChunkSaveClass;
class GridCullSystemClass
{
public:
	explicit GridCullSystemClass(int) {}
	virtual ~GridCullSystemClass();
	virtual void Collect_Objects(const Vector3 &point);
	virtual void Collect_Objects(const AABoxClass &box);
	virtual void Collect_Objects(const OBBoxClass &box);
	virtual void Collect_Objects(const FrustumClass &frustum);
	virtual void Update_Culling(CullableClass *obj);
	virtual void Re_Partition(const Vector3 &min, const Vector3 &max, float objdim);
	virtual void Load(ChunkLoadClass &cload);
	virtual void Save(ChunkSaveClass &csave);
	virtual int Get_Object_Count(void) const;
private:
	int m_famgen;
};

GridCullSystemClass *famgenNew_GridCullSystemClass() { return new GridCullSystemClass(0); }

void famgenDelete(GridCullSystemClass *p)
{
	delete p;
}
