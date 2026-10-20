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

## 2026-10-19 follow-up (hans-agent-oct5)

11 loop/flag spellings tried; none moves the 484B bank. The residue is EBX zero coalescing with `found`: retail's xor bl,bl before the loop and `and [ebp-4],0` after the catch show EBX is not a known zero there. Look for source that clobbers or retires the EBX zero before the vector loop (e.g. an EH-state or name-temporary change), not loop syntax.

## Round 2026-10-20 (claude-opus-5-5, ~45 min)

The new bank is `found=false` declared before `try` (the same result when declared at the function top): 483 B and
7 alignment regions, against 484 B and 8 for the previous bank. The in-loop parser reload is gone. Remaining:
- no `xor bl,bl`;
- `cmp al,bl` / `xor cl,cl; cmp cl,bl` where retail has `test al,al` / `test bl,bl`;
- post-catch `xor ebx,ebx; mov [ebp-4],ebx` where retail has `and [ebp-4],0`.

Reading of retail: the break path jumps straight to the found/return block (the `found=true` store is
jump-threaded away), and the loop exit tests a genuinely live `bl`. Retail's zero-constant register (EBX) web
ends at 336FE7, before the loop, so the zero after the catch is an immediate. Ours keeps the zero CSE alive across
the whole try into the post-catch state store and copy-coalesces `found=false` into it.

Ruled out this round:
- `&&!found` in the loop condition: 488 B. This is the only shape with retail's `xor bl,bl`, but it swaps EBX/EDI and adds `inc bl`.
- while loop with the found/else `++it` shape: 476 B.
- `!found&&` condition: 474 B.
- no break: 474 B.
- `found` declared right before the loop or after `it`: 483 B, 21 regions, with the parser homed out of EDI.
- `if(found)return; push_back` with `found` inside the try: 483 B, 21 regions.

Untested next lever: break the zero CSE between the try and the post-catch code, so `found` stops being a copy of the zero register.

## Round 2026-10-20 r44 (claude-opus-5-5, ~25 min)

WB C00CD0 confirms the late definition: `found` (local_69) = 0 right after
setKeyFromName, then it = begin (local_84), end re-read each test. Measured on the
0.98 bank (482B, 3 lines):
- found=false at function top (before or after `name`): prologue and the str()
  `cmp eax,ebx` match; only retail's re-zero `xor bl,bl` before the loop is
  missing (found coalesced with the EBX zero, 483B nd36).
- Any found definition after setKeyFromName (decl+init, top decl + late assign,
  decl before try + late assign, top init + redundant late reset, `for(it=..,
  found=false;...)`, a forceinline has-event helper with its own found or with
  return-in-loop) flips the prologue: zero/i coalesce in ESI, this in EDI,
  parser in EBX, frame 0x58, 472B (nd160; helper-return form 474B nd48).
- `const char *key=name.str()` before found: 484B nd49. Cached count / int i
  declaration position with late found: inert (472/474B).
The retail EBX zero lives to the str() compare while found is a separate late
web in the same register; no source form above reproduces both.
