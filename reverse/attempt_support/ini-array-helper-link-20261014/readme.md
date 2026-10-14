# INI compiler array-helper reconciliation

INI's emitted plain vector-constructor iterator was a 50-byte /O2 variant.
The retail owner at RVA 0x00001423 is the 34-byte /O1 iterator. Reuse the existing
part_ldr.cpp compiler anchor pattern to select that exact helper before INI's
ordinary bodies. The anchor and its constructor declaration emit no definition
or undefined dependency. The native iterator has no relocations or EH state.

All 124 INI rows remain exact. Of 174 external function definitions, only the
iterator bytes change. Get_Bool's local labels renumber, but all bytes and
relocation destination sections/offsets remain identical (independently reviewed).
The 18 EH results are unchanged: 17 exact and one pre-existing baseline
Increase_Table_Size .text$x discrepancy. No new EH debt is added.

At the same de7bb30890 census index, current INI findings decrease from seven
to six. Its remaining duplicate Get_String, Buffer/BufferStraw, TPoint2D and
Shutdown findings prevent closure: zero linked-byte gain, zero new authored
bytes. This repair adds two documented optimization pragma hatch occurrences,
admitted through tools/hatch_counters.py with the native-helper evidence above;
the scoped register grants two occurrences and every verifier is unchanged. This is the established
compiler-helper codegen exception, with the complete helper verified against
retail, not a lifted body or a gate workaround.

Donor reviewed: BFME 1 a7c38d3b2597121f178ab5190b3062478823257d. Its
262d3e950 particle-loader duplicate repair was already inherited/inapplicable.
BFME 2 part_ldr repair 6b2b1790b supplies the applicable target-native anchor.
Final eight-source strict verification and data checks are recorded beside
link-inline-emitters-20261014. No shared headers, ledger or pins change.
