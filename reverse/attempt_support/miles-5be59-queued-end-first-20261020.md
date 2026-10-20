# MilesAudioManager 0x0005BE59: queued end-first closes the music-loop wall

Target: `?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z`, retail RVA 0x0005BE59, 789 B, RET 0xC, home unit `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp` (measured against the unit at c1701c17f3, which already carries the visible `__declspec(noinline) inline` rva0005A9F8 copy and both AIL imports). The banked body is the earlier bank's body appended to that unit, with one change.

## Result

The new bank compiles to 789 B with 0 structural regions. The only remaining defect is a frame-slot exchange in six instructions of the 2D and 3D blocks.

| body | size | structural regions | memory | register |
|---|---|---|---|---|
| previous bank (re-applied to the current unit) | 782 B | 4 | 14 | 8 |
| new bank (queued end-first) | 789 B | 0 | 8 | 1 |

Both memory counts include three `call dword ptr [import]` lines that are relocations. Measured with `tools/align_diff.py <unit> ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z 0x0005BE59 789` after deleting the unit's cached object.

## The lever that closed the music loop

The queued loop now computes its end before its begin:

```cpp
QueuedAudioEvents::iterator queuedEnd = m_queuedEvents[viewType].end();
for (QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin(); event != queuedEnd; ++event) {
```

With begin first, viewType's last use is the end index, and cl loads viewType afresh after the music loops (`mov eax,[ebp+10h]; mov ecx,eax; add eax,13h`). With end first, the begin index is the last use, so cl keeps viewType in EAX across the whole music section, exactly as retail does: `mov ecx,eax; imul ecx,ecx,50h` before the outer loop, a reload `mov eax,[ebp+10h]` only on the inner deque loop's natural exit, and `lea ecx,[eax+13h]; imul eax,eax,0Ch` after it. Because the two inner-loop exits now differ, cl no longer cross-jumps the guard into the bottom test, and the inner loop is rotated (`cmp [ebp-30h],esi; je`) like retail's.

How it was found: a throwaway `g_sink = viewType;` placed just before, inside (outer level) or just after the music loop reproduced retail's EAX carry and rotation; the same store at the function top or inside the queued loop did not. So the wall was a one-reference register-priority gap local to the music/queued stretch, and the natural spelling that supplies it is the end-first queued loop.

## Remaining mismatch: frame-slot grouping

Retail puts volume (2D spill), sample3D and the music-loop counter at `[ebp-18h]` and pan alone at `[ebp-20h]`. Ours puts pan and the counter at `[ebp-18h]` and volume and sample3D at `[ebp-20h]`. `this` is at `[ebp-1Ch]` in both. Affected retail offsets: +0x9F, +0xA2, +0xB1, +0xBA, +0x13D, +0x15D.

Evidence about the cause: declaring pan at function scope, as Zero Hour's `adjustVolumeOfPlayingAudio` does (`Real pan;` at the top), gives retail's grouping (volume, sample3D and counter share one slot, pan has its own), which fits pan's lifetime spanning the later loops. But every pan scope wider than the 2D `if` blocks (function scope, the 2D loop body, a block around the 2D loop or around loops 1 to 4, a nested block holding only the two AIL calls, or an inline helper owning pan) switches the body to a different allocation: 766 B, 18 regions, `this` in EBX for the whole function and no EBX cache of the PlayingAudioRef pointer. Replacing the `AIL_sample_volume_pan` call with a visible non-leaking writer in that variant still gave the same register shape, so pan's escape is not what changes it.

Ruled out this session (all measured, all left the slot exchange in place or regressed): pan declared after volume, pan in the outer `if` block, volume declared at the outer `if`, loop-body or function scope, `sample` and/or `sample3D` at function scope, one shared `sample` for 2D and 3D (worse), a named volume in the 3D block, the counter spelled `!= 2`, `unsigned` or post-increment. With function-scope pan, sixteen combinations of iterator order, pan position, function-scope volume, sample and event locals and a shared 3D iterator all stayed at 766 B; extra throwaway uses of `this` or of the playing pointer did not restore the 789 B allocation either.

## Next experiment

Find why a function-scope address-taken float changes cl's choice for `this` (EBX for the whole function instead of ESI split around the movsd copies) and drops the PlayingAudioRef pointer web. A start would be compiling the function-scope-pan variant with one earlier bank lever changed at a time (the by-value rva0005A9F8 read, the 3D event local) to see which of them interacts with pan's scope.
