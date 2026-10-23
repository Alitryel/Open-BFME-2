# Drawable shroud: the final receiver's allocation cost

Continue only `?onComingOutOfShroud@Drawable@@AAEXXZ`, RVA 0x0027893E,
747 B. The unchanged best bank is `reverse/attempts/0x0027893e.cpp`, score
0.995. It emits 748 B / 220 instructions against retail's 747 B / 220.
Full-symbol comparison, with actual COFF relocations masked and branch target
instruction indices checked, still has one difference at instruction 201,
+0x2BA: `mov ecx,[ebp-0x10]` instead of `mov ecx,edx`.
No Code, ledger, pin, alias, compiler setting or verifier change is claimed.

## New causal evidence

Read-only debugger observations on the pinned MSVC 7.1 C2, base 0x10700000:

- Function context: RVA 0x83ACD. Integer allocation rounds: 0x82978. Candidate
  selection: 0x82A4D. Assigned candidate: 0x831F7. Finished: 0x82273.
- In the bank, `_obj` candidate 33 reaches round 5 with refs=2, cost=-2,
  priority=-2 and allowed register ID 3 (EDX). It is popped but not coloured.
- In the ordinary split-tail control, `_obj` candidates 33 and 20 reach round 5
  with refs=2, cost=+1 and allowed register ID 3. Both are coloured EDX.
- The common-tail candidate's cost writes show two reload penalties. At the
  observed round-3 cost pass, reload at 0x8281C changes 0 -> -3; source use at
  0x82692 changes -3 -> 0; another reload changes 0 -> -3; another source use
  changes -3 -> -2. Raw tuple word 1 is respectively 0x26A, 0x33, 0x26A, 1.
  These are measured fields, not a complete decoding of those tuples.
- **Diagnostic intervention, never a match:** change only candidate 33's cost
  at its round-5 selection from -2 to +1 in a private compiler process. The
  resulting full symbol is 747 B and `compile_function` reports all relocated
  bytes equal to retail, with no unresolved names. This isolates allocation
  cost as sufficient for the residue; it supplies no eligible source change.
  Never admit, bank as C++, or copy that object's contents into a build cache.

The passive traces' complete parent bytes AND relocation lists equal ordinary
compiler objects, for both the 748 B bank and 738 B split-tail control. The
separate passive cost-write trace also equals the ordinary bank object.
[observations.json](observations.json) includes hashes, selected records and
normal/diagnostic controls. The intervention object exists only in ignored
scratch storage, not this evidence directory.

The split-tail source still regresses earlier holder/template allocation. The
holder has priority 13 in both traces. The 0x80 mask candidate, index 7,
has priority 10 in the common-tail trace and 14 in the split-tail trace; it is
selected before the holder in the latter. A further passive trace reads its constant operand: word 1 is 0x24B and
words 4 and 6 are 0x80. Its full body and relocations equal the ordinary
bank. This identifies the literal, not the entire interference relationship.

## Late tuple removal

At `TupRemoveRange`, RVA 0x9724C, every observed caller return is RVA 0x513EF.
The common-tail bank removes three single-tuple ranges. The split-tail control
removes one single-tuple range and one 14-tuple range. This confirms a different
late removal shape, but does not identify a named pass or establish which tuple
implements the desired move. Neither tracer alters compiler data.

## Ordinary C++ trials this session

All 1,184 generated sources compiled and scored, with eight workers and separate
private objects. No exact result or improved eligible bank. Counts are trials,
not distinct compiler outputs; metrics' normalized instruction count includes
the known relocation-normalization artifact. Preserve all prior exclusions in
`../drawable-shroud-join-review-20261022.md` and its linked handoffs.

| Family | Count | Finding |
| --- | ---: | --- |
| Whole status/death/store/event helper inlining | 256 | Only 748 B / nd 2 or 738 B / nd 16 |
| Individual existing field reads with local volatile qualification | 256 | Same two best states; other forms regress |
| Join before status guard via event address/selector/offset | 208 | Best nd 58; earlier join regresses allocation |
| Stable position-address preparation on each predecessor | 80 | Best unchanged 748 B / nd 2 |
| Whole transition helper returning the guarded Object pointer | 256 | 128 unchanged; 128 have nd 63 or 83 |
| Split-tail KindOf inline chains, mask type, template getter, callback constructor | 128 | Best unchanged 738 B / nd 16 |

The last family specifically tested the new allocation-order observation in the
native split-tail context. It did not correct the holder allocation. The earlier
join family includes a diagnostic cross-member indexing variant, which must not
be promoted as eligible C++. Field qualifiers are compiler controls, not claims
that retail's class fields were volatile. All variants remain outside Code.

## Replay and next step

Copy the `.py.txt` tracers and `wdbg.py.txt` into one scratch directory as `.py`.
Run from the repository root, passing a source path and a private output object:
`python3 <scratch>/trace_colors.py <source> <scratch>/ordinary.obj`.
`trace_colors_diagnostic.py` is explicitly an intervention and its output is
ineligible. It has the same arguments; its object must remain private.
`trace_object_costs.py` and `trace_removals.py` are passive alternatives.

To replay the split-tail control, copy the unchanged bank to
`<scratch>/native_split.cpp`, then, from the repository root, run
`git apply --ignore-whitespace --directory=<scratch> reverse/attempt_support/drawable-shroud-allocator-cost-20261022/native_split.patch`.
Indentation/whitespace is normalized in the patch; a normal replay compile
emits the same complete body and relocation list as the original native control. The preserved generators document the finite families; some
retain the historical scratch native-base path. Their include inputs, driver and
results remain in `build/drawable27893e-20261022d/`, with the scoring driver under
`build/drawable27893e-20261022b/`. Use the complete raw symbol, not the 747 B
truncated `compile_function()['bytes']`, when measuring a nonmatching body.

Next source hypothesis should explain how two predecessor reloads can feed the
shared tail without the negative-cost range, while retaining the earlier
holder/template allocation. The diagnostic establishes that changing unrelated
callees or retail extent is unnecessary; it does not prove all C++ source shapes
have been tried. No missing-function prerequisite or `blocked-on=` RVA was found.
The production home still needs BFME method/layout integration after a match,
as documented in the preceding handoff.

Inputs: BFME2 234ab5822cbdb709dc9d8cc1e8403e655e930fef; BFME1 verified pointer
42bba2ddbd5cb895d99293583891d3b7315fa49e. Flags unchanged: O1, Ob1,
d2inlS100, static STLport, G7, SSE, MD, EHsc, DNDEBUG. Compiler hashes are in the
JSON evidence. The recent BFME1 update lock belonged to claudec2; this seat
followed the runner rule and skipped its update without marking freshness
successful. Ledger check passes; fresh ordinary explain/residue checks reproduce
the nonmatch. No full gate, link cycle or runtime verification is claimed.

About 30 minutes, model gpt-6.1-sol. Preserve the .995 bank and resume this same
body only. Claim released at handoff; session outcome remains in_progress.
