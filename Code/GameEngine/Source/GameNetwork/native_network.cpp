// cl: /DNDEBUG /MD /GX
// Trimmed from reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/native_network.cpp:
// only _BFMENetworkBackendThreadStart@4 is placed here. The file's naked
// event-callback body stays out (conversion gate), everything else is
// declared-only.

class BFMENetworkThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void threadTick();
};

class BFMENetworkBackendThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void dispatchEvents();
};
class Debug;
extern class Debug *theDebug;

// _BFMENetworkBackendThreadStart@4 (b1 0x009DB630, 25B @0x00610490)
extern "C" unsigned int __stdcall BFMENetworkBackendThreadStart(void *backend)
{
// Retail disp32 proves the BFME2 global lives at 0x00DE0880 (donor says
// 0x01336e5c); displacement bytes outrank the donor.
	BFMENetworkThreadRunner *globalNetwork = reinterpret_cast<BFMENetworkThreadRunner *>(theDebug);
	globalNetwork->threadTick();
	reinterpret_cast<BFMENetworkBackendThreadRunner *>(backend)->dispatchEvents();
	return 0;
}
