// cl: /MD
// ?set@Rva001F3C20Slot@@QAEXPBVRva0055A88BDwordField@@@Z @0x001F3C20 35B,
// ?set@Rva001F3C43Slot@@QAEXPBURva001F3C43Arg@@@Z @0x001F3C43 29B,
// ?set@Rva001F3C60Slot@@QAEXABVAsciiString@@@Z @0x001F3C60 11B.
// Three consecutive nullable setters writing +0xb0/+0xb4/+0xb8: 0x001F3C20 calls
// rowed ?get@Rva0055A88BDwordField@@QBEHXZ (+0x100) or zeroes +0xb0; 0x001F3C43
// copies arg+0x74 or zeroes +0xb4 (unblocks W3DTruckDraw teardown 0x000CB5C3 and
// named dtor 0x000CDE73); 0x001F3C60 tail-jumps the canonical
// void StringBase<char>::set(copy) worker at 0x366F0, at +0xb8.
// No return value is established by that worker; the earlier reference
// return and AsciiString assignment spelling were inferred incorrectly. Callers at 0x000C7427/0x000CE8A2,
// 0x000CB5E2/0x000CB61E/0x000CB65A, 0x001E227F. Honest Rva names; /O1 for the
// and [m],0 plus add+ jmp idioms.
class Rva0055A88BDwordField {
public:
    int get() const;
};
struct Rva001F3C43Arg {
    char m_pad[0x74];
    int m_value;
};
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Rva001F3C20Slot {
public:
    void set(const Rva0055A88BDwordField *arg);
    char m_lead[0xb0];
    int m_value;
};
class Rva001F3C43Slot {
public:
    void set(const Rva001F3C43Arg *arg);
    char m_lead[0xb4];
    int m_value;
};
class Rva001F3C60Slot {
public:
    void set(const AsciiString &other);
    char m_lead[0xb8];
    AsciiString m_value;
};
void Rva001F3C20Slot::set(const Rva0055A88BDwordField *arg)
{
    if (arg)
        m_value = arg->get();
    else
        m_value = 0;
}
void Rva001F3C43Slot::set(const Rva001F3C43Arg *arg)
{
    if (arg)
        m_value = arg->m_value;
    else
        m_value = 0;
}
void Rva001F3C60Slot::set(const AsciiString &other)
{
    ((StringBase<char> *)&m_value)->set(*(const StringBase<char> *)&other);
}
