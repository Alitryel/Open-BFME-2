Radar alpha masks and signed maximum (2026-10-18)

Target facts: rowed render caller 0x00050125 passes VA BC4E80 to private
helper 0x4F29B and BC4E84 to 0x4F037. The former reflects two indices with
domain 0..1; the latter reflects domain 0..2 with stride three. Retail bytes
therefore give complete 2x2 (4 B) and 3x3 (9 B) quarter masks. Three zero
alignment bytes follow the second mask before the float at BC4E90; these
are not claimed as mask data. No donor layout or semantic name is asserted.

The old extern declarations are now initialized arrays with the same names
and types. Two data_rows entries verify sizeof and every initializer byte.
A file-local signed max overload retains the standard comparison/reference
semantics without emitting the incompatible external helper.

Acceptance: build.sh and link_check --prepare-current verify the 2/2 function
rows and 2/2 data rows, with strict reusable receipts. data_check --enforce
has zero findings; --converged has zero second names and unjudged rows.
check_csv passes 96634 functions, 15999 symbols, 929 data rows.

Additional read-only use of build.compile_function on the current object,
allow_weak=False, checks all five existing static helper symbols at their
retail RVAs: 4DF6F/569 B, 4E55B/71 B, 4E704/206 B, 4F29B/605 B,
4F037/612 B. Each equals its complete retail body, has no unresolved
relocations, and uses no masking. No raw compile API was invoked.

Same-index current-object link_check, census c2c5ac8c27 (2026-10-18 11:36):
before 0 B, blocked on two masks and signed max; after LINKS, 1054 B.
This is +1054 B legacy predicted linking. Self-strict verification passes;
closed-strict linking is not measured. Authored C++ coverage is unchanged.
Ignored raw logs: build/seat-link-oct18/radar-{before,after,build,data,strict,helper-check}.log.
