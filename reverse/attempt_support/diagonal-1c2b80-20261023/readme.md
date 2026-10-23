# DiagonalBlur address-expression follow-up

`_DiagonalBlur`, RVA `0x001C2B80`, complete extent **916 B**, remains partial.
The preserved bank has exactly two differing bytes: `+0xB5` and `+0x138`,
compiled SIB `0B` versus retail `19`. Both are the already-documented commuted
base/index encodings. The existing bank and its score are unchanged.

Only the approved spec `reverse/vp6_cleanroom/specs/001c2b80.md`, retail,
the bank and permitted repository evidence were used. No decoder source was
consulted. No source, header, compiler profile, pin, ledger or gate was changed.

## Previous evidence checked before work

Read the full served history with `/opt/runner/pick-hard --rva 0x1C2B80` and
`reverse/attempt_support/diagonal-1c2b80-20261022.md` plus its diagnostic sources.
That work already distinguishes the positive-pitch lower-left taps from older
incorrect descriptions, measures the C2 temporary-key cause, and rules out a
common temporary-ID rotation as a solution. It also covers loop entry/control
flow, cursor layout and lifetimes, helper/inlining boundaries, ordinary compiler
settings and source-context trials. Those unchanged trials were not repeated.

## New hypotheses and results

The new hypothesis was to change *relative* address temporary creation through
actual computation, rather than add inert locals or rotate every identity.
Every load remains a real consumed stencil sample. Stores stay in pixel order.

- `wide`: signed/unsigned 64-bit offset computation explicitly narrowed to the
  32-bit index; all nonempty nine-tap subsets, with even/odd/all pixel groups.
  **3,067 trials**. Best remains the two SIB bytes. The other two output classes
  introduce one or nine further commuted addresses; neither fixes these SIBs.
- `loadtypes`: read through signed/plain-char views and convert to unsigned char,
  retaining the specified byte value; the same tap-subset factorial.
  **3,067 trials**, all identical to the bank's output.
- `loadorders`: permutations of the first five and last four actual sample
  initializations in pixel zero, pixel one, or both. Reads are reordered only
  within a pixel, before its store. **8,641 trials**, all identical to the bank.
- `unsigned-orders`: combine that initialization-order factorial with the earlier
  unsigned-address lever at pixel zero's lower-left sample. **8,641 trials**,
  all identical to its 916 B control, with 72 raw differing bytes and five
  differing mnemonic regions. Initialization order does not recover scheduling.
- `offsetrefs`: bind const signed/unsigned integer references to actual tap
  indices, trying the same nine-tap subsets and pixel groups. **3,067 trials**;
  every changed candidate is worse than the control. The closest changed
  candidate is 916 B with 13 differing bytes.

Counts include repeated controls and equivalent compiled outcomes; they are
scored records, not independent hypotheses. No input restriction, padding,
assembly, fabricated callee or equal-arm expression was introduced.

## Reproduction and remaining problem

The companion directory preserves the control, isolated ordinary-compiler
scorer, five generators and summarized full-extent results. Copy its `.txt`
files to their original names in `build/diagonal-1c2b80-20261023/`, then run
`search.py`, `loadtypes.py`, `loadorders.py`, `unsigned-orders.py` and
`offsetrefs.py` from the repository root. Every object has its own private path;
the shared `build/match` cache is not used.

The strongest prior bank remains preferable. There is no missing callee or
layout prerequisite. A useful next attempt must change relative temporary
identities or repair scheduling around the unsigned-address alternative; merely
reordering these real sample declarations or changing their byte-load type is
now concretely disproved. The function still requires exact byte verification
before any recovery row can be added.

Inputs: BFME 2 `17471328f5`; BFME 1 verified pointer
`42bba2ddbd5cb895d99293583891d3b7315fa49e`, with no donor dependency here.
Compiler and retail hashes, extent checks, errors and score classes are in
`proof.json`. All **26,483** records compiled without error; none was exact.
Approximately **t=15 minutes**, model=Codex-GPT-6.
