# Attack aim: real kind storage and the generic test API

No exact recovery; keep `reverse/attempts/0x003508c5.cpp` unchanged. Read the
whole bank, all target verdicts, both October 19/20 handoffs and both current
small owner/caller TUs before this attempt. The onExit home remains unfrozen.
No Code source, header, row or pin was changed.

Identity and boundary are unchanged: named WB twin 0xE1F350, the aim-state
callers, and native 0x003508C5..0x00350D15 (1104 bytes, RET 4). The bank gives
1109 bytes with correct source/victim register roles but its eager source-ID
snapshot. Reading ID at the native call site gives 1104 bytes and swaps those
roles throughout. Earlier control-flow, lifetime, visibility, owner/layout and
compiler explanations were reviewed rather than repeated.

New hypothesis follows the successful ElvenWood/shroud container work: the
three template tests are bits 60, 137 and 150 of the actual 218-bit container
at ThingTemplate+0x108. Checked STLport storage and the original generic
ThingTemplate/BitFlags API might change the compiler's intermediate lifetimes
without adding operations. The official ZH BitFlags.h confirms a bitset member
and `Bool test(Int) const { return m_bits.test(i); }`; count 218 comes from target
evidence, not the older donor's enum count.

Sixty-two successfully compiled controls rule out this route on current inputs:

* All eight choices of checked versus byte-view accesses at the three sites,
  both with and without the source-ID snapshot. Checked constant-specific
  adapters introduce word loads/shifts where native uses byte tests. Ordinary,
  Ob1, Ob2 and larger inline-budget profiles give 1108..1127 bytes; no allocation
  improvement. The fully raw control reproduces the retained baseline.
* Generic Int and enum arguments, direct bitset or the donor-shaped BitFlags
  wrapper, raw normalized Bool and raw nonzero-word adapters. Generic checked
  forms can reach 1109 bytes but use a 0x2C frame versus native 0x28 and retain
  the register swap; equal total length to the bank hides worse structure.
* Remove all three obsolete constant-specific adapters after switching to the
  generic API. This is inert. Const bitset indexing reaches the baseline 1104
  native-ID/1109 snapshot forms, including the same global register swap or
  eager-ID residue respectively. No unused helper or mutable proxy was retained.

Thus the extra standard-container layer does not supply a natural exact use of
the source pointer here. This family differs from the ElvenWood success. Do not
retry these type/API combinations without new target or dependency evidence.

The three adjacent `aim-kind-{context,generic,pruned}-20261020.py.txt` drivers
replay the experiment when copied to build/ and run in that order. The first
freezes the bank from 9ab2513cb9; all scratch outputs are uniquely named under
build/aim-kind-context-oct20. An initial declaration-insertion typo in the
generic driver was corrected and asserted before collecting its sixteen valid
results; those failed generations are not counted as matching trials.

Inputs: BFME2 9ab2513cb9, verified BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790; O1/G7/SSE/NDEBUG/MD/EHsc, static target
STLport in the checked-container controls. Normal mismatch CLI only, no custom
shared-cache compiler or optimization barrier. Work began about 14:11 UTC on
2026-10-20; model=gpt-6.1-sol. The claim is released after verdict recording.
