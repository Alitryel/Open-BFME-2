#pragma once

// Zero Hour's single-filter views of two filters that BFME 2 moved onto the
// Rva000421C8 chain.  The Dozer, Spectre and Jet donor code builds
// PartitionFilter* arrays from the ZH source; those ZH classes share the
// BFME 2 class names but have the ZH 4-byte single-slot vtable and ZH field
// offsets.  Naming the donor views here keeps the real BFME 2 vtable and
// constructor symbols (emitted by the BFME 2 units) free of the ZH copies.
//
// Layout and allow bodies: inputs/reference/CnC_Generals_Zero_Hour/.../
// GameLogic/PartitionManager.h and PartitionManager.cpp (ZH), rebased onto
// the ZH PartitionFilter base (one virtual slot, allow).

#include "GameLogic/PartitionManager.h"
#include "GameLogic/Object.h"
#include "GameLogic/WeaponSet.h"

// ZH layout: vptr at +0x00, m_obj at +0x04.
class PartitionFilterSameMapStatusZh : public PartitionFilter
{
public:
	PartitionFilterSameMapStatusZh(const Object *obj) : m_obj(obj) { }
protected:
	virtual Bool allow(Object *objOther)
	{
		return objOther->isOffMap() == m_obj->isOffMap();
	}
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterSameMapStatusZh"; }
#endif
private:
	const Object *m_obj;						// +0x04
};

// ZH layout: vptr at +0x00, m_obj at +0x04, m_commandSource at +0x08,
// m_attackType at +0x0C (the ZH declaration order).
class PartitionFilterPossibleToAttackZh : public PartitionFilter
{
public:
	PartitionFilterPossibleToAttackZh(AbleToAttackType t, const Object *obj, CommandSourceType commandSource) :
		m_obj(obj),
		m_commandSource(commandSource),
		m_attackType(t)
	{
	}
	virtual Bool allow(Object *objOther)
	{
		CanAttackResult result = m_obj->getAbleToAttackSpecificObject(m_attackType, objOther, m_commandSource);
		if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
		{
			return true;
		}
		return false;
	}
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterPossibleToAttackZh"; }
#endif
private:
	const Object *m_obj;						// +0x04
	CommandSourceType m_commandSource;			// +0x08
	AbleToAttackType m_attackType;				// +0x0C
};
