// Close a handle and log on failure.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv1038.cpp); trimmed to the single T1
// body the sweep places.

class BfmeLog1038
{
public:
	virtual void bfmeV01038();
	virtual void bfmeSay1038(char *m);
};

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *h);
BfmeLog1038 *bfmeGetLog1038(void);

class BfmeD1038
{
public:
	void bfmeGo1038D(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

void BfmeD1038::bfmeGo1038D(void)
{
	if (ReleaseMutex(m_bfmeHandle) == 0)
		bfmeGetLog1038()->bfmeSay1038((char *)"Error leaving critical section\n");
}
