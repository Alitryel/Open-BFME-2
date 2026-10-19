# ??1AsciiString@@QAE@XZ: row 0x0048BA39 vs pin 0x00036410 (lane C, seat8)

## Verdict

Retail's out-of-line AsciiString destructor is the rowed 5-byte `jmp 0x00036410` at
**0x0048BA39** (`ascii_string.cpp`). Target facts: function-static atexit thunks
(`_$E2` of GetRegistryLanguage 0x007B7740, the Rva007B6A00AtexitThunks family) and
EH unwind funclets tail-jump to 0x0048BA39; ICF folds it with ~StringBase<char> (AAE),
clear and ~20 element/pair destructors whose only non-trivial member is the string.
0x00036410 is `StringBase<char>::releaseBuffer` (133 B row; ~StringBase QAE folds onto it):
the call an *inlined* ~AsciiString leaves behind.

The symbols.csv pin `??1AsciiString@@QAE@XZ,0x00036410` is a pin on the wrong body that
still byte-matches (the pattern link_census.RetailTruth's docstring describes for
Open-BFME-1). It only serves units built with `/DBFME_ASCII_DTOR_DECL` (or private views
with an out-of-line dtor) whose retail code inlined the destructor: their
`call ??1AsciiString` passes the byte gate through the pin, while the census (row first,
pins ignored) sees those calls as unknown and their `jmp ??1AsciiString` element-dtor
copies lose to the retail `jmp releaseBuffer` copies. Remove the pin once nothing
depends on it (`pin_consistency.py --symbol` still reports it "consistent": it checks
ownership, not retail truth).

## Measurement (census 2026-10-19 13:17, objects in build/match)

REL32 scan of every object naming the destructor, judged at each matched row's retail
site: 623 sites in 133 sources land on 0x00036410 through ??1AsciiString (pin-dependent),
476 land on 0x0048BA39 (honest). Scanner: relocation owner = enclosing function symbol,
row = single matched target_rva; landing = site + 4 + rel32 - addend.

Commit 0457c9f4e5 dropped the switch from 48 units (252 sites; LINKED +1,395, no unit
lost bytes). Remaining pin-dependent sources (sites, file), 371 sites:

    40	Code/GameEngine/Source/GameLogic/Object/CreateAHeroHero.cpp
    36	Code/GameEngine/Source/Common/GameSpyLoginPreferences.cpp
    26	Code/GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp
    24	Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp
    16	Code/GameEngine/Source/Common/System/Rva003F2D03Dtor.cpp
    14	Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
    12	Code/GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp
    12	Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatchOptions.cpp
    10	Code/GameEngine/Source/Common/Rva0035BB4BDtor.cpp
    8	Code/Libraries/Source/WWVegas/WWLib/Rva0026F684Dtor.cpp
    8	Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldScenarioDtor.cpp
    8	Code/GameEngine/Source/GameClient/CreateAHeroFileListCtor.cpp
    8	Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
    7	Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateQueue.cpp
    6	Code/Libraries/Source/WWVegas/WWLib/stlport_string_pair_cleanup.cpp
    6	Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
    6	Code/GameEngine/Source/Common/System/SaveGame/CreateAHeroElementCopy.cpp
    6	Code/GameEngine/Source/Common/System/SaveGame/CreateAHeroDataDtor.cpp
    6	Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawAnimationFrameCount.cpp
    5	Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp
    5	Code/GameEngine/Source/Common/System/Rva002362B4Dtor.cpp
    5	Code/GameEngine/Source/Common/Rva005C3A37ElemDtor.cpp
    4	Code/GameEngine/Source/Main/WinMain.cpp
    4	Code/GameEngine/Source/GameClient/GUI/window_video_manager.cpp
    4	Code/GameEngine/Source/Common/Rva0041F760Dtor.cpp
    3	Code/GameEngine/Source/GameLogic/Object/SpecialPower/Rva003F9FE6Dtor.cpp
    3	Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainModuleDataDtor.cpp
    3	Code/GameEngine/Source/Common/System/RegistrySetString.cpp
    3	Code/GameEngine/Source/Common/System/INI_loadDirectory.cpp
    3	Code/GameEngine/Source/Common/Rva00579731Dtor.cpp
    3	Code/GameEngine/Source/Common/Rva0054D8D8Dtor.cpp
    3	Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleData_parseEmbedPortal_Rva000C39F5.cpp
    2	Code/GameEngine/Source/GameLogic/ScriptEngine/iniParseObjectFilter.cpp
    2	Code/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyMapBfmeAddKey.cpp
    2	Code/GameEngine/Source/GameClient/MapCacheLoadUserMapsBFME2.cpp
    2	Code/GameEngine/Source/Common/UserPreferences.cpp
    2	Code/GameEngine/Source/Common/System/Upgrade.cpp
    2	Code/GameEngine/Source/Common/System/RegistrySetUnsignedInt.cpp
    2	Code/GameEngine/Source/Common/Rva00595D95Firewall.cpp
    2	Code/GameEngine/Source/Common/Rva002214A6Dtor.cpp
    2	Code/GameEngine/Source/Common/Rva000B9887Permuted.cpp
    2	Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptAuxGeometryLoad.cpp
    2	Code/GameEngineDevice/Source/MilesAudioDevice/AudioFileCacheThreadEntry.cpp
    1	Code/Libraries/Source/WWVegas/WWLib/stlport_vector_record_2154f3_allocate_copy.cpp
    1	Code/Libraries/Source/WWVegas/WWLib/stlport_vector_asciistring_fill_insert.cpp
    1	Code/Libraries/Source/WWVegas/WWLib/Rva0054F434Dtor.cpp
    1	Code/gen_small/Rva00240167Finish.cpp
    1	Code/GameEngine/Source/GameNetwork/Transport_init_AsciiString_Rva004d5534.cpp
    1	Code/GameEngine/Source/GameNetwork/GameSpy/OnlinePreferences.cpp
    1	Code/GameEngine/Source/GameLogic/System/Rva0023DC8EStringFlag.cpp
    1	Code/GameEngine/Source/GameLogic/System/GameLogicRva00246F8E.cpp
    1	Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIStructureCreepTactic.cpp
    1	Code/GameEngine/Source/GameLogic/ScriptEngine/ObjectTypesXfer.cpp
    1	Code/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineExecuteChunk.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/Rva0049D1B1.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/FloodUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdateModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Made002CC6AECtor.cpp
    1	Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDieModuleDataDtor.cpp
    1	Code/GameEngine/Source/GameLogic/Map/LibraryMapsParserCtor_Rva00329F83.cpp
    1	Code/GameEngine/Source/GameLogic/AI/AIRva002FFD03Parse.cpp
    1	Code/GameEngine/Source/GameClient/MapMetaDataCopy.cpp
    1	Code/GameEngine/Source/GameClient/GUI/Rva00427311Dtor.cpp
    1	Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/QuickMatchPopulateSideComboBoxRva005BB3A1.cpp
    1	Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptDrawData.cpp
    1	Code/GameEngine/Source/Common/Thing/ProductionPrerequisiteCtor.cpp
    1	Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp
    1	Code/GameEngine/Source/Common/System/XferAsciiStringVector.cpp
    1	Code/GameEngine/Source/Common/System/GeometryInfoSet.cpp
    1	Code/GameEngine/Source/Common/System/DataChunkInputReadAsciiString.cpp
    1	Code/GameEngine/Source/Common/Rva00524477Dispatch.cpp
    1	Code/GameEngine/Source/Common/Rva002FED8DDtor.cpp
    1	Code/GameEngine/Source/Common/Rva00202B6CGet.cpp
    1	Code/GameEngine/Source/Common/INI/INIEnvironment.cpp
    1	Code/GameEngine/Source/Common/Glo012F1024Entry_bfmeStep_Rva005669c2.cpp
    1	Code/GameEngine/Source/Common/Gen004502D0ParserRegistrationCtor.cpp
    1	Code/GameEngine/Source/Common/GameLODManagerGetStaticGameLODIndex.cpp
    1	Code/GameEngine/Source/Common/BfmeOwnedStringReset.cpp
    1	Code/GameEngine/Source/Common/AsciiStringFoldDeleters.cpp
    1	Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva000EE198Reset.cpp
    1	Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_doSingleBoneName.cpp

## Why the other 43 switch users were not converted

Without the switch their `??_GAsciiString@@QAEPAXI@Z`, `_Destroy<AsciiString>` (both
overloads), `_List_base<AsciiString>::clear` and set/_Rb_tree `_M_erase` COMDATs inline the
destructor, while retail's copies call 0x0048BA39 (the kept copy): link_check lost
13.5 KB across 30 units. PeerThread.cpp fails `PeerThreadClass::Thread_Function` outright.
These need per-site control: user code inlines (releaseBuffer), compiler-generated and STL
helper copies call out of line. Untested next steps: a decl-only or
`template<> __declspec(dllimport) __forceinline` `_Destroy<AsciiString>` specialization so
the unit does not emit its own copy (the lever from 0000b3c0-string-base-dtor-comdat);
check each helper's retail body first. MIXED sources (both landings in one unit:
CreateAHeroHero, GameSpyLoginPreferences, MilesAudioManager,
W3DScriptedModelDrawAnimationFrameCount, AudioFileCacheThreadEntry, XferAsciiStringVector)
and the NODECL ones (private views, e.g. stlport_string_pair_cleanup, WinMain) need their
own look.

Inputs: seat8 at 1ba4f4ded4 + 3 local commits; BFME1 pointer unchanged; model claude-opus-5-5.
