// Subsystem literal name getters, fourth unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
// Each body returns a pointer to a NUL-terminated class-name string in .rdata
// with exactly one vtable (body-VA) reference behind a C3 predecessor;
// verify_string_refs re-reads the string.
// No // cl: line (defaults match the frameless 6-byte shape).

#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

BFME_LITERAL_NAME_GETTER(Rva00271892Named, "TintEnvelope")
BFME_LITERAL_NAME_GETTER(Rva002B6476Named, "RegionAwardDispute")
BFME_LITERAL_NAME_GETTER(Rva0033F517Named, "AIAttackSquadState")
BFME_LITERAL_NAME_GETTER(Rva0033FB6DNamed, "AttackHordeStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0033FC04Named, "AttackPositionHordeStateMachine")
BFME_LITERAL_NAME_GETTER(Rva00340C27Named, "AIAttackMeleeEngageState")
BFME_LITERAL_NAME_GETTER(Rva00340D6ANamed, "AIFollowPathAsTeamState")
BFME_LITERAL_NAME_GETTER(Rva00345CFANamed, "AIAttackMoveToState")
BFME_LITERAL_NAME_GETTER(Rva00345F70Named, "AIAttackFollowWaypointPathState")
BFME_LITERAL_NAME_GETTER(Rva0034B172Named, "AIAttackState")
BFME_LITERAL_NAME_GETTER(Rva00354EF6Named, "AiOrdersManager")
BFME_LITERAL_NAME_GETTER(Rva0035701FNamed, "AttackPriorityInfo")
BFME_LITERAL_NAME_GETTER(Rva00359E8DNamed, "TerrainResourceManager")
BFME_LITERAL_NAME_GETTER(Rva00362493Named, "GlowMaterial")
BFME_LITERAL_NAME_GETTER(Rva00362D66Named, "BuffInstance")
BFME_LITERAL_NAME_GETTER(Rva00367929Named, "GiantBirdDieState")
BFME_LITERAL_NAME_GETTER(Rva0036B8E0Named, "GiantBirdAIUpdate")
BFME_LITERAL_NAME_GETTER(Rva0036E55ENamed, "AIGroup")
BFME_LITERAL_NAME_GETTER(Rva00373411Named, "MineshaftPortalNetworkManager")
BFME_LITERAL_NAME_GETTER(Rva00373D0FNamed, "StealthUpdate")
BFME_LITERAL_NAME_GETTER(Rva00376A19Named, "ObjectTypes")
BFME_LITERAL_NAME_GETTER(Rva003908A1Named, "PhysicsBehavior")
BFME_LITERAL_NAME_GETTER(Rva0039143FNamed, "RadiusDecalUpdate")
BFME_LITERAL_NAME_GETTER(Rva003957C0Named, "CastleMemberBehavior")
BFME_LITERAL_NAME_GETTER(Rva0039C3A6Named, "ScoreKeeper")
BFME_LITERAL_NAME_GETTER(Rva003A25ABNamed, "TeamRelationMap")
// TeamFactory::GetSnapshotName is owned by RTS/TeamFactoryDtor.cpp.
BFME_LITERAL_NAME_GETTER(Rva003B03EDNamed, "GPUParticleSystemStorageModule")
// Rva003B3662 "Script" is Script::GetSnapshotName, rowed under its real
// name from Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptDtor.cpp.
BFME_LITERAL_NAME_GETTER(Rva003B40FANamed, "ScriptGroup")
BFME_LITERAL_NAME_GETTER(Rva003B7745Named, "ScriptList")
BFME_LITERAL_NAME_GETTER(Rva003B9124Named, "LivingWorldCampaignManager")
BFME_LITERAL_NAME_GETTER(Rva003F3418Named, "LivingWorldRegion")
BFME_LITERAL_NAME_GETTER(Rva003F6A8BNamed, "LivingWorldBattle")
BFME_LITERAL_NAME_GETTER(Rva003F9CCCNamed, "LivingWorldEyeTower")
BFME_LITERAL_NAME_GETTER(Rva003FD374Named, "DelayedRegionFlashModule")
BFME_LITERAL_NAME_GETTER(Rva00403A5BNamed, "AttributeModifierPoolUpdate")
BFME_LITERAL_NAME_GETTER(Rva00405411Named, "VictorySystem")
BFME_LITERAL_NAME_GETTER(Rva005C43C9Named, "LivingWorldBuildingNuggetIncreaseCommandPoints")
BFME_LITERAL_NAME_GETTER(Rva00351753Named, "AIStateMachine")
BFME_LITERAL_NAME_GETTER(Rva0037BB4DNamed, "GameInfo")
BFME_LITERAL_NAME_GETTER(Rva003A5784Named, "ParticleWindModuleInfo")
BFME_LITERAL_NAME_GETTER(Rva003ABE7FNamed, "RenderObjectUpdateModule")
BFME_LITERAL_NAME_GETTER(Rva00409353Named, "CreateAHeroData")
