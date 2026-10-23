# 0x001C5E30: exact clean-room closure

Native boundary: 0x001C5E30..0x001C6130, 768 B. The existing pinned cdecl
identity `Rva009B5530Prepare` is retained. The spec calls this
VP6_PredictFilteredBlock; layout, callback arguments and frame selection come
from `reverse/vp6_cleanroom/specs/001c5e30.md` and retail, not decoder source.
No external decoder implementation was read.

## Decisive interaction

The incoming 0.975 bank actually compiled to 768 B with 22 differing bytes
under MSVC 13.10.3077, `/O2 /G6 /DNDEBUG /MD`. Replacing only `abs(y)` with
`abs((int)mvy)` restored retail's unfiltered Y register but disturbed the
filtered arm and shortened the body. Keep both equivalent captures alive with
`pbi->profile ? abs((int)mvy) : abs(y)` at the magnitude test instead: this
recovers every instruction/register with 12 stack-displacement differences.
Both captures represent the same signed 16-bit value, including after the
loop-filtered builder has changed the vector.

One 542-trial `permute.py` run reached a six-byte gap. A 32-way factorial
showed its only causal edit was moving filtered `yPhase` before `offset2`:
the native stack homes then matched, but `mov ebp,ecx` preceded the offset2
store instead of following it. The `/Op`, comparison reversal and declaration
swaps in that winner were inert and were removed.

A seeded family of valid topological orders of the filtered setup closed the
remaining scheduling gap. The landed order is base, stride, offset1, offset2,
raw X, promoted X, phase X, raw Y, promoted Y, phase Y. First exact trial:
`filt-order-703`; the completed family had 4,824 valid compiles, 1,189 distinct
bodies and 18 exact variants. This interaction was absent from earlier
statement-order searches because those lacked the magnitude split.

## Earlier experiments in this session

Ordinary local field/inline accessor/nested-field wrappers, grouped scalar
fields, extracted setup helpers, actual visible matched provider bodies,
duplicated tail paths, nested sign/offset branches, sign-correction spellings,
raw capture widths, union-backed captures and recombinations did not close the
original bank. Examples: grouped fields 493 trials; setup helpers 217 (108
ordinary-inline helpers did not inline and were rejected); visible providers
37; tail paths 4,600; nested branches 577; offset assignments 577; rounding
2,129; magnitude 1,153; capture widths 1,729; unions 1,189. Local-field
wrappers were retried after generator-only syntax fixes; invalid compiles were
never scored as evidence. No compiler, gate or retail bytes were modified.
Private scratch objects were used, outside the normal match cache.

## Verification

- `add_match.py` ran `./build.sh` and accepted all 768 bytes plus relocations.
- Resolved code SHA-256:
  `4db8db0dc2d1b92c009d33e823955f3c4a75bd9a7cb5adab3f72f3a4784a0e52`.
- The existing 20261018 Unicorn oracle passed 1,238 cases (zero failures),
  including builder mutation and every threshold byte. It checks dispatch,
  arguments, state, cdecl stack and preserved registers; pixel callees are stubs.
- `find_declared_unmatched.py`: all definitions matched.
- `place_bodies.py`: no incidental bodies or pins.
- The published link index at 0fa62a2841 predates this TU, so the normal
  census preview cannot measure its link status yet. No maintainer-only runner
  was started. `link_check.py --new-variants` passed for the new TU, both
  providers and both matched callers; no new competing COMDAT body was found.

The BFME 1 checkout was f890413e75e671748215ba2ef3304aa7953993e9. Freshness
update was skipped under the runner's active codex4 update lock, not marked
successful. Provider-visibility experiments also used clean-room specs
001d8dd0 and 001d8a30. The helpers remain external in the landed TU.
