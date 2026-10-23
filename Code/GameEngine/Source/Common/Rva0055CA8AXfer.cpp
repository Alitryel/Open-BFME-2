// cl: /MD
// ?xfer@Rva0055CA8A@@MAEXPAVXfer@@@Z at 0x0055CA8A size 34
// Evidence: unlock lane; vtable slot 3 of 0x00817300/0x0081D00C/0x0081C730;
// Version1 via rowed 0x000053EE then bool at +0x20 via Xfer slot 0x90;
// State base 0x20 layout per Rva00367539Ctor.cpp/Rva00367647Xfer.cpp precedent.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};

class Rva0055CA8A : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_20;
};

void Rva0055CA8A::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
}
