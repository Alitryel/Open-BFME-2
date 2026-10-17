// ?rva001E68D7@Locomotor@@QAEXXZ
// partial score=0.078 date=2026-10-17
// Native1E685F..1E68D7 RET12; WB ADF040 and owned1E702E forwarder
// establish the same receiver and matrix-copy/turn/pivot sequence. The source
// matrix begins at object+08 and three16-byte rows populate receiver+68.
// Row setters copy four words each; whole-matrix assignment emits REP MOVS.
// The existing address-derived three-word signature is retained: objectWord
// is the first caller pointer and the other words are passed as pointer bits
// to the now-owned turn/pivot worker. Original API type spelling is unproven.
// Row storage/layout and complete calls are target evidence; no donor layout
// or class extent is claimed.
// cl: /O1 /DNDEBUG /MD
class Object; struct Coord3D;
float normalizeAngle(float);
float Cos(float);
float Sin(float);
float fabs(float);
float _atan2f(float,float);

struct Coord3D {
    float x;
    float y;
    float z;
    float GetLengthEstimate2D() const;
};

class Object {
public:
    void rva0028AE6D();
};

class Locomotor {
public:
    float getMaxTurnRate(Object*) const;
    float getMaxSpeed(Object*) const;
    void rva001E68D7();
};

class Rva001E685F {
public:
    void rva001E685F(int,int,int);
    char prefix[0x68];
    unsigned int matrix[12];
};

class Rva001E46E1 {
public:
    float rva001E46E1(Object*);
    float rva001E4845(Object*);
    void rva001E56DC(Object*, const Coord3D*, float, float*);
};

class Rva001E6007 {
public:
    void rva001E6007(unsigned int, unsigned int, float, float);
};

void Locomotor::rva001E68D7()
{
    Object* obj = *(Object**)((char*)this - 4 + 8);
    const Coord3D* pos = (const Coord3D*)this;
    float arg2 = *(float*)((char*)this - 4 + 12);
    float arg3 = *(float*)((char*)this - 4 + 20);

    float relAngle = ((Rva001E46E1*)this)->rva001E46E1(obj);

    float dx = pos->x - ((float*)obj)[0x38/4];
    float dy = pos->y - ((float*)obj)[0x3c/4];
    float angle;
    {
        float tdy = dy;
        float tdx = dx;
        angle = _atan2f(tdy, tdx);
    }
    float rel = normalizeAngle(angle - relAngle);

    float maxSpeed = getMaxSpeed(obj);
    if ((maxSpeed < arg3) ? true : true) {
        *(volatile float*)&arg3 = maxSpeed;
    }

    void* ow = *(void**)((char*)obj + 4);
    bool turn = (*(int*)((char*)ow + 0xd8) != 0);
    if (turn) {
        Coord3D v;
        v.x = ((float*)this)[0x14/4] - ((float*)obj)[0x38/4];
        v.y = ((float*)this)[0x18/4] - ((float*)obj)[0x3c/4];
        v.z = ((float*)this)[0x1c/4] - ((float*)obj)[0x40/4];
        float len = v.GetLengthEstimate2D();
        if (len > ((float*)obj)[0x140/4] && arg2 > ((float*)obj)[0x144/4])
            turn = false;
    }

    float savedAngle;
    {
        float t = ((float*)this)[0x40/4];
        savedAngle = t;
    }

    if ((turn ? true : false)) {
        if (fabs(rel) > ((float*)obj)[0x148/4] * 3.1415927f) {
            if (!(*(unsigned int*)((char*)obj + 0x11c) & 0x10000000)) {
                *(unsigned int*)((char*)obj + 0x11c) |= 0x10000000;
                obj->rva0028AE6D();
            }
            *(unsigned char*)((char*)this + 0x44) |= 0x80;
        } else {
            if (*(unsigned char*)((char*)obj + 0x11f) & 0x10) {
                *(unsigned char*)((char*)obj + 0x11f) &= 0xef;
                obj->rva0028AE6D();
            }
            *(unsigned char*)((char*)this + 0x44) &= 0x7f;
        }
    } else {
        if (*(unsigned char*)((char*)obj + 0x11f) & 0x10) {
            *(unsigned char*)((char*)obj + 0x11f) &= 0xef;
            obj->rva0028AE6D();
        }
        *(unsigned char*)((char*)this + 0x44) &= 0x7f;
    }

    if ((*(unsigned int*)((char*)this + 0x44) >> 7) & 1)
        angle = normalizeAngle(angle - 3.1415927f);

    Coord3D out;
    {
        float px = ((float*)obj)[0x38/4];
        float py = ((float*)obj)[0x3c/4];
        px = px + Cos(angle) * 10.0f;
        py = py + Sin(angle) * 10.0f;
        out.x = px;
        out.y = py;
        out.z = ((float*)obj)[0x40/4];
    }

    ((Rva001E685F*)this)->rva001E685F((int)obj, (int)&out, 0);

    float newSpeed = ((Rva001E46E1*)this)->rva001E4845(obj);
    if (newSpeed < savedAngle)
        rel *= 0.5f;

    if (maxSpeed > 0.0001f) {
        float maxTurn = getMaxTurnRate(obj);
        float t = (maxTurn * 3.5f) / 57.29578f;
        if (t > 57.29578f)
            t = 57.29578f;
        arg3 = (1.0f - t) * arg3;
        if (*(unsigned char*)((char*)obj + 0x13c)) {
            if ((*(unsigned int*)((char*)this + 0x44) >> 7) & 1) {
                unsigned int mc = *(unsigned int*)((char*)obj + 0x11c);
                if ((mc >> 5) & 1 || (mc >> 6) & 1)
                    arg3 = 0.0f;
            }
        }
        ((Rva001E6007*)this)->rva001E6007((unsigned int)obj, (unsigned int)arg2, arg3, arg3);
    }
}
