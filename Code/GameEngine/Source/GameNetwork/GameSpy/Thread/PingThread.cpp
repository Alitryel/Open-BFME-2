// cl: /DNDEBUG /MD /EHsc

// PingThreadClass ICMP helper, retail 0x0054F99E.
// Zero Hour donor: GeneralsMD GameSpy/Thread/PingThread.cpp, doPing.
// The retail thread caller passes its receiver in ECX.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef int BOOL;
typedef void *HMODULE;
typedef void *HANDLE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE module);
}

struct PingIpOptionInfo
{
	UnsignedByte ttl;
	UnsignedByte tos;
	UnsignedByte flags;
	UnsignedByte optionsSize;
	void *optionsData;
};

struct PingEchoReply
{
	UnsignedInt sourceAddress;
	UnsignedInt roundTripTime;
	WORD replyDataSize;
	WORD reserved;
	void *replyData;
	PingIpOptionInfo replyOptions;
};

typedef HANDLE (__stdcall *IcmpCreateFileProc)(void);
typedef BOOL (__stdcall *IcmpCloseHandleProc)(HANDLE handle);
typedef DWORD (__stdcall *IcmpSendEchoProc)(HANDLE handle, UnsignedInt destAddress,
	void *requestData, WORD requestSize, void *requestOptions,
	void *replyBuffer, DWORD replySize, DWORD timeoutMs);

class PingThreadClass
{
private:
	Int doPing(UnsignedInt IP, Int timeout);
};

// Return the ICMP reply time clamped to the timeout, or -1 on failure.
Int PingThreadClass::doPing(UnsignedInt IP, Int timeout)
{
	Int pingTime = -1;
	Int requestLen = 32;
	Int fillSeed = 32;

	char replyBuffer[sizeof(PingEchoReply) + 8192];
	char requestBuffer[8192];

	HMODULE icmpLib = LoadLibraryA("ICMP.DLL");
	if (icmpLib == 0) {
		goto cleanupDone;
	}

	IcmpCreateFileProc createFile = (IcmpCreateFileProc)GetProcAddress(icmpLib, "IcmpCreateFile");
	IcmpCloseHandleProc closeHandle = (IcmpCloseHandleProc)GetProcAddress(icmpLib, "IcmpCloseHandle");
	IcmpSendEchoProc sendEcho = (IcmpSendEchoProc)GetProcAddress(icmpLib, "IcmpSendEcho");
	if (createFile == 0 || closeHandle == 0 || sendEcho == 0) {
		goto cleanupLib;
	}

	HANDLE icmpHandle = createFile();
	if (icmpHandle == (HANDLE)-1) {
		goto cleanupLib;
	}

	for (Int i = 0, fillValue = fillSeed; i < requestLen; ++i, ++fillValue) {
		fillValue = fillValue >= 126 ? fillSeed : fillValue;
		requestBuffer[i] = (char)fillValue;
	}

	PingIpOptionInfo requestOptions;
	requestOptions.ttl = 64;
	requestOptions.tos = 0;
	requestOptions.flags = 0;
	requestOptions.optionsSize = 0;
	requestOptions.optionsData = 0;

	DWORD replyCount = sendEcho(icmpHandle, IP,
		requestBuffer, (WORD)requestLen,
		&requestOptions,
		replyBuffer, sizeof(replyBuffer),
		(DWORD)timeout);
	if (replyCount != 0) {
		pingTime = *(UnsignedInt *)&replyBuffer[8];
		if (pingTime > timeout) {
			pingTime = timeout;
		}
	} else {
		pingTime = -1;
		goto cleanupLib;
	}

cleanupHandle:
	closeHandle(icmpHandle);
cleanupLib:
	FreeLibrary(icmpLib);
cleanupDone:
	return pingTime;
}
