// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD
// BFME1 ba7ddda7e8 WaterTracksRenderSystemInit.cpp supplies init semantics.
// Native000FE93B..000FE9C7 RET0 independently measures level+74, list10/14,
// strips18/1C, material8 and shaderC. Constructor FE2A3 already rowed182B;
// it only writes fields and cannot throw. Keep its existing BfmeThingSH name
// and native B8 extent rather than asserting a new name for the provider.
// NativeFE065..FE188 uses ECX, strips18/1C, resource pointers0/4 and
// index/vertex allocation plus write-lock loop, confirming ReAcquireResources.
// Reuse the donor's minimal material and shader call views. These avoid
// importing unrelated mapper dependencies into this initializer.
#include "ascii_string.h"
struct FeNode {unsigned char m_pad0[0x30];int m_30;unsigned char m_pad1[0x3c-0x34];unsigned char m_flag3c;unsigned char m_pad2[0x58-0x3d];float m_58;float m_5c;float m_60;float m_64;unsigned char m_pad3[0xb0-0x68];FeNode *m_next;FeNode *m_prev;};
class WaterTracksObj;
enum waveType {WaveTypePond,WaveTypeOcean};
class ShaderClass {
public:
 ShaderClass() : bits(0x10441b) {}
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 enum CullMode { CULL_MODE_DISABLE=0 };
 void Set_Cull_Mode(CullMode) {bits &= 0xffefffff;}
};
class VertexMaterialClass {
public:
 enum PresetType { PRESET_ZERO=0 };
 static VertexMaterialClass *Get_Preset(PresetType);
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct WaterTracksLevelView { char unknown00[0x74];float level; };
class BfmeThingSH {
public:
 BfmeThingSH() throw();
 unsigned char unknown00[0xb0];BfmeThingSH *next,*prev;
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
void WaterTracksRenderSystem::init()
{
 stripX=2;stripY=2;
 level=reinterpret_cast<WaterTracksLevelView *>(TheWritableGlobalData)->level;
 ReAcquireResources();
 material=VertexMaterialClass::Get_Preset((VertexMaterialClass::PresetType)0);
 shader=ShaderClass::_PresetAlphaShader;
 shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
 if(m_head14 || m_tail10)return;
 int i=0;
 while(i<2000) {
  FeNode *mod=(FeNode *)new BfmeThingSH;
  if(!mod)break;
  mod->m_prev=0;
  mod->m_next=m_head14;
  if(m_head14)m_head14->m_prev=mod;
  ++i;
  m_head14=mod;
 }
}
