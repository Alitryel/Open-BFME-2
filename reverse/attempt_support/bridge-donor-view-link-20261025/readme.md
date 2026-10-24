# Retire the obsolete bridge destructor view

BridgeBehavior.cpp owns the two existing tower-accessor rows at 45657F (38 B)
and 4565A5 (24 B). Its leftover protected donor destructor is a different,
240-byte MAE definition. The native public UAE destructor is already owned by
BridgeBehaviorDtor.cpp at 457113, 150 bytes, with exact EH and its deleting
wrapper. The obsolete donor view emitted six tables and extra interface/pool
helpers and required the unresolved AudioEventRTS destructor name. That pin
actually names the list<int> base destructor at 4EC395; it is not a valid
reason to introduce an AudioEventRTS wrapper.

Remove only that obsolete protected destructor and its annotation. All other
donor bodies and the two owned accessor implementations remain. The source
comment points to the real existing owner. No method or class is renamed.

## Retain the needed helper with its native layout

An export audit prevents a blind deletion. The ordinary object's removed sole
providers have no surviving consumer except isScaffoldPresent, which the real
BridgeBehaviorInterface table references. Its old donor copy loads a byte at
interface-this+3FD. Native evidence gives a different layout:

- The matched 150-byte destructor binds table C408FC; slot five points to the
  complete seven-byte native getter at 4571F4, which loads interface-this+DD.
- The interface receiver is the complete object plus20, as the matched
  destructor and tower calls independently establish. The flag is therefore
  complete-object+FD, which the existing matched constructor also clears.
- The EA/ZH header supplies the method's scaffold-flag purpose. The original
  field name and old layout alone do not establish the target layout.

The existing native view gains a bool at FD inside its opaque padding and
provides the already-declared inline getter. Padding still ends at100 and the
pool member remains at100. The compiler emits exactly the native seven bytes,
without relocations; all ordinary existing provider bodies are unchanged.
The compiler renumbers FuncInfo/cleanup labels; the normal parent EH graph
places the cleanup at its original native address and is EXACT.
The neutral DispByteFieldGetters.cpp row retains address ownership. No new
row, pin, alias or recovered-byte claim is added for this emitted helper.
Frozen-file checks pass without introducing any annotation or allowance for it.

## Export and provider safety

The audit examines39589 cached objects, then restricts evidence to the current
ledger/data object inventory. Two old harvest objects are explicitly excluded;
they are not current providers. Only the donor object and native destructor
object reference the disappearing sole-provider names. The required flag
getter now has its real definition in the native provider.

Four shared tables change their selected provider when the old copy disappears.
Every complete byte and relocation in each surviving native table is identical
to the former copy. Other shared definitions keep their previous selected
providers. The two unique old donor tables and protected destructor have no
outside current-object consumers. Evidence records the exact scope and names.

## Verification and measured effect

Both whole accessor bodies are unchanged. The normal two-source gate passes
all6 existing function rows and literal/float/import checks. EH1 is EXACT with
no baseline or missing object. Both units have strict current receipts.
The staged code-identity check reports6 rows and zero new findings; frozen
checks pass. Placement rescanning returns0 bodies and0 pins.

Same-index paired current-provider prediction:

| Unit | Before | After |
| --- | ---: | ---: |
| BridgeBehavior.cpp | 0 | 62 |
| BridgeBehaviorDtor.cpp | 188 | 188 |
| Total existing nonpadding matched bytes | 188 | 250 |

Net **62 existing bytes predicted linkable**, plus correction of the old
out-of-layout flag getter. This is no new C++ recovery, census, placed link
or closed strict dependency result. No maintainer-only runner was used.
The removed protected-destructor marker's keyed allowance falls1->0. No
baseline, verifier rule or allowance is weakened.
