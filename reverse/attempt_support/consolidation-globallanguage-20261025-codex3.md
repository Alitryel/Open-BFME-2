# Consolidation handoff: GlobalLanguage.cpp

Merged the accepted in-prefix `GlobalLanguageAdjustFontSize.cpp` donor into the
approved `GlobalLanguage.cpp` TU. Net source-file change: -1. Two matched
function rows and one matched data row were repointed; no byte coverage or debt
retirement is claimed.

Verification passed: `./build.sh Code/GameEngine/Source/GameClient/GlobalLanguage.cpp`
reports 4/4 matched functions, three data rows, five string literals plus one
empty-string reference, one compiler literal and 13 named imports. The frozen
file check reports all definitions matched. Staged `link_check.py --fetch-index
--new-variants --shadow` exited 0 without COMDAT variant diagnostics.

Path audit covered the staged old-to-new path and searched active tools, hooks,
workflows, source/includes, build/configuration files and registries. No active
consumer needs a manual path repair. The remaining old-path hits are the last
link census receipt (`reverse/link_status.csv`, awaiting the next maintainer
census), the historical re-attempt log and prior handoff, and the provenance
comment in the merged TU. `reverse/header_queue.tsv` has no source entry;
`reverse/ms_header_queue.tsv` was repointed and retains a `conflicting abi`
finding at the new TU. Code identity remains in shadow with no key for this
source; the data-check baseline has no key for it. These registers were not
retired or edited by hand. Historical EA paths remain intact.

Remaining dry-run rejections: duplicate `_STL::operator !=` in the external
list-clear donor; missing `TheGlobalLanguageData` type in
`GlobalLanguageOnGameEngineExit.cpp`; and the `subsystem_interface.h(36)`
`loadIniFilesFromLegend` syntax error in `GlobalLanguageCtor.cpp`. Their repairs
are outside this seat.
