// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp): only the
// placed DisconnectManager::resetPlayerTimeout body is defined here. The
// donor's other 36 members stay out, so the unmatched-definition gate
// passes. The per-slot timeout stamps live at +0x14 (moved from ZH +0x38;
// see reference/shims/disconnectmanager) and are refreshed from winmm
// timeGetTime.

typedef int Int;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

int Rva004D39DEGet(int a, int b);

class ConnectionManager
{
public:
	unsigned int getLocalPlayerID();
};

class DisconnectManager
{
protected:
	__declspec(noinline) void resetPlayerTimeout(Int slot);

public:
	void processDisconnectKeepAlive(void *a1, ConnectionManager *a2);

private:
	unsigned char m_pad[0x14];
	long m_playerTimeouts[1];
};

void DisconnectManager::resetPlayerTimeout(Int slot)
{
	m_playerTimeouts[slot] = timeGetTime();
}

void DisconnectManager::processDisconnectKeepAlive(void *a1, ConnectionManager *conMgr)
{
	int valC = *(int *)((char *)a1 + 0xC);
	int localID = conMgr->getLocalPlayerID();
	int idx = Rva004D39DEGet(valC, localID);
	if (idx != -1)
		resetPlayerTimeout(idx);
}
