// cl: /DNDEBUG /MD /EHsc
//
// HTreeClass::Is_Bone_Captured (retail 0x00162030, 48 bytes).
//
// BFME 2 rewrote Zero Hour's per-pivot IsCaptured flag as a sorted vector of
// 36-byte captured-bone records (Begin at +0x1C, End at +0x20), walked by
// index. Same record model as the landed Control_Bone unit in
// htree_control.cpp; that unit builds /O2 without a loop-top pad, while this
// body carries a 2-byte hotpatch-style nop before the loop, so this unit
// builds /G7 like the landed bone-lookup unit.
// The copy helper already names this 36-byte record BfmePod36. Only Index
// is read here; the rest stays opaque. htree.h stores the vector words as
// OwnedSequence1C, with begin/end at +0x1C/+0x20.
struct BfmePod36 { int Index; unsigned char m_bfmePad[32]; };
class HTreeClass {
	char m_bfmeTreeFields[28];
	unsigned int OwnedSequence1C[3];
public:
	bool Is_Bone_Captured(int boneindex) const;
};

// ?Is_Bone_Captured@HTreeClass@@QBE_NH@Z
bool HTreeClass::Is_Bone_Captured(int boneindex) const
{
	BfmePod36 *bone = reinterpret_cast<BfmePod36 *>(OwnedSequence1C[0]);
	while (bone != reinterpret_cast<BfmePod36 *>(OwnedSequence1C[1]) && bone->Index < boneindex) ++bone;
	return bone != reinterpret_cast<BfmePod36 *>(OwnedSequence1C[1]) && bone->Index == boneindex;
}
