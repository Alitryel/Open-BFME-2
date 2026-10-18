BattleSide vector cleanup 00784066

Native constructors 003F64B2 (124 bytes) and 003F652E (127 bytes) share exact EH handler 00784084 and FuncInfo 00930158. Unwind entry 00784066 is 11 bytes: load this from EBP-10, add 4, then jump to 003F5E85. The source emits a private vector<Rva003F64B2Element> destructor of 59 bytes; the retail owner vector<Rva003F610FElement> is 63 bytes in FamilyVectorDtors_new.cpp. A pin cannot establish whole-body equivalence.

The attached trial reconciles the 48-byte element spelling supported by constructor 3F55D6, destructor 3F535B and reserve 3F5F15, declares the existing vector destructor, and removes three redundant aliases. All parent instructions remain identical except unresolved REL32 sites for the renamed push_back and second constructor(int,const void*). Existing linker aliases do not supply verifier identities for those renamed declarations. No guessed pin was added, and the original Code source was restored.

The unchanged provider FamilyVectorDtors_new.cpp also has a pre-existing missing Rva004DA181Element teardown and private Destroy COMDAT conflicts. OuterRecordCtorRva003F64B2.cpp itself links at baseline. Repair requires coherent element/provider declarations and consumed-operation identities; do not retry an unchanged pin or the same rename alone. The independent cleanup entries 784071 (vector<int> at 7FAB3) and 78407C (element at 3F535B) have since been verified and committed.

The patch uses zero context. Check it without changing production source with:

    git apply --check --unidiff-zero reverse/attempt_support/b66d-battleside-cleanup-20261018.patch

Inputs: author HEAD 898c514205; BFME 1 reference a18d9ed50607e9175de4d6568798d7d73119de09; existing source flags /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc. Evidence comes from tools/build.py full-byte checks, tools/link_check.py and the complete EH graph. Model: gpt-6.1-sol. Approximately 8 minutes.
