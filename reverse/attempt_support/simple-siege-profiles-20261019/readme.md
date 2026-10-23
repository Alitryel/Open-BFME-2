# SimpleSiege initialization compiler comparison

Target `0x005A9F70..0x005AA046`, 214 bytes, RET 8.
The complete saved bank and current `Rva005A9CB3Tactic.cpp` home were compared,
including the current split of `canRun` into its own source. Native identity
and layout evidence remain those documented in the existing bank and log.

New hypothesis: the authenticated VC7.1 service-pack/DDK compiler profiles or
the current whole-file definition context might close the known owner-load
scheduling mismatch. Six official `explain_mismatch.py` runs compare the saved
bank and the current home context under default, `vc71-sp1`, and
`vc71-ddk-4035`. Every run emits exactly 214 bytes with the same three differing
instruction rows. There are no unresolved calls. No exact match is claimed.

At `+0x4D`, retail branches on the null object, reads object field `+0x304`,
then loads this object's owner at `+0x24`. All six trials load the owner before
the null branch, preserving the previous mismatch and changing its branch
displacement. The old compiler/profile and source-context hypotheses are now
tested; no further source permutations were run.

Scratch copies preserve the committed Coord3D header by changing the relative
include spelling and adding the repository-root include directory. The first
scratch invocation lacked that include directory and failed to compile; the
recorded six results are the subsequent successful compiles, not those errors.
The trial generator and results are adjacent. Full diagnostic logs remain in
`build/resume-eh-local/turn47-siege-*.txt`.

No Code source, symbol pin, layout, ledger row or existing bank was changed.
Retain `reverse/attempts/0x005a9f70.cpp`; investigate a genuinely new supported
compiler/alias explanation before repeating the prior scheduling trials.
