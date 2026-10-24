// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: VertexMaterialClass::Clone at 0x0092EF30 (94 B): allocate a
// 0x6c-byte VertexMaterialClass with the global operator new, default
// construct it (EH state around the raw allocation), copy-assign from this,
// return it. The ported vertmaterial.h spells the allocation through NEW_REF,
// which adds a registration call retail does not have.
class VertexMaterialClass
{
public:
	VertexMaterialClass();
	VertexMaterialClass &operator=(const VertexMaterialClass &);
	VertexMaterialClass *Clone();
private:
	char m_body[0x6c];
};

inline VertexMaterialClass *VertexMaterialClass::Clone()
{
	VertexMaterialClass *mat = new VertexMaterialClass;
	*mat = *this;
	return mat;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeVertexMaterialClassInlineAnchor@@YAXPAVVertexMaterialClass@@@Z absent-from-retail
void _bfmeVertexMaterialClassInlineAnchor(VertexMaterialClass *vertexMaterial)
{
    vertexMaterial->Clone();
}
#pragma inline_depth()
