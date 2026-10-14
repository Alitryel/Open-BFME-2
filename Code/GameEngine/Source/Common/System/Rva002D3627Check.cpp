// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?check@Rva002D3627Host@@QAE_NXZ retail 0x002D3627 23 bytes. Dual byte check
// via global plus member target. Evidence: pin check, caller 0x003FE8F1,
// global g_00DFEF18, no callees.

class Rva002D3627Host
{
public:
	bool check();
private:
	char m_00[0x10];
	Rva002D3627Host *m_10;
	unsigned char m_14;
	char m_15[0x18 - 0x15];
	unsigned char m_18;
	char m_19[0x7C - 0x19];
	unsigned char m_7C;
};

class LivingWorld; extern LivingWorld *TheLivingWorld;
// TheLivingWorld: GameClient::init owns the VA00DFEF18 singleton.
// Target callers use the rowed LivingWorld::FindClickableObject/ZoomInTo interface.
// Private accessed-field views below do not introduce another global.
LivingWorld *TheLivingWorld;

bool Rva002D3627Host::check()
{
	return ((Rva002D3627Host *)TheLivingWorld)->m_18 == 0 && m_10->m_7C != 0;
}
