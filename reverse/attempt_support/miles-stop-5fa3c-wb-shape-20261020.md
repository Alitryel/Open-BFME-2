# Miles stop-chain: WorldBuilder shape and the loop-1 CSE wall

Result: blocked for `?rva0005FA3C@MilesAudioManager@@QAEXI@Z`, RVA `0x0005FA3C`, 910 bytes. The score-0.99 bank `reverse/attempts/0x0005fa3c.cpp` is unchanged and still the best body: 918 bytes, structural/memory/register 1/0/0, the only region being retail `+0xBD` `jg` against the bank's `setle al; test al,al; je; mov eax,[esi+0x1C]`. Base revision `e36c11916fab2c1c2a2ef8881096bb71a5eb142f`, BFME 1 reference `cf0a80c228583af789772b794ab27abcab2debbf`. Model `claude-opus-5-5`.

## New target evidence: the WorldBuilder twin

`python tools/wb_show.py 0x0005FA3C` pairs the body with WB `0x00792D90` (6514 bytes, match score 1.0 by call graph). Its unoptimised code fixes the source shape of every block:

- The whole body sits under one `if (handle >= 5)` (a materialised bool, false jumps to a closing INTENSIVE_AUDIO_DEBUG log), not an early return.
- Loop 1's found block is `--event->m_at80; if (<hold> <= 0) { event->m_at4C = true; if (!<BitIsSet>(info->m_control, 0x10)) processAudioCompletion(audio); } else { DEBUG_LOG(" [Not physically stopped, ref count ..."); return; } break;`. The test is a direct `cmp; jg` on an inline getter's return value, so the bank's named `bool stopped` is not the original spelling.
- Loops 2 and 3, the queued events, the current music, the music stacks, the request set and the request list all use the same `if (<hold> <= 0) { ... } else { return; }` shape, and every held branch except the current music's logs the remaining count before returning. In release these compile to exactly what the bank's `if (x > 0) return;` spellings give (trial `wfb`: bank loop 1 plus WB shapes everywhere else, 918 bytes 1/0/0, identical).
- Handle and hold reads go through inline getters (return-value temporaries), the control test through an inline BitIsSet whose arguments are evaluated right to left, and the event's +0x08 info through a member call on a reference object.

## Why the direct form fails

With the WB shape for loop 1 (trial `w1`) cl emits 902 bytes, 13/23/6: retail's block order and the `jg` to the release-and-return block are reproduced, and the +0x4C store reuses the event register as retail does, but cl CSEs `&audio->m_event` into `lea r,[audio+0x1C]` because the found block has three loads through it (decrement, compare, control test) in one fall-through region. That removes two references of the audio copy, which then loses ESI to the iterator, and the handle parameter is cached in EDI (`mov edi,[ebp+8]`, live range split around loop 1), so loop 2 loses its `or edi,-1` EH-state register. Diagnostic `v16` (the control test dropped, semantics changed, scratch only) has no lea and reproduces loop 1 exactly, which isolates the third load as the trigger. Retail has the same three loads and no lea, so some source difference still unknown keeps cl from forming that CSE.

The bank avoids the CSE only because its bool's set/test diamond splits the region, at the cost of `setle` clobbering AL and the reload. Every `if (x > 0) return;` spelling (`d1`, `ka`, `e1` empty then-arm, `g1` goto, `v5` continue form) avoids the CSE and keeps the allocation, but cl tail-duplicates the return path inline after a `jle` and places the found block between loops 1 and 2: 918 bytes, 2/0/0.

## Ruled out this run (all measured with align_diff, sizes in bytes, regions/memory/register)

- Direct `<= 0` forms: `d2` (if-break-return), `w1` (WB if/else then break), `f1` (store-only then-arm), `s1` `x--`, `s2` `-= 1`, `s3` `0 >= x`: all 902, 13/23/6.
- Inline helpers that fold away: free predicates on the event or PlayingAudio (`p1`..`p4`), member getters for handle and hold (`mg`), `.get()` spellings (`v11`), info through `AudioEventInfoRef::get()` (`h3`), out-of-class smart-pointer `operator->` (`oa`, `ob`): all 902, 13/23/6; `obk` on the bank 918, 1/0/0.
- WB top-level `if (handle >= 5) {...}` wrapping (`w2`): 902, 13/23/6.
- Guard and request spellings meant to lower the handle's weight: flat `audio.get() && ...` guards (`t1` 923 17/21/6, `t2` 900 15/23/6, `t4` 925 15/21/6), BFME 1 donor-style `request->m_request == 0 && matches(handle)` (`t3` 901 18/30/11; on the bank `b3` 917 6/7/5).
- Other found-block shapes: positive bool `held` (`kg` 923 2/0/0), control test as an early break (`kh` 908 5/15/6), inline `bitIsSet(unsigned,unsigned)` (`g1b` 909 14/23/7, also turns the byte test into `shr`/`test al,1`).

## Next step

What is open is why retail's compiler did not CSE `&audio->m_event` across decrement, compare and control test. One weak candidate is untested: WB inlines the plain getters but calls both smart pointers' `operator->` out of line, which suggests template members defined outside the class; a non-template out-of-class definition (`oa`, `ob`) changed nothing, so a template form is unlikely to differ. Repeating the spellings above is not worth a seat; a new lead has to explain the missing CSE first. Trial sources and raw align and explain logs are under `build/s5fa3c/` of the seat that ran this (`summary.txt` lists every measurement, `wb.log` is the WB dump, `hypotheses.md` the pre-registered hypotheses).
