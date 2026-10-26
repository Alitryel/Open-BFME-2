#ifndef BFME2_UNIT_CRATE_COLLIDE_VIEW_H
#define BFME2_UNIT_CRATE_COLLIDE_VIEW_H

// Shared receiver for the matched execute and pool-key bodies. Execute reads
// ModuleData at +4. This partial interface preserves those accesses; it does
// not model the complete virtual interface or the opaque constructor donor.
class Object;
class UnitCrateCollideModuleData;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
};

class UnitCrateCollide : public CrateCollide
{
	const UnitCrateCollideModuleData *m_moduleData;	// +4
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual bool executeCrateBehavior(Object *other);
};

#endif
