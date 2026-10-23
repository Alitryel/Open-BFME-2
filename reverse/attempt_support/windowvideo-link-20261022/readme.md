# WindowVideo linking repair, 2026-10-22

Base: c73adde6d3; published census/index: 08160bc2c9 (17:08 UTC).
BFME 1 verified pointer remains 37c3022de1ab944c7ffe536440d637dc8199091c;
no donor update or changed compiler flags are involved.

## Verified consumer repair

`Code/GameEngine/Source/GameClient/GUI/Rva00427311Dtor.cpp` previously had
an undefined `Rva004271D9` constructor (pin 0x00427507) and a losing
WindowVideoManager hashtable `_M_bkt_num_key` copy.
An inline constructor adapter now calls the existing rowed empty hash_map
constructor at 0x00427507. A declaration-only specialization prevents emission
of the losing iterator helper. Merely calling the constructor without its
specialization declaration also emitted an incorrect underlying hashtable
constructor; the declaration is necessary.

The neutral element view is copied from the row owner. Target call addresses,
ABI and complete parent/funclet bytes support this constructor call; they do
not prove the neutral element's identity or the class's other map semantics.
No pin, class registry, shared header or compiler setting changed.

Acceptance: normal byte gate 8/8; all literal/float/import checks pass;
three renumbered funclet labels verified through parent EH data;
`find_declared_unmatched.py` passes. `link_check.py --prepare-current` passed
for the explicit consumer and wrote a strict reusable byte receipt, without
claiming link closure. Plain explicit current-object `link_check.py` measured
0 -> 232 nonpadding bytes, LINKS. This is a **legacy preview** gain; neither
self-strict nor closed-strict LINK gains were measured. The two remaining
helper diagnostics are unreferenced and are not blockers under retail-truth-2.
The other indexed unit sharing this helper, `Rva002E0298.cpp`, already has
its own inline specialization repair and was not modified.

## Constructor provider handoff

`StlSweepW4Rva00427507.cpp` remains unchanged and blocked (0/31 bytes).
Its whole-class instantiation emits an undefined element equality operator
and a nonretail hashtable constructor copy. Narrowing to only the owned
hash_map constructor preserves its row (1/1), removes the equality reference,
but leaves the losing constructor and still gains zero linked bytes: restored.

The underlying address 0x004274C7 IS rowed, in
`StlSweepW5Rva004274C7.cpp`, and its current object LINKS 64/64 bytes.
Its neutral element is `Rva004274C7Element` (8-byte opaque payload), whereas
this caller uses `Rva00427507Element` (1-byte opaque payload). Thus a missing
implementation is not the problem: their constructor identities/views need
reconciliation. Do not infer either element layout solely from empty-table
construction. The pin for the caller's hashtable name at 0x004274C7 is older
alias debt; no pin was added or changed here.

`provider-trial.patch` preserves the best diagnostic trial, not a recovery:
an inline specialized hashtable constructor forwarding to the rowed type.
MSVC 7.1 rejects it with C2512 because `_M_num_elements`' alloc_proxy has no
default constructor. Adding normal member construction would execute a second
construction before forwarding and is not justified by the target's bytes.
The source was restored and its original 1/1 byte gate rerun. Resume with a
proper evidence-backed class/view reconciliation, not another blind inline
wrapper. Provider claim released at session close.
