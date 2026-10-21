// cl: /O1 /GX /MD /DNDEBUG /arch:SSE
//
// ??1StructureCollapseUpdateModuleData@@UAE@XZ, retail 0x00256B94, 86 bytes.
// Virtual dtor over vtable RVA 0x7F3E30 (VA 0xBF3E30, slot 0 deleting dtor
// at 0x00256B78). Donor BFME1 StructureCollapseUpdateModuleDataCtorThunk.cpp
// (dual 5-element 0x0C arrays). Same layout as the rowed ctor TU
// (StructureCollapseUpdateModuleDataCtor.cpp): base at +0 (inline BBB554 restore,
// size 8 with pad), DieMuxData at +0x08 (trivial dtor), scalars to +0x50,
// OCL/FX 5x0xC arrays at +0x54/+0x90 via ehvec dtor 0x629110 (element
// 0x47fab3 BasicStringCharDtor_dup, count 5 size 0xC, states 1/0), counts
// at +0xCC/+0xE0. Empty body: the two reverse-order ??_M destroys plus the
// base restore are compiler-generated. No base call in retail (inline).
// Size 0xFC matches the rowed factory 0x00256BEA.

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

class DieMuxData
{
public:
	DieMuxData();

private:
	unsigned char m_bytes[0x30];
};

class CollapseOCLVec
{
public:
	CollapseOCLVec();
	~CollapseOCLVec();

private:
	unsigned char m_data[0x0C];
};

class CollapseFXVec
{
public:
	CollapseFXVec();
	~CollapseFXVec();

private:
	unsigned char m_data[0x0C];
};

class StructureCollapseBase
{
public:
	virtual ~StructureCollapseBase()
	{
		*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
	}

private:
	unsigned char m_pad04[4];
};

enum
{
	COLLAPSE_PHASE_COUNT = 5,
};

class __declspec(novtable) StructureCollapseUpdateModuleData : public StructureCollapseBase
{
public:
	virtual ~StructureCollapseUpdateModuleData();

private:
	DieMuxData m_dieMuxData; // +0x08
	int m_minCollapseDelay; // +0x38
	int m_maxCollapseDelay; // +0x3C
	int m_minBurstDelay; // +0x40
	int m_maxBurstDelay; // +0x44, INI-only, never stored here
	int m_bigBurstFrequency; // +0x48
	float m_collapseDamping; // +0x4C
	float m_maxShudder; // +0x50
	CollapseOCLVec m_ocls[COLLAPSE_PHASE_COUNT]; // +0x54
	CollapseFXVec m_fxs[COLLAPSE_PHASE_COUNT]; // +0x90
	unsigned int m_oclCount[COLLAPSE_PHASE_COUNT]; // +0xCC
	unsigned int m_fxCount[COLLAPSE_PHASE_COUNT]; // +0xE0
	bool m_destroyObjectWhenDone; // +0xF4
	char m_padF5[3];
	float m_collapseHeight; // +0xF8
};

inline StructureCollapseUpdateModuleData::~StructureCollapseUpdateModuleData()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStructureCollapseUpdateModuleDataInlineAnchorStructureCollapseUpdateModuleDataDtor@@YAXPAVStructureCollapseUpdateModuleData@@@Z absent-from-retail
void _bfmeStructureCollapseUpdateModuleDataInlineAnchorStructureCollapseUpdateModuleDataDtor(StructureCollapseUpdateModuleData *structureCollapseUpdateModuleData)
{
    structureCollapseUpdateModuleData->StructureCollapseUpdateModuleData::~StructureCollapseUpdateModuleData();
}
#pragma inline_depth()
