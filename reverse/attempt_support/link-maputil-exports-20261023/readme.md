# MapUtil exports for the recovered addMap

Inputs: BFME2 parent ebab526732; published census 456ce161c5 (2026-10-23
06:28); BFME1 reference 96c88c73a5cd1a58fc2f8db691beea50acd996db.

MapCacheAddMap.cpp had only two remaining unresolved references: resetMap
and worldDict. MapUtil.cpp already owns both, but declared them static.
Give resetMap external linkage and define worldDict with the C spelling
already used by its data-ledger owner and the recovered caller. There is
still exactly one definition of the dictionary, at data RVA 0x009FF140.
No new data name, pin, alias or row is added.

Target evidence: resetMap is the existing verified 76-byte row at
0x00303187. The caller at 0x00304E64 independently resolves its call and
dictionary references through the normal full-byte gate. MapUtil's
dictionary initializer and atexit cleanup remain exact as well.

Donor review: BFME1 game/GameEngine/Source/GameClient/MapUtil.cpp still
has the file-local definitions, while its MapCacheAddMap.cpp declares an
external resetMap. Thus this is a local linkage repair supported by BFME2
ownership and bytes, not an inherited BFME1 linking result.

## Acceptance

Paired link_check.py previews on MapUtil.cpp and MapCacheAddMap.cpp, using
the same census and source list before and after:

- Before: neither unit links, total 0 linked bytes.
- After: MapCacheAddMap links 1,085 bytes; MapUtil remains blocked by its
  existing unrelated references and competing helper copies. Gain +1,085 B.
- This is a legacy scoped preview, not closed-strict LINK evidence.
- build.sh: MapUtil 20/20 rows exact.
- link_check --prepare-current: both units 33/33 rows exact, two strict
  reusable compiler receipts; self-strict preparation only.
- eh_verify: three EH graphs EXACT, no debt.
- data_check --converged: two sources, ten addresses, zero second names,
  zero unjudged rows.
- find_declared_unmatched: all MapUtil definitions already matched.
- check_csv: passes.

The source sweep finds only the recovered addMap declaring these two
exports. No compiler settings, baseline or ledger modifications are needed.
