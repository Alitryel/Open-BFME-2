// Open-BFME5 conversions.
// Named from the literals the bodies emit ("conn made" / "conn broken") and
// the +0x6A4 control-pointer layout it shares with the FESL "conn err %d"
// sibling at 0x007F91A0; the retail class name is still unknown.

class BfmeLogSNA
{
public:
	virtual void bfmeV0SNA() = 0;
	virtual void bfmeSaySNA(const char *s) = 0;
};

class BfmeCtlSNA
{
public:
	virtual void bfmeV0SNA() = 0;
	virtual void bfmeV1SNA() = 0;
	virtual void bfmeModeSNA(int a, int b) = 0;
};

struct Rva007EB810Diag;
extern Rva007EB810Diag *Rva007EB810Get();

class FeslConnectionHandler
{
public:
	void onConnectionMade();
	void onConnectionBroken();
	char m_bfmePad[0x6a4];
	BfmeCtlSNA *m_bfmeCtl;
};

void FeslConnectionHandler::onConnectionMade()
{
	((BfmeLogSNA *)Rva007EB810Get())->bfmeSaySNA("conn made\n");
	m_bfmeCtl->bfmeModeSNA(3, 0);
}

void FeslConnectionHandler::onConnectionBroken()
{
	((BfmeLogSNA *)Rva007EB810Get())->bfmeSaySNA("conn broken\n");
	m_bfmeCtl->bfmeModeSNA(0, 0);
}
