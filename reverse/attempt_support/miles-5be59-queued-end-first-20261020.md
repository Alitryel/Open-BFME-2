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

## Session 2026-10-21: why wide pan flips the allocation (bank unchanged, 0.99)

Retail's loop 1 keeps the PlayingAudioRef pointer in EBX and reloads the event (`push [ebx+1Ch]` at +0x86). With function-scope pan (variant "pantop", 766 B), cl instead holds `this` in EBX and CSEs the event into EDI (`push edi`). The new findings below separate the two allocations.

- **An exact body exists if get2D clobbers memory.** pantop plus a global store in `get2DSampleHandleForPlayingAudio` (0x52696), `int g_probeW; ... g_probeW = 1;`, compiles 0x5BE59 to retail's 789 B. But that store breaks 0x52FA0's bytes, so the real get2D is pure. Dead or volatile forms of the same store (`if (0)`, `while (0)`, `0 &&`, `__noop`, volatile reads, static locals, uncalled killer helpers) do not reproduce the effect.
- **The function sits on a register-pressure threshold.** Cutting pantop's queued loop ("cut5") restores retail's loop-1 shape, and loops 1 to 3 then match except for the this/pan slot swap. Adding two or three trivial top-level `if` statements to cut5 flips it back to the CSE shape.
- **Only pan's own scope moves it.** On the bank (pan inside `if (sample)`), nothing flips the allocation:
  - extra uses of `this` or `playing`, at the start or the end;
  - extra `if` statements at the end;
  - unrelated wide address-taken int or float dummies, including one that mimics pan's `AIL_sample_volume_pan` write and read.

  Every scope for pan wider than the inner block flips it: function, `playing`, the loop, after the loop, or a wrapping block. Where pan's scope starts inside the `if` (before or after `sample`, first or last) makes no difference.
- **Typed parameters have no effect.** `const AsciiString &`, `float` or `int` for the slot, value and index parameters change nothing, because the copy locals coalesce.
- **WorldBuilder twin details** (0x79F2C0, 2289 B, unoptimised):
  - the queued loop takes `end` first (`local_c`), then `begin` (`local_50`), which matches the bank;
  - the 592B8 argument is spelled `*playing->m_event` (operator* 0x7AD4D0, assert line 253);
  - `isEmpty` is inlined in WB but is a call in retail;
  - the event name goes through a ReferencePtr `operator->` (0x401032 → 0x239099), then virtual `[+4]` getEventName, then StringBase::compare.

  The `value` float parameter is unused in retail; the caller passes -1.0f.

Next angles, untried:

1. With pan in-block, which keeps retail's allocation, look for a slot-packing lever in variable processing order, for example the declaration order of sample3D against volume, or the shape of the 3D block.
2. With pan wide, look for the natural source change that supplies the memory-kill effect `g_probeW` had. Examples: a real call in loop 1 that the bank currently inlines, or a non-inline `PlayingAudioRef::operator=` / `get()` (WB inlines operator=).
3. Check the music-loop entry shape (cut5 showed jmp against a top test).

Scratch generators for this session (untracked): `build/s5be59/gen.py` (`_g2dmod` probes), `mk.py`, `l1.sh` (loop-1 signature: retail shows `mov ebx,[ebp-10h]` and `push [ebx+1Ch]`).

## Session 2026-10-21 (claude-opus-5-5): the whole residue is one event CSE across get2D

The bank is unchanged (789 B, 0 regions, slot exchange only). The probes ran on the full owner unit replayed with the bank (`build/s5be/v/.../base.cpp`, scratch).

**Diagnostic exact (must not land).** Widen `pan` to function scope as in ZH, which gives retail's slot grouping by itself. Then force the loop-1 `rva000592B8` argument to reload the event:

```cpp
rva000592B8(*(AudioEventRTS *volatile *)&playing->m_event);
```

That compiles to 789 B, 0 regions, memory 3 (the three import relocations) and register 0, which is byte-exact. Without the volatile, wide pan gives 766 B with 18 regions: `this` moves to EBX, and `playing->m_event` is CSE'd into EDI across the pure in-TU `get2DSampleHandleForPlayingAudio(&playing)` call (0x52696, 47 B). Retail reloads it (`push [ebx+1Ch]` at +0x86, with EBX = playing.m_ptr). So with wide pan, the only missing thing is that one memory kill between get2D and the 592B8 argument.

Inert this session. Each gives the same 766 B / 18 regions with wide pan, or the bank's result with in-block pan:

- `permute.py --flags`, 7 flag sets: best 0.9918, no close;
- random permute: it stops with "only constants or offsets differ";
- branch-weight probes s1, s3, s4: confirmed again that slot packing is by static weight only;
- dummy-local k-scan wk0..wk11;
- one `__forceinline` kdum expansion of k = 0..20 parameters (the 0x2FD344 lever) before the body, before get2D and after the 592B8 call: all 63 inert;
- `*playing->m_event` spelling (operator*, as in WB);
- an in-TU noinline stand-in for 592B8 (wq1, wq2);
- a nested `if`, `getViewType()`, or `continue` in loop 1.
- wide pan plus function-scope `sample`, `volume` or `sample3D` (alone or combined; sv1..sv9): slot map unchanged (-28 pan, -24 {tv287, sample3D, volume}, -20 {tv794, sample}), still 766 B / 18 regions; `volume` inlined into the `AIL_set_sample_volume_pan` call (sva): 755 B / 21 regions.

The WB twins call the same get2D, so there is no ICF twin. Retail has no vtable reference to get2D.

**Reading.** Retail loads `[ebx+1Ch]` three times in loop 1: at +0x50 (name), at +0x69 after the opaque compare call (viewType test), and at +0x86 after get2D (the 592B8 argument). EBX (`playing.m_ptr`) survives get2D. So retail did not treat get2D as an opaque call. Either the +0x69/+0x86 CSE candidate never existed in retail's source, or it lost register priority and was rematerialised. That is what in-block pan gets right and wide pan gets wrong.

**What a closer needs.** A natural source in which the event is not available in a register after get2D, with pan at function scope. The earlier handoff showed that a global store inside get2D supplies the kill, but it breaks 0x52FA0, which relies on get2D being pure.

Untried:
- an event read through a non-inline or out-of-TU accessor of `PlayingAudio` (for example a `getEvent()` member defined in another TU);
- a 592B8 argument taken from a local copied before get2D, once its lifetime is restructured;
- calling get2D through a member pointer or an out-of-TU wrapper, which would make the call opaque only at this site.

Scratch for this session (untracked): `build/s5be/vg.py`, `run.sh`, `score.sh`, `rdis.py` (retail capstone), `kg.py` (kdum scan).

## Session 2026-10-21b (claude-opus-5-5): WB frame says wide pan; loop-1 reload is an allocation outcome

Bank unchanged (789 B, 0 regions, memory 8, register 1).

**WorldBuilder frame (0x79F2C0, /Od).** Named slots: `it` -4 (one function-scope iterator shared by loops 1, 2 and 3), `playing` -8, `queuedEnd` -0xC, `pan` -0x10, `sample` -0x14, loop-1 `volume` -0x18, `sample3D` -0x1C, loop-2 `volume` -0x20, loop-3 `volume` -0x24, `musicSystem` -0x28, music `end` -0x38..-0x2C and `begin` -0x48..-0x3C (deque iterators, `begin` copied from +0, `end` from +0x10), `MusicStack &stack` -0x4C, queued `begin` -0x50. A calibration probe of this /Od compiler put function-scope locals first, then nested scopes in source DFS order. `pan` sitting with `it`, `playing` and `queuedEnd`, ahead of `sample`, therefore means function-scope pan, as in ZH.
- Loops 1 and 2 have the same source shape: `playing->m_event->` (operator-> calls), the viewType through an inline getter temp, get2D or get3D(&playing), `592B8(*playing->m_event)` (operator*), and a named volume stored and then passed.
- Loop 3 additionally reads `m_info[+0xB0]` through an inline getter temp (`!= 3`).
- The music elements are `PlayingAudioRef`: WB inlines `operator=` with its self-assignment check.
- The queued events are a vector with stride 0x90; their `m_info` ReferencePtr sits at +8.

**get2D is pure in retail.** Retail 0x52FA0 keeps `ESI = *ref` across both get2D (+0xDA) and get3D (+0x86), but reloads `*ref` (`mov eax,[edi]` at +0x108) after the opaque `getGlobalReverbMultiplier` call. The loop-1 event reload in 0x5BE59 is therefore not a callee mod/ref effect. It is a register-allocation outcome:
- loop 1: EDI goes to the iterator and the event CSE is rematerialised; `sample` is spilled to -0x14;
- loop 2: the event wins EDI, and the iterator and `sample3D` are spilled.

The real source (wide pan) must reach that outcome. Ours with wide pan instead gives `this` EBX for the whole function and the event EDI (766 B, 18 regions).

**Slot packing with in-block pan.**
- Retail: -0x18 = {volume, sample3D, music countdown}, -0x20 = {pan}.
- Ours: -0x18 = {pan, countdown}, -0x20 = {volume, sample3D}.

In retail the countdown joins volume's slot, which is again what wide pan predicts. No in-block spelling moved the countdown.

**Disproven this session (scratch `build/s5/`, untracked):**
- genx factorial of 288 variants with in-block pan. Inert:
  - `sample` scope (same block, if-condition declaration, extra block);
  - nested against single condition;
  - three loop-2 forms (event local; the shared `it` with named sample3D/volume; `if (void *sample3D = ...)`);
  - loop-3 volume naming.

  Inlining the loop-1 volume costs 11 B. Only pan's placement moves the result: in-block gives 789/0/8/1, top of the loop body or wider gives 766/18.
- Opaque get2D (declared, not defined in the TU): 796 B, register 36. `playing` is then never cached, so the in-TU escape analysis must see get2D.
- 21 local-rename variants (name-hash order) are inert at /O1.
- The full WB loop-2 shape is inert. The earlier families f1..f12, g, h, r and w are documented in their generators.

**Next angles, untried:**
1. With wide pan, change the weights of the loop-1 iterator against the event candidate, so the iterator keeps EDI and the event CSE is undone. Examples: a `while` form of loop 1 only, `it` re-read as `m_playingSounds.end()` once per iteration, or the shared `it` combined with the WB loop-3 getter temps.
2. With wide pan, change what keeps `this` split in retail (ESI, spilled to -0x1C at +0x14) rather than in EBX for the whole function. The music/queued tail sets the threshold (cut5), so try tail forms that use `this` less, for example `m_queuedEvents[viewType]` bound to a reference first.
