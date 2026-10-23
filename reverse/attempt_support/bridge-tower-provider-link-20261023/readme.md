BridgeTowerBehavior provider repair, 2026-10-23

Paired legacy previews at BFME2 6a8e4fe020 against retail-truth-4 census
0fa62a2841 change both tower units from 0 to 212 linked nonpadding bytes.
See before.txt and after.txt. All five rows pass self-strict preparation,
including literal/float/import checks (self-strict.txt). Closed-strict closure,
a new census and executable placement were not measured. Authored coverage is
unchanged; the existing 28-byte deleting destructor changes source owner.

Earlier attempts correctly found that removing the non-retail ZH constructor
also removed the compiler's deleting-destructor emission trigger. The new
Defector provider repair supplies the missing ownership approach: preserve the
two live indexed units, replace the flat constructor stand-in with the actual
virtual class, move the implicit deleting-destructor row into that unit, and
remove the obsolete constructor from the home. The ordinary protected virtual
destructor stays in the home. No artificial anchor is introduced.

Native constructor 0x00458704 clears both +0x1C and +0x20. The donor declaration
already has m_bridgeID and m_type at these offsets; its constructor initializes
only the former. Initializing the existing m_type to zero gives the exact
85-byte native body with all vtable relocations, using the home unit's compiler
settings. No header/layout edit is needed. Native protected deleting destructor
0x004587B1 is the exact 28-byte compiler-generated body calling the rowed
ordinary destructor 0x004586C7. The home retains exact destructor, setBridge
and onDie rows. Existing row/table/caller evidence remains the target identity
basis; donor source and declarations are from verified BFME1
f36a4db066aa61edeee90085a31d628eb829001d. No semantic label is newly inferred
for the zero initialization.

Scope sweep: the only additional census consumer of the constructor is
ModuleFactory.cpp; its independent ModuleData/UpgradeModuleData destructor and
GrantScienceUpgrade parse-provider blockers remain. Its bytes are not counted.
Claims cover both changed units and their five RVAs. No pins, aliases or data
definitions are introduced. t=12 model=gpt-6.1-sol.
