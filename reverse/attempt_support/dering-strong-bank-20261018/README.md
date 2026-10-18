This remains a banked reconstruction of DeringBlockStrong_C, not recovered
coverage. Native 001C1AD0..001C22BE is 2,030 bytes; the bank emits 2,031 bytes
with a 0x168-byte frame instead of native's 0x178-byte frame. Similar size does
not mean a one-byte discrepancy: register allocation, stack locations and
pointer induction still differ throughout the body.

Retail's back edges establish two groups of four vertical pairs per row, three
horizontal pairs per group, and eight fully unrolled output columns. Outputs
are held until the whole row has been read. Fusing the per-pair calculations,
using `quality - difference + 32`, and following those loop structures improves
the earlier 1,589-byte draft. Exact instruction-sequence similarity, counting
mnemonics and operands including branch addresses, rises from 0.088929 to
0.261011. Neither source layout trials nor the C90 frontend and authenticated
RTM/DDK 4035/SP1 compiler variants close the remaining allocation difference.

`oracle.py` compares retail, actual relocated COFF bytes, and an independent
implementation of the published spec. All 1,280 full-buffer cases pass. They
cover all 64 sharpen indices, flat/checker/ramp/random inputs, scale values
around the cap, disjoint destinations, exact in-place writes, and three partial
overlaps. Canary bytes, the scale table, cdecl stack balance and nonvolatile
registers are checked. Unlike the predictor dispatch oracle, this executes the
entire pixel-producing native and candidate bodies without stubbing callees.

With the normal repository compiler dependencies and Unicorn 2.1.4, run from
the repository root:

```text
python3 tools/explain_mismatch.py _DeringBlockStrong_C --rva 0x001C1AD0 --size 2030 --source reverse/attempts/0x001c1ad0.cpp
python3 reverse/attempt_support/dering-strong-bank-20261018/oracle.py
```

The JSON report binds source, native and compiled bytes by SHA-256. Only the
published clean-room spec `reverse/vp6_cleanroom/specs/001c1ad0.md`, retail and
this repository were consulted; no external decoder source was used.
