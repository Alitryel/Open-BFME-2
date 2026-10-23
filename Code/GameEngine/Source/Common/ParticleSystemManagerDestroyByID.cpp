// cl: /MD /EHsc
//
// ParticleSystemManager::destroyParticleSystemByID, retail 0x001F5B79 (69
// bytes), after Zero Hour's GameEngine/Source/GameClient/System/
// ParticleSys.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): find the system and destroy it.
// BFME 2 (target evidence) finds it through the rowed findParticleSystemByID
// 0x001F5B0A, which returns a 12-byte handle by value (see
// ParticleSystemManagerFindByID.cpp); the temporary is released only when it
// holds a system, through the rowed handle release 0x0004CBC0 (the
// RvaSmartPtr12 view other units use for the same handle: W3DTruckDrawDtor,
// Rva0056224FCtor), and ParticleSystem::destroy is the rowed 0x001F462C.
enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem
{
public:
	void destroy();
};

// The handle findParticleSystemByID returns: the BfmeParticleSystemHandle
// class of ParticleSystemManagerFindByID.cpp. Its release is the rowed
// RvaSmartPtr12::rva0004CBC0, reached only when the handle holds a system.
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw(); // 0x0004CBC0
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
	}
	void *m_system;
	void *m_previous;
	void *m_next;
};

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

// ------------------------------------------------------------------------------------------------
void ParticleSystemManager::destroyParticleSystemByID(ParticleSystemID id)
{
	BfmeParticleSystemHandle sys = findParticleSystemByID(id);
	ParticleSystem *system = (ParticleSystem *)sys.m_system;
	if (system)
		system->destroy();
}
