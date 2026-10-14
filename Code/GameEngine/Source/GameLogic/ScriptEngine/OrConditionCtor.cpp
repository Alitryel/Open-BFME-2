// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ??0OrCondition@@QAE@XZ, retail 0x003B238A, 17 bytes.
// Zero Hour Scripts.h: OrCondition():m_nextOr(NULL),m_firstAnd(NULL){} - the
// two link words at +4/+8 cleared and the OrCondition vtable VA 0x00C1F3F4
// installed (the same table OrConditionParse.cpp's inline allocation writes
// as ??_7OrCondition@@6B@). Retail keeps this out-of-line copy with no
// direct caller; duplicate() and the chunk parser expand it inline. Only the
// two members the body touches are modelled; MemoryPoolObject contributes
// just the vptr here. Skeleton twin of the 0x0031454D base constructor.

class Condition;

class OrCondition
{
public:
	OrCondition();
	virtual ~OrCondition();

protected:
	OrCondition *m_nextOr;	// Next or clause.
	Condition *m_firstAnd;	// These are Anded.
};

OrCondition::OrCondition() : m_nextOr(0), m_firstAnd(0)
{
}
