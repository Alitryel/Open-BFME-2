# StrategicHUD CommandUIImpl linking reconciliation

BFME2 input: `ce1b975697`, published index `3bdfeee392` (2026-10-25 00:45).
Verified BFME1 donor pointer retained: `0bf534ea7ccde110c456edb9cd2dd5dae823c953`.
No pointer advance, nested references, census or link-cycle runner.

## Reference linking audit

Reviewed donor `87dbf3e3` (EAStringC default constructor becomes COMDAT): already
inherited here as the in-class EAStringC constructor, so no new repair or gain.
Reviewed donor `99960037` (APT banner dispatcher reconciled with an existing
provider): its rule is applicable as an identity-based declaration reconciliation,
but BFME2 requires its own target/provider proof; donor addresses are not reused.
Current EA/Apt blocker filtering finds the selected CommandUI owner and the
independent AptPlayerTooltipMap family. The latter still needs three unrelated
provider/class contracts and is not part of this repair.

## Target identity and repair

Target constructor `005D2BD4` binds native `005D26B2` under its frame-loaded
callback name. `reverse/name_basis.csv` row32 records canonical WB evidence:
WB `15ADD80` self-asserts `StrategicHUD::CommandUIImpl::OnButtonFrameLoaded`
at StrategicHUDCommandUIImpl.cpp line318, alignment pairing7.5. The native
constructor, direct destructor `005D25F2`, table C75800 and six1C-byte slots
independently establish that the formerly address-named owner is that same
CommandUIImpl. Source field meanings remain structural where not independently
named. The five-slot table has no destructor slot; nonvirtual destruction and
object sizeC4 are preserved.

The old private class name left two unresolved references: virtual
DoFlashButton@Rva005D25F2 and OnButtonFrameLoaded@Rva005D2664. Their existing
native providers already belong to CommandUIImpl. Reconcile the owner class,
constructor/destructor and three consumer units with that existing identity;
address the frame callback through its actual class. The separate Rva005D2664
nonvirtual views are retained only for their already verified clear/unload
providers. No inheritance, wrapper, alias, new symbol pin or address is added.
The four existing folded virtual-helper rows are only respelled, not duplicated.

`tools/rename.py class` accepts one free unqualified identifier and refuses an
existing target name; it cannot merge this existing namespace-qualified class.
This is the documented manual exception. All10 renamed row names are tombstoned;
all existing EH parent references and constructor/Update pins move coherently.
`name_basis.csv` is deliberately unchanged under that exception.

## Verification

Ordinary whole-file verification covers the four changed TUs plus existing
StrategicHUDCommandUIImpl.cpp provider:111/111 bodies,1 data row,32 strings,
8 empty-string references,2 compiler float literals and3 named imports pass.
All12 EH-bearing rows are EXACT, no baseline debt.

Joint current-object prediction: all5 units LINKS, LINKED4704 ->5534 (+830
unique bytes). The repaired owner changes0 ->830; its rank's1195 includes
folded/duplicate extents rather than additional unique bytes. Setter35,
deleter26, Palantir3229 and callback provider1414 remain linked. This is a
published-index prediction, not a new full census or executable link result.
C++ exact byte coverage is unchanged: this repair makes existing matched code
link. Normal commit hooks remain required.
