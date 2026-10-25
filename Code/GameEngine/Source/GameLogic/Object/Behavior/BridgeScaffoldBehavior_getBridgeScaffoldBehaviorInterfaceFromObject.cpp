// cl: /DNDEBUG /MD
//
// ?getBridgeScaffoldBehaviorInterfaceFromObject@BridgeScaffoldBehavior@@SAPAVBridgeScaffoldBehaviorInterface@@PAVObject@@@Z,
// retail 0x004582F3, 41 bytes. Dedicated TU.
// In the BridgeScaffoldBehavior.cpp code range, immediately after
// reverseMotion (0x004582CB + 40) and before the BridgeScaffoldBehavior ctor
// (0x0045831C). Same ZH shape as getBridgeBehaviorInterfaceFromObject
// (0x00456556, slot 12) and getBridgeTowerBehaviorInterfaceFromObject
// (0x0045880B, slot 13), with no template test: reject a null object, then scan
// the BehaviorModule array at +0x244 and ask each module's +0x0C interface
// sub-object for the scaffold interface at slot 14 (+0x38). Called from the
// Dozer/Worker scaffolding paths.

#include "BridgeScaffoldBehaviorView.h"

// ?getBridgeScaffoldBehaviorInterfaceFromObject@BridgeScaffoldBehavior@@SAPAVBridgeScaffoldBehaviorInterface@@PAVObject@@@Z
BridgeScaffoldBehaviorInterface *BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(Object *obj)
{
	// sanity
	if (obj == 0)
		return 0;

	// get the bridge scaffold behavior module
	BehaviorModule **bmi;
	BridgeScaffoldBehaviorInterface *bbi;
	for (bmi = obj->getBehaviorModules(); *bmi; ++bmi)
	{
		bbi = (*bmi)->getBridgeScaffoldBehaviorInterface();
		if (bbi)
			return bbi;
	}

	// interface not found
	return 0;
}
