class AsciiString;
class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class BfmeThingBMD
{
public:
	void bfmeGoBMD();
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x24];
	void *m_bfmeGot;
};

// ?bfmeGoBMD@BfmeThingBMD@@QAEXXZ
//
// BFME1 donor BfmeConv491.cpp shape: fetch ((char *)m_bfmeWhat + 0x18) and
// hand it to the sink. BFME2 repair: the sink slot calls matched
// ?findUpgrade@UpgradeCenter@@ at 0x0026F26D (the sweep's bfmeMakeBMD/
// bfmeGet1095/j_ pins all name this same address; the row is the verified
// identity, so no new pin), which takes const AsciiString&. The +0x18 word
// is therefore an embedded AsciiString here, reached through a free
// reinterpret_cast. B1 0x00203110 26B -> B2 0x00481A54 26B.
void BfmeThingBMD::bfmeGoBMD()
{
	m_bfmeGot = (void *)TheUpgradeCenter->findUpgrade(
		*reinterpret_cast<const AsciiString *>((const char *)m_bfmeWhat + 0x18));
}
