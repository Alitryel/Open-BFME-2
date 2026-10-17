// ??0LocomotorTemplate@@QAE@XZ @0x001E4ABE 754B
// LocomotorTemplate default constructor: the class of the rowed dtor
// 0x001E4DB0, copy ctor 0x001E4DEB, copy assignment 0x001E3955 and validate
// 0x001E38B9 (vtable 0x007DE8B4, 0x154 bytes, as LocomotorStore's
// parseLocomotorTemplateDefinition 0x001E8A94 allocates it). WB 0xADBAE0 plus
// the BFME1 a7c38d3b donor Locomotor.cpp constructor give the semantic lead,
// retail/WB establish every field. The native Locomotor ctor 0x1E449A
// consumes template +58/+60/+C4/+C8; m_2C/m_44/m_50 are integer frame counts
// from 0x00DBA4E4, not floats. Field names past the ZH set are not recovered;
// +0x150 is the byte flag LocomotorSet::addLocomotor tests into the set's
// +0x15 and the rowed clone 0x001E67BF clears (default 0; +0x151 defaults
// to 1).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME1 donor a7c38d3b2597121f178ab5190b3062478823257d:
// game/GameEngine/Source/GameLogic/Object/Locomotor.cpp supplies the semantic
// LocomotorTemplate constructor lead; retail/WB establish every field below.
// The canonical Locomotor.cpp still declares the ZH layout of this class; its
// matched getLegalSurfaces reads template+10 rather than native+14.
#include "ascii_string.h"
extern int BfmeLogicFramesPerSecond;
class Rva001E3624 {
public:
    Rva001E3624() : next(0), isOverride(false), key(-1) {}
    virtual ~Rva001E3624();
    void *next;
    bool isOverride;
    int key;
};
class LocomotorTemplate : public Rva001E3624 {
public:
    LocomotorTemplate();
    virtual ~LocomotorTemplate();
private:
	AsciiString m_10;
	int m_14;
	float m_18;
	unsigned char m_1C;
	float m_20;
	float m_24;
	float m_28;
	int m_2C;
	int m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	int m_44;
	float m_48;
	float m_4C;
	int m_50;
	float m_54;
	float m_58;
	float m_5C;
	float m_60;
	float m_64;
	float m_68;
	float m_6C;
	int m_70;
	int m_74;
	int m_78;
	float m_7C;
	float m_80;
	float m_84;
	float m_88;
	float m_8C;
	float m_90;
	float m_94;
	float m_98;
	float m_9C;
	float m_A0;
	float m_A4;
	float m_A8;
	float m_AC;
	float m_B0;
	float m_B4;
	float m_B8;
	float m_BC;
	int m_C0;
	float m_C4;
	unsigned char m_C8;
	float m_CC;
	unsigned char m_D0;
	unsigned char m_D1;
	unsigned char m_D2;
	unsigned char m_D3;
	unsigned char m_D4;
	int m_D8;
	unsigned char m_DC;
	float m_E0;
	float m_E4;
	float m_E8;
	unsigned char m_EC;
	unsigned char m_ED;
	float m_F0;
	float m_F4;
	float m_F8;
	float m_FC;
	unsigned char m_100;
	float m_104;
	unsigned char m_108;
	unsigned char m_109;
	unsigned char m_10A;
	unsigned char m_10B;
	float m_10C;
	float m_110;
	float m_114;
	float m_118;
	float m_11C;
	float m_120;
	float m_124;
	float m_128;
	float m_12C;
	float m_130;
	float m_134;
	float m_138;
	unsigned char m_13C;
	float m_140;
	float m_144;
	float m_148;
	float m_14C;
	unsigned char m_150;
	unsigned char m_151;
};

LocomotorTemplate::LocomotorTemplate()
{
    m_14C = 1.0f;
    m_24 = 1.0f;
    m_30 = 0;
    m_4C = -1.0f;
    m_14 = 0;
    m_20 = 0.0f;
    m_18 = 1.0f;
    m_1C = 0;
    m_2C = BfmeLogicFramesPerSecond;
    m_34 = 0.0f;
    m_38 = 20.0f;
    m_3C = 0.2617993950843811f;
    m_40 = 3.1415927410125732f;
    m_44 = BfmeLogicFramesPerSecond;
    m_48 = 0.0f;
    m_50 = BfmeLogicFramesPerSecond;
    m_28 = 0.0f;
    m_54 = 99999.0f;
    m_70 = 0;
    m_74 = 1;
    m_78 = 7;
    m_58 = 0.0f;
    m_5C = 0.0f;
    m_60 = 1.0f;
    m_64 = 0.0f;
    m_7C = 0.5f;
    m_80 = 0.0f;
    m_6C = 0.0f;
    m_68 = 999999.0f;
    m_84 = 6.2831854820251465f;
    m_88 = 0.0f;
    m_8C = 0.0f;
    m_90 = 0.10000000149011612f;
    m_94 = 0.10000000149011612f;
    m_98 = 0.8999999761581421f;
    m_9C = 0.8999999761581421f;
    m_A8 = 0.0f;
    m_A0 = 0.0f;
    m_A4 = 3.4028234663852886e+38f;
    m_AC = 0.0f;
    m_B0 = 0.0f;
    m_B4 = 0.0f;
    m_B8 = 1.0f;
    m_BC = 0.0f;
    m_D2 = 0;
    m_D3 = 0;
    m_151 = 1;
    m_D1 = 0;
    m_D0 = 0;
    m_C0 = 0x7fffffff;
    m_D4 = 0;
    m_D8 = 0;
    m_DC = 0;
    m_E8 = 0.0f;
    m_E0 = 0.0f;
    m_E4 = 0.0f;
    m_C4 = 1.0f;
    m_C8 = 0;
    m_150 = 0;
    m_CC = 0.0f;
    m_EC = 0;
    m_ED = 0;
    m_F0 = 0.0f;
    m_F4 = 1.0f;
    m_F8 = 0.0f;
    m_FC = 0.0f;
    m_100 = 0;
    m_104 = 0.0f;
    m_108 = 0;
    m_109 = 0;
    m_10A = 1;
    m_10B = 0;
    m_10C = 0.0f;
    m_110 = 0.0f;
    m_114 = 0.0f;
    m_118 = 0.0f;
    m_11C = 0.0f;
    m_120 = 0.0f;
    m_124 = 200.0f;
    m_128 = 200.0f;
    m_12C = 0.07000000029802322f;
    m_130 = 0.003000000026077032f;
    m_134 = 1.0f;
    m_138 = 0.75f;
    m_13C = 0;
    m_140 = 0.0f;
    m_144 = 0.0f;
    m_148 = 0.5f;
}

