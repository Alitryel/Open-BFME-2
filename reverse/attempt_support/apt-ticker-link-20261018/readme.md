Apt ticker display linking (2026-10-18)

The display unit previously bundled the response pump 5BA02B and its
79FB17 EH handler with ticker and spell-button display functions. Its
current object had three unresolved names: the two label tables and the
unmatched shared peer-response handler 5AF12F. The home AptHeroPowerText.cpp
already links; its declarations are not duplicate function definitions.

Move only the unchanged response pump, its required declarations and EH
row to AptTickerGameSpyUpdate.cpp. Its 466-byte parent and 10-byte EH body
remain exact. The 2200-byte 5AF12F body is not reconstructed here: the room
map/response ABI blocker in the existing attempts remains unresolved.

Target data: DD3B90 contains six ticker label pointers used for rows 0..5:
APT:Date, APT:Time, APT:1v1RankLabel, APT:2v2RankLabel,
APT:PlayersOnline, APT:GamesInProgress. The immediately following six
pointers at DD3BA8 name SIDE labels and are excluded from this claim.
C3D700 contains six spell-button states, from _unused to _active, through
C3D717. The two 24-byte data rows check complete initializers and all string
relocations. Names are address-derived; these are target pointer/string
facts, not donor layout claims. Preserve the existing pointer element types
and bind the Apt manager through the data ledger's g_bfmeAptWindowManager.

Acceptance: build.sh and link_check --prepare-current both pass 6/6
function rows across the two units, 2/2 data rows, seven string references,
and the import reference. find_declared_unmatched passes. data_check
--enforce has zero findings and --converged has no second names or unjudged
rows. check_csv passes 96634 functions, 15999 symbols and 931 data rows.

Same published index c2c5ac8c27 (2026-10-18 11:36), current-object link_check:
before display unit 0/798 non-padding bytes, after LINKS 337 bytes. The new
response-pump file has no entry in that index and is not previewable; no
linked bytes are attributed to it. The gain is +337 legacy predicted bytes.
Self-strict byte verification passes; closed-strict linking was not measured.
Authored C++ coverage is unchanged. Raw ignored logs are
build/seat-link-oct18/apt-{shader-current,after,build-final,data,strict}.log.
