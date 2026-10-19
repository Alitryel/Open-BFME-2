// cl: /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ow
// Split from Rva0008EF3FProductCtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ??0Rva0008EF3FProduct@@QAE@XZ retail 0x0008EF3F 66B.
//
// The 0xAC0-byte product of game client vtable 0x00BC4738 factory 0x0004C492
// (W3DGameClientFactories.cpp). Target facts: it calls the rowed
// ??0InGameUI@@QAE@XZ 0x002A61A9, stores its own vptrs 0x00BC7A88/+0x0C
// 0x00BC7A78/+0x10 0x00BC7A64 over InGameUI's three bases, clears two
// 25-pointer arrays at +0x9F0/+0xA54 in one loop and then +0xAB8/+0xABC; the
// object ends at 0xAC0, the factory's allocation size.
//
// Donor inference (Zero Hour W3DInGameUI.cpp, not asserted as the target
// name): this is W3DInGameUI::W3DInGameUI -- MAX_MOVE_HINTS is 25 and the
// fields are m_moveHintRenderObj/m_moveHintAnim then the building placement
// anchor and arrow. The class keeps the ledger's address-derived name.

#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
#define SLOT(N) virtual void slot##N();
	SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
#undef SLOT
	virtual void reset();	// slot 9
	virtual void update();	// slot 10

private:
	char m_opaque04[0xC - 0x4];
};

class View;
class Drawable;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class RenderObjClass;
class HAnimClass;

// The five-slot interface at +0x10 (InGameUICtor.cpp).
class InGameUIInterface10
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10
{
public:
	InGameUI();
	virtual ~InGameUI();
	virtual void init();
	virtual void reset();
	virtual void update();
#define SLOT(N) virtual void slot##N();
	SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
#undef SLOT
	virtual bool isPlacementAnchored(void);					// +0xF0
	virtual void getPlacementPoints(ICoord2D *start, ICoord2D *end);	// +0xF4

protected:
	// BFME's lasso selection: points in screen order, closed to the cursor.
	struct LassoPointNode
	{
		LassoPointNode *next;
		LassoPointNode *prev;
		ICoord2D point;
	};

	char m_opaque14[0x2C - 0x14];
	ICoord2D m_dragSelectRegionLo;	// +0x2C
	ICoord2D m_dragSelectRegionHi;	// +0x34
	char m_opaque3C[0x40 - 0x3C];
	// BFME 2's move hint record (0x14 bytes): Zero Hour's MoveHintStruct with
	// the source ID dropped and a byte that suppresses the hint (labels are
	// descriptive; the offsets are what 0x0008F48E reads).
	struct MoveHint
	{
		Coord3D pos;		// +0x00
		unsigned int frame;	// +0x0C
		bool suppressed;	// +0x10
	};
	MoveHint m_moveHint[25];	// +0x40
	char m_opaque234[0x544 - 0x234];
	Drawable **m_placeIcon;		// +0x544
	char m_opaque548[0x910 - 0x548];
	LassoPointNode *m_lassoPoints;	// +0x910, list sentinel
	char m_opaque914[0x924 - 0x914];
	bool m_lassoSelecting;		// +0x924
	char m_opaque925[0x9F0 - 0x925];
};

class Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void drawSelectionRegion(void);
	virtual void drawMoveHints(View *view);
	virtual void drawPlaceAngle(View *view);

private:
	enum { MAX_MOVE_HINTS = 25 };

	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	class RenderObjClass *m_buildingPlacementAnchor;	// +0xAB8
	class RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};

Rva0008EF3FProduct::Rva0008EF3FProduct()
{
	int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		m_moveHintRenderObj[i] = 0;
		m_moveHintAnim[i] = 0;
	}

	m_buildingPlacementAnchor = 0;
	m_buildingPlacementArrow = 0;
}
