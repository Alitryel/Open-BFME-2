// cl: /MD /GX
// ?rva0023D6D5@Rva0023D6D5@@QAEX_N@Z @0x0023D6D5 (27B): global-guarded call.
// Retail: ecx=[0xDFDC8C]; cmp [ecx+0x10],0; je ret; cmp byte [esp+4],0;
// jne ret; call 0x1EC98E (pinned TU-local); ret 4. Single stack arg, a bool
// (only its byte is tested; GameLogic::startNewGame passes its
// loadingSaveGame flag); this unused (ecx clobbered by global); no EBP.
// Address-derived; pin for callee.
class Rva0023D6D5Callee
{
public:
	void thru();
};

class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;

class Rva0023D6D5
{
public:
	void rva0023D6D5(bool loadingSaveGame);
};

// ?rva0023D6D5@Rva0023D6D5@@QAEX_N@Z
void Rva0023D6D5::rva0023D6D5(bool loadingSaveGame)
{
	struct Guard
	{
		char m_pad[0x10];
		int m_10;
	};
	Guard *guard = (Guard *)TheLinearCampaignManager;
	if (guard->m_10 == 0)
		return;
	if (loadingSaveGame)
		return;
	Rva0023D6D5Callee *c = (Rva0023D6D5Callee *)guard;
	c->thru();
}
