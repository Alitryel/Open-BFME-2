// cl: /O1 /MD
// ??0Rva0013107A@@QAE@XZ @ 0x0013107A (85B), unlock lane: ctor stores vtable at +0 then byte0 +8 zeros +6 ones +0x7fffffff +3 zeros +2 +0. Callers 0x00131BAE 0x00131C74 0x00131D65.

class Rva0013107A
{
public:
    virtual ~Rva0013107A();
    Rva0013107A();
    unsigned char m_04;
    char _pad05[3];
    int m_08;
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
    int m_34;
    int m_38;
    int m_3c;
    int m_40;
    int m_44;
    int m_48;
    int m_4c;
    int m_50;
    int m_54;
};

Rva0013107A::Rva0013107A()
    : m_04(0)
    , m_08(0)
    , m_0c(0)
    , m_10(0)
    , m_14(0)
    , m_18(0)
    , m_1c(0)
    , m_20(0)
    , m_24(0)
    , m_28(1)
    , m_2c(1)
    , m_30(1)
    , m_34(1)
    , m_38(1)
    , m_3c(1)
    , m_40(0x7fffffff)
    , m_44(0)
    , m_48(0)
    , m_4c(0)
    , m_50(2)
    , m_54(0)
{
}
