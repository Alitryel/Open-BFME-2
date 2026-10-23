# Text-entry renderer internal linkage

The private renderer at native RVA `0x0009FE49` is now `static`, and its font comparison directly reads `text->getFont()`. This removes the artificial `(x ? text->getFont() : text->getFont())` expression formerly used to change argument/register allocation. Both source callers remain in the same translation unit. No function ranges, pins, headers, compiler flags, or verifier rules change; this repair adds zero recovered bytes.

The new evidence was Open-BFME-1 revision `4483e88` and its `game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DGadgetTextEntryDraw.cpp`: the analogous 0x007986C0 helper only matches with internal linkage, which fixes its x-argument placement. This is a compiler/linkage lead, not a claim of byte identity between the games. The source was inspected from that revision; BFME2 still builds against its committed BFME1 pointer `92f6bbe8`.

For BFME2, `tools/callers_of.py 0x0009FE49` reports exactly the normal and image text-entry callbacks at 0x000A03BF and 0x000A0581. The native calls at 0x000A0575 and 0x000A0860 go directly to the helper. Source search finds no external callers or declarations. `native-calls-and-symbol.json` preserves these native call bytes and the emitted helper's static COFF storage class (3). Direct calls alone do not prove original source linkage, but internal linkage is consistent with the complete known caller set and reproduces every claimed body without the artificial condition.

Verification on BFME2 `413ecd9e`:

- Normal `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DTextEntry.cpp`: baseline and repaired source both pass 5/5 rows, 2,622 claimed bytes, including both callbacks, renderer, min helper and compiler EH handler. String, float and named-import checks pass.
- `python3 tools/eh_verify.py <source> --json ...`: 1/1 EXACT, zero missing objects and zero baselined failures; recorded in `eh.json`.
- `python3 tools/link_check.py <source>` against the published census dated 2026-10-20 12:21 at `5366c4f808`: LINKS; predicted linked bytes unchanged at 2,611 to 2,611. This is a census prediction, not a new full-link run or new byte credit.
- Independent source review found no semantic or identity blocker. The normal staged hook remains the final commit gate.

The existing parent and EH-handler ledger notes were updated through verified `add_match.py --replace-existing` calls so they no longer describe the removed shaping expression. Agent: Codex (runtime model not exposed).
