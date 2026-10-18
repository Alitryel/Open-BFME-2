The predictor bank is still unmatched: the repaired body emits 769 bytes for
retail's complete 768-byte boundary, 001C5E30..001C6130. This evidence claims
dispatch equivalence on the enumerated cases, not exact bytes or pixel decoding.

The previous bank at e3c94fc435 read `y` before assigning it in the unfiltered
branch. It also contained equal-arm conditions and volatile casts used to shape
the compiler. The repaired bank loads both motion components before computing
their phases, removes those expressions, and uses unsigned arithmetic and the
retail x86 shift-count mask for the threshold calculation.

`oracle.py` executes retail and the compiled bank in separate Unicorn instances.
It relocates the actual COFF body, stubs the four named or indirect callees, and
compares their argument traces and final instance memory. It checks cdecl stack
balance and EBX/ESI/EDI/EBP preservation. Cases include all 256 size-threshold
values, signed motion, all six block positions, source-frame choices, filter
modes, variance boundaries, and a builder callback that changes the motion
vector. Pixel-producing callees are not executed.

The old bank fails 470 of 1,238 cases. The repaired bank passes all 1,238.
The JSON reports bind the source, compiled body and retail body by SHA-256.
RTM, DDK 4035 and SP1 compile the corrected source to the same remaining shape;
the C frontend does not resolve it either.

To reproduce with the repository's compiler dependencies and Unicorn 2.1.4,
run from the repository root:

```text
python3 tools/explain_mismatch.py ?Rva009B5530Prepare@@YAXPAURva009B5830State@@PAXH@Z --rva 0x001C5E30 --size 768 --source reverse/attempts/0x001c5e30.cpp
python3 reverse/attempt_support/predict-filtered-bank-repair-20261018/oracle.py
```

Clean room: only spec `reverse/vp6_cleanroom/specs/001c5e30.md`, retail and this
repository were used. No external decoder source was consulted.
