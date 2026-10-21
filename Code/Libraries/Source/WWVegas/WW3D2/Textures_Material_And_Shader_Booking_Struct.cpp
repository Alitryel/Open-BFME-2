// cl: /DNDEBUG /MD /EHsc

typedef void (*Rva00945B80CellFunction)(void *);

class TextureClass
{
public:
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}

	void Release_Ref();
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p != 0)
			other.p->Add_Ref();
		if (p != 0)
			p->Release_Ref();
		p = other.p;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const
	{
		return p == other.p;
	}
};

class VertexMaterialClass
{
	unsigned char pad[0x64];
	mutable unsigned long CRC;
	mutable bool CRCDirty;
	unsigned long Compute_CRC() const;

public:
	unsigned long Get_CRC() const
	{
		if (CRCDirty) {
			CRC = Compute_CRC();
			CRCDirty = false;
		}
		return CRC;
	}
};

class ShaderClass
{
public:
	unsigned long ShaderBits;

	bool operator==(const ShaderClass &other) const
	{
		return ShaderBits == other.ShaderBits;
	}
};

extern void __stdcall rva00906340VecCtor(
	void *ptr,
	unsigned element_size,
	int count,
	Rva00945B80CellFunction ctor,
	Rva00945B80CellFunction dtor);
extern void rva00906340CellCtor(void *self);
extern void rva00906340CellDtor(void *self);

class Textures_Material_And_Shader_Booking_Struct
{
public:
	Textures_Material_And_Shader_Booking_Struct();
	bool Add_Textures_Material_And_Shader(
		BfmeHandleCX *texs,
		VertexMaterialClass *mat,
		ShaderClass shd);

private:
	BfmeHandleCX added_textures[2][0x40];
	VertexMaterialClass *added_materials[0x40];
	ShaderClass added_shaders[0x40];
	unsigned added_type_count;
};

inline Textures_Material_And_Shader_Booking_Struct::Textures_Material_And_Shader_Booking_Struct()
{
	rva00906340VecCtor(
		this,
		4,
		0x80,
		rva00906340CellCtor,
		rva00906340CellDtor);

	for (int index = 0; index < 0x40; ++index)
		added_shaders[index].ShaderBits = 0x0010441B;

    added_type_count = 0;

    for (int index = 0; index < 0x40; ++index)
        added_materials[index] = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeTextures_Material_And_Shader_Booking_StructInlineAnchor@@YAXPAVTextures_Material_And_Shader_Booking_Struct@@@Z absent-from-retail
void _bfmeTextures_Material_And_Shader_Booking_StructInlineAnchor(Textures_Material_And_Shader_Booking_Struct *textures_Material_And_Shader_Booking_)
{
    textures_Material_And_Shader_Booking_->Textures_Material_And_Shader_Booking_Struct::Textures_Material_And_Shader_Booking_Struct();
}
#pragma inline_depth()

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?rva00906340VecCtor@@YGXPAXIHP6AX0@Z1@Z=??_L@YGXPAXIHP6EX0@Z1@Z")
