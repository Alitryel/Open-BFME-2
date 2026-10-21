# Link census false reject: losing copies of retail-proven COMDATs (2026-10-21)

Index: {'date': '2026-10-21 18:42', 'commit': 'd08db10acb', 'clean_tree': True}. Model claude-opus-5-5.

`keep_rule` charges a COMDAT copy whose verdict is `wrong` (bytes differ from the
retail body at the name's ledger/pin address) even when another object in the same
link supplies the retail-proven copy. Such a losing copy is discarded by the link,
as the original build discarded its own non-retail copies (retail's body is one
unit's copy). Whether the kept copy is retail's is already judged separately
by `wrong_selected` (`judge_selected` on the /MAP).

69 census files (88,040 matched bytes) are blocked only by such losers:
no unresolved name, duplicate, address or wrong_selected, and every losing name has a
`retail` copy in another object. The 244 losing names with no retail copy anywhere
are not affected: those copies may be the one the image runs.

| source | bytes | losing names |
|---|---:|---|
| `Code/GameEngine/Source/Common/BfmeConv1456.cpp` | 153 | 1 |
| `Code/GameEngine/Source/Common/BfmeObject476Copy.cpp` | 2491 | 3 |
| `Code/GameEngine/Source/Common/BfmeResultSourceA.cpp` | 209 | 1 |
| `Code/GameEngine/Source/Common/BucketDtor.cpp` | 14 | 1 |
| `Code/GameEngine/Source/Common/NameKeyGeneratorNameToLowercaseKey.cpp` | 187 | 2 |
| `Code/GameEngine/Source/Common/RTS/ShroudManagerImplGetNearestGroupWithValue.cpp` | 1191 | 5 |
| `Code/GameEngine/Source/Common/Rva0054FD83Destroy.cpp` | 118 | 1 |
| `Code/GameEngine/Source/Common/Rva0060147B.cpp` | 177 | 1 |
| `Code/GameEngine/Source/Common/Rva00893030RefDispatch.cpp` | 131 | 1 |
| `Code/GameEngine/Source/GameClient/DrawableRva00278440.cpp` | 111 | 1 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptStrategicPlayerStatus.cpp` | 1717 | 1 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTributePageLoaded.cpp` | 569 | 1 |
| `Code/GameEngine/Source/GameClient/System/ParticleSystemUpdate.cpp` | 1702 | 7 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainChangeToFormation.cpp` | 819 | 1 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeInitiate.cpp` | 467 | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdateTick.cpp` | 433 | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateClearUpgrades.cpp` | 310 | 1 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathRva00365B8A.cpp` | 611 | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamPartialUseCommandButton.cpp` | 300 | 3 |
| `Code/GameEngine/Source/GameLogic/SkirmishAI/AISpecialPowers/AIRva005D8B0BCheck.cpp` | 194 | 1 |
| `Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/TargetlessTactics/AIRoamingDefenseTacticRoam.cpp` | 592 | 3 |
| `Code/GameEngine/Source/GameLogic/SkirmishAI/AITeamBuilder/AITeamBuilder_checkIdleTeams.cpp` | 407 | 2 |
| `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_Pinger_addRequest.cpp` | 79 | 2 |
| `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread_Pinger_getRequest.cpp` | 131 | 2 |
| `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioMultisound.cpp` | 3263 | 5 |
| `Code/Libraries/Source/Apt/AptHandleVectorDelete.cpp` | 112 | 1 |
| `Code/Libraries/Source/GdiPlus/gdiplusbitmap_dtor.cpp` | 151 | 1 |
| `Code/Libraries/Source/Math/MathCoord2DClosestPoint.cpp` | 256 | 2 |
| `Code/Libraries/Source/WWVegas/WW3D2/HLodUpdateObjSpaceBoundingVolumes.cpp` | 2495 | 9 |
| `Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorCollectMaterials.cpp` | 1489 | 4 |
| `Code/Libraries/Source/WWVegas/WW3D2/MeshClassRenderWithFXMaterial.cpp` | 2487 | 6 |
| `Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRender.cpp` | 1517 | 1 |
| `Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRenderVolumeParticle.cpp` | 1021 | 6 |
| `Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRva0017D770.cpp` | 1583 | 1 |
| `Code/Libraries/Source/WWVegas/WW3D2/SceneOwnership.cpp` | 1351 | 6 |
| `Code/Libraries/Source/WWVegas/WW3D2/SceneSpatialRescale_Unresolved.cpp` | 207 | 1 |
| `Code/Libraries/Source/WWVegas/WW3D2/SortingRendererBFME1.cpp` | 13209 | 4 |
| `Code/Libraries/Source/WWVegas/WW3D2/htree.cpp` | 44 | 7 |
| `Code/Libraries/Source/WWVegas/WW3D2/mapper.cpp` | 8123 | 1 |
| `Code/Libraries/Source/WWVegas/WW3D2/part_buf.cpp` | 33849 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva000AB7FB.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva000E0816.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00148F7E.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva001DE80F.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva001E2F8E.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00210566.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0023ADC8.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0030A0BC.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00355B02.cpp` | 73 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva003ED2E1.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva003EF40B.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva00411AC7.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0041F720.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0041FC37.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0042FFC0.cpp` | 105 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva004DAA9E.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva004E007A.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0052B7B8.cpp` | 74 | 4 |
| `Code/Libraries/Source/WWVegas/WWLib/WideStringCompareCharacterBFME2.cpp` | 66 | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_list_create_node_vecuint.cpp` | 195 | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_pod16_subscript.cpp` | 91 | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_filebuf_underflow.cpp` | 53 | 2 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_insert_unique_nocase.cpp` | 27 | 6 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_string_int_erase.cpp` | 53 | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva004e32f2_pushback.cpp` | 55 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva0052bde6_pushback.cpp` | 55 | 3 |
| `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva0052bef0_pushback.cpp` | 55 | 3 |
| `Code/Libraries/Source/WWVegas/WWMath/quat_BuildMatrix4.cpp` | 372 | 1 |
| `Code/Libraries/Source/assetmanager/AssetManagerImplUpdate.cpp` | 1386 | 2 |
