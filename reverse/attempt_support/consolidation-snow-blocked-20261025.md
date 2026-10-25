# Snow mechanical consolidation blocked (2026-10-25)

Allocated destination: `Code/GameEngine/Source/GameClient/Snow.cpp` (shard 0/5, unheld). The planner was regenerated under `Code/GameEngine/Source/GameClient/`; snapshot check passed. The plan has 13 approved rows, 5 donors, 2 mixed files, and no protected refusals. Dry run accepted no donors and reported `blocked: no verified merge of two or more donors`; no source or ledger changes were applied. It also reported `adopt_first: {'Code/GameEngine/Source/GameClient/Snow.cpp': ['SubsystemInterface']}`.

Exact dry-run rejections (diagnostics are truncated by the tool):

- `Snow_Unresolved.cpp`: `subsystem_interface.h(36) : error C2146: syntax error : missing ';' before identifier 'loadIniFilesFromLegend' | ...`.
- `WeatherSettingAssign.cpp`: `Snow.<hash>.tu_skeleton.cpp(309) : error C2600: 'WeatherSetting::operator`=' : cannot define a compiler-generated special member function (must be declared in the class first) | ...`.
- `WeatherSettingCtor.cpp`: `Snow.<hash>.tu_skeleton.cpp(139) : error C2065: 'WeatherSetting' : undeclared identifier | ... C2955: 'OVERRIDE' : use of class template requires template argument list | ...`.
- `INIParseWeatherDefinition.cpp`: `Snow.<hash>.tu_skeleton.cpp(95) : error C2143: syntax error : missing ';' before '<' | ... (100) : error C2143: syntax error : missing ';' before '<' | ...`.

The destination itself is in the header-adoption queue for `SubsystemInterface`; resolve that prerequisite through Sol's header lane before retrying. Do not repeat this unchanged dry run.
