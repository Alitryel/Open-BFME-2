// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?init@W3DTerrainLogic@@UAEXXZ @0x00062B17 45B. Frameless thiscall init:
// push esi; mov esi,ecx; call 0x0000B3FD0; xorps xmm0,xmm0;
// and [esi+0x18],0; and [esi+0x1C],0; movss [esi+0x1918],xmm0;
// movss xmm0,[g_Va00BBB8D8]; movss [esi+0x191C],xmm0; pop esi; ret.
//
// Identity: slot 1 (init) of the W3DTerrainLogic subsystem table (slot 9 is
// the rowed W3DTerrainLogic::reset 0x00062B44, slot 10 W3DTerrainLogic::update
// 0x00062B97), and the body is Zero Hour's W3DTerrainLogic::init exactly: the
// base TerrainLogic::init (rowed at the shared empty ret 0x000B3FD0), then
// m_mapDX/m_mapDY cleared and the height range set to 0..1. The fields sit at
// BFME 2's offsets +0x18/+0x1C and +0x1918/+0x191C, the same ones the sibling
// reset writes (W3DTerrainLogicReset.cpp). The 1.0f global is the
// ledger-owned g_Va00BBB8D8 (defined once in AudioManagerFocusVolume.cpp).

extern float g_Va00BBB8D8;

class TerrainLogic
{
public:
	virtual void init();				// 0x000B3FD0

private:
	unsigned char m_pad04[0x18 - 0x04];

protected:
	int m_mapDX;						// +0x18
	int m_mapDY;						// +0x1C
};

class W3DTerrainLogic : public TerrainLogic
{
public:
	virtual void init();

private:
	unsigned char m_pad20[0x1918 - 0x20];
	float m_mapMinZ;					// +0x1918
	float m_mapMaxZ;					// +0x191C
};

void W3DTerrainLogic::init( void )
{
	TerrainLogic::init();
	m_mapDX = 0;
	m_mapDY = 0;
	m_mapMinZ = 0;
	m_mapMaxZ = g_Va00BBB8D8;
}
