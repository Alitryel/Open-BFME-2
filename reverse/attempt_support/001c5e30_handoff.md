# Handoff: _VP6_PredictFilteredBlock 0x001C5E30 (768 B retail)

Clean-room target. Branch `opencode/goal-1015` (worktree `Temp/opencode/bfme2-goal-1015`,
`BFME_CLAIM_OWNER=opencode-goal-1015`). Claim **renewed** this session — renew again at
session start (`python tools/claims.py renew 0x001C5E30`, 4 h lease).

## Slot maps (decoded, current)
- Retail frame: `sub esp,0x14` + push ebx/ebp/esi/edi → S = ret-0x24; 5 local slots:
  stride [S+0x10], ptr1/adjX/share [S+0x14], x16-ze home [S+0x18], y-home [S+0x1C]
  (reused as mode-2 limit), y32-SE home [S+0x20] (re-load feeds mode-2 vy-abs);
  arg1 slot [S+0x28] holds the `frame` value (incoming-arg repurposed).
- Mine (672 B body): `sub esp,0x10`, 4 slots; x-ze spill landed at [S+0x14] (pushes
  x16 above), walk-accumulator [S+0x24]. Arg-slot offsets shifted by -4 accordingly.
- Retail LF-load block: pos in ECX (`mov ecx,[S+0x30]`), x = `xor eax,eax; mov ax,[..0x24]`
  ZE, y = `movsx ecx,[..0x26]` (pos reg reused as y dest), y32 kept in EBP after
  `mov ebp,ecx` then clobbered by the motionShift load → homes are the only copies.
- Mine keeps y live in EAX the whole walk because my stride/motionShift loads don't
  clobber the y register; my x side already matches (ze bits spill + home re-read
  exactly as retail does).

## Where the work stands
- WIP TU (untracked, freshest copy): `Code/Libraries/Source/VP6/PredictFilteredBlock.cpp`
  — compiles to **672 B** vs retail 768. Entry-region bytes 0x000-0x02E match retail
  (mod relocations). Mode-2 abs needs: limit hoisted to ECX before cdq, vx already in
  EAX at the cdq (no `mov eax,edx` remat), `sub eax,edx` reg form (no `>>31` home spill).
- Prior body also banked via `re_log.py record ... partial --stash` (score 0.9) →
  `reverse/attempts/0x001c5e30.cpp`; commits e3a053741e9 + e91af4e51d9 hold the bank.
- Retail ground truth: `build/probe/pred_disasm.txt`.
- Probe loop: `& 'C:\Program Files\Git\bin\bash.exe' -c 'cd /c/Users/nleig/AppData/Local/Temp/opencode/bfme2-goal-1015 && python build/probe/entryprobe.py 0x100'`
  (arg = INSTRUCTION count, not bytes — 0x100 = 256 instructions covers the whole body;
  first output line = symbol size).

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

## Failed this session (do not retry blindly)
- `short y16 = (short)blockVecs[pos][1]; y = y16;` — in the LF branch AND in the else
  branch (both probed): MSVC folds the chain to the identical SSA; emitted body
  byte-identical (still 672 B / sub 0x10). Typed-small-alias locals do not force
  the y-home commitment here.
- (Prior) `short y16v/unsigned short x16v` pair → 16-bit reg copies `mov cx/di,[mem]`
  and reg-alloc distortion (pbi→ESI, pos→EDI); reverted.
- (Prior) x double-assign `(short)x`-re-cast fuses; do not re-cast after assigning.

## Verified SAME between mine and retail
- Selected-frame logic shape (overwrite form promotes `(mode,cmp)` to entry front).
- Home slots (post `add esp,0x10`): x32 `[0x18]`, y16 `[0x1c]`, y32 `[0x20]`,
  stride `[0x10]`, ptr1Offset `[0x14]`, walk/home `[0x28]`.
- Walk phase regs: phaseX=EBX, phaseY=EBP; tests `test ebx,ebx` / `test ebp,ebp`.
- LF mask re-read → ECX right after the call; stride `[0x10]=0x10` immediate.
- Block 1 walk-inside reload `mov ecx,[esp+0x28]` after the je.

## Remaining deltas (672→768 B, current accounting)
Entry region 0x000-0x02E matches retail byte-for-byte (mod relocations). All remaining
deltas sit in the shared walk/mode-2 machinery, one placement cascade:
- prologue locals: `sub esp,0x10` (4 slots) vs retail `sub 0x14` (5). Mine is missing the
  y16/y32 home commitments; every [esp+N] reference shifts by -4.
- pos: EBX (mine, home [S+0x2C]) vs retail EBP (home [S+0x30]).
- x-load form: mine `movzx ebx,[edi+eax*4+0x24]` + store [S+0x14] vs retail
  `xor eax,eax; mov ax,[edi+ecx*4+0x24]` + store [S+0x18].
- y home commitment (the keystone): retail stores y twice (y16 [S+0x1C] feeding the
  walk-Y `cmp word [S+0x1c],cx` sign test; y32 [S+0x20] feeding the mode-2 vy-abs
  reload) and re-SEs in-reg (`movsx ecx,cx`); mine keeps y live in EAX the whole walk
  → mine's walk-Y sign test emitted `test ax,ax` instead of the home word-compare.
- mode-2 limit block: mine schedules the 0x80 default store above the branch and an
  x16-home load inside the shl region; retail falls through a diamond whose taken
  tail does `mov edx,[S+0x14]` reload + `jmp` over the 0x80 store.
- mode-2 abs: mine has vx in EDX (→ `mov eax,edx; sar eax,0x1f` + `>>31` spilled home +
  mem-form `sub eax,[S+0x18]`) and limit never hoisted to ECX;
  retail has vx already in EAX (`movsx eax,ax` at 0x1C5F0D survives the whole walk)
  and hoists limit to ECX (→ direct `cdq; xor eax,edx; sub eax,edx; cmp eax,ecx; ja`).
- walk block 2 back-end and dispatch shapes reg-RMW details (see probes; mine has
  extra `mov ecx,[S+0x18]` inside the walk cardioid region and shares the walk
  accumulator slot differently).

## Experiments exhausted (do not repeat)
- Any **unconditional** top-level mask statement kills the `(mode,cmp)` entry promotion:
  tested before-default (v5), after-default (v9), `int mode`-first + mask (v11),
  between-ifs (v13). Comma-condition variant `if (mask = pbi->modulusMask, cond)` (v14):
  mask landed `mov ebp @0x34` in the je shadow, promotion dead, 590 B cascade.
- Ternary and if/else forms of frame selection: both lower branchy (2 jmps).
  The overwrite form (default assign + if-overwrite, current) is the retail shape.
- x/y declaration order swap: zero effect (earlier session).
- Mask read deferred to WP first statement + LF inline re-read (v12, current),
  and mask read after x/y in the WP — WP-local EBP either way; never hoists.
- Typed-small-alias locals for y (`short y16 = ...; y = y16;`) in either branch: folded
  to identical output. Small-typed spills do NOT drive the allocator here.

## Not yet tried (concrete next list)
1. **Y-in-ECX force** — the retail y-load lands in ECX and the motionShift/stride loads
   clobber it, forcing the homes. Shape levers: reorder the else-branch statements so
   `motionShift`-dependent arithmetic (adjYShift) precedes phaseY, or introduce a second
   cheap int temp (e.g. `int shift = pbi->motionShift;`) consumed by both shifts in a
   way that occupies ECX earlier. Probe each against `entryprobe.py 0x100`; a win here
   should simultaneously fix the walk-Y home-cmp and the frame size.
2. If that does not move bytes after 2-3 probes, close per the 30-min rule: the banked
   672 B body stands; reconsider only after other seats land VP6 siblings that refresh
   pressure heuristics.

## Also tried (recorded outcomes, do not repeat blind)
2. **Limit-diamond form** — TRIED: `if (st) limit = ...; else limit = 0x80;` gave the
   retail structure (0x80 store sinks into the else tail, taken tail `jmp`s over it)
   but net +2 B (674) and the emitting reg/slot details stayed off (je vs jbe test,
   `mov cl,dl` copy vs direct `mov cl,[mem]` reload, stray `(x16-slot)` load vs
   retail's `[S+0x14]` reload). Reverted to the banked default+overwrite form. If the
   frame-slot fixes land first, retry the diamond after — the two interact.

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
