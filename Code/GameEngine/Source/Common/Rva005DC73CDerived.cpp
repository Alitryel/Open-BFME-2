// cl: /MD
//
// Opaque single-inheritance destructors tail-calling AITacticOffensive::~
// AITacticOffensive at 0x005DC73C (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class AITacticOffensive
{
public:
	virtual ~AITacticOffensive();
};

class AIBasePenetrationTroopsTactic : public AITacticOffensive
{
public:
	virtual ~AIBasePenetrationTroopsTactic();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AIBasePenetrationTroopsTactic::~AIBasePenetrationTroopsTactic()
{
}

// ?bfmeAnchorAIBasePenetrationTroopsTacticDtor absent-from-retail
void bfmeAnchorAIBasePenetrationTroopsTacticDtor(AIBasePenetrationTroopsTactic *aIBasePenetrationTroopsTactic)
{
	aIBasePenetrationTroopsTactic->AIBasePenetrationTroopsTactic::~AIBasePenetrationTroopsTactic();
}

// AISimpleAttackTactic's destructor and ??_G are in Rva005AA647Tactic.cpp, whose full class view
// owns the vtable (a one-slot view here shadowed it at link time).

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AITacticSiege::~AITacticSiege()
{
}

// ?bfmeAnchorAITacticSiegeDtor absent-from-retail
void bfmeAnchorAITacticSiegeDtor(AITacticSiege *aITacticSiege)
{
	aITacticSiege->AITacticSiege::~AITacticSiege();
}
