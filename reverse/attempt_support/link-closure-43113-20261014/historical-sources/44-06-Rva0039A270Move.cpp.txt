// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// Native 0x0039A270..0x0039A48E, 542 bytes; WB twin 0x00EC0F30.
// Member ABI: the receiver is unused and Object* is the single stack argument.
// Move eligible colliding objects outward from the source's bounding circle.
// Object argument and member ABI are also established at callers 0x0039A64F and 0x0039A970.
// Evidence and helper audit: reverse/attempt_evidence/crack-v-move-20261014.txt.
#include "Lib/Coord3D.h"
struct DisplacementCoord : Coord3D
{
    DisplacementCoord() {}
    DisplacementCoord(const Coord3D &r)
    {
        x = r.x;
        y = r.y;
        z = r.z;
    }
    ~DisplacementCoord() {}
    DisplacementCoord &Sub(const Coord3D &r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }
    DisplacementCoord &Scale(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
};
// Keep the final scalar copy in its own inline reference operation. MSVC 7.1
// then preserves retail's operand order when this height is added to delta.z.
inline void copyCoordinateComponent(float &out, const float &in) { out = in; }
typedef bool Bool;
typedef float Real;

class GeometryInfo
{
  public:
    GeometryInfo(const GeometryInfo &that);
    virtual ~GeometryInfo();
    float getBoundingCircleRadius() const { return m_radius14; }

  private:
    char m_pad00[0x10];
    float m_radius14;
    char m_pad18[0x5C - 0x18];
};

class Rva000421C8
{
  public:
    virtual ~Rva000421C8() {}
    virtual Bool allow(void *obj) = 0;
    virtual int getPlayerMask();
    Rva000421C8 *m_next;
};

class Rva00261603Filter : public Rva000421C8
{
  public:
    Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
    virtual Bool allow(void *obj);

  private:
    Coord3D m_position;
    const GeometryInfo &m_geom;
    Real m_angle;
    Bool m_desired;
};

class Object;

#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

class ThingTemplate
{
  public:
    char m_pad[0x108];
    unsigned char m_kind00;
    unsigned char m_kind01;
    unsigned char m_kind02;
    unsigned char m_kind03;
    unsigned char m_kind04;
    unsigned char m_kind05;
    unsigned char m_kind06;
    unsigned char m_kind07;
    unsigned char m_kind08;
    unsigned char m_kind09;
    unsigned char m_kind0A;
    unsigned char m_kind0B;
    unsigned char m_kind0C;
    unsigned char m_kind0D;
    unsigned char m_kind0E;
    unsigned char m_kind0F;
    unsigned char m_kind10;
};

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_AI = 1,
    CMD_FROM_DOZER = 2
};

class AICommandInterface
{
  public:
    void aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType src);
};

struct AIHolder
{
    char m_pad[0x20];
    AICommandInterface m_cmd;
};

class Slot114Module
{
  public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void slot021();
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060();
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual bool slot114();
};

class Object
{
  public:
    virtual ~Object();
    ThingTemplate *m_template04;
    char m_pad08[0x38 - 0x08];
    Coord3D m_pos38;
    float m_angle44;
    char m_pad48[0xA8 - 0x48];
    GeometryInfo m_geomA8;
    char m_padAfterGeom[0x258 - 0xA8 - 0x5C];
    AIHolder *m_ai258;
    void *rva0029439D();
};

class Rva0039A270MoveOwner
{
  public:
    void rva0039A270Move(Object *);
};
// ?rva0039A270Move@Rva0039A270MoveOwner@@QAEXPAVObject@@@Z
void Rva0039A270MoveOwner::rva0039A270Move(Object *src)
{
    if (!src)
        return;
    Coord3D pos;
    pos.x = src->m_pos38.x;
    pos.y = src->m_pos38.y;
    copyCoordinateComponent(pos.z, src->m_pos38.z);
    GeometryInfo gi(src->m_geomA8);
    Real radius = gi.getBoundingCircleRadius() * 1.1f;
    BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(
        &pos, radius, 3, &Rva00261603Filter(pos, gi, src->m_angle44, true), 0);
    for (Object *them = iter.next(); them; them = iter.next())
    {
        ThingTemplate *tmpl = them->m_template04;
        if (tmpl->m_kind0B & 2)
            continue;
        if (tmpl->m_kind10 & 0x40)
            continue;
        if (tmpl->m_kind0D & 1)
            continue;
        if (tmpl->m_kind07 & 0x10)
            continue;
        if (tmpl->m_kind00 & 4)
            continue;
        Slot114Module *mod = (Slot114Module *)them->rva0029439D();
        if (mod && mod->slot114())
            continue;
        AIHolder *holder = them->m_ai258;
        if (!holder)
            continue;
        DisplacementCoord delta = them->m_pos38;
        delta.Sub(src->m_pos38);

        if (delta.GetLength2D() > 0.0f)
        {
            delta.z = 0.0f;
            delta.normalize();
        }
        else
        {
            delta.x = 1.0f;
            delta.y = 0.0f;
            delta.z = 0.0f;
        }
        Real step = radius * 1.5f;
        delta.Scale(step);
        DisplacementCoord dest;
        dest.x = pos.x + delta.x;
        dest.y = pos.y + delta.y;
        dest.z = pos.z + delta.z;
        holder->m_cmd.aiMoveToPositionEvenIfSleeping(&dest, CMD_FROM_DOZER);
    }
}

#include <math.h>
inline float Coord3D::GetLength2D() const
{
    float a = x, b = y;
    return (float)sqrt(a * a + b * b);
}
inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f)
    {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}
