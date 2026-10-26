// Shared partial receiver for the matched pool-key and apply/remove bodies.
// The implementation donor proves the +0x10 secondary UpgradeMux receiver
// and ModuleData/Object operands. No ctor, dtor or complete vtable is emitted
// through this view; the separate constructor remains unreconciled.
#ifndef BFME2_STATUS_BITS_UPGRADE_VIEW_H
#define BFME2_STATUS_BITS_UPGRADE_VIEW_H

enum NameKeyType { NK_UNKNOWN = 0 };

class Rva00346BC0
{
	public:
	unsigned int m_words[4];
};

class Object
{
public:
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
};

class ModuleData;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

template <int N> class StatusBitsUpgradeMuxSlots : public StatusBitsUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class StatusBitsUpgradeMuxSlots<0>
{
};

class UpgradeMuxIface : public StatusBitsUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public ObjectModuleBase,
	public UpgradeModuleInterface,
	public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
};

class StatusBitsUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Rva00346BC0 m_statusToSet;
	Rva00346BC0 m_statusToClear;
};

class StatusBitsUpgrade : public UpgradeModule
{
public:
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};

#endif
