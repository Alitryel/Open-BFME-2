# Object-status event parser: boundary and ABI corrected, body still partial

Target: LuaScriptEngine::ProcessObjectStatusEvent, existing pin
?rva002E9AA0ParseObjectStatusEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z.
WorldBuilder C00CD0 (2317 bytes, LuaScriptEngine.cpp assertions 1089..1133)
provides identity and semantic flow. The earlier 421-byte queue extent stops
at the catch entry. Native whole extent is 482 bytes: 00336EB0..00337092,
with RET 4 at 0033708F and the next function starting at 00337092.

Earlier attempt-log claims of private EBX/EDI/ESI inputs are refuted by the
native prologue: ordinary _EH_prolog at 00336EB5, XOR EBX at 00336EC0,
parser from [EBP+8] at 00336ECB, XOR ESI at 00336ED3. Handler 0077C2B6
uses FuncInfo 00925924 (4 unwind states, one try block). Catch-all 00337055
returns continuation VA 0073705B. The existing 6-byte ConstIntGettersAddr
row at 00337055 is actually this catch, not an independent int getter;
retire it only when the complete parent is verified and landed.

Inputs: author 3318feda7a6, verified BFME1 pointer
cf0a80c228583af789772b794ab27abcab2debbf; MSVC7.1 region settings
/O1 /G7 /arch:SSE /EHsc /MD, STLport static/no-exceptions and BFME2 ASCII
shim. Semantic starting point was the complete bank at 00336C5D and its
BFME1 model-condition donor; target-specific dimensions come from native
and WB evidence: two 16-byte flags, 36-byte event record, vector at +C8.
These opaque class names do not establish donor type identities.

Previously missing lexer finish 00542890 is now matched. Equality 00332FE7
is bool, proved independently by WB C01880 returning AL; corrected provider
3318feda7a6 passes both 64-byte equality and 38-byte constructor, and links
all 102 bytes. No new pins were needed. Parser calls all resolve.

Best saved candidate: reverse/attempts/0x00336eb0.cpp, 484 bytes.
It matches the native instruction stream through 00336FFE except jump
displacements. Remaining differences: missing XOR BL,BL before vector loop;
CMP AL,BL versus TEST AL,AL; extra parser reload inside loop; CMP BL,BL
versus TEST BL,BL; post-catch zero-EH-state assignment uses XOR EBX/MOV
rather than AND [EBP-4],0. See alignment.txt. Score .95 is conservative
instruction agreement, not proof or recovered-byte credit.

Trials ruled out:
- Initial int return plus unsigned-char cast versus proven bool: same caller shape.
- Moving found=false from before record construction to WB's after setKey:
  483 bytes but much worse register allocation from prologue onward.
- Early-return then push_back versus if/else: unchanged.
- Iterator initialization before the flag: same 483-byte shape.
- /EHs and /GX: 475 bytes with wrong frame (58 versus 5C);
  /EHa: 516 bytes with wrong frame and an out-of-line helper.
- Assigning comparison into found on each iteration: 477 bytes, not exact.

No nonmatching production source was installed. Full parser EH graph and
DIR32 identity checks remain prerequisites after byte equality; positional
explain_mismatch relocation patches become misleading once lengths diverge,
so use alignment/raw relocations. Stop requested after current publication;
do not start another trial without fresh authorization.
