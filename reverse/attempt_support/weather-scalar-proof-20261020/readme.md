# Weather scalar address-detector investigation — blocked

Model: GPT-6 Astra subagent, with independent review by the Codex lead and
repair seat. Input revision: `3d009a9247912b1251d375f2f9e57a19d4703aea`.

This is an incomplete verifier experiment, not an approved relaxation. Keep the
existing address finding until the counterexamples below are closed. No game
source, ledger, pin or baseline change is part of this investigation.

## Correct-work reproduction

At the inspected upstream state `3d009a9247`, `link_debt.addresses` classifies
`0x886655` in `WeatherSettingCtor.cpp` as an image address. The source passes this
literal to `RGBColor::setFromInt`. The lead ran the normal Weather/color build:
16/16 functions and 20 float references passed.

- Caller: `??0WeatherSetting@@QAE@XZ`, RVA `0x201618`, full extent 503 bytes.
- Immediate PUSH: caller +`0x175`; direct CALL: +`0x185`; REL32 field: +`0x186`.
- Callee: `?setFromInt@RGBColor@@QAEXH@Z`, RVA `0x4edf`, full extent 76 bytes.
- The full callee masks three byte channels, converts them to floats, scales
  each by binary32 `1/255` (`8180803b`), stores three floats, and returns with
  `RET 4`. Its sole relocation at +8 resolves to the matching float pool.
- Actual selected provider: `^code_^libraries_^source_^w^w^vegas_^w^w^math_color.obj`.
- Caller source SHA256:
  `0ce829e5ff1b545f302b81383e8534db1dc5b73ca3c98abb7e4ecd545e4738c9`.
- Caller object SHA256:
  `088ab893e8b2b3789a1d1929b50ea58efa4451e499ed67cb5c68efc422fec7bd`.

`reproduce.py` reads the current normally built objects, narrow ledger rows,
retail bytes and the published link index. It performs no compilation or
publication. Its positive result requires the candidate patch to be applied.
With that patch it reports text-only `["0x886655"]`, compiled-proof `[]`, and
the selected whole-callee proof succeeds.

The lead's normal link preview confirmed removal of this address finding, but
Weather still reports 0 linked bytes because of five existing unresolved
virtual-dtor/slot names and the Overridable vtable COMDAT. The color unit remains
linked at 656 bytes. This investigation does **not** recover 503 linked bytes.

Fade's `0xDCF0FA` and the asset reader's `0x544558`/`0x424F58` remain conservative
findings; their different machine uses were outside this experiment.

## Candidate design and its limit

`candidate.patch` changes four existing tool/test files. It retains text-only
behavior and the staged pointer-cast check. The optional path checks current
source/object inputs twice, full caller masked bytes, disjoint decoded operand
relocations, the direct PUSH-to-CALL path, exact native call target, the actual
selected provider, and the callee's complete bytes and every relocation. It
recognizes the complete byte-channel instruction idiom, without exempting a
function name, RVA or literal value.

Unrelated caller relocations outside the scalar window remain the ordinary
link checks' responsibility. This was intended as a scalar-use certificate,
not a whole-caller identity verdict. Normal receipt currency is used here with
content rechecks; existing strict preparation/census contracts are unchanged.

Additional refusals cover unknown/wrong callees or providers, operand overlap,
invalid COFF bounds and indexes, alternative instruction entries, source/object
changes, repeated raw values, same-body folded pointer arithmetic, explicit
ESP aliases, negative ESP accesses, and post-call stack descent or calls.

These restrictions still do not prove that the source literal has no other
compiled pointer use. **Do not apply the patch to active verification as-is.**

## Independently confirmed false accepts

`review_counterexamples.py.txt` imports the candidate's real-COFF fixture.
The lead ran it centrally; all three refusal assertions fail because the
candidate incorrectly clears the finding:

1. `push ebp; mov ebp,esp; sub esp,4; push colour; call RET4 consumer;`
   `mov eax,[ebp-8]; mov [eax],1; leave; ret`.
   The popped argument survives in the frame and becomes an address through EBP.
2. One source constant feeds the scalar consumer in one function and a folded
   `x+1` pointer in another exact function. Scanning only the original DWORD
   and the scalar caller misses the second function's distinct pointer value.
3. The same `x+1` pointer is emitted in static data, again with only one source
   occurrence of the original constant.

The independent seat's first sandbox run raised a Capstone DLL access error,
which the conservative failure path caught. Those apparent passes were invalid
evidence. The central run established the three false accepts.

To resume in an isolated checkout of the input revision, inspect and apply
`candidate.patch`, build the Weather/color units normally, and run:

```
mkdir -p build/weather-scalar-review/replay
cp reverse/attempt_support/weather-scalar-proof-20261020/review_counterexamples.py.txt build/weather-scalar-review/replay/test_review_counterexamples.py
python3 -B reverse/attempt_support/weather-scalar-proof-20261020/reproduce.py
python3 -B -m pytest build/weather-scalar-review/replay/test_review_counterexamples.py -q -s --basetemp build/pytest-weather-review
```

The first command is the positive reproduction; the second must currently
report **3 failed** assertions. The tests import the COFF fixture added by the
candidate patch, so the unapplied bank is intentionally not a runnable verifier.
The `.py.txt` suffix keeps default pytest discovery from collecting this bank.
`receipt.json` preserves the successful positive run before reverting the tool
experiment. `sha256.json` identifies the retained evidence files.

## Validation performed

Final local narrow command (with the candidate active):

```
python3 -B -m pytest tools/tests/test_link_debt.py tools/tests/test_gate_exploits.py -q -s --basetemp build/pytest-link-address-20261020-stack-safety
```

Result: 80 passed, 1 skipped. Every existing gate exploit remained refused, but
the later independent counterexamples show that this suite was insufficient.

Ten relevant link_check/link_census modules: 303 passed after separately
observing and deselecting two unrelated Windows failures:

- `test_link_census_history.py::test_census_dates_are_utc` calls unavailable
  `time.tzset()`.
- `test_link_check_decoder_policy.py::test_boundary_policy_move_during_read_fails_closed`
  did not observe its same-size file mutation in the stat identity check.
  `decoder_policy`'s AST is identical to HEAD. No change to that policy was made.

## Next concrete prerequisite

A sound exemption needs either receipt-bound preprocessed literal-use binding,
or a bounded proof that accounts for the entire object's folded code/data uses
and the caller's actual frame/argument-slot lifetimes. A source regex plus
literal counting is insufficient because aliases and macros can propagate the
constant.

For Weather's EBP separation, the frame starts through the 31-byte
`__EH_prolog` at `0x629188`, then calls StringBase construction, the
`Rva00200D38` constructor, releaseBuffer and set before the scalar site.
Proving frame separation must account for their stack effects rather than
trusting decorated names or a trailing RET in isolation.

A naive whole-data DWORD scan is also not ready: Weather contains ordinary
string bytes `tga\0` and `her\0` whose little-endian values fall inside the image
range. Any string/data distinction must be independently justified, not a new
name/value whitelist. No such extra proof was completed in this attempt.
