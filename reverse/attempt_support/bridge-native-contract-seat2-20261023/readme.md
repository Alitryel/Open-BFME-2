# BridgeBehavior native hierarchy prerequisite, Seat2, 2026-10-23

## Scope and result

Existing destructor TU only: `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorDtor.cpp`.
Native rows 457113/150B, 457536/28B, 78A0D5/10B, 78A0BF/8B.
Source is unchanged from both local20c6ca8b4 and published fab9bcb40c.
No production source, ledger row, provider, header, flag, pin or alias changed.
No source trial or compiler launch of BridgeBehavior.cpp occurred.

Normal baseline build passes4/4, complete parent EH1/1 EXACT, frozen and
canonical-class checks pass. Legacy scoped preview is0->0 with sole blocker
`??_7BridgeBehavior@@6BUpdateModule@@@`: different from the first copy,
with no retail-address verdict. The index is456ce161c5, 2026-10-23 06:28;
this is not a current-ledger or closed-strict linkage claim. All196 row bytes
remain verified; legacy nonpadding own bytes188 differ from row-byte total.

## Native facts versus source views

Retail457113 independently restores these six vptrs:

| Receiver | Table RVA | Supported interface/prefix |
| --- | --- | --- |
| 0 | 8409DC | primary13-entry table, through phase callback22C4CB |
| C | 840920 | behavior-acquisition interface; exact end/slot semantics unresolved |
| 10 | 840914 | update456E8D, disabled-mask253376, scheduler44DF8D |
| 20 | 8408FC | six bridge-tower/scaffold callbacks |
| 24 | 8408F0 | three damage callbacks |
| 28 | 8408EC | die4581FD |

The JSON preserves a47-word raw window at840920; **47 is not a proven
interface size**. Its last words may belong to adjacent tables. No guessed
slots were added. The donor BehaviorModuleInterface has34 declarations,
so copying it wholesale cannot establish BFME2's complete native contract.

The destructor's compiled private view emits only one primary entry and
one entry each for MiBase1 and UpdateModuleInterfaceData. The published
kept provider additionally owns ObjectModule and BehaviorModuleInterface
branches. Its `BridgeBehavior{for UpdateModule}` name denotes a different
subobject from the flattened destructor's primary table. This is genuine
inheritance/contract debt, not merely a missing callback declaration.

Primary slot2 is4571EE: `mov eax,0xBF5CA8; ret`, returning `BridgeBehavior`.
The existing actual owner is Common/ModuleNameGetters.cpp, with established
`?name@BridgeBehavior@@QBEPBDXZ`. Its declaration is a const **nonvirtual**
member, although retail stores its body in the primary table. Bytes prove
no stack arguments and the string return, not original C++ method spelling
or const qualification. Existing const qualification is carried provenance.

The registered Snapshot header has default `crc(Xfer*)` in this slot and
an optional canonical `GetSnapshotName() const` API. Blindly copying default
crc preserves the wrong method contract. Using getter mode requires a real
virtual override; a nonvirtual name() reference cannot provide that override.
No wrapper, extra slot, macro spelling alias, new pin or getter duplicate was
introduced to conceal this issue.

Actual destructor calls remain getTowerID4565A5, findObjectByID49DC5,
destroyObject242C09, native PoolMember release268902 at receiver+100,
UpdateModule teardown24A797. The whole8B unwind78A0BF restores the original
receiver and jumps to24A797; native268AFF is a tail jump to268902.
The compiler-generated deleting callback457536 calls457113 and global
delete2FD60. Native handler78A0D5 and complete parent EH are unchanged.

## Read-only naming expansion and normal refusals

Read docs/naming.md, actual owner macro, name_basis/name_tiers, exports,
WB row18664 and linked prior attempts. No canonical function basis or
inferred record was found for this BridgeBehavior method. WB4571EE records
an empty proposed name and the old placeholder; it is not a self-assert.
The retail string and previous class rename establish the owner class,
not the original method identifier. A trivial six-byte getter is not a
specific same-body canonical donor proof. Pinned BFME1 Snapshot headers
retain crc, not GetSnapshotName. No blind votes or naming records were made.

Two normal `rename.py function --rva0x004571EE --dry-run` requests were
read-only and exit2; exact commands/results are in the adjacent logs:

- Identifier-only GetSnapshotName: `name` is not recorded inferred and is
  not classified as a placeholder; the normal engine refuses replacement.
- Full virtual `?GetSnapshotName@BridgeBehavior@@UBEPBDXZ`: changes the
  signature beyond the identifier. Allowed identifier-only rewrite retains
  `?GetSnapshotName@BridgeBehavior@@QBEPBDXZ`, still nonvirtual.

**Precise plan count:0 admitted files**, because refusal precedes a plan.
The observed minimum owner scope is1source containing70 matched rows/420B
and68 macro invocations. A global macro rename changes all invocations, not
only this row. This is not a permitted workaround. No successful full
consumer/dependent count can be inferred from a refused plan. A future
owner identity/virtualness correction would need independent naming basis,
normal identity admission, whole-owner verification and actual dependent
verification; shared Snapshot-header work additionally triggers the full
shared-input gate and is outside authorization. No full build or census ran.

Fresh sequential guarded claims list showed no live4571EE,
ModuleNameGetters.cpp, class:BridgeBehavior or class:Snapshot claim.
Absence of conflict is not edit permission. The5destructor scope claims
are released after this evidence bank, not retained for an unsupported trial.

## Resume prerequisite and provenance

Resolve native Snapshot-name ownership/virtualness through a supported
identity/naming reconciliation, with approval for every actual owner and
consumer. Also establish the BFME2 acquisition-interface contract; retain
unknown slots as unknown. Only then compile a genuine destructor hierarchy
and check all four rows, native table relocations, complete EH and a paired
provider/consumer overlay. BridgeBehavior.cpp's forced include has no local
mapping grant, and its current object is absent from this worker's cache;
do not compile it or fabricate current closure using the historical index.

BFME1 input138757e9b74645fbcbb7724a7af2764e34931e11; parent96c88c73 results
are independent and not borrowed. Previous relevant banks:
link-helper-emission-20261022/readme.md, link-seat-20261022d.md and
link-seat-20261021-late/readme.md. Current root/source inputs untouched.
This is a bounded prerequisite bank, not semantic recovery failure,
exhaustion of all GameLogic work, new coverage or a measured link gain.

model=gpt-6.1-sol owner=sol-team-supply-20261023
