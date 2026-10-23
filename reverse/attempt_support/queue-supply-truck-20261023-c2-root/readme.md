# AIPlayer::queueSupplyTruck: stock C2 allocation evidence

Retail 0x004F37B0..0x004F3DB1, 1537 bytes. No recovery is claimed. The existing
bank `reverse/attempts/0x004f37b0.cpp` (align score 0.7867) is retained unchanged.
The clean source has the right 1537-byte extent and five-state EH graph, but
its registers, loop entry and local homes still differ. Model: GPT-6.

## Reproducible inputs

The patch is against the tracked `../queue-supply-truck-20261020-w5/`
`hack-free-candidate.cpp.txt`. Apply it to a scratch copy named
`clean-candidate.cpp`; it uses the canonical KINDOFMASK_NONE datum, current
aiDock name and ordinary C++ without the bank's priority helper, receiver PHIs
or compiler barrier. BFME1 pointer: 96c88c73a5cd1a58fc2f8db691beea50acd996db.
The recorded stock traces were taken on the 7dd59793af21ff83e58db6e94ad5156009bbf539
BFME2 tree; subsequent normal trials at 1d6d78fa07 retain the same residue.
The source/C2 hashes and byte-preservation receipts are in `input-proof.json`.
For the exact recorded baseline input, apply `trace-baseline.patch` to the
same tracked c7 lead instead. It retains the older address-named storage and
callee spellings for diagnostic reproduction only; the canonical clean patch
is a follow-up. Neither is an admitted recovery.

Copy `stock-c2-observer.py.txt` into `build/` as a .py file. First compile the
scratch source through the normal explain_mismatch command at this RVA/size.
Then run the observer with that source's repository-relative path and a fresh
label. It is a Windows/WOW64 observer of its own cl.exe child. Its software
breakpoints are restored before single-stepping; it never changes allocation
choices or DLL files. It checks the traced function's bytes AND relocations
against the normal object. It does not produce an admissible match by itself.

## New measured finding

C2's record first/last fields are span endpoints, not proof of continuous
liveness. The observer now reads the actual candidate-membership bitsets at
BB+0x4C and BB+0x50. `allocation.csv` retains these counts separately.

At round 3 the baseline vtable fragment has priority -14, cost 2, and appears
in 55 of its 75 span blocks. A deliberately WRONG control with the final
setCanBuildUnits restore removed has priority 100, cost 2, and membership in
6/7 blocks at +0x4C and 7/7 at +0x50. Its vtable definition is inside the loop
header, as retail's is. The baseline already has compensating vtable
rematerializations at the outer latch before the final zero/ESI allocation.
Thus the observed difference precedes final register preference; changing
only an initial priority does not explain it. The no-restore control is
INADMISSIBLE, not a candidate to bank or land. Earlier private decision-mutation
diagnostics are also inadmissible and are not included as recovery tools.

The baseline initially scores `this` 106/50/20 (priority/cost/references), versus
97/47/19 without the restore. The template cursor is 59/18/8 versus 55/18/8.
The baseline's late zero fragment has five uses spanning the closest-object
call, including the null comparison; it takes ESI before the vtable fragment.

## Independent hypotheses tested

Normal source trials covered real iterator representations and all three scan
loops; count lifetimes and types; owner accessors; captured build state;
construction, return and cleanup lifetimes; condition declarations/switches;
factory search separated from allocation; whole-arm and per-entry helpers;
explicit exit/continue edges; actual callee definitions; independent field
initialization orders; valid branch/allocation facts; the home TU in retail
order; and supported RTM/DDK/SP1, CPU, EH and size-optimization controls.
None was exact. Most canonicalize to the same 1537 bytes. Larger helpers that
do not inline, extra temporary objects, ordinary overextent mismatches and
incorrect single-path restores are not solutions. Named filters with a null
test while still alive produce 1550/1559-byte nonmatches, without the required
ESI vtable definition. The clean source is not a stronger bank by align score.

The long-header compiler-directive bug found during this investigation was
fixed separately in 188285d0f739c3e4e330f4aa9934cc5e5c3e1d80, with regression
tests and normal hooks. A corrected isolated flag search found no exact body:
clean fitness 0.8358 unchanged; bank 0.8684 -> 0.8688 with G6. These are the
permuter's fitness values, NOT the bank's align score. Old flag searches that
lost the line-14 directive are not reliable negative evidence. No new pin,
alias, global, manual vptr write, assembly body or verification exception was
introduced. Do not repeat the named families without a new concrete explanation.

Resume at the regional split/rematerialization decision, or with genuinely new
reference/type evidence. Preserve the real restore on BOTH normal exits,
after the AsciiString destructor, and do not add restoration on exceptions.

Elapsed wall time since the first clean baseline: approximately 228 minutes (including synchronization and the separately published tool repair).
