// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?setMouseText@Mouse@@QAEXVUnicodeString@@PBU_MouseSixteen@@1@Z, retail 0x001EEBD5, 118 bytes.
// Zero Hour's and BFME1's Mouse::setMouseText (BFME1 0x005A5950, same
// signature; the text goes to the cursor display string, then the optional
// colour and drop colour are copied). Evidence: Mouse neighbours
// (same /O1 area, +0x4Fxx offsets near rva001EEA6D); by-value wide-string temp
// via rowed private StringBase<G> copyctor plus rowed releaseBuffer EH
// cleanup (GadgetStaticText/MouseRva001EEC4B friend pattern); virtual slot 1
// on +0x4FA8; guarded 16-byte copies into +0x4FAC/+0x4FBC.
class Mouse;
#include "unicode_string.h"
struct RGBAColorInt { int v[4]; };
struct MouseFontThunk {
    virtual void slot0();
    virtual void setText(UnicodeString text);
};
class Mouse {
    char m_pad[0x4FA8];
    MouseFontThunk *m_4FA8;
    RGBAColorInt m_4FAC;
    RGBAColorInt m_4FBC;
public:
    void setMouseText(UnicodeString text, const RGBAColorInt *lhs, const RGBAColorInt *rhs);
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void Mouse::setMouseText(UnicodeString text, const RGBAColorInt *lhs, const RGBAColorInt *rhs)
{
    if (m_4FA8) {
        _ReadWriteBarrier();
        m_4FA8->setText(text);
        if (lhs)
            m_4FAC = *lhs;
        if (rhs)
            m_4FBC = *rhs;
    }
}
