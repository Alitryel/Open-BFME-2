// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva001F9BA4@ParticleSystem@FXParticleSystem@@QAEXPAXH@Z
// Retail 0x001F9BA4..0x001F9C73 (207 bytes) RET8: the particle generation
// loop of an FX particle system. The slave system template is looked up by
// the name at +0x78 (none when empty); then, while the generator at +0xA4
// still accepts (virtual slot 4), each of the requested particles gets its
// start values from generateNewParticleStartValues (0x001F55A8, named by
// WorldBuilder) into a local Rva001F376E record and is emitted through this
// system's virtual slot 5 -- unless the system emits above ground only
// (+0x81) and the start position lies below the terrain height plus 0.01.
// Evidence: WorldBuilder twin 0x00B12C90 (unnamed; its callees named),
// retail offsets and callees. The method name is address-derived.
#include "ascii_string.h"

// The out-of-line non-throwing isEmpty body 0x00001E2F (as the sibling
// ParticleSystemManagerMappedTextureUVs.cpp binds it).
template <> bool StringBase<char>::isEmpty() const throw();

typedef float Real;
struct Coord3D;

class Rva001F376E
{
public:
	Rva001F376E();
	virtual ~Rva001F376E() {}
	float m_04, m_08, m_0c, m_10, m_14, m_18;
	float m_x;	// +0x1C
	float m_y;	// +0x20
	float m_z;	// +0x24
	float m_28, m_2c, m_30;
	int m_34;
	unsigned char m_38;
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};
extern ParticleSystemManager *TheParticleSystemManager;

class TerrainLogic
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0C(); virtual void v10(); virtual void v14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};
extern TerrainLogic *TheTerrainLogic;

class Rva001F9BA4Generator
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual bool canGenerate();
};

namespace FXParticleSystem {

class ParticleSystem
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual void v0C(); virtual void v10();
	virtual void emitParticle(Rva001F376E *info, void *context, ParticleSystemTemplate *slave, int flags);

	void rva001F9BA4(void *context, int count);
	void generateNewParticleStartValues(Rva001F376E *info, int index, int count);

private:
	unsigned char m_pad04[0x78 - 0x04];
	AsciiString m_slaveSystemName;		// +0x78
	unsigned char m_pad7c[0x81 - 0x7C];
	bool m_aboveGroundOnly;			// +0x81
	unsigned char m_pad82[0xA4 - 0x82];
	Rva001F9BA4Generator *m_generator;	// +0xA4
};

void ParticleSystem::rva001F9BA4(void *context, int count)
{
	ParticleSystemTemplate *slave = ((const StringBase<char> *)&m_slaveSystemName)->isEmpty() ? 0 : TheParticleSystemManager->findTemplate(m_slaveSystemName);
	Rva001F376E info;
	if (m_generator) {
		for (int i = 0; i < count; ++i) {
			if (!m_generator->canGenerate())
				break;
			generateNewParticleStartValues(&info, i, count);
			if (m_aboveGroundOnly) {
				Real height = info.m_z + 0.01f;
				if (!(height >= TheTerrainLogic->getGroundHeight(info.m_x, info.m_y, 0)))
					continue;
			}
			emitParticle(&info, context, slave, 0);
		}
	}
}

}
