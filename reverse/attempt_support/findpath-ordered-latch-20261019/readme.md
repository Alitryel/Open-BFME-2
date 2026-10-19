# FindPath ordered latch investigation

Blocked; retain reverse/attempts/0x002fd344.cpp unchanged. The complete native
body is 781 bytes at 0x002FD344..0x002FD651, thiscall RET20. Its identity,
boundary, WorldBuilder D48230 relationship and resolved providers are established
in the existing findpath-2fd344-scaled-temporaries-20261019.md handoff. All prior
attempt entries and that handoff were read. The whole owner is unchanged from
the earlier fully reviewed f51bbefda6a8b5ab3437d6028401cf990d39f75d inputs;
inputs.json records the current revision and hashes. Compiler settings and all
headers remain unchanged. Model: gpt-6.1-sol.

The new hypothesis separates the initial scaled values from the loop's reloads:
three scalar cached values serve the subtraction, and explicit assignments after
the exit tests reload y, x, z for the next iteration. This preserves the first
iteration's existing SSE values and avoids extra reads on an exiting iteration.
The conditional counter forms, explicit labels and selective ordered-read
controls test whether correct reload order and retail block placement can coexist.
No production source, row, pin, alias, baseline or compiler option was edited.

The official explain_mismatch baseline reproduces all 781 bytes except four
operand bytes in the two swapped reload instructions at 0x002FD505/0x002FD50A.
The ordinary cached-value loop with ++i in its exit test reproduces that same
baseline, including all calls and the 0x18 frame. Explicit ordered reads in the
same loop give the correct y-to-XMM2, x-to-XMM1, z-to-XMM3 reload sequence and
remain 781 bytes. However the compiler puts that sequence after the body and
exit tests, with a backward unconditional jump, instead of retail's header block
and conditional back edge. Everything before 0x002FD503 and from 0x002FD55B to
the end remains byte-identical. This is 86 differing positional bytes and is not
a closer bank than the four-byte baseline. No exactness or runtime proof is claimed.

Nineteen total compiler outputs, including the reproduced baseline, cover:

- Direct ordered reads in the subtraction: 779 bytes, different SSE allocation.
- Cached values with a separate i+1 test: 786 ordinary / 784 ordered bytes.
- ++i exit test: 781 bytes, baseline order for ordinary reads; correct reloads
  but different block placement for ordered reads.
- Explicit guard/infinite loop and explicit header labels: 806 ordinary /
  818 ordered bytes, no useful placement recovery.
- Conditional reads at the loop header: 818 bytes and a 0x24 frame.
- Short-circuit and conditional iteration expressions: the same 781-byte
  ordered-loop placement result.
- Six selective read qualifiers: all 781 bytes; block placement and/or initial
  SSE register allocation differs. No complete exact candidate.

measurements.json records actual whole object extents separately from resolved
row bytes. The normal mismatch API truncates overlong candidates to the row for
its positional diagnostic: such candidates fail regardless of that diagnostic.
Every trial has no unresolved REL32 names. The existing helper/global bindings
are unchanged; resolved diagnostics do not establish separate data proof.

Selected patches preserve the useful new loop shapes against the baseline.
Copy replay.py.txt to build/findpath-latch-oct19/prepare.py to regenerate the
whole-owner baseline from the unchanged owner and bank before applying a patch.
Its source hash must agree with inputs.json. Full probe sources and normal
compiler logs remain under ignored build/findpath-latch-oct19/. No exact body
was admitted, no better bank replaces the existing one, and reservations are
released. Further work needs a new supported lever for reload-block placement.
