// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva005D508E@Rva005D4FFC@@QAEXABUTreeHintRef00217D4C@@@Z @0x005D508E 7B: forwards to the
// rowed 0x005D5001 on the object this one holds at +0 (tail call, argument passed through).
struct TreeHintRef00217D4C;

class Rva005D5001
{
public:
	void rva005D5001(const TreeHintRef00217D4C &ref);
};

class Rva005D4FFC
{
public:
	void rva005D508E(const TreeHintRef00217D4C &ref);
private:
	Rva005D5001 *m_inner;
};

void Rva005D4FFC::rva005D508E(const TreeHintRef00217D4C &ref)
{
	m_inner->rva005D5001(ref);
}
