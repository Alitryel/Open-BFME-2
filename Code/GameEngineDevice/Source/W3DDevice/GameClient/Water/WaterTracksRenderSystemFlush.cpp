// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /DEXTENDED_STATS /Ireference/shims/bfmestages /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// platformsdk
// dxsdk
// Keep the existing vector/matrix helper providers and their link-view ABI.
#include "../../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// BFME1 9cbfb551fe20 WaterTracksRenderSystem_flush.cpp semantic donor.
// Native10004D..1001D5 RET4: system slots0/8/C/10/20 and node4/30/B0
// agree with the independently matched bindTrack/init/update/save units.
// Target editor flag85 and stats water-disable guard are native deltas.
#include "ascii_string.h"
// Shutdown only needs the resource refcount interface. Importing dx8wrapper
// also defines the material class, conflicting with init's small call view.
#include "refcount.h"
#define Matrix4x4 Matrix4
#include "matrix3d.h"
class TextureBaseClass;
class DX8VertexBufferClass;
class RenderInfoClass;
class VertexMaterialClass;
class ShaderClass {
public:
 ShaderClass() : bits(0x10441b) {}
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 enum CullMode { CULL_MODE_DISABLE=0 };
 void Set_Cull_Mode(CullMode) {bits &= 0xffefffff;}
};
class WaterTracksObj {
public:
 char unknown00[4]; TextureBaseClass *texture;
 char unknown08[0x30-8]; int type;
 char unknown34[8]; bool bound; char unknown3d[0xb0-0x3d]; WaterTracksObj *next;
 int render(DX8VertexBufferClass *,int,RenderInfoClass &);
};
struct FeNode;
class BfmeThingSH {
public:
 void bfmeResetSH();
 // ?BfmeThingSH::~BfmeThingSH present-unmatched
 // Local deletion view delegates cleanup to the existing FE290 provider.
 // The inline view is not an additional recovery or pin.
 ~BfmeThingSH() { bfmeResetSH(); }
};
class WaterTracksRenderSystem {
public:
 void *vertexBuffer,*indexBuffer;
 VertexMaterialClass *material;
 ShaderClass shader;
 FeNode *m_tail10,*m_head14;
 int stripX,stripY,batch;
 float level; AsciiString filename;
 void rva000FE1AC();
 void releaseTrack(FeNode *);
 void shutdown();
 ~WaterTracksRenderSystem();
 void flush(RenderInfoClass &);
};
// BFME1/ZH shutdown donor. Native FF448..FF4D6 clears used after moving
// unbound nodes via the independently rowed releaseTrack FE001; node cleanup
// calls existing BfmeThingSH::bfmeResetSH FE290 before the native delete worker.
// The three resource pointers use native base+4 counters and virtual slot0.
void WaterTracksRenderSystem::shutdown()
{
 WaterTracksObj *mod=reinterpret_cast<WaterTracksObj *>(m_tail10);
 while(mod) {
  WaterTracksObj *next=mod->next;
  if(!mod->bound)releaseTrack(reinterpret_cast<FeNode *>(mod));
  mod=next;
 }
 m_tail10=0;
 while(m_head14) {
  WaterTracksObj *mod=reinterpret_cast<WaterTracksObj *>(m_head14);
  WaterTracksObj *next=mod->next;
  delete reinterpret_cast<BfmeThingSH *>(m_head14);
  m_head14=reinterpret_cast<FeNode *>(next);
 }
 if(indexBuffer) { reinterpret_cast<RefCountClass *>(indexBuffer)->Release_Ref(); indexBuffer=0; }
 if(material) { reinterpret_cast<RefCountClass *>(material)->Release_Ref(); material=0; }
 if(vertexBuffer) { reinterpret_cast<RefCountClass *>(vertexBuffer)->Release_Ref(); vertexBuffer=0; }
}
// BFME1/ZH destructor body; target FF4D6..FF50D RET0/55B establishes the
// owning AsciiString member at28 and its releaseBuffer worker36410.
WaterTracksRenderSystem::~WaterTracksRenderSystem()
{
 shutdown();
 material=0;
}
