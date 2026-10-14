// 0x004F46A9 is rowed as the protected AIPlayer::queueUnits
// (AIPlayerTeamBuild.cpp); this unit's carrier reaches it on the same this.
class AIPlayer
{
	friend class BfmeThingDTK;
protected:
	void queueUnits();
};

class BfmeThingDTK
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual bool bfmeAskDTK();
	void bfmeGoDTK();
	// NOTE: BFME1 donor also defines bfmeGoDTL/bfmeTailDTL, but game.dat holds
	// a single 22B body at 0x4EF4A1 (both twins ICF-fold to it, as in BFME1).
	// One body per address: only bfmeGoDTK is claimed here.
};

void BfmeThingDTK::bfmeGoDTK()
{
	if (bfmeAskDTK())
		((AIPlayer *)this)->queueUnits();
}
