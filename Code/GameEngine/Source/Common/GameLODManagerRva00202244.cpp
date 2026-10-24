// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00202244@Rva00DFE144Globals@@QAEXHPAVOptionPreferences@@@Z, retail
// 0x00202244..0x002022E9 (165 bytes, RET 8): a method of the object at
// 0x00DFE144 (TheGameLODManager, viewed as Rva00DFE144Globals, the spelling
// its caller AptOptions pinned). It writes the 0x4C-byte preset the first
// argument selects into nine OptionPreferences settings (rowed setSetting):
// the +0x00, +0x34, +0x04 and +0x10 words; 2 when the +0x14 flag is set, else
// the +0x15 flag; the +0x18 word; the +0x2C mode mapped 2 -> 0, 1 -> 1,
// anything else -> 2; and the +0x38 and +0x40 words.

class OptionPreferences
{
public:
	void setSetting(int index, int value);
};

struct Rva00202244Preset
{
	int m_modelLOD;
	int m_effectsLOD;
	unsigned char m_pad08[0x10 - 0x08];
	int m_shadowLOD;
	bool m_14;
	bool m_15;
	unsigned char m_pad16[0x18 - 0x16];
	int m_waterLOD;
	unsigned char m_pad1C[0x2C - 0x1C];
	int m_textureReduction;
	unsigned char m_pad30[0x34 - 0x30];
	int m_animationDetail;
	int m_38;
	unsigned char m_pad3C[0x40 - 0x3C];
	int m_decalLOD;
	unsigned char m_pad44[0x4C - 0x44];
};

class Rva00DFE144Globals
{
public:
	void rva00202244(int preset, OptionPreferences *prefs);
private:
	Rva00202244Preset m_presets[1];
};

void Rva00DFE144Globals::rva00202244(int preset, OptionPreferences *prefs)
{
	const Rva00202244Preset &lodInfo = m_presets[preset];
	prefs->setSetting(0, lodInfo.m_modelLOD);
	prefs->setSetting(1, lodInfo.m_animationDetail);
	prefs->setSetting(2, lodInfo.m_effectsLOD);
	prefs->setSetting(3, lodInfo.m_shadowLOD);
	prefs->setSetting(4, lodInfo.m_14 ? 2 : (lodInfo.m_15 != 0));
	prefs->setSetting(5, lodInfo.m_waterLOD);
	prefs->setSetting(6, lodInfo.m_textureReduction == 2 ? 0 : (lodInfo.m_textureReduction == 1 ? 1 : 2));
	prefs->setSetting(7, lodInfo.m_38);
	prefs->setSetting(8, lodInfo.m_decalLOD);
}
