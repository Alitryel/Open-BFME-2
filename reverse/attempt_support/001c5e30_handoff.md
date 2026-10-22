# Handoff: _VP6_PredictFilteredBlock 0x001C5E30 (768 B retail)

Clean-room target. Branch `opencode/goal-1015` (worktree `Temp/opencode/bfme2-goal-1015`,
`BFME_CLAIM_OWNER=opencode-goal-1015`). Claim **renewed** this session — renew again at
session start (`python tools/claims.py renew 0x001C5E30`, 4 h lease).

## Where the work stands
- WIP TU (untracked, freshest copy): `Code/Libraries/Source/VP6/PredictFilteredBlock.cpp`
  — compiles to **635 B** vs retail 768. Last edit = x/y declaration order swap (y-then-x);
  verified zero effect, safe to keep or revert.
- Prior body also banked via `re_log.py record ... partial --stash` (score 0.55) →
  `reverse/attempts/001c5e30.cpp` per convention; the on-disk TU is newer.
- Retail ground truth: `build/probe/pred_disasm.txt` (279 lines, fully decoded).
- Probe loop: `& 'C:\Program Files\Git\bin\bash.exe' -c "cd /c/Users/nleig/AppData/Local/Temp/opencode/bfme2-goal-1015 && python build/probe/entryprobe.py 0xff"`
  (arg = line cap; first output line = symbol size).

## Converged this session (all byte-verified vs retail)
1. Walk ±1 update as literal `ptr2Offset += 2 * ((short)x > 0) - 1;`
   → retail's fused `setg dl; lea edx,[ecx+edx*2-1]` (`8d 54 51 ff`). Block 2 same with
   `imul edx,[esp+0x10]`.
2. Per-branch chained assignments (delete the shared `ptr2Offset = ptr1Offset;`):
   - LF: `ptr2Offset = ptr1Offset = 0x22;` → one reg materialized `mov eax,0x22` + two stores.
   - WP: `ptr2Offset = ptr1Offset = 0;` → `xor ecx` + two stores (retail-identical shape).
3. Tail restructure: `if (ptr2Offset != ptr1Offset) { <all filter work, final filter call
   inside, plain `return;` after it> } unpack-tail;` → dispatch emits `cmp; je → cold
   unpack-tail block`, matching retail's `je 0x1c6112` layout.
4. profile/loopFilter byte tests already load CL (EAX busy) — matches retail.

## Verified SAME between mine and retail
- Selected-frame logic shape (overwrite form promotes `(mode,cmp)` to entry front).
- Home slots (post `add esp,0x10`): x32 `[0x18]`, y16 `[0x1c]`, y32 `[0x20]`,
  stride `[0x10]`, ptr1Offset `[0x14]`, walk/home `[0x28]`.
- Walk phase regs: phaseX=EBX, phaseY=EBP; tests `test ebx,ebx` / `test ebp,ebp`.
- LF mask re-read → ECX right after the call; stride `[0x10]=0x10` immediate.
- Block 1 walk-inside reload `mov ecx,[esp+0x28]` after the je.

## Remaining deltas (~133 B), one register-liveness cascade
All trace to one root: retail keeps **frame live in EAX** across the entry region
(LR→EAX survives to LF `add edx,eax` @0x59) and re-reads slot [0x28] only in the WP.
Mine spills frame at store1 and reloads it. Consequences, mine vs retail:
- prologue: 3 pushes + pbi→ESI + deferred `push edi` @0x1B vs 4 pushes + pbi→EDI @0x007.
- mask: WP-local `mov ebp,[esi+0x80]` at WP start vs unconditional entry
  `mov edx,[edi+0x80]` @0x01C serving the WP (LF re-reads into ECX either way).
- pos: EBX vs EBP (retail EBP self-overwrites at the second y-read @0x075).
- base: →EDI vs →ESI.
- x32 carrier: EBP (`movsx ebp,ax`) vs EAX (`movsx eax,ax`).
- x read: `movzx eax,[mem]` vs `xor eax,eax; mov ax,[mem]` (the ZE+reSE idiom).
- 0x22 stores emitted before `add esp,0x10` (mine, slots 0x24/0x38) vs after
  (retail, 0x14/0x28) — same absolute homes, scheduling only.
- Walk block 2 write-back: memory RMW `add dword ptr [esp+0x28],edx` vs retail reg-RMW
  `mov ecx,[0x28]; add ecx,edx; mov edx,[0x14]; mov [0x28],ecx` (walk stays in ECX).
- Dispatch: `cmp [esp+0x28],edx` vs retail `cmp edx,ecx` (values preloaded in regs).
- Sign tests: `test ax,ax` / `test dx,dx` vs retail home word-compares
  `cmp word ptr [esp+0x18],dx` / `cmp word ptr [esp+0x1c],cx`.

## Experiments exhausted (do not repeat)
- Any **unconditional** top-level mask statement kills the `(mode,cmp)` entry promotion:
  tested before-default (v5), after-default (v9), `int mode`-first + mask (v11),
  between-ifs (v13). Comma-condition variant `if (mask = pbi->modulusMask, cond)` (v14):
  mask landed `mov ebp @0x34` in the je shadow, promotion dead, 590 B cascade.
- Ternary and if/else forms of frame selection: both lower branchy (2 jmps).
  The overwrite form (default assign + if-overwrite, current) is the retail shape.
- x/y declaration order swap: zero effect (this session).
- Mask read deferred to WP first statement + LF inline re-read (v12, current),
  and mask read after x/y in the WP — WP-local EBP either way; never hoists.

## Not yet tried (concrete next list)
1. **Frame-liveness lever** (never directly attacked): give the LF path's ptr1 its own
   variable so the compiler may keep frame in EAX, e.g.
   `unsigned char *src; ... src = frame + pbi->reconIndex; VP6_PredictFiltered(pbi, src, ...)`
   as separate statements before the call. One edit + one probe.
2. WP mask-read placement inside the WP after x/y loads instead of first statement.
3. If the entry persists after 1–2 probes, move on per the 30-min rule: record
   (`re_log.py record ... blocked/partial --stash --score ...`), `claims.py release`,
   and switch to another queue body.

## Batch/publication context
- Publish bar ≥500 new retail bytes; this function is the pending batch centerpiece
  alongside the earlier banked work (DiagonalBlur bank, InitGadgets +158 B linked).
- Landing procedure unchanged: `tools/add_match.py _VP6_PredictFilteredBlock 0x001C5E30 768
  Code/Libraries/Source/VP6/PredictFilteredBlock.cpp`, commit with
  `Clean-Room: reverse/vp6_cleanroom/specs/001c5e30.md` trailer, push per AGENTS.md
  (pull --rebase before/after, 5-min account cooldown, never bypass hooks).

## Notes / gotchas
- Spec file `reverse/vp6_cleanroom/specs/001c5e30.md` has an exceed-limit clause that
  contradicts retail (retail pushes 0). Trust the bytes in `pred_disasm.txt`.
- Never compile through `tools/build.py` by hand; use `build.sh`/probe only.
- Retail byte addresses in `pred_disasm.txt` are absolute (base 0x1C5E30).
- Pre/post `add esp,0x10` ESP rebasing: pre-adjust slot N = post-adjust N-0x10; earlier
  "slot swap" confusion came from mixing these two bases. Slots listed above are all
  post-adjust and verified consistent.
