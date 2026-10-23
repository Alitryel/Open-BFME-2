# HordeDispatch natural exception handler and destructor binding

This adds the existing C++ compiler's natural ten-byte handler at 0x00790487,
installed directly by the independently identified 278-byte HordeDispatch
doSpecialPowerAtObject parent at 0x004C8B62, with FuncInfo at 0x00941CC8.
The complete parent exception graph and every cleanup call agree with retail.
It accounts for compiler EH coverage, not newly reconstructed gameplay logic.
The full 129-line owning source was read and remains unchanged.

The earlier cohort withheld this handler because list<Object*>::~list had
eleven definitions, two shapes, and no certified binding. Its selected copy
in the existing InGameUICtor object is the same five-byte tail jump the Horde
source emits. Native cleanup calls establish target 0x00200667; its complete
callee is the independently bound 23-byte list-base destructor at 0x004EC395.
Both bodies, including all relocation destinations, match retail. The kept
InGameUI object defines both bodies, so it provides the required same-object
anchor for the tiny folded destructor. The official pin_admission --add tool
proved the whole fold against every owner and admitted this one pin plus its
derived hatch-register entry. No alias row, alternate name, source code,
compiler setting or verifier implementation was added or changed.

Target identity evidence is the rowed Horde constructor, named pool key and
secondary vtable, and contained-child traversal through real Object methods.
The pre-existing InGameUI source carries its own ZH/BFME1 provenance and an
Object-pointer idle-worker list. This change imports no new donor source and
claims no newly established full layout for either class. A pin contributes
zero additional retail bytes; only the handler adds ten unique bytes.

Bounded preparation byte-verified 87 rows across the handler owner and proof
provider and produced strict reusable dependency receipts. The handler owner
has zero identity findings over its four original rows and a clean current
link preview, retaining its existing 659 bytes. The unchanged InGameUI provider
has existing unrelated identity/link debt; provider-existing-identity-debt.json
preserves the findings rather than asserting that whole file links. The
fold admission proves the two complete bodies it uses independently.
Published census: 4ae54b0a4f, 2026-10-19 10:38 UTC. No new census, link cycle,
measured linked-byte gain or runtime verification is claimed.

Normal add_match_batch verified all five resulting owner rows. Pin consistency
passes. Normal commit and push hooks remain enabled. Raw checks are retained
under ignored build/horde-list-closure-oct19. Model: gpt-6.1-sol.
