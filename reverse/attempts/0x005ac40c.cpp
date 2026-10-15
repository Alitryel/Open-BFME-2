// ?moveDozerAway@AIStructureCreepTactic@@QAEXXZ
// partial score=0.88 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// d3 seat2 bank: append to Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIStructureCreepTactic.cpp
// after adding to its Object view: `const Coord3DBase *getPosition() const { return (const Coord3DBase *)m_pos; }`.
// Uses that unit's BfmeVector3/Coord3DAdd helpers (the getBuildPos 0x005ABCFE shape). Head through the
// Inv_Sqrt normalise is exact; residue is only the destination add order/coloring (retail dir.X+pos.x in xmm3).

void AIStructureCreepTactic::moveDozerAway()
{
	Object *dozer = TheGameLogic->findObjectByID(m_58);
	if (dozer == 0)
		return;
	dozer->m_ai->m_commands.aiIdle(CMD_FROM_PLAYER);
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	BfmeVector3 dir = ((Rva004EBF4B *)record)->rva004EBF4B();
	BfmeVector3 base = *dozer->getPosition();
	dir -= base;
	dir.Normalize();
	dir.Scale(BfmeVector3(500.0f, 500.0f, 500.0f));
	const Coord3DBase *p = dozer->getPosition();
	dir.X += p->x;
	dir.Y += p->y;
	dir.Z += p->z;
	{
		Coord3D pos;
		pos.x = dir.X;
		pos.y = dir.Y;
		pos.z = dir.Z;
		dozer->m_ai->m_commands.aiMoveToPosition(&pos, CMD_FROM_PLAYER);
	}
}
