# PolygonTrigger camera: exact through candidate field ownership

Recovered the body led by WB `PolygonTrigger::adjustCameraMovement`, native 0x002E3AA8..0x002E3D7B,
723 B, RET16, in Code/GameEngine/Source/Common/Rva002E3A39Pair.cpp. The existing
46-byte planar predicate in the home unit still verifies. All 723 bytes and
external bindings verify through add_match and build.sh; six float literals
verify. No authored asm, volatile reads, compiler barriers, new pins or header
changes. There is no C++ EH in this landing. The old bank is removed by
add_match. The assignment is solved.

## Identity and provenance

The prior bank and WB ABA7D0 provide the semantic guide: clip camera travel
against polygon edges and, when requested, slide the unused movement along the
intersected edge. Native camera caller 0x00101DFC, AL consumption, RET16, the
2E3A39 planar predicate, 2E3A8D edge accessor, IntersectLine2D, coordinate calls
and measured array fields establish target ABI and relationships independently
of the WB name. The landed spelling is the existing
`PolygonTrigger::rva002E3AA8`, preserving its sole pin and native caller.
`rename.py function --rva 0x2E3AA8 --new adjustCameraMovement --basis canonical:wb`
was dry-run only and refused: the self-assert pairing score is 3, below the
canonical threshold of 4. This is a remaining naming-evidence limitation, not a
byte or linkage blocker; no pin or caller was changed. Do not bypass that check. Coordinate layout/constructors come from the existing canonical
constructor view and prior native evidence. The helper CameraPlanar preserves
the WB planar constructor/copy/subtraction structure from the incoming clean
bank. CameraValueSlot is a C++ codegen adapter, not an assertion that retail
contained a class by that name or a holder type at all.

Inputs: BFME2 03422ed0de; BFME1 verified pointer
f890413e75e671748215ba2ef3304aa7953993e9. check_csv passed. The fresh BFME1 update
lock belonged to codex4, so this session skipped that update as instructed and
did not write a successful freshness stamp. RTM compiler 13.10.3077,
/O1 /DNDEBUG /MD /arch:SSE; c2 SHA256 and source hashes are in results.json.

## Prior exclusions and new evidence

Read the RVA history with pick-hard, the constructor, tail-selection and
C2-load-selection handoffs and relevant recipes. Ordinary Add/Scale spellings,
local numbering, lifetime, real layouts/providers, compiler builds/settings and
the previous large qualifier/barrier family were already tested. Do not retry
those unchanged.

The first new hypothesis was real preceding-function context, following the
ArmyDefinition EBP-availability finding. Forty-two normal source variants
covered the predicate, real getter and real math-provider placements across the
clean, bank and complementary near seeds. Twenty-one inline-suppression controls
covered dllimport and forceinline combinations. None improved the corresponding
seed. Importantly, read-only compiler emission traces proved that suppressing
CameraPlanar's three unused external copies changes the camera's inherited
_regAvail[6] at c2 VA 0x108A7B30 from 1 to 0. Its bytes remain unchanged. This
specific state explanation is ruled out by a measured state change.

The next hypothesis was ownership of the addressable candidate fields, rather
than arithmetic spelling or late scheduling. Read-only snapshots corrected the
phase boundary: +0xB0010 is before call +0x70532. Inside that call, +0x73407
lowers generic MUL/ADD to SSE. Selection has completed by +0x70627, and therefore
also by +0xB0029, before the later +0x7C937 and allocation passes. The snapshot
collector now captures secondary operands and excludes tuples from recursive
operand-next traversal, avoiding its former depth-limit omissions.

The clean final generic ADD inputs are product H554 / candidate H550, and
product H555 / candidate H552. At +0x6FE13 they have become ADDSS but still have
two memory operands. The +0x700DB operand-form decision returns flag 4 for both;
+0x771ED then inserts a register copy of the first source. Earlier additions,
with a scalar first source, instead return flag 32. Thus the tail's candidate
loads are already lost during lowering, before register allocation or final
scheduling. The word values and operand nodes are preserved in results.json. A read-only
trace of the normal exact holder reverses just those final source orders to
candidate H583 / product H587 and candidate H585 / product H588; the form flags
remain 4. This directly confirms the source-level ownership change before the
register copies are inserted.

A diagnostic reversal of only the final two source lists at +0x6FE13 produced
exact 723 B. Reversing the earlier dot as well produced exact tail bytes but
four dot-register instruction differences. These debugger mutations are causal
diagnostics only; their objects were never rowed, banked or used as verification.
The unmodified debugger control reproduces the normal 715-byte body.

## Normal source family and landing

Tested the full 5^4 factorial over candidate, along, used and next object homes:
plain Coord3D, a one-member holder, a one-element array holder, a nested holder,
and a constructor-forwarding derived Coord3D. All 625 sources compile normally;
84 distinct bodies, 16 exact full723-byte winners. The smallest is home-1000:
only candidate changes from `Coord3D candidate` to:

    struct CameraValueSlot { Coord3D value; };
    CameraValueSlot candidateSlot;
    Coord3D &candidate = candidateSlot.value;

No added reads, calls, branches, qualifiers or compiler barriers. The field's
C2 ownership changes the canonical operand order, while preserving native stack
homes, registers and instruction schedule. Nested-holder candidates also match;
array-holder candidates do not. The derived used/next choices are inert in the
exact subfamily; wrapping along as a member breaks it. This is an interaction
in addressable fields, not proof of a particular original type.

Removed unused trial holder definitions, restored home-unit include paths,
formatted the source and reran build.sh: 2/2 rows exact. find_declared_unmatched
passes. place_bodies reports zero additional bodies/pins. Fetched the published
link index and link_check reports this unit LINKS, LINKED 46 -> 768 unique
non-padding bytes, with no blockers in the recovered unit. The unchanged camera-settings consumer
also passes byte verification: the two units together verify 15/15 rows and 23
float literals. Its link check still reports thirteen pre-existing unresolved
`vslot00`..`vslot11` and `vslot20` definitions on Rva00BCF670CameraSettings; the
new PolygonTrigger provider is resolved. No maintainer-only runner was started.

## Replay

Copy homes.py.txt and check.py.txt into build/camera-field-owner-replay/ as .py;
copy the earlier camera-c2-load-selection-20261023/clean-base.cpp.txt to base.cpp
there. Run homes.py; eight workers use private objects through compiler_command,
never the shared match cache. The exact predicate resolves all relocations and
compares all 723 bytes, including length and unresolved references. results.json
records the sixteen normal winners and identical raw-body SHA256.

For traces, copy wdbg.py.txt from the earlier handoff as wdbg.py and copy this
folder's diagnostic scripts. choose.py normal is read-only; flip and flip2
mutate compiler IR and their output is inadmissible. phases.py lower-clean
clean-base.cpp captures the lowering boundaries. emission.py is read-only.
context.py and suppress.py also require the earlier bank and complementary
candidate sources under their local expected names; see their generator text.
The full trace JSON and all 688 trial sources/objects remain scratch under
build/camera-context-20261023. The normal source is now the ledger-owned file. Trial scripts retain the WB
method spelling; changing that identifier to the existing pinned spelling leaves
the verified body unchanged.
