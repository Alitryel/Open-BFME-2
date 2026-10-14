// ?rva00599870@Rva005997CD@@QAE?AW4ObjectID@@PBUVec2@@_N@Z
// partial score=0.890229447125561 date=2026-10-14
// ?rva00599870@Rva005997CD@@QAE?AW4ObjectID@@PBUVec2@@_N@Z
// partial score=0.93 date=2026-10-14
// ?rva00599870@Rva005997CD@@QAE?AW4ObjectID@@PBUVec2@@_N@Z
// partial score=0.94 date=2026-10-01
// cl: /O1 /MD /GX- /arch:SSE2
// ?rva00599870@Rva005997CD@@QAEW4ObjectID@@PBVVec2@@_N@Z present-unmatched
// retail 0x00599870 186B. Closest-object search over the +0 list: walks the
// sentinel list pushing each node's ObjectID at +8 through GameLogic
// findObjectByID then filters via two virtuals and Object status 0x5A before
// keeping the smallest XY distance squared from the input point. Caller and
// layout evidence from the Rva005997CD dtor neighbours.
enum ObjectID
{
    INVALID_OBJECT_ID = 0
};

struct Vec2
{
    float x;
    float y;
};

class Object;
enum ObjectStatusTypes;

class Object
{
public:
    bool testStatus(ObjectStatusTypes bit) const;
};

class GameLogic
{
public:
    class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct ListNode
{
    ListNode *next;
    int unk04;
    ObjectID id;
};

class FilterResult
{
public:
    virtual void _s00();
    virtual void _s01();
    virtual void _s02();
    virtual void _s03();
    virtual void _s04();
    virtual void _s05();
    virtual void _s06();
    virtual void _s07();
    virtual bool isValid();
};

class FilterSource
{
public:
    virtual void _t00();
    virtual void _t01();
    virtual void _t02();
    virtual void _t03();
    virtual void _t04();
    virtual void _t05();
    virtual void _t06();
    virtual void _t07();
    virtual void _t08();
    virtual void _t09();
    virtual void _t10();
    virtual void _t11();
    virtual void _t12();
    virtual void _t13();
    virtual void _t14();
    virtual void _t15();
    virtual void _t16();
    virtual void _t17();
    virtual void _t18();
    virtual void _t19();
    virtual void _t20();
    virtual void _t21();
    virtual void _t22();
    virtual void _t23();
    virtual void _t24();
    virtual void _t25();
    virtual void _t26();
    virtual void _t27();
    virtual void _t28();
    virtual void _t29();
    virtual void _t30();
    virtual void _t31();
    virtual void _t32();
    virtual void _t33();
    virtual void _t34();
    virtual void _t35();
    virtual void _t36();
    virtual void _t37();
    virtual void _t38();
    virtual void _t39();
    virtual void _t40();
    virtual void _t41();
    virtual void _t42();
    virtual void _t43();
    virtual void _t44();
    virtual void _t45();
    virtual void _t46();
    virtual void _t47();
    virtual void _t48();
    virtual void _t49();
    virtual void _t50();
    virtual void _t51();
    virtual void _t52();
    virtual void _t53();
    virtual void _t54();
    virtual void _t55();
    virtual void _t56();
    virtual void _t57();
    virtual void _t58();
    virtual void _t59();
    virtual void _t60();
    virtual void _t61();
    virtual void _t62();
    virtual void _t63();
    virtual void _t64();
    virtual void _t65();
    virtual void _t66();
    virtual void _t67();
    virtual void _t68();
    virtual void _t69();
    virtual void _t70();
    virtual void _t71();
    virtual void _t72();
    virtual void _t73();
    virtual void _t74();
    virtual void _t75();
    virtual void _t76();
    virtual void _t77();
    virtual void _t78();
    virtual void _t79();
    virtual void _t80();
    virtual void _t81();
    virtual void _t82();
    virtual void _t83();
    virtual void _t84();
    virtual void _t85();
    virtual void _t86();
    virtual void _t87();
    virtual void _t88();
    virtual void _t89();
    virtual void _t90();
    virtual void _t91();
    virtual void _t92();
    virtual FilterResult *getResult();
};

struct ObjectFull
{
    float m_00[14];
    float m_x38;
    float m_y3C;
    unsigned char m_40[536];
    FilterSource *m_258;
};

class Rva005997CD
{
public:
    ObjectID rva00599870(const Vec2 *pos, bool flag);
private:
    ListNode *m_list;
};

// ?rva00599870@Rva005997CD@@QAEW4ObjectID@@PBVVec2@@_N@Z present-unmatched
ObjectID Rva005997CD::rva00599870(const Vec2 *pos, bool flag)
{
    ListNode *head = m_list;
    float bestDist = 0.0f;
    ObjectID best = INVALID_OBJECT_ID;
    for (ListNode *node = head->next; node != head; node = node->next) {
        Object *obj = TheGameLogic->findObjectByID(node->id);
        if (obj != 0) {
            ObjectFull *full = (ObjectFull *)obj;
            FilterResult *res = full->m_258->getResult();
            if (!res->isValid()) {
                if (!obj->testStatus((ObjectStatusTypes)0x5A) || flag) {
                    float dx = pos->x - full->m_x38;
                    float dy = pos->y - full->m_y3C;
                    float d2 = dx * dx + dy * dy;
                    if (bestDist > d2 || (obj ? (best == INVALID_OBJECT_ID) : (best == INVALID_OBJECT_ID))) {
                        bestDist = d2;
                        best = node->id;
                    }
                }
            }
        }
    }
    return best;
}
