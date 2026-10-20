# SelectionTranslator prerequisite continuation, 2026-10-20

Continue only SelectionTranslator::translateGameMessage at 0x0043003C.
The retained bank is still 4054 bytes, score 0.98, with five unmasked
comparison bytes remaining. Prior comparison trials are in
../0043003c-20261020-codex7-third/handoff.md; do not repeat them.

## Constructor admission findings

The existing 31-byte owner at 0x0043001D uses an address-derived one-byte
Rva0043001DElement. The parent uses four-byte ID keys and stores Boolean true
at node value +8; int/bool is the retained structural reconstruction, not an
independently named target type. A typed hash_map<int,bool> emits the same
31 non-relocated bytes, but its typed hashtable constructor is unresolved.
Under the W4 settings that callee is 77 bytes; the W5 owner settings produce
64 bytes, equal to retail outside relocation fields.

Whole-body fold proof correctly refuses the proposed 64-byte typed callee:
its initialize_buckets initially emits 64 bytes rather than retail's 59.
The existing end() declaration forces a call instead of the native +8 field
load. Making end() visible fixes that region but the insert declaration then
calls public insert at 0x0002A2D0 rather than native _M_fill_insert at
0x00029CA0. Matching both inline wrappers produces the required 59-byte shape.

The deeper constraint is the native 64-byte constructor's call to the
canonical unoptimized _Vector_base<void*>(allocator const&) at 0x00025100
(55 bytes). The W5 optimized copy is 29 bytes and conflicts at link. Hiding
its definition changes the caller's dummy allocator address from argument
padding [EBP+0B] to a new stack slot [EBP-0D], adding a push and changing 64
to 65 bytes. Destructor declaration/import variants produce 69/72/77 bytes;
forcing the vector constructor inline with the base visible produces 59.
Neither exception specifications nor __declspec(nothrow) fixes that layout.
The native body needs base-ctor visibility for stack reuse without emitting
the conflicting optimized copy. This is a compiler/provider prerequisite,
not evidence that the native function cannot be recovered.

A 16-way base visibility/vector wrapper/allocator-dtor factorial, four
nothrow followups and a 16-way extern-template class factorial were compiled.
The extern-template declarations leave inline COMDATs emitted and do not
solve suppression. Ordinary MSVC explicit-specialization ordering errors in
an intermediate control were generator errors, not verifier false rejects.
No trial is production code. The W5 file is restored exactly to HEAD.
The link predictor reports its pre-existing four conflicts (allocator dtor,
allocator proxy dtor, vector-base ctor and vector ctor); allowing end() to
emit adds another conflict. Do not publish that diagnostic configuration.

## Lookup admission

Verified the 47-byte `_M_find<int>` body at 0x002888D4 in the small
`Code/GameEngine/Source/GameClient/MessageStream/SelectionIDMap.cpp` unit.
This explicitly instantiates STLport 4.5.3's real algorithm for the parent
bank's int/bool map; no new address pin or replacement owner is needed.
Whole bytes equal retail with zero relocations. Full fold proof against every
existing owner succeeds (`lookup-fold.json`); add_match's normal byte gate
passes. The vector size/index accessor bodies use Armor.cpp's established
imported-inline provider pattern and do not emit competing definitions.

`find_declared_unmatched` passes. `link_check --new-variants` succeeds with no
new COMDAT variant. Ordinary link preview cannot assess a new file absent
from the published 5366c4f808 census; no maintainer-only census was started.
This is not a claim that the new unit has a published LINKED census receipt.

A fresh isolated compile of the parent bank still emits 4054 bytes and
184 relocations with exactly five raw non-relocation differences, C6B..C6F
(`parent-raw-diff.json`); extent and jump-table checks pass
(`parent-extent.json`). The typed lookup now resolves through the new ledger
row. Four distinct unresolved names remain (five call references): deselectAll
0x42F9DA, map constructor 0x43001D, subscript 0x42FE40, and hashtable destructor
0x42FD1C (`parent-resolved.json`). Preserve the score-0.98 bank.

## Reproduction and continuation

Input BFME2 revision: 78e479af485a8524279cc2a96bb9664fb846a0eb.
BFME1 committed/checkout input: 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
MSVC 7.1 via Wine; the frozen constructor source records its exact flags.
No reference input or production constructor file was changed.

From the repository root, run this directory's `ctor_factorial.py`, then
`ctor_nothrow.py`; `extern_factorial.py` is independent. They compile only
private objects under ignored build/selection43003c-prereqs-reproduce.
The frozen constructor input is diagnostic evidence, not production source.
`constructor-results.json` retains all 36 outcomes. Do not repeat these
visibility/nothrow/extern-template controls without new compiler evidence.

Continue only the parent. The smallest comparison residue is unchanged;
prior third-session handoff records rejected lifetime/control-flow trials.
For constructor admission, investigate how native compiler visibility can
retain the argument-padding lifetime decision while using the canonical
55-byte vector-base provider; the current 29-byte optimized provider cannot
be landed. Subscript and EH destructor admission are other concrete parent
prerequisites. Do not revert the newly admitted lookup or add padding.
