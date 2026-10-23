# Existing PrereqUnitRec copy-provider blocker

This bounded ancillary check follows the 51DE3D landing. No provider source,
pin, ledger row or class spelling is changed. Scope file claim was acquired.
Frozen definitions passed before editing; the original source is restored.

At verified BFME1 42bba2dd and BFME2 a79e3ddfb7, the existing
ProductionPrerequisiteRecVectorCopy.cpp has three matched rows / 158 bytes,
but links zero. Its const-iterator __uninitialized_copy<PrereqUnitRec> emits
42 bytes while its existing pin names 4F5097 (38 bytes). The compiler's kept
copy therefore fails retail truth. The score screen independently LINKS
1798 -> 2979, and stlport_vector_prerequnitrec_allocate_copy.cpp LINKS 258/258.

One concrete declaration-only trial, copied from the existing suppression in
the overflow-provider TU, added before the explicit vector instantiation:

```cpp
namespace _STL {
template <> PrereqUnitRec *
__uninitialized_copy<PrereqUnitRec const *, PrereqUnitRec *>(
    PrereqUnitRec const *, PrereqUnitRec const *, PrereqUnitRec *,
    __false_type const &);
}
```

Normal verification failed the 96-byte copy constructor: extra stack pushes,
EBX receiver instead of EDI and an extra byte temporary initialization. The
52-byte push_back and handler still matched. Link preview additionally reports
the const-iterator helper unresolved. There is no kept provider under this
name, so declaring it external cannot repair the unit. The restoration passes
normal bytes again; no failed source is left under Code/.

Independent retail inspection explains the deeper conflict: native 4F5097's
loop calls 2CF99D for each 12-byte element. That existing _Construct owner is
BfmeStringRecord002CF5B1, with two words plus AsciiString, and its canonical
provider emits the required 38-byte worker. In contrast, the record view in
ProductionPrerequisiteRecVectorCopy.cpp has three raw words and an empty
destructor. Its 52-byte push_back at 2DF89B and overflow at 2A1C02 really do use
three movsd copies and no string operations, so changing the global record
layout blindly would invalidate those proven copies and the new score screen.
The copy-constructor name / pin history requires type reconciliation, with
providers and their callers checked together. Read docs/naming.md before any
owner/name repair; exact body bytes alone cannot establish that identity.

The verified BFME1 nested ProductionPrerequisite::PrereqUnitRec constructor
uses a real AsciiString field and a different nested type; its source is
reviewed but not directly transferable to this raw global record view. This is
an applicable structural lead, not proof of BFME2 identity or an inherited fix.
The existing no-exception overflow TU already suppresses this const-iterator
copy and operator= together because neither is needed there; the actual
copy-constructor provider cannot use that same omission.

Reproduction: build the unchanged provider; link_check.py the provider, the
screen and the overflow TU. Baseline preview reports 2/3 clean, 2056 -> 3237
bytes against census08160bc2c9. Private scratch trial outputs remain under
build/apt51de3d-20261023/prereq-copy-*.log. Do not repeat declaration suppression
alone. A broader class/owner repair is a separate substantive target.
