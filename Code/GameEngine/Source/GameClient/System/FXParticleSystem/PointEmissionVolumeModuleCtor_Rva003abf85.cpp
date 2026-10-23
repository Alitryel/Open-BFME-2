// cl: -DNDEBUG -MD -GX- -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/System/FXParticleSystem

// Constructor-only slices preserve the retail multiple-inheritance layout
// without exposing it through the shared particle-system header.

// The shared base with FXParticleSystem.cpp's slot spellings.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *system, void *module_template );
	virtual void unusedVirtual() = 0;

private:
	unsigned int m_storage[ 4 ];
};

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class ParticleModuleCategorySlice
{
public:
	virtual void unusedVirtual() = 0;
};

class ParticleModuleSnapshotSlice
{
public:
	virtual void unusedVirtual() = 0;
};

template <int Category>
class DefaultParticleModule
	: public T1A1_005DD290,
	  public ParticleModuleCategorySlice,
	  public ParticleModuleSnapshotSlice
{
public:
	// Defined in ModuleCtorChainsB.cpp (0x003ABF54); the derived ctor calls it.
	DefaultParticleModule( void *system, void *module_template );
};

// FXParticleSystem.cpp's view: the copy constructor below installs the
// vtable that unit emits first, so this one must emit the same four slots.
class EmissionVolumeInfo : public ::Snapshot
{
public:
	EmissionVolumeInfo( const EmissionVolumeInfo &that )
		: m_flag( that.m_flag )
	{
	}

	// Out of line in FXParticleSystem.cpp (0x0049B47C), whose /O1 deleting
	// destructor calls it rather than inlining it.
	virtual ~EmissionVolumeInfo();
	virtual void LoadPostProcess();

	bool m_flag;
	virtual const char *GetSnapshotName();
	virtual void DoXfer( ::Xfer & );
};

class ModuleTemplateSlice
{
public:
	virtual void unusedVirtual() = 0;
};

class CategoryModuleTemplateInfoSlice
{
public:
	virtual void unusedVirtual() = 0;
};

class CategoryModuleTemplateSlice
	: public ModuleTemplateSlice, public CategoryModuleTemplateInfoSlice
{
};

class PointEmissionVolumeModuleTemplate
	: public CategoryModuleTemplateSlice, public EmissionVolumeInfo
{
};

class PointEmissionVolumeModule
	: public DefaultParticleModule<5>, public EmissionVolumeInfo
{
public:
	PointEmissionVolumeModule( TrackingPtr<ParticleSystem> &system,
		const PointEmissionVolumeModuleTemplate *module_template );
};

PointEmissionVolumeModule::PointEmissionVolumeModule(
	TrackingPtr<ParticleSystem> &system,
	const PointEmissionVolumeModuleTemplate *module_template )
	: DefaultParticleModule<5>( &system,
		const_cast<PointEmissionVolumeModuleTemplate *>( module_template ) ),
	  EmissionVolumeInfo( *module_template )
{
}

}
