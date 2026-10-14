// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Script clause removal on BFME 2's Script layout (clause heads +0x30 or,
// +0x34/+0x38 true/false actions, as ScriptGetUiText.cpp reads them):
//  - Script::deleteOrCondition @0x003B258F (62B): Zero Hour Scripts.cpp's
//    body; OrCondition links through +4.
//  - 0x003B25CD (66B, RET 8): the same unlink-and-delete over the action list
//    the int selects (+0x34 + 4*which), ScriptAction linking through +0x3C.
//    Zero Hour's deleteAction/deleteFalseAction pair takes no index; BFME 2's
//    name for the merged form is not established, so it is address-derived.
// Both end in a global-scope delete: the virtual destructor with flags 0,
// then ::operator delete on the pointer it returns (deleteCondition
// 0x003B26A1 in Scripts.cpp has the same tail).
typedef int Int;

class OrCondition
{
public:
	virtual ~OrCondition();
	OrCondition *getNextOrCondition() const { return m_next; }
	void setNextOrCondition(OrCondition *next) { m_next = next; }
private:
	OrCondition *m_next;	// +0x04
};

class ScriptAction
{
public:
	virtual ~ScriptAction();
	ScriptAction *getNext() const { return m_next; }
	void setNextAction(ScriptAction *next) { m_next = next; }
private:
	char m_pad04[0x3C - 0x04];
	ScriptAction *m_next;	// +0x3C
};

class Script
{
public:
	void deleteOrCondition(OrCondition *pCond);
	void rva003B25CD(Int which, ScriptAction *pAct);
private:
	char m_pad00[0x30];
	OrCondition *m_condition;	// +0x30
	ScriptAction *m_actions[2];	// +0x34 true, +0x38 false
};

void Script::deleteOrCondition(OrCondition *pCond)
{
	OrCondition *pPrev = 0;
	OrCondition *pCur = m_condition;
	while (pCond != pCur) {
		pPrev = pCur;
		pCur = pCur->getNextOrCondition();
	}
	if (pCur == 0) return;
	if (pPrev) {
		pPrev->setNextOrCondition(pCur->getNextOrCondition());
	} else {
		m_condition = pCur->getNextOrCondition();
	}
	pCur->setNextOrCondition(0);
	::delete pCur;
}

void Script::rva003B25CD(Int which, ScriptAction *pAct)
{
	ScriptAction *&head = m_actions[which];
	ScriptAction *pPrev = 0;
	ScriptAction *pCur = head;
	while (pAct != pCur) {
		pPrev = pCur;
		pCur = pCur->getNext();
	}
	if (pCur == 0) return;
	if (pPrev) {
		pPrev->setNextAction(pCur->getNext());
	} else {
		head = pCur->getNext();
	}
	pCur->setNextAction(0);
	::delete pCur;
}
