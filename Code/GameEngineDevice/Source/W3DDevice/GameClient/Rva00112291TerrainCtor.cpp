// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00112DBE,00112ED3), 277B, RET0 returning this. The array-new
// caller at 000E1A39 supplies the D4-byte stride and binds this constructor
// to the existing Rva00112291TerrainOwner destructor and delete helper.
// BFME1 a7c38d3b2597121f178ab5190b3062478823257d:
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DTerrainBackgroundConstructor.cpp provides the initialization guide.
// BFME2 updateCenter proves three cull states and the six-float bounds;
// its destructor proves the four texture-reference slots at 34..40.
// The donor's compiler barrier is unnecessary with these visible members.
struct TerrainBackgroundBounds {
    float centerX, centerY, centerZ, extentX, extentY, extentZ;
    TerrainBackgroundBounds() {
        centerX = 0.0f; centerY = 0.0f; centerZ = 0.0f;
        extentX = 0.0f; extentY = 0.0f; extentZ = 0.0f;
    }
};
class BfmeResetResource;
class BfmeResetTextureRef {
public:
    BfmeResetTextureRef() : pointer(0) {}
private:
    BfmeResetResource *pointer;
};
class Rva00112291TerrainOwner {
public:
    Rva00112291TerrainOwner();
private:
    int cullStatus[3];
TerrainBackgroundBounds bounds;
void *m_24; int m_28; void *m_2C; int m_30;BfmeResetTextureRef m_34,m_38,m_3C,m_40;int m_44,m_48,m_4C,m_50,m_54,m_58,m_5C;
char m_60,m_61,m_62;
float m_64;
int m_68,m_6C,m_70,m_74,m_78,m_7C,m_80;
char m_84;
int m_88,m_8C,m_90,m_94;
float m_98,m_9C,m_A0,m_A4;
int m_A8,m_AC,m_B0,padB4,m_B8,padBC,m_C0,padC4,m_C8;
float m_CC;
int m_D0;
};
Rva00112291TerrainOwner::Rva00112291TerrainOwner() : m_24(0),m_28(0),m_2C(0),m_30(0) {

m_44 = 1;
m_48 = 0;
m_4C = 0;
m_50 = 0;
m_54 = 0;
m_58 = 1;
m_5C = 0;
m_60 = 0;
m_61 = 0;
m_62 = 0;
m_64 = 0.0f;
m_68 = 0;
m_6C = 0;
m_70 = 0;
m_74 = 0;
m_78 = 0;
m_7C = 0;
m_80 = 0;
m_84 = 0;
m_88 = 1;
m_8C = 1;
m_90 = 1;
m_94 = 1;
m_C8 = 0;
m_CC = 0.0f;
m_D0 = 0;
for(int i=0;i<3;++i) cullStatus[i]=0;
m_98 = 500.0f;
m_9C = 900.0f;
m_A0 = 1500.0f;
m_A4 = 2000.0f;
m_A8 = 0;
m_B0 = 0;
m_B8 = 0;
m_AC = 0;
m_C0 = 0;
}
