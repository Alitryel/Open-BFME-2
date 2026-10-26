// cl: /DNDEBUG /MD
//
// ?getBridgeTowerBehaviorInterfaceFromObject@BridgeTowerBehavior@@SAPAVBridgeTowerBehaviorInterface@@PAVObject@@@Z,
// retail 0x0045880B, 54 bytes. Dedicated TU.
// In the BridgeTowerBehavior.cpp code range (after setBridge 0x004586EE); called
// by the Dozer/Worker scaffolding and repair paths. ZH shape: reject a null
// object or one whose template lacks KINDOF_BRIDGE_TOWER (bit 0 of template
// byte +0x10B in BFME2), then scan the BehaviorModule array at +0x244 and ask
// each module's +0x0C interface sub-object for the tower interface at slot 13
// (+0x34).

class BridgeTowerBehaviorInterface;

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterface() = 0;
};

class BfmeObjectModule
{
public:
	virtual void slot0() = 0;

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class Object;

// These views expose only the measured template/module pointers and kind-of byte.
// These partial views do not require private Object/ThingTemplate helpers
// to be redeclared when this body joins the original translation unit.
struct BridgeTowerKindOfView
{
	char m_pad[0x10B];
	unsigned char m_kindOfByte10B;
};

struct BridgeTowerObjectTemplateView
{
	char m_pad[4];
	const BridgeTowerKindOfView *m_template;
	char m_remaining[0x244 - 8];
	BehaviorModule **m_modules244;
};

class BridgeTowerBehavior
{
public:
	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *obj);
};

// ?getBridgeTowerBehaviorInterfaceFromObject@BridgeTowerBehavior@@SAPAVBridgeTowerBehaviorInterface@@PAVObject@@@Z
BridgeTowerBehaviorInterface *BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(Object *obj)
{
	// sanity
	if (obj == 0 || (((const BridgeTowerObjectTemplateView *)obj)->m_template->m_kindOfByte10B & 1) == 0)
		return 0;

	// get the bridge tower behavior module
	BehaviorModule **bmi;
	BridgeTowerBehaviorInterface *bbi;
	for (bmi = ((const BridgeTowerObjectTemplateView *)obj)->m_modules244; *bmi; ++bmi)
	{
		bbi = (*bmi)->getBridgeTowerBehaviorInterface();
		if (bbi)
			return bbi;
	}

	// interface not found
	return 0;
}
