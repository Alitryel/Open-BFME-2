// ?rva006F69D0@Rva006F69D0@@QAEXPBUSrc006F69D0@@GI@Z
// partial score=0.95 date=2026-10-04
// ?rva006F69D0@Rva006F69D0@@QAEXPBUSrc006F69D0@@GI@Z
// partial score=0.95 date=2026-09-30
// ?rva006F69D0@Rva006F69D0@@QAEXPBUSrc006F69D0@@GI@Z
// partial score=0.95 date=2026-09-30
// cl: /O2 /DNDEBUG /MD /Op
extern float BfmeZeroRange;
struct Src006F69D0 {
    char m_pad00[4];
    unsigned int m_flags;
    char m_pad08[8];
    char m_field10[4];
    char m_pad14[20];
    char m_field28[4];
    char m_pad2C[4];
    float m_float30;
    char m_pad34[4];
    unsigned short m_word38;
    char m_pad3A[2];
    unsigned int m_ptr3C;
};
struct Dst006F69D0 {
    unsigned int m_00;
    void *m_04;
    void *m_08;
    void *m_0C;
    float m_10;
    unsigned int m_14;
    unsigned short m_18;
    unsigned short m_1A;
};
class Rva006F69D0 {
public:
    void rva006F69D0(const Src006F69D0 *src, unsigned short w, unsigned int d);
};
// ?rva006F69D0@Rva006F69D0@@QAEXPBUSrc006F69D0@@GPAU02@@Z present-unmatched
void Rva006F69D0::rva006F69D0(const Src006F69D0 *src, unsigned short w, unsigned int d)
{
    Dst006F69D0 *dst = (Dst006F69D0 *)this;
    dst->m_18 = w;
    dst->m_14 = src->m_flags;
    dst->m_00 = d;
    dst->m_1A = src->m_word38;
    if (src->m_flags & 4)
        dst->m_04 = (void *)&src->m_field10;
    else
        dst->m_04 = 0;
    if (src->m_flags & 8)
        dst->m_08 = (void *)&src->m_field28;
    else
        dst->m_08 = 0;
    if ((char)src->m_flags < 0)
        dst->m_0C = (void *)src->m_ptr3C;
    else
        dst->m_0C = 0;
    if (src->m_flags & 0x10)
        dst->m_10 = (src->m_flags ? src->m_float30 : src->m_float30);
    else
        dst->m_10 = BfmeZeroRange;
}
