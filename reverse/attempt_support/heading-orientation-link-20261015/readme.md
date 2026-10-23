# BFME orientation getter link repair

Base: `53b5e72f8bc861b01c7c47c57c218ea2e34766bd`. The retained runner index
is dated 2026-10-15 09:33 at `19a2565407`, from census `5986a99448`.
`context.json` records its SHA-256. The committed link-status measurement
is different and is not used to calculate the paired improvement.

Two consumers emitted an unused external `Object::getOrientation` COMDAT
loading offset +0x1C0. Other private Object views emit a +0x44 load under
that same name. The retained index has 24 copies: these two +0x1C0 copies
and 22 +0x44 copies. No retail address is established for this standalone
getter, so local link rules select by link order rather than retail identity.
The two edited functions already inline their +0x1C0 access. Marking this
view's getter `dllimport forceinline` retains the access and suppresses the
unused external copy. Neither object acquires an import or new external
binding. This removes competing copies without establishing a canonical
Object layout or changing callers to another view's offset.

The target facts, identity and layouts remain those documented in the two
existing sources: InGameUI's 155-byte heading query at 0x0029B3C1 and the
730-byte W3DModelDraw transform callback at 0x000B7FE8. The compiled and
relocated body comparisons establish acceptance, not a new class identity.

## Acceptance

- Bounded preparation verifies both matched rows and establishes strict-current
  reusable receipts before and after. The after byte gate passes 2/2 with
  three float literals; there are no string or named-import references.
- `proof.py` compares saved before objects with current objects. All five
  retained COMDATs in the heading query and all 25 in the model callback are
  identical in bytes, size and relocation digest. Every remaining nondebug
  section and every linker directive is identical. Each object loses only
  the unused seven-byte `fld [ecx+0x1C0]; ret` getter and its external binding;
  neither object had any nondebug reference to that standalone getter.
- Paired local previews deep-copy the same retained index and refresh only
  the same two objects. Heading-query findings decrease 1 -> 0, and model-draw
  findings decrease 2 -> 1. Existing authored bytes predicted linked increase
  0 -> **155**. The model callback still has the unresolved
  `Rva00084206Track::addEdgeToTrack(float,float)` at pinned 0x0008458A;
  it contributes **zero** linked bytes to this result.
- Declared-definition, class, enforced data, converged-data, new-variant and
  CSV checks pass. Neither row has EH data. Placement resweep finds zero additional bodies or pins; no ledger row, pin, compiler flag or shared header is changed.

This is a bounded local **legacy** prediction using strict-current objects.
It is not a self-strict executable-placement or closed-strict result. New
C++ recovery bytes are zero. The census, index and status CSV are untouched.
Full link cycles, census rebuilds, nightlies and boot checks were not run;
broader linked-image verification remains outstanding.

`proof.py` runs from the repository root using ignored snapshots in
`build/heading-orientation-link-20261015`; `proof.json` preserves their hashes
and the complete paired findings. The previous source is available at the
base revision above.

## Reference review and deferrals

Reviewed BFME 1 repairs `d3f9000fe08615a100e844adfff57fa4a39cd615`
(TileData's incidental competing constructor) and
`d2e21369067f2f2c762c1c7ec2792c75f1ecf53d` (seven BfmeStrVKI wrapper
constructors changed to declarations). The applicable ownership lesson is to
remove incidental competing definitions while preserving retail callers.
Their layouts and implementations are not imported. BFME 2's own offset
accesses and object equality support this local adaptation.

The verified BFME 1 checkout and gitlink remain
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`75ff0c148` during this pass. Another seat owns `file:reference/open-bfme-1`;
the overdue comparative pointer update is deferred to that owner. The old
freshness stamp is preserved, with no new success claimed.

Two other candidates were investigated and recorded in `re_attempts.log`:

- RTS3DSceneFlushOccludedObjectsIntoStencil already LINKS **1,853** bytes
  after strict preparation at this base. Its stale queue entry warrants no
  source edit or gain claim. AIIdleStateUpdate, GameLogicRegisterObject,
  Rva000E473F and ModuleFactoryInit also already pass ordinary local checks.
- Rva0042CB81's rowed camera handler still touches a wrongly selected generic
  Rva0004224C constructor. Two wrapper trials redirecting through its rowed
  member owner each change the handler frame from push/push to sub esp,0xC
  and move the guard from the parameter's +8 home to a local -0x18 slot.
  The handler fails while its seven sibling rows retain their matches. The
  source was restored and its byte gate passes **8/8** again. The provider
  W3DDisplayGatherAnimationDebuggingInfo is foreign-claimed. Both claims for
  this abandoned consumer were released; no third trial was made.
