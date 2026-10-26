// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD
// BF1 WaterTracksRenderSystem source and native new(0x2c) at 7FD0D
// followed by FE90D prove this is the WaterTracksRenderSystem constructor.
// Target member offsets agree with the separately verified init FE93B.
#include "ascii_string.h"
struct FeNode {unsigned char m_pad0[0x30];int m_30;unsigned char m_pad1[0x3c-0x34];unsigned char m_flag3c;unsigned char m_pad2[0x58-0x3d];float m_58;float m_5c;float m_60;float m_64;unsigned char m_pad3[0xb0-0x68];FeNode *m_next;FeNode *m_prev;};
class WaterTracksObj;
class VertexMaterialClass;
enum waveType {WaveTypePond,WaveTypeOcean};
class ShaderClass {
public:
 ShaderClass() : bits(0x10441b) {}
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 enum CullMode { CULL_MODE_DISABLE=0 };
 void Set_Cull_Mode(CullMode) {bits &= 0xffefffff;}
};
class WaterTracksRenderSystem {
public:
 WaterTracksRenderSystem();
 void init();void ReAcquireResources();
 WaterTracksObj *bindTrack(waveType);
 void rva000FE188();
 __declspec(noinline) FeNode *rva000FE207(const float *,const float *,int);
 void *vertexBuffer,*indexBuffer;
 VertexMaterialClass *material;
 ShaderClass shader;
 FeNode *m_tail10,*m_head14;
 int stripX,stripY,batch;
 float level;
 AsciiString filename;
};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
WaterTracksRenderSystem::WaterTracksRenderSystem() {
 m_tail10=0;
 m_head14=0;
 indexBuffer=0;
 material=0;
 vertexBuffer=0;
 stripX=2;
 stripY=2;
 batch=0;
 TheWaterTracksRenderSystem=this;
}
