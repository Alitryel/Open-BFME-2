# SubsystemInterface consolidation blockers (2026-10-26)

Allocated `Code/GameEngine/Source/Common/System/SubsystemInterface.cpp` passed
`check-tu`; the fresh planner approved 18 rows across 10 donors. The merge dry
run accepted no donors. It rejected `Rva001B4E21Get.cpp` because
`rva001B4E21` is not a member of `SubsystemInterfaceList` (C2039), and rejected
several `SubsystemInterfaceList*` donors for missing member/identifier
declarations. `Rva001B4EABExport.cpp`, `Rva001B4F8B.cpp`, and
`SubsystemInterfaceLoadIniFilesFromLegend.cpp` fail on duplicate `AsciiString`
definition/operator declarations in `reference/shims/bfme2_ascii/ascii_string.h`
(C2011/C2084). No donor was changed or claimed.

Mixed-file review also found no accepted split. `SubsystemInterfaceListRemoveSubsystem.cpp`
can carve `0x001B4E82`, but the residual loses matched rows `0x0020E873` and
`0x005250A5`. `Code/Libraries/Source/subsystem/SubsystemInterface.cpp` cannot
be carved: `0x001B5266` also defines a row for another TU (`0x00229AC8`), and
the source's namespace/`extern "C"` definitions make the carve unsupported.
These declaration, shim and mixed-file repairs belong to Sol.
