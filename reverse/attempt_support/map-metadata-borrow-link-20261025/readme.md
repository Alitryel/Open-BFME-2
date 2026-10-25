# Keep the native map-metadata copy provider selected

Inspected master `d4cd9b535c`, BFME 1 reference
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`, published index
`ef9c691284` (2026-10-25 18:23 UTC).

SkirmishGameOptionsMenu.cpp included Zero Hour's shorter MapMetaData view and
copied two cache records solely to read them. Its implicitly emitted copy
constructor preceded the recovered native 257-byte copy at 003039E8 in link
order. That native body copies the full 256-byte BFME 2 record; the shorter
implicit copy is not a valid provider under its name.

Borrow the existing cache records instead. startPressed reads only player count
and uses a const reference. The legacy positionStartSpots overload reads player
count, multiplayer state and waypoint positions. Its native positioning helpers
read the metadata/coordinates and write window positions or the separate
TechAndSupplyImages lists, not the input metadata. Their existing non-const
signatures require a non-const reference at this call site. The additional-image
call passes force=true, so the helper's prior-pointer shortcut is disabled.
No metadata copy or destruction is needed for either read-only use.

Source semantics come from the existing Zero Hour menu. Native field evidence
is separate: MapMetaData's recovered copy/layout and GUI users prove the shared
prefix, and the whole byte-verified positionStartSpotControls (396B) and
positionAdditionalImages (557B) bodies establish the read-only helper behavior.
This does not promote the remaining legacy menu bodies or its shorter class
view to recovered BFME 2 source. No native copy is called on a shorter temporary.

All 56 existing rows across the six-source cohort pass normal build.sh gates,
including 11 string references, with no baselined or skipped references. All
13 EH graphs are EXACT, with no missing object or baseline exception. All six
sources have strict reusable current receipts, independently checked against
their actual object MD5. Changed-source data checking has zero findings; the
frozen-file and whitespace checks pass. Three ordinary owned method bodies are
byte-and-relocation unchanged, as is the handler's complete code; the parent EH
graph proves the handler and renumbered cleanup association. No row, pin, alias,
header, verifier or baseline changes.

The before/after preview refreshes the same six current objects against the same
index and ledger facts, replacing only the menu object with its immutable
original for the control. The obsolete metadata-copy and three tree-copy
emissions disappear. Four formerly blocked units become ordinary-preview clean,
covering **2,295 authored nonpadding bytes**, from zero in the control:

- stlport_pair_asciistring_twins.cpp
- GameInfoSetMapSize.cpp
- SkirmishMapStartSpots.cpp
- PositionStartSpots.cpp

This is bounded ordinary-preview availability, not new census LINKED/LINKING,
closed dependency verification or an executable link. The menu retains 49
unresolved legacy names, GameSlot and Money conflicts, and a selected runInit
conflict. MapMetaDataCopyDeferred.cpp still has its separate waypoint-tree
identity/provider conflicts; its complete native body remains byte-verified.
The paired evidence lists every remaining name. Do not count this as whole
map-family closure or repeat the documented tree-identity pin substitutions.
