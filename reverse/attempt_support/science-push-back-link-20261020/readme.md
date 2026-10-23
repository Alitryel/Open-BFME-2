# ScienceType unlock helper binding

The 110-byte `Rva0043D3DAClear.cpp` unit had one retail-truth-2 COMDAT loser:
`vector<ScienceType>::push_back`. Its unlock body already calls the out-of-line
49-byte retail provider at RVA 002E01C6, rowed in `ThingTemplate.cpp`. Declaring
that specialization before the caller suppresses the different local helper;
no code body, symbol pin or allocation semantics changes.

Paired local legacy previews use the same published census (5366c4f808,
2026-10-20 12:21) with only this object's definitions refreshed in memory:
0 -> 110 linked bytes. `paired.json` records all blocker categories, object and
source hashes, index hash and current strict receipt. This is a local legacy
preview, not a closed-strict measurement or a newly published census.

Acceptance: `./build.sh Code/GameEngine/Source/Common/Rva0043D3DAClear.cpp`
passes both rows; `link_check.py --prepare-current` verifies both rows and
creates a reusable strict receipt. Ordinary `link_check.py` reports LINKS,
0 -> 110 bytes. No closed-strict gain is claimed. The repair follows the
reviewed BFME 1 binding principle (canonical rowed callees rather than private
copies); the provider and unchanged caller identity are BFME 2 ledger/byte
facts, with no donor body imported.
