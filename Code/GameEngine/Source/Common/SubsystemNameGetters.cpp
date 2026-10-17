// Subsystem literal name getters: six-byte const members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated class-name string in
// .rdata. The vtable at each site carries the body at slot 2 (offset 8)
// behind a shared pair (slot 0 varies, slot 1 is 0xA9E440) and ahead of
// class-specific tails, closed by 0x5B5384 -- the Subsystem/Snapshot family
// pattern. Ported from Open-BFME-1
// (Code/GameEngine/Source/Common/LiteralNameGetters_01.cpp): the
// BFME_LITERAL_NAME_GETTER macro is verbatim; only the class names follow
// this tree's address-derived convention (identity unrecoverable from 6
// bytes, string carried in source where verify_string_refs re-reads it).
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

BFME_LITERAL_NAME_GETTER(Rva006254A0Named, "PartitionManager")
BFME_LITERAL_NAME_GETTER(Rva00065212Named, "ModuleData")
BFME_LITERAL_NAME_GETTER(Rva00041FC9Named, "GameLogic")
BFME_LITERAL_NAME_GETTER(Rva000420D6Named, "ModuleFactory")
BFME_LITERAL_NAME_GETTER(Rva0004C457Named, "GameClient")
BFME_LITERAL_NAME_GETTER(Rva0004CE28Named, "FXParticleSystemManager")
BFME_LITERAL_NAME_GETTER(Rva0004FA11Named, "Radar")
BFME_LITERAL_NAME_GETTER(Rva00063531Named, "W3DGhostObjectManager")
BFME_LITERAL_NAME_GETTER(Rva000647CENamed, "W3DBuffLogic")
BFME_LITERAL_NAME_GETTER(Rva000665B9Named, "TScorch")
BFME_LITERAL_NAME_GETTER(Rva0006CE6BNamed, "UNNAMED")
BFME_LITERAL_NAME_GETTER(Rva0006D054Named, "BaseHeightMapRenderObjClass")
BFME_LITERAL_NAME_GETTER(Rva00078B7DNamed, "W3DHordeModelDraw")
BFME_LITERAL_NAME_GETTER(Rva000822F7Named, "WaterRenderObjClass")
BFME_LITERAL_NAME_GETTER(Rva0008EFD2Named, "InGameUI")
BFME_LITERAL_NAME_GETTER(Rva001DD02BNamed, "Eva")
BFME_LITERAL_NAME_GETTER(Rva002AA3AFNamed, "Energy")
BFME_LITERAL_NAME_GETTER(Rva00091AACNamed, "W3DTerrainVisual")
BFME_LITERAL_NAME_GETTER(Rva000B1CDCNamed, "W3DDebrisDraw")
BFME_LITERAL_NAME_GETTER(Rva000B696BNamed, "EventParameter")
BFME_LITERAL_NAME_GETTER(Rva000B6DCCNamed, "LuaEventParameters")
BFME_LITERAL_NAME_GETTER(Rva001042C1Named, "Palantir")
BFME_LITERAL_NAME_GETTER(Rva001E3E56Named, "Locomotor")
BFME_LITERAL_NAME_GETTER(Rva001E70BCNamed, "LocomotorSet")
BFME_LITERAL_NAME_GETTER(Rva001EAE63Named, "LinearCampaign")
BFME_LITERAL_NAME_GETTER(Rva001EAE69Named, "LinearCampaignManager")
BFME_LITERAL_NAME_GETTER(Rva001FBEB1Named, "FXParticleSystem")
BFME_LITERAL_NAME_GETTER(Rva002086B7Named, "ScriptEngine")
BFME_LITERAL_NAME_GETTER(Rva00286F81Named, "FireLogicSystem")
BFME_LITERAL_NAME_GETTER(Rva002AE621Named, "Command")
BFME_LITERAL_NAME_GETTER(Rva0037DC84Named, "CarryoverUnit")
BFME_LITERAL_NAME_GETTER(Rva00414307Named, "ScoredKillEvaAnnouncer")
BFME_LITERAL_NAME_GETTER(Rva004E0777Named, "LivingWorldBuilding")
BFME_LITERAL_NAME_GETTER(Rva004E1794Named, "SpawnBuilding")
BFME_LITERAL_NAME_GETTER(Rva001F37BENamed, "FXParticleInfo")
BFME_LITERAL_NAME_GETTER(Rva001FC179Named, "FXParticle")
BFME_LITERAL_NAME_GETTER(Rva002047C9Named, "SequentialScript")
// LargeGroupAudio getter is owned by the complete subsystem unit.
BFME_LITERAL_NAME_GETTER(Rva00050C2BNamed, "GeometryInfo")
BFME_LITERAL_NAME_GETTER(Rva000518B2Named, "MilesAudioManager")
BFME_LITERAL_NAME_GETTER(Rva000638A2Named, "W3DRenderObjectSnapshot")
BFME_LITERAL_NAME_GETTER(Rva0008BC8BNamed, "View")
BFME_LITERAL_NAME_GETTER(Rva000B19BDNamed, "DrawModule")
BFME_LITERAL_NAME_GETTER(Rva00226309Named, "SaveMapPreview")
BFME_LITERAL_NAME_GETTER(Rva002296E6Named, "GameSlot")
BFME_LITERAL_NAME_GETTER(Rva00229902Named, "LobbyGameInfo")
BFME_LITERAL_NAME_GETTER(Rva0022CEF1Named, "SaveGameInfo")
BFME_LITERAL_NAME_GETTER(Rva002431A9Named, "InvisibilityManager")
BFME_LITERAL_NAME_GETTER(Rva0024A791Named, "BehaviorModule")
BFME_LITERAL_NAME_GETTER(Rva0024E353Named, "GateProxyBehavior")
BFME_LITERAL_NAME_GETTER(Rva00250A93Named, "SpawnedModelConditionCreate")
BFME_LITERAL_NAME_GETTER(Rva00251C76Named, "SpecialPowerTimerRefreshSpecialPower")
BFME_LITERAL_NAME_GETTER(Rva00252B84Named, "DrawableModule")
BFME_LITERAL_NAME_GETTER(Rva00252D24Named, "UpgradeSoundSelectorClientBehavior")
BFME_LITERAL_NAME_GETTER(Rva0028C9D7Named, "ObjectDefectionHelper")
BFME_LITERAL_NAME_GETTER(Rva0028CA92Named, "ObjectRecoveryHelper")
BFME_LITERAL_NAME_GETTER(Rva0028CB23Named, "ObjectRepulsorHelper")
