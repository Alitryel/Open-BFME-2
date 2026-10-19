// cl: /Ob1
#include "../GameLogic/AI/TeamInQueue.h"
// Native4EF5CE installs C62B78 and clears the complete 0x30 queue node.
TeamInQueue::TeamInQueue() throw()
{
    m_prev=0; m_next=0; m_prevReady=0; m_nextReady=0;
    m_workOrders=0; m_priorityBuild=0; m_team=0; m_unknown20=0;
    m_frameStarted=0; m_sentToStartLocation=0; m_stopQueueing=0;
    m_reinforcement=0; m_reinforcementID=(ObjectID)0;
}
