// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2htree /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
//
// ?Scale@HTreeClass@@QAEXM@Z,
// retail 0x00160C00 (110 bytes).
//
// Pivot-translation scaler: no-op for a 1.0 factor, otherwise multiplies
// every pivot's translation triple by the factor and folds it into
// ScaleFactor. Ported from Open-BFME-1 (Code/Libraries/Source/WWVegas/
// WW3D2/htree.cpp), whose body is the same shape including the
// `factor == 1.0f` early-out; the BFME2 adaptation is the data path:
// BFME1 round-trips each translation through Get_Translation /
// Set_Translation calls while retail scales the three floats at pivot
// +0x24 in place with SSE (the second half of the +0x14 28-byte block,
// matching the landed 0x58-byte PivotClass model: Name[16], Parent at
// +0x10, rotation-plus-translation blocks at +0x14/+0x30, Index at +0x4C).
// The loop homes the pivot address through a float pointer: spelling the
// three stores through trans[0..2] folds the +0x24 into one leading lea
// with [eax+0/4/8] stores, while three member stores (or a reference
// alone) keep the +0x24 on every memory operand.
// HTree layout repeats the BoneLookup unit: Name[16], NumPivots at +0x10,
// Pivot at +0x14, ScaleFactor at +0x18.

#include <windows.h>
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "../../../../../reference/shims/bfme2htree/htree.h"

// This compact target view is independent of the older pivot.h matrix layout.
// Scale consumes only its +24 translation and the target-proven 58-byte stride.
struct HTreeScalePivotView
{
public:
	char Name[16];
	HTreeScalePivotView *Parent; // +0x10
	float m_rot[4]; // +0x14
	float m_tx; // +0x24
	float m_ty; // +0x28
	float m_tz; // +0x2C
	unsigned char m_bfme30[0x58 - 0x30];
};

// ?Scale@HTreeClass@@QAEXM@Z
void HTreeClass::Scale(float factor)
{
	if (factor == 1.0f) {
		return;
	}

	for (int i = 0; i < NumPivots; i++) {
		HTreeScalePivotView &piv = reinterpret_cast<HTreeScalePivotView *>(Pivot)[i];
		float *trans = &piv.m_tx;
		trans[0] *= factor;
		trans[1] *= factor;
		trans[2] *= factor;
	}

	ScaleFactor *= factor;
}
