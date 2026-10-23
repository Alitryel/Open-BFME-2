# OpenContain exit: scalar reference helpers

The whole hack-free bank, all prior RVA entries, the coordinate-view and
member-mutator handoffs were read. Native46525F..4656DF is1152 bytes, RET8.
The bank reproduces1154 bytes with every call resolved. Frame50 is retained.
The first+239 difference is a downstream branch displacement from the two
extra bytes; the actual defects remain the FLD/MOV swap4654FB/4654FE and
x/y preload plus register multiply instead of retail's memory multiply.

The successful Drawable ship mutable-reference spring helper supplied a new,
bounded hypothesis.27 ordinary C++ helper trials were run through the normal
explain tool, retaining the complete bank and its visible command/vector chain:

-12 scalar scale contexts: free/member, factor by value/const reference/mutable
 reference, returning void/reference. All remain1154 and the same99 differing
 explain lines, including shifted instructions after the scale region.
-6 combined scale/add contexts: free/member and the three factor forms.
 `step *= factor; destination += step` still emits1154; it changes scheduling
 within the goal block (95 positional instruction lines), but preloads x and
 interleaves the adds differently from retail. Neither original defect closes.
-9 subtraction-return contexts: value/const-reference/mutable-reference inputs,
 replacing x alone, xy or xyz. All remain1154/the original99 lines. The early
 FLD and goal-view pointer load remain swapped.

This technique does not transfer here. The observed fewer positional lines in
the combined variant is not a new matching claim or an aligned improvement;
the two-byte excess and both substantive defects persist. No volatile, barrier,
dead statement, pragma, asm, pin, production source or header was introduced.
The better existing bank remains unchanged.

Inputs e56d7ceb70/BFME1b3cc6b1588f2. Settings are the bank's O1/G7/SSE/MD/EHs
and actual allocator/string headers. Complete trial sources, normal logs and
JSON manifests remain build/open-exit-scalar-reference-oct20/. Reproduce the
new operation with an inline helper taking scalar references, scaling step in
place and adding it to destination; all three factor modes are equivalent in
this diagnostic. The earlier tracked coordinate-view handoff retains the
focused native-versus-bank diff needed to resume a different hypothesis.
