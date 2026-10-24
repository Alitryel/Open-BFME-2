# GUI comparisons and tab arithmetic: pure C++ family repairs

BFME2 base2c7d0eefe5; pinned BFME1 reference32774ab03393709a7f14331ba8d98d281a55ffd9.
These replace existing inline assembly with real C++ without changing their
native bodies. The old enclosing .cpp files already count as C++ in progress.py;
these are assembly-debt repairs, not additional unique coverage bytes.

## Text-entry selection, RVA00444016,25 bytes

The original class, userdata layout and /Ob0 flag remain unchanged. The two
unsigned-word fields at+1C/+1E are compared after the same winGetUserData call.
The pure boolean identity `(user->at1E != user->at1C) && true` restores the
native DX comparison register and ECX boolean register under stock VC7.1.
Direct comparison chooses the opposite register web; merely introducing a
boolean/int temporary does not close it. No volatile, register constraint,
input bound, extra memory, ABI adapter or changed flag is used.

The complete inline-assembly block is removed. The whole25-byte function and
sole real relocation match with no masks or unresolved calls, independently
repeated using the production command and a separate scratch object. This is
instruction and ABI proof, not a claim that the original source used &&true.
Normal add_match and the full source's checks are required before committing.

Normal production add_match passes the sole row and all references, and the
whole-file declared-definition check passes. The published index a9f880ad06
does not include this source, so ordinary link_check cannot preview it; no
published linked-byte gain or final runtime result is claimed.


## Tab pane sizing, RVA003271D9,174 bytes

All four inline-assembly fragments are replaced by ordinary C++ arithmetic.
The original output-pointer order, two local homes, calls, branches and store
order are preserved. Unsigned multiplication/addition/subtraction explicitly
model native modulo32 arithmetic for every input word; the final int stores
use this pinned compiler's conversion behavior. No positive-size or signed-
overflow assumption is introduced. Potential output/data aliases see the same
native accesses; the complete emitted instructions independently verify this.

The useful native negative scale is expressed as `-2u * (unsigned)paneBorder`
inside the original add/subtract chain. The opposite arm uses two unsigned
border additions. The source-only expression choice avoids the prior SHL/NEG
shape under exactly the existing flags; no new flag, header, pin or memory
barrier is required. Simple signed/negated-sum controls independently show
that the earlier blocker is stale, but the unsigned form preserves the full
native word-domain semantics.

Both worker and independent reviewer compiled the complete candidate file:
eight rows /1265 bytes, every emitted extent equal to its whole native row,
all relocations resolved, no masking and no unresolved calls. Only the174B
pane-sizing body changes; seven siblings retain their exact original bodies.
No assembly, emit or naked body remains anywhere in the candidate file.

Carried provenance from the existing row: BFME1 GadgetTabControl.cpp is the
semantic donor; the already-matched GadgetTabControlResizeSubPanes call at
003272AC establishes identity. Existing native local-layout evidence records
[ebp-4] height and [ebp-8] width. All class fields and seven sibling bodies
retain that prior evidence; this repair adds no new layout or naming claim.


Normal production add_match passes all8 rows and the literal/import checks.
Declared-definition check passes and whole-file placement rescan is empty.
Published-index preview remains LINKS1265->1265 bytes, with no blockers.
This is a current preview and no additional published linked bytes are claimed.

