// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /Ireference/shims/moduledata
// Native4F1B56/54 and deleting4F1D1C/28 belong to WorkOrder: constructor
// 4F10E6 installs the same C62E40 table, whose getter4F1116 says WorkOrder.
// Slot order is destructor, empty post-load, name getter, xfer4F0716.
#include "../GameLogic/AI/WorkOrder.h"
WorkOrder::~WorkOrder() {}
void WorkOrder::loadPostProcess() {}
