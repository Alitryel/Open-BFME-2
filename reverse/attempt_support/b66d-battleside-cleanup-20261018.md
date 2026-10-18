BattleSide vector cleanup 00784066

Native constructors003F64B2/124B and003F652E/127B share EXACT EH handler00784084, FuncInfo00930158. Unwind entry00784066 is11B: load this from EBP-10, add4, jump003F5E85. The source emits a private vector<Rva003F64B2Element> destructor59B; retail owner vector<Rva003F610FElement> is63B in FamilyVectorDtors_new.cpp. A pin cannot establish whole-body equivalence.

The attached trial reconciles the48B element spelling supported by constructor3F55D6, destructor3F535B and reserve3F5F15, declares the existing vector destructor, and removes three redundant aliases. All parent instructions remain identical except unresolved REL32 sites for renamed push_back and second constructor(int,const void*). Existing linker aliases do not supply verifier identities for the renamed declarations. No guessed pin was added; original Code source restored.

The unchanged provider FamilyVectorDtors_new.cpp also has pre-existing missing Rva004DA181Element teardown and private Destroy COMDAT conflicts. OuterRecordCtorRva003F64B2.cpp itself links at baseline. Repair needs coherent element/provider declarations and consumed operation identities; do not retry an unchanged pin or the same rename alone. Other cleanup entries784071 (vector<int>7FAB3) and78407C (element3F535B) are independent verified providers and remain viable.

Inputs: author HEAD898c514205; referencea18d9ed50607e9175de4d6568798d7d73119de09; existing source /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc. Diagnostics: tools/build.py full-byte checks; tools/link_check.py; complete EH graph. Modelgpt-6.1-sol; approximately8minutes.
