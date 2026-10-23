# RTS2DScene destructor identity blocks linking

Read-only investigation at BFME2 7de360dd63, BFME1 donor 96c88c73, published
retail-truth-4 census b711de3634. No Code edits or body growth.

Target evidence establishes the constructor/destructor relationship:

* Named ctor 0x0006F9D6 (RTS2DSceneCtor.cpp) passes string VA 00BC6438
  RTS2DScene to setName and installs primary table 00BC62A0 at this+0 and
  secondary table 00BC6264 at this+0x108.
* Primary table slot 1 is VA 0046F24A. Its complete 28 B deleting destructor
  calls VA 0046ED6F, tests delete flag 1, calls operator delete and returns 4.
  It is rowed as ??_GRva006ED6F@@UAEPAXI@Z.
* Secondary slot 0 is VA 0046F02E: subtract 0x108, jump 0046F24A. This 11 B
  thunk is rowed as ??_ERva006ED6F@@WBAI@AEPAXI@Z.
* Complete 116 B destructor 0x0006ED6F is rowed in Rva006ED6FDtor.cpp. It
  installs its two tables, directly removes this+0x114 from SimpleSceneClass,
  releases/clears that reference, then destroys SubsystemInterface and
  SimpleSceneClass. These members/bases agree with the named constructor.

Donor semantics independently agree: Zero Hour W3DScene.cpp:1757 implements
RTS2DScene::~RTS2DScene by Remove_Render_Object(m_status) and REF_PTR_RELEASE.
BFME1 game/GameEngineDevice/Source/W3DDevice/GameClient/
RTS2DSceneDestructorThunk.cpp at 96c88c73 is the corresponding clean C++ donor;
place_bodies.py against BFME2 finds 0 bodies/0 pins. The donor private
SubsystemInterface is 8 B while the BFME2 canonical base is 12 B, and BFME2 calls
the scene removal directly; do not count the donor trial as byte proof.

Current three-unit `link_check.py --refresh` leaves RTS2DSceneCtor.cpp out
(163 B in the current preview; the census rank says 196 B) solely for undefined
??1RTS2DScene@@UAE@XZ. The complete-dtor provider already links 116 B under
Rva006ED6F; the opaque
deleting-dtor unit retains independent unresolved base destructors. The paired
preview is 1/3, 116 -> 116 B, with the constructor still blocked. Log:
`build/link-seat-20261023b/rts2d-before.txt`. A coordinated class-name
reconciliation must include the
complete dtor, EH rows, deleting bodies/thunk, constructor and other users;
never add a second pin, alias wrapper or duplicate body.

Dry-run command:

    python3 tools/rename.py class --name Rva006ED6F --new RTS2DScene \
      --basis canonical:string --evidence '<constructor0x0006F9D6 string, tables and dtor chain above>' --dry-run

Refusal: `canonical:string: no function of Rva006ED6F is at 0x0006F9D6`.
The string belongs to an already named constructor; the tool does not accept
this cross-name constructor/table/destructor relationship as canonical proof.
Per the false-reject lane, no check or production source was changed. A tooling
seat can add checked relationship evidence and a regression test, retaining
all existing exploit refusals, then retry the coordinated rename and measure
the paired providers/consumer. No linked-byte gain is claimed here.

Other measurement limitation: --refresh --current-ledger refuses 11,864 objects
without current compiler evidence at this checkout; this is distinct from
the naming refusal. The normal full function phase passes 98,186/98,186, and
full EH inspection has 11,870 exact plus 24 existing baselined findings, no
missing objects. Retain the published index; do not launch a census here.
