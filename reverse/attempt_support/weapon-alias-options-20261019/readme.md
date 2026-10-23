# Weapon caller: alias-optimization controls

At BFME 2 revision25166aafc7 and verified BFME 1 revision6b9d92bf, the unchanged
complete caller bank reproduces955B with eight differing bytes after the local
helper is independently proven exact and bound only in a diagnostic resolver.
The199B helper remains exact with the genuine caller. Both banks are unchanged.

The remaining differences are frame30 versus24 and seven bonus addresses.
Native parent002CE30A..002CE6C5 uses a24B bonus at EBP-24; the bank keeps it
disjoint from later target coordinates at EBP-18. Prior provider-visibility,
typed-boundary, constructor, scope and authenticated-compiler trials were read
and were not repeated. The existing six-float computeBonus/append/constructor
owners independently confirm the24B bonus; no smaller object is justified.

New hypothesis: ordinary alias-optimization settings could affect dead-field
or stack allocation. Four isolated official explain_mismatch builds test the
unchanged baseline, /Oa, /Ow and /Oa /Ow. /Oa produces950B with extensive new
differences; /Ow and the combined setting produce955B with53 differing bytes.
All retain the original frame/bonus mismatches. All four helper copies remain
whole199B exact, with no unresolved calls. This hypothesis is refuted; no
production flag change is warranted.

Baseline differing offsets are5/18/1D/E6/130/1A9/2E4/2F1 (hex). The original
banks remain the best resumption point. The exact helper still needs its real
caller to land, and the caller still needs a supported stack-allocation
explanation. No artificial overlap, expired pointer, shorter bonus, synthetic
caller, pin, source edit or verifier change was introduced.

Reproduction artifacts are build/weapon-alias-oct19/hypotheses.md, probe.py,
results.json, four isolated .cpp sources and their -explain.txt outputs. The
script uses normal explain_mismatch compilation, then read-only byte probes;
it asserts that the original caller bank is unchanged. /Oa and /Ow are the
only source-flag differences. Existing handoffs002cb594-return-value.md,
002ce30a-real-caller.md,002ce30a-lifetime-visibility.md and
weapon-private-types-20261019/readme.md retain identity and earlier evidence.
