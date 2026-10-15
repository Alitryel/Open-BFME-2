// cl: /MD
//
// The 0x001E3F08 helper is owned by Rva001E4073Ratio.cpp, where its
// caller needs the visible definition for register-use analysis.
// The retained 0x001E3F2E sibling computes [esp+4]->+0x258->+0x1f8
// times [this+4]->+0x54 times global 0x00DBA4F8 in x87 instructions.
// Owner identity unproven, honest Rva name.

extern float g_secondsPerLogicFrame;

struct Rva001E3F08MidA
{
	int m_pad00[10]; // +0x00..+0x27
	float m_val28; // +0x28
	int m_pad2C[10]; // +0x2C..+0x53
	float m_val54; // +0x54
};

struct Rva001E3F08MidB
{
	int m_pad00[126]; // +0x00..+0x1F7
	float m_val1F8; // +0x1F8
};

struct Rva001E3F08Arg
{
	int m_pad00[150]; // +0x00..+0x257
	Rva001E3F08MidB *m_p258; // +0x258
};

class Rva001E3F08
{
public:
	float rva001E3F2E(Rva001E3F08Arg *p);
private:
	int m_pad00; // +0x00
	Rva001E3F08MidA *m_p04; // +0x04
};

// ?rva001E3F2E@Rva001E3F08@@QAEMPAURva001E3F08Arg@@@Z, retail 0x001E3F2E,
// 31 bytes: the same product over the [this+4]->+0x54 field (sibling after
// the 0x001E3F27 getter). Owner identity unproven.
float Rva001E3F08::rva001E3F2E(Rva001E3F08Arg *p)
{
	return p->m_p258->m_val1F8 * m_p04->m_val54 * g_secondsPerLogicFrame;
}
