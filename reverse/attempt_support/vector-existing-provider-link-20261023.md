# Existing vector helper providers (2026-10-23)

Move five existing STLport 4.5.3 helper rows from the blocked overflow-family
collector to five existing consumer units that already emit the identical named
template bodies and link under the current legacy preview. Identities, retail
boundaries, flags, code and pins are unchanged. This repairs ownership of
existing C++ rather than adding new authored C++ bytes.

The pre-existing row and call-site notes remain the identity evidence. Each
consumer already uses the same element/template name; byte placement alone
is not used to infer a new type or donor identity.

| RVA | Bytes | Existing provider |
| --- | ---: | --- |
| 0x0033DCEA | 183 | Code/Libraries/Source/WWVegas/WWLib/stlport_vector_container_record_2cf46e_allocate_copy.cpp |
| 0x000CF76E | 178 | Code/Libraries/Source/WWVegas/WWLib/CameraMarkerParse.cpp |
| 0x002B8174 | 178 | Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicPlayerObserverRva002BA3F2.cpp |
| 0x005E818E | 178 | Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUIBuildQueueIconSelect.cpp |
| 0x005EFB7E | 178 | Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/StrategicHUDRegionDetailsArmiesMovieClip.cpp |

Base: 367d9885ae0bc49ff1eb15a2dd41f0ce95b139fe. Census: b711de3634,
2026-10-23 14:28, retail-truth-4. Index SHA-256:
1707d876c79d52c4e34a88342706796110595063d75abb3d5ed81bd080c08ad7.

Before, `python3 tools/link_check.py <five providers>` reports 5/5 clean,
5,063 B linked; the collector separately reports 0/9,375 B. After, the
same providers plus collector report 5/6 clean, 5,063 -> 5,958 B linked:
**+895 B in the paired legacy preview**. The collector remains blocked,
now owning 8,480 B. All objects are unchanged (SHA-256 comparison).
No census/index/status data was rewritten.

Each move used `tools/add_match.py --replace-existing` and passed its ordinary
`./build.sh <provider>` byte/reference gates. `check_csv.py` and
`find_declared_unmatched.py <providers>` pass. `code_identity_gate.py --staged`
checks 107 rows with **zero new findings**, in shadow mode.

Optional `link_check.py --prepare-current` waited on the shared compiler lock
and was interrupted before compilation. Reusable strict receipts are absent
for these providers. No self-strict or closed-strict gain is claimed; no full
link cycle or census was run.

## Excluded moves and next prerequisites

A larger candidate batch byte-verified but introduced shadow identity findings.
The commit was interrupted before creation/publication, those moves were
restored, and only the five zero-new-finding providers above were retained.
The excluded rows remain in the collector; blocked attempts are recorded and
their claims released. Resolve the typed callee identity first; do not add aliases
or pins merely to make the relocation resolver accept a body.

| RVA | Excluded provider | Specific issue |
| --- | --- | --- |
| 0x004043E1 | Rva004045B4.cpp | clear binds _Destroy at 0x00214B09 (wrong); overflow shares that view |
| 0x002098A0 | ScriptEngineDoXfer.cpp | _Construct at 0x0020596A (wrong) |
| 0x004141A1 | LivingWorldAutoResolveResourceBonus.cpp | _M_clear at 0x00414148 (wrong) |
| 0x005E1D5D | StrategicInGameUIRegionDetailsArmiesPage.cpp | _M_clear at 0x00577EF1 (wrong) |
| 0x0032CAA1 | SidesListTeamsInfoRecAddTeam.cpp | _Construct at 0x0032ACEA (divergent) |
| 0x00404457 | Rva004045B4.cpp | clear binds _Destroy at 0x00214B09 (wrong); overflow shares that view |

The collector retains unrelated missing element copy/dtor interfaces and wrong
selected GeometryShape/pointer-vector copies. The push-back collector was also
excluded after a current preview refuted its old census status.
