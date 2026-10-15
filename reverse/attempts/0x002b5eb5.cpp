// ?rva002B5EB5@Rva002B5EB5@@QAE_NXZ
// partial score=0.845 date=2026-10-15
// Bank for 0x002B5EB5: apply to Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp (home TU, its // cl: line).
// 1) class Rva003F81FDProxy gains: unsigned char rva003F85C6();
// 2) LivingWorldLogic gains, after rva002B5CBB: __forceinline Bool IsLocalPlayerAllowedToEndPhase();
// 3) append the code below at the end of the unit.
// LivingWorldLogic::IsLocalPlayerAllowedToEndPhase, retail 0x002B5EB5 (213 B;
// WorldBuilder name and file). Callers (0x002B5F8A, 0x0057718D, the resolve
// battles behavior) reach it as ?rva002B5EB5@Rva002B5EB5@@QAE_NXZ, so the row
// keeps that spelling and the body is the WB-named member. With the rowed
// campaign gate 0x002B254F set, the campaign manager's current entry must
// accept (0x003F85C6); the pending +0x154 list must be empty and the rowed
// 0x002B3621 probe clear; then the turn phase decides.
class Rva002B32CE {public:bool rva002B32CE();};
__forceinline Bool LivingWorldLogic::IsLocalPlayerAllowedToEndPhase()
{
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0 &&
		!((Rva003F81FDProxy *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->rva003F85C6())
		return false;
	if (!m_pending154.empty() || ((Rva002B4C09 *)this)->rva002B3621())
		return false;
	Int allowed = false;
	switch (m_turnPhase)
	{
	case 0:
		allowed = m_fieldCC.empty();
		break;
	case 3:
	case 6:
		return true;
	case 1:
	case 5:
		allowed = !((Rva002B4B3D *)this)->rva002B4B3D();
		break;
	case 4:
		allowed = m_field10C.empty() || ((Rva002B32CE *)this)->rva002B32CE();
		break;
	case 2:
		if (((Rva0020E72A *)m_field0B0)->rva0020E72A(m_localPlayer))
			return false;
		return !rva002B5CBB((Rva002B4C35Player *)m_localPlayer);
	default:
		break;	// WB: DEBUG("Unhandled phase in IsLocalPlayerAllowedToEndPhase")
	}
	return allowed;
}

class Rva002B5EB5 {public:bool rva002B5EB5();};
bool Rva002B5EB5::rva002B5EB5()
{
	return ((LivingWorldLogic *)this)->IsLocalPlayerAllowedToEndPhase();
}
