# MilesAudioManager 0x0005BE59: exact getter/lifetime recovery

Recovered the 789-byte view-scoped audio volume refresh in its existing home,
`Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`.
Input revision: `7db94a8c3b7ca5cc92384588b419ff1779f01e15`.

The existing inline `AudioEventRTS::getViewType()` returns `m_viewType`.
Using that accessor in both the 2D-sound and stream loops, together with a
function-scope `pan`, reproduces retail register allocation and stack packing.
The music-loop accessor is optional for byte identity; the landed body uses the
same accessor consistently. No helper, flags, volatile access, side effect,
padding or artificial temporary was added. The WorldBuilder evidence in
`miles-5be59-queued-end-first-20261020.md` supports the wider pan lifetime and
inline getter expressions.

## Controls

- Original bank: 789 bytes; six stack-slot differences at +A1,+A4,+B3,+BC,+13F,+15F.
- Wide pan alone: 766 bytes.
- Original narrow pan plus all getters: original six differences remain.
- Wide pan plus only the 2D getter or only the stream getter: 766 bytes.
- Wide pan plus both getters: 789 bytes, exact after relocation.
- Adding the music getter preserves exactness.

This interaction explains why prior single-getter probes did not solve the
frame-slot exchange. It does not support the older missing-memory-kill theory.

## Independent verification

Two Astra workers independently compiled the complete translation-unit candidate
with `BFME_OBJSTORE=off`; full raw function extent is 789 bytes. Raw SHA-256:
`e12221116fea12dcd81ef893c696a8f00b8ee5c491402b8c6ae1f4d3a6b679bb`.
All 28 REL32 destinations and five DIR32 operands were checked separately:
three named mss32 IAT entries, the EH handler and FS `__except_list`.
The 18-byte EH handler and 36-byte exception metadata, including all five EH
relocations, are exact. The source change also passed independent semantic review.
Scorer's `masked=false` alone was not used as proof of DIR32 correctness.

The ordinary final-path `add_match.py` gate passes all 335 function rows in this
source, 19 string literals, 32 compiler floats, 105 named imports and the source
data row. Explicit EH verification reports 77 EXACT, zero baseline debt, zero
missing objects. Converged-data checking reports zero second names and zero
unjudged rows; declared-definition checking passes.

The bounded link preview still reports this TU does not link against the old
2026-10-18 census (`2d2ca9cd35`), with existing unresolved names and competing
providers. This recovery claims byte/EH coverage, not new linked coverage or a
runtime result. No full link cycle or census was run.

Target game.dat SHA-256:
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
Model: gpt-6-astra, with independent gpt-6-astra candidate and semantic reviews.
