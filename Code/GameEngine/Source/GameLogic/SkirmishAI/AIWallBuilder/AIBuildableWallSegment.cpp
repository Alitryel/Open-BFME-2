// cl: /O1 /G7 /arch:SSE /MD /EHsc
// WorldBuilder names 0x1538510 AIBuildableWallSegment::build. The paired
// retail body 0x00596D99..0x00596E13 preserves its base-build fallback,
// start-node lookup, virtual wall construction and terminal-hub ID update.
// Target offsets differ from WB: Object position +0x38 and ID +0x74;
// produced ID +0x24 and start-node ID +0x4C are observed in retail.
// Unrecovered virtual slots and class extents remain opaque.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct MakeCodeLife
{
    int code;
    __forceinline MakeCodeLife() : code(0) {}
    __forceinline ~MakeCodeLife() {}
    __forceinline int get() const { return code; }
};

class Object
{
public:
    char m_unrecovered00[0x38];
    Coord3D m_position;
    char m_unrecovered44[0x74 - 0x44];
    ObjectID m_id;
};

class Player
{
public:
    char m_pad00[0x94];
    unsigned int m_money;
};
extern GameLogic *TheGameLogic;

void operator delete[](void *p);
class Rva004D9A3C
{
public:
    ~Rva004D9A3C();
private:
    char m_unrecovered00[0x1C];
};
// Same quote-record layout as the matched constructor and destructor.
class Rva0039205C
{
public:
    Rva0039205C()
    {
        m_20 = -1;
        m_unk00 = 0;
        m_array08 = 0;
        m_1C = 0;
        m_1D = 0;
        m_pad04 = 0;
        m_24 = 0;
    }
    // Same 26-byte body as the matched cleanup provider; kept visible so
    // the five-byte unwind wrapper can carry a complete fold proof.
    __declspec(noinline) ~Rva0039205C()
    {
        if (m_array08)
        {
            delete[] m_array08;
            m_array08 = 0;
            m_unk00 = 0;
        }
    }
    int m_unk00;
    int m_pad04;
    Rva004D9A3C *m_array08;
    unsigned char m_1C;
    unsigned char m_1D;
    int m_20;
    int m_24;
};

// Preserve the native unwind wrapper separately from normal-path cleanup.
struct WallQuoteResult : Rva0039205C {};

class BuildAssistant
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual bool buildWall(Object *startNode, const Coord3D *startPosition,
                           const Coord3D &endPosition, Player *player,
                           bool option, Object **terminalHub);
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual bool quoteWall(Rva0039205C *result, Object *startNode,
                           const Coord3D *startPosition,
                           const Coord3D &endPosition, bool option);
};
class Rva00A027B8;
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;

class Rva0055ADD8
{
public:
    int failBuild(int ignored);
};

class AIBuildableStructure
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual Coord3D getWorldPosition(); // slot 13, hidden result pointer
    virtual void s14();
    virtual bool build(Player *player); // WB 0x1506950; retail 0x00573C7C, a vtable slot (0x0086E2AC)
    virtual int canMake(Player *player); // slot 16; retail 0x00573CFB
protected:
    char m_unrecovered04[0x24 - 4];
    ObjectID m_producedObjectID;
    char m_unrecovered28[0x4C - 0x28];
};

class AIBuildableWallSegment : public AIBuildableStructure
{
public:
    bool build(Player *player);
    float getTotalCost(Player *player);
    int canMake(Player *player);
private:
    ObjectID m_startNodeID;
    char m_unrecovered50[4];
    int m_totalCost;
};

bool AIBuildableWallSegment::build(Player *player)
{
    if (m_startNodeID == INVALID_OBJECT_ID)
        return AIBuildableStructure::build(player);
    Object *startNode = TheGameLogic->findObjectByID(m_startNodeID);
    Object *terminalHub = 0;
    if (((BuildAssistant *)TheBuildAssistant)->buildWall(startNode, &startNode->m_position,
                            getWorldPosition(), player, false, &terminalHub))
    {
        m_producedObjectID = terminalHub->m_id;
        return true;
    }
    ((Rva0055ADD8 *)this)->failBuild((int)player);
    return false;
}

class Rva00573B23
{
public:
    float rva00573DCD(int player);
};

// WB 0x1538930 names getTotalCost. Retail 0x00596C6B..0x00596C7C
// tail-calls the existing base-cost provider for an unset start node;
// otherwise FILD establishes the signed cached cost at +0x54.
float AIBuildableWallSegment::getTotalCost(Player *player)
{
    if (m_startNodeID == INVALID_OBJECT_ID)
        return ((Rva00573B23 *)this)->rva00573DCD((int)player);
    return (float)m_totalCost;
}

// WB 0x15386C0 identifies canMake; retail [0x00596E15, 0x00596EEF).
// Keep the empty return-holder lifetime and separate success cleanup.
int AIBuildableWallSegment::canMake(Player *player)
{
    MakeCodeLife selected;
    if (m_startNodeID == 0)
        return AIBuildableStructure::canMake(player);
    Object *startNode = TheGameLogic->findObjectByID(m_startNodeID);
    WallQuoteResult result;
    bool failed = !((BuildAssistant *)TheBuildAssistant)->quoteWall(
        &result, startNode, &startNode->m_position, getWorldPosition(), false);
    if (failed)
    {
        selected.code = 9;
        return selected.code;
    }
    switch (result.m_20)
    {
    case 0:
        break;
    case 7:
    {
        selected.code = 2;
        return selected.code;
    }
    default:
    {
        selected.code = 9;
        return selected.code;
    }
    }
    unsigned int money = player->m_money;
    if (money < result.m_pad04)
    {
        do
        {
            if (!(player->m_money < (unsigned int)result.m_pad04))
                break;
            {
                selected.code = 2;
                return selected.code;
            }
        } while (0);
        // No call or store separates these identical funds comparisons.
        // This arm is unreachable. Returning two here avoids the allocator's
        // zero-copy preference and preserves retail's ESI failure return.
        {
            selected.code = 2;
            return selected.code;
        }
    }
    m_totalCost = result.m_pad04;
    {
        selected.code = 0;
        return selected.code;
    }
}
