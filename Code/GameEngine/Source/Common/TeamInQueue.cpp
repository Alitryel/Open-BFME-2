// cl: /O1 /DNDEBUG /MD /GX /Ireference/shims/moduledata
#include "../GameLogic/AI/TeamInQueue.h"
#include "../GameLogic/AI/WorkOrder.h"
// Native4F05F0 walks WorkOrder.next at +0C, calls virtual destructor
// with flags0 and global delete, then marks Team bytes +5D/+5E.
// Keep the existing evidenced flag view until Team has a shared layout.
struct Rva004F05F0Flags {
    unsigned char pad[0x5D];
    unsigned char m_5D;
    unsigned char m_5E;
};
TeamInQueue::~TeamInQueue()
{
    WorkOrder *cur=m_workOrders;
    while(cur!=0) {
        WorkOrder *next=cur->m_next;
        ::delete cur;
        cur=next;
    }
    Rva004F05F0Flags *flag=(Rva004F05F0Flags *)m_team;
    if(flag!=0 && flag->m_5D==0) {
        flag->m_5E=1;
        flag->m_5D=1;
    }
    m_workOrders=0;
}
void TeamInQueue::loadPostProcess() {}
