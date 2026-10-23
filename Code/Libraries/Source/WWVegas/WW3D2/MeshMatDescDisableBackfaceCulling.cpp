// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// MeshMatDescClass::Disable_Backface_Culling, retail 0x00188670 (67 bytes).
// Dedicated TU: the shared shader.h still carries Zero Hour's cull-mode bit
// (bit 19, byte mask 0xF7), which the other landed rows rely on, while retail
// clears bit 20 here (byte mask 0xEF at the flag byte). Retail-measured
// layout: PassCount at +0x0, four 4-byte shader flag words at +0x98 (cull is
// bit 20, the +2 byte), and the per-pass shader ShareBuffers at +0xF8
// (pointer array, Array at +0xC, Count at +0x10, matching the WWLib
// ShareBufferClass template this TU mirrors). The whole class pads to the
// proven 0x118 MeshMatDesc size. Loop spelling is the BFME1 meshmatdesc.h
// inline verbatim; only the view is BFME2.

struct ShaderFlags
{
	unsigned long m_bits;
	void Clear_Cull_Bit() { m_bits &= ~(1u << 20); }
};

template <class T>
struct ShaderBuffer
{
	char m_pool[0xC];
	T *Array;
	int Count;
	int Get_Count() { return Count; }
	T &Get_Element(int index) { return Array[index]; }
};

class MeshMatDescClass
{
public:
	static void bfmeEmitMeshMatDescDisableBackfaceCulling(MeshMatDescClass *p);
protected:
	void Disable_Backface_Culling();

private:
	int PassCount;
	char m_pad0[0x98 - 4];
	ShaderFlags Shader[4];
	char m_pad1[0xF8 - 0xA8];
	ShaderBuffer<ShaderFlags> *ShaderArray[4];
	char m_pad2[0x118 - 0x108];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

inline void MeshMatDescClass::Disable_Backface_Culling()
{
	for (int pass = 0; pass < PassCount; pass++) {
		Shader[pass].Clear_Cull_Bit();
		if (ShaderArray[pass]) {
			for (int tri = 0; tri < ShaderArray[pass]->Get_Count(); tri++) {
				ShaderArray[pass]->Get_Element(tri).Clear_Cull_Bit();
			}
		}
	}
}

// This file owns the row, but other files emit the same function as an inline
// copy they cannot stop emitting, so a strong definition here was a duplicate
// symbol in the linked build. The anchor below emits the select-any copy for
// the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitMeshMatDescDisableBackfaceCulling@MeshMatDescClass@@SAXPAV1@@Z present-unmatched
void MeshMatDescClass::bfmeEmitMeshMatDescDisableBackfaceCulling(MeshMatDescClass *meshMatDesc)
{
	meshMatDesc->Disable_Backface_Culling();
}
#pragma inline_depth()
