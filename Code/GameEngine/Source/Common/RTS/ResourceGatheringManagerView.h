#pragma once

// Existing list-maintenance and transfer bodies share the measured prefix:
// primary vptr +0, warehouse list +4 and center list +8. Real STLport lists
// retain their single-node-pointer layout. No constructor/vtable is emitted
// through this partial declaration; lifecycle rows still need reconciliation.
#ifndef _STLP_NO_EXCEPTIONS
#define _STLP_NO_EXCEPTIONS 1
#endif
#include <list>

class Object;
class Xfer;

class ResourceGatheringManager
{
public:
    void removeSupplyCenter(Object *oldCenter);
    void removeSupplyWarehouse(Object *oldWarehouse);
    void addSupplyCenter(Object *newCenter);
    void addSupplyWarehouse(Object *newWarehouse);
    void rva004F5C44(Object *newCenter);
protected:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void xfer(Xfer *xfer);
private:
    typedef _STL::list<int> objectIDList;
    objectIDList m_supplyWarehouses;
    objectIDList m_supplyCenters;
};
