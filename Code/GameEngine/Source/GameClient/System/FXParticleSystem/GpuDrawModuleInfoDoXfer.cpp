// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX

// GpuDrawModuleInfo::DoXfer, retail 0x0056390A (64B). BFME2-new class (no
// BFME1 donor). Member semantics from the writeINI field strings at
// 0x00563D3F: TotalFrames, FramesPerRow, DetailTexture, SpeedMultiplier,
// matching the default ctor's 1, 1, 0, 1.0f. Occupies the GpuDraw vtable
// (0xC1C1E8) slots 0xC/0x2C. Xfer declaration is the UpdateModuleXfer-proven
// spelling; Version1 resolves to the rowed 0x53EE.

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

#include "../../../../Include/Common/BfmeXfer.h"

// AsciiString with its inline nulling default, as retail's TU sees it: the
// default ctor (rowed 6B at 0x326BE6, `m_text = 0`) folds into the member
// slot with no out-of-line call, and the member transfers via ==AsciiString.
#include "ascii_string.h"

namespace FXParticleSystem
{

class GpuDrawModuleInfo
{
public:
    virtual void DoXfer(Xfer &xfer);
    virtual ~GpuDrawModuleInfo();

private:
    int m_totalFrames;
    int m_framesPerRow;
    AsciiString m_detailTexture;
    float m_speedMultiplier;
};

// ?DoXfer@GpuDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void GpuDrawModuleInfo::DoXfer(Xfer &xfer)
{
    xfer.Version1();
    xfer == m_totalFrames;
    xfer == m_framesPerRow;
    xfer == m_detailTexture;
    xfer == m_speedMultiplier;
}

}
