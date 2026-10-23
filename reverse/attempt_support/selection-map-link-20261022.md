# SelectionTranslator constructor provider repair

At BFME2 355c52a208, SelectionXlatTranslateGameMessage.cpp emitted a competing
hashtable<int,bool> constructor. Declaring that specialization moved the sole
blocker to its hash_map<int,bool> constructor; declaring both binds them to the
existing StlSweepW5Rva0042FFC0.cpp provider. No names, layouts or providers change.

Paired current-object legacy previews, including the provider in both runs:
`python3 tools/link_check.py Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva0042FFC0.cpp`
reported 105 B before and 4,250 B after: +4,145 B. The provider's existing
105 B are excluded from this gain. This is a legacy preview against the published
08160bc2c9 census, not a closed-strict measurement.

`./build.sh Code/GameEngine/Source/GameClient/MessageStream/SelectionXlatTranslateGameMessage.cpp`
passes all three rows (4,145 B), strings, float and import references. The frozen
source check passes. No other unit in the rank map had this exact constructor
blocker. Donor provider comments retain its existing identity and provenance.
