// cl: /MD
#include "TeamInQueue.h"
#include "WorkOrder.h"
// ZH AIPlayer.cpp isAllBuilt supplies the queue-check identity. BFME2
// checkQueuedTeams4F1653 calls this body at4F16F4 with the actual queue
// entry; optional flag29 and positive completed-count requirement are
// target-specific changes. Existing native43B control flow is retained.
bool TeamInQueue::isAllBuilt()
{
    int sum=0;
    WorkOrder *cur=m_workOrders;
    if(cur==0)
        goto fail;
    do {
        if(cur->m_bfmeFlag29==0) {
            if(cur->m_numRequired>cur->m_numCompleted)
                goto fail;
        }
        sum+=cur->m_numCompleted;
        cur=cur->m_next;
    } while(cur!=0);
    if(sum>0)
        return true;
fail:
    return false;
}
