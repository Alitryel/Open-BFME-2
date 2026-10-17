// cl: /DNDEBUG /MD
//
// ?onObjectCreated@GateProxyBehavior@@UAEXXZ, retail 0x00499475, 5 bytes:
// slot 1 of GateProxyBehavior's ProxyBaseB vtable 0x00BEF304. It extends
// nothing: a tail jump to the rowed GateOpenAndCloseBehavior::onObjectCreated
// 0x0049936A with the same this, the introducing interface's sub-object (no
// adjustment). GateProxyBehavior overrides GateOpenAndCloseBehavior
// (GateProxyBehaviorFloatGetters.cpp); only the interface that introduces
// onObjectCreated is modelled here.

class GateProxyPrimaryView
{
public:
	virtual void p00();
};

class GateProxyCreateInterface
{
public:
	virtual ~GateProxyCreateInterface();
	virtual void onObjectCreated();
};

class GateOpenAndCloseBehavior : public GateProxyPrimaryView, public GateProxyCreateInterface
{
public:
	virtual ~GateOpenAndCloseBehavior();
	virtual void onObjectCreated();
};

class __declspec(novtable) GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	virtual ~GateProxyBehavior();
	virtual void onObjectCreated();
};

void GateProxyBehavior::onObjectCreated()
{
	GateOpenAndCloseBehavior::onObjectCreated();
}

// Native 254024..254029 is an unchanged-this jump to the complete base dtor
// 498798. Constructor 24E2CC calls base 49889C then installs BEF304 at +4;
// its slot 0 is 253328 (this-4) -> 254008 (deleting dtor) -> 254024.
// This independently establishes GateProxy ownership and the base relation.
// Only the primary/creation-interface prefix is modelled here. novtable is
// the destructor-only compilation context: retail has no derived vptr stores;
// the separate constructor still installs all four derived vptrs. The BF1
// 3ce339fbfa AIDockStateDestructors pattern is compiler context, not identity.
GateProxyBehavior::~GateProxyBehavior()
{
}
