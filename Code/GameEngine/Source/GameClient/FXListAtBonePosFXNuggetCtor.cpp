// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0FXListAtBonePosFXNugget@@QAE@XZ 78B @0x1E0A57: no-arg ctor called by
// FXListAtBonePosFXNugget::parse (0x001E1814) for the FXListAtBonePos FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD2F8 (FX@0x148, BoneName@0x14C) and the BFME1 donor
// (m_fx NULL, m_boneName clear, m_nuggetType 10; BFME2 drops orientToBone).
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
protected:
	int m_nuggetType; // +4, nugget type id (BFME1 FXNugget::m_nuggetType)
	unsigned char m_pad[0x148 - 8];
};

#include "ascii_string.h"

class FXListAtBonePosFXNugget : public Rva001DFEAABase
{
public:
	FXListAtBonePosFXNugget();
	virtual ~FXListAtBonePosFXNugget();
private:
	const char *m_fxName; // +0x148
	AsciiString m_boneName; // +0x14C
};

// ??0FXListAtBonePosFXNugget@@QAE@XZ
inline FXListAtBonePosFXNugget::FXListAtBonePosFXNugget()
{
	m_fxName = 0;
	m_boneName.clear();
	m_nuggetType = 10;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFXListAtBonePosFXNuggetInlineAnchor@@YAXPAVFXListAtBonePosFXNugget@@@Z absent-from-retail
void _bfmeFXListAtBonePosFXNuggetInlineAnchor(FXListAtBonePosFXNugget *fXListAtBonePosFXNugget)
{
    fXListAtBonePosFXNugget->FXListAtBonePosFXNugget::FXListAtBonePosFXNugget();
}
#pragma inline_depth()
