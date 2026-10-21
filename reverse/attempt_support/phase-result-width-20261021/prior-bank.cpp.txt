// ?rva002B5EB5@Rva002B5EB5@@QAE_NXZ
// partial score=0.995 date=2026-10-18
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
typedef int Bool;
typedef int Int;
class Rva002B254F {public:int rva002B254F();};
class Rva003B8BAA {public: void* rva003B8BAA(); };
class Rva003F81FDProxy {public: unsigned char rva003F85C6(); };
class Rva002B4C09 {public: bool rva002B3621(); };
class Rva002B4B3D {public: bool rva002B4B3D(); };
class Rva0020E72A {public: bool rva0020E72A(void*); };
struct Rva002B4C35Player {};
extern void* TheCampaignManager;
struct SimpleList2 { void* _head; void* _tail; void* _end; bool empty() const { return _head==_tail; } };
class LivingWorldLogic {
public:
  Bool IsLocalPlayerAllowedToEndPhase();
  bool rva002B5CBB(const Rva002B4C35Player*);
  unsigned char pad0[0x98];
  void* m_localPlayer;
  unsigned char padA[0xB0-0x9C];
  void* m_field0B0;
  unsigned char pad1[0xCC-0xB4];
  SimpleList2 m_fieldCC;
  unsigned char pad2[0xF4-0xD8];
  int m_turnPhase;
  unsigned char pad2b[0x10C-0xF8];
  SimpleList2 m_field10C;
  unsigned char pad3[0x154-0x118];
  SimpleList2 m_pending154;
};
class Rva002B32CE {public:bool rva002B32CE();};
__forceinline Bool LivingWorldLogic::IsLocalPlayerAllowedToEndPhase()
{
	if ((1 ? ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0 &&
		!((Rva003F81FDProxy *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->rva003F85C6()) : 0))
		return (1 ? false : false);
	if ((1 ? (!m_pending154.empty() || ((Rva002B4C09 *)this)->rva002B3621()) : 0))
		return (1 ? false : false);
	Int allowed = 0;
	switch (m_turnPhase)
	{
	case 0:
		return (m_fieldCC.empty() ? 1 : 0);
	case 3:
	case 6:
		return 1;
	case 1:
	case 5:
		allowed = (((Rva002B4B3D *)this)->rva002B4B3D() ? 0 : 1);
		break;
	case 4:
		allowed = (m_field10C.empty() || ((Rva002B32CE *)this)->rva002B32CE() ? 1 : 0);
		break;
	case 2:
		if (((Rva0020E72A *)m_field0B0)->rva0020E72A(m_localPlayer))
			return false;
		{
			bool tmp = !rva002B5CBB((Rva002B4C35Player *)m_localPlayer);
			return tmp;
		}
	default:
		break;	// WB: DEBUG("Unhandled phase in IsLocalPlayerAllowedToEndPhase")
	}
	return allowed;
}

class Rva002B5EB5 {public:bool rva002B5EB5();};
bool Rva002B5EB5::rva002B5EB5()
{
	LivingWorldLogic* p = (LivingWorldLogic*)this;
	Int allowed;
	if ((unsigned char)((Rva002B254F *)p)->rva002B254F() != 0 &&
		!((Rva003F81FDProxy *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->rva003F85C6())
		return false;
	if (!p->m_pending154.empty() || ((Rva002B4C09 *)p)->rva002B3621())
		return false;
	switch (p->m_turnPhase)
	{
	case 0:
		return (p->m_fieldCC.empty() ? 1 : 0);
	case 3:
	case 6:
		return 1;
	case 1:
	case 5:
		return ((Rva002B4B3D *)p)->rva002B4B3D() ? 0 : 1;
	case 4:
		allowed = (p->m_field10C.empty() || ((Rva002B32CE *)p)->rva002B32CE()) ? 1 : 0;
		break;
	case 2:
		if (((Rva0020E72A *)p->m_field0B0)->rva0020E72A(p->m_localPlayer))
			return false;
		{
			bool tmp = !p->rva002B5CBB((Rva002B4C35Player *)p->m_localPlayer);
			return tmp;
		}
	default:
		allowed = 0;
		break;
	}
	return *(bool *)&allowed;
}
