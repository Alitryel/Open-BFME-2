// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
//
// ?bfmeCompact@Gen_0018BC70@@QAEPAVBfmeVecAK@@_N@Z @0x004D6D4F 70B
// LINK 1 file 47B. Reference transfer from BFME1 Bfme5CompactAlive.cpp:61
// Gen_0018BC70::bfmeCompact with rowed callees liveObjects/rva004D6CAC and
// Object::isSelectable plus rowed vector<void*>::erase. Evidence pin plus
// LINK BONUS name plus donor loop shape plus callers in PlayerHotkeySquads.
#include "../GameLogic/AI/SquadCompactView.h"
class Object
{
public:
	bool isSelectable() const;
};
class Squad
{
public:
	const _STL::vector<Object *> &getAllObjectsAndRemoveDead();
	const _STL::vector<Object *> &rva004D6CAC();
};
BfmeVecAK *Gen_0018BC70::bfmeCompact(bool restart)
{
	if (restart)
		((Squad *)this)->getAllObjectsAndRemoveDead();
	else
		((Squad *)this)->rva004D6CAC();
	void ***vec = (void ***)&m_vector;
	void **it = (void **)m_vector.m_start;
	while (it != (void **)m_vector.m_finish)
	{
		Object *obj = (Object *)*it;
		if (!obj->isSelectable())
			it = (void **)((_STL::vector<void *> *)vec)->erase(it);
		else
			++it;
	}
	return &m_vector;
}
