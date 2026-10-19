# PredictFilteredBlock working-buffer lifetime hypothesis

Read approved spec001c5e30, complete 768-byte retail disassembly, whole repaired
bank, all six RVA attempt records and the prior oracle handoff. No decoder
source is consulted. BFME1 has no permitted same-function donor; this is the
explicit clean-room lane.

Native filtered branch after the real builder reloads the vector mask into ECX,
then loads the working buffer into ESI before fetching x/y via an EBP index.
The corrected bank currently defers that buffer assignment until after phases,
so its dead block index can occupy ESI and its mask uses EBP. Test a real earlier
working-buffer lifetime: assign base immediately after the builder, then retain
all six signed motion loads and phase/threshold semantics. The pointer must not
be loaded before the builder, which may mutate decoder state. Also test moving
the independent constant stride/offset initialization with that early base.
Reject if byte-identical or if alignment worsens without a new target-supported
cause. No volatile, dead throw, equal-arm expression or synthetic caller.

Follow-up: approved spec supplies a two-short motion value. Test a real local
value copy and a const element reference after the mutating builder, preserving
the unfiltered scalar load order. These test whether element lifetime, rather
than independent buffer assignment order, explains index/base register overlap.

Early buffer allocation restores the native ESI load but not the EBP index.
Native then preserves raw short Y and its promoted integer separately, ANDs
phase Y in ECX, spills integer Y, and only then copies phase Y into EBP.
Test deriving phase directly from the genuine short motion value and promoting
the magnitude operand after phase setup, or after filtered setup completes.
Keep X and the entire unfiltered branch unchanged. Compare all three earlier
working-buffer lifetime models; six bounded trials, no synthetic side effects.
