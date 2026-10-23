// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// ?LoadPostProcess@Drawable@@UAEXXZ 0x002717BC 47B
// Slot 1 of Drawable's Snapshot sub-vtable 0x00BFB0A4 (the canonical
// LoadPostProcess slot); Zero Hour Drawable::loadPostProcess likewise restores
// the transform from the bound object.
// Retail: if the Thing* at +0x9c is set, Thing::setTransformMatrix on the
// base at this-0x60 gets that Thing's matrix (+8). Then the module pointer
// at +0x3f0 is tail-called through vslot +4. WB debug uses +0x10 / this-0x68;
// retail displacements are +8 and -0x60.
class Matrix3D { public: float m[12]; };
class Thing {
public:
	virtual void slot0() = 0;
	int m_pad4;
	Matrix3D m_transform;
	void setTransformMatrix(const Matrix3D *mx);
};
class Rva002717BCModule {
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
};
class Drawable {
public:
	virtual void LoadPostProcess();
	char m_pad[0x9c - 4];
	Thing *m_other;
	char m_pad2[0x3f0 - 0x9c - 4];
	Rva002717BCModule *m_module;
};
void Drawable::LoadPostProcess()
{
	Thing *base = (Thing *)((char *)this - 0x60);
	if (m_other)
		base->setTransformMatrix(&m_other->m_transform);
	if (m_module)
		m_module->slot4();
}
