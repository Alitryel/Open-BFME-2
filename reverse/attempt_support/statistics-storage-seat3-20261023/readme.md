# Statistics lifecycle ownership: rejected visibility trial and prerequisites

Evidence only; no new match, storage definition, name, pin, header or closure
claim. Seat3, worktree t3-b3925755, source base e469b67b947a6686489318b60c3c49d20ebb958c,
unchanged donor 138757e9b74645fbcbb7724a7af2764e34931e11. Compiler grant is unset.
The earlier authorized baseline/trial/restoration used the existing isolated
OrbStack mapping, BUILD_POOL=1, BFME_OBJSTORE=off and unchanged compiler flags.
This bank and subsequent contract planning require zero source builds.

## Measured experiment, not a proposed repair

`trial.patch` is the ONLY attempted source change: Record's inline handle
destructor became an ordinary declaration. Before editing, the exact demand
`??1?$RefCountPtr@VTextureClass@@@@QAE@XZ` was independently checked against
the physical streakRender.cpp provider, native whole body and relocation,
the Record specialization's whole COMDAT, and Shutdown's existing undefined
same-name demand. The native handle destructor is **12 B at 0x0017098D**;
the native shutdown callback is **10 B at 0x007B7040**. These are not the same
extent. The provider object was unavailable and was not compiled.

Baseline: 27/27 rows, 1,763 B; EH 3/3 EXACT. Trial: 25/27 rows; EH 3/3 EXACT.
Add_Record_Texture 0x0012A210 grows 154 -> 165 B; Record_Texture 0x0012A2B0
grows 333 -> 349 B. The generated handle callback becomes a genuine exact
10 B tail call instead of 16 B, but temporary null-state optimization is lost.
Record's TextureStatisticsStruct dtor changes 12 -> 5 B; the handle dtor
definition becomes an undefined exact-name demand. No statics or registration
duplicates disappear. A correct callback alone is not lifecycle closure.

The single authorized restoration returned 27/27 and EH 3/3 EXACT, recompiling
Record only. Every source hash is restored. All parsed symbols and non-debug
COFF sections equal baseline; the sole raw-object difference is .debug$S's
per-job output filename, retained explicitly rather than hidden. Each trial
and restoration interval had one Record compiler job and six ordinary internal
winepath jobs, all runtime exits zero. No retries or provider/probe expansion.
The build's trial exit 1 is a byte mismatch, not a runtime failure.

## Native storage and registration witnesses

Image: baselines/bfme2/workshop-vanilla-1.06/files/game.dat, SHA256
f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640.
RVA is VA minus 0x400000. The saved native-lifecycle.json carries full bytes
and disassembly for the handle/vector lifecycle, not donor inference.

| Entity | Native witness | Established relationship |
| --- | --- | --- |
| owning handle | VA 0xDEE918 | init 0x7ACCC0/22 calls ctor 0x326BE6/6; atexit 0x7B7040/10 calls dtor 0x17098D/12, release 0x61ED10 |
| StringClass global | VA 0xDEE91C | init 0x7ACCE0/50 accesses this datum and registers 0x7B7050/10 with the same receiver |
| dynamic statistics vector | VA 0xDEE920 | init 0x7ACD20/26 calls ctor 0x12A520/46 with size/array zero and registers 0x7B7060/10 |
| vector destruction | 0x7B7060/10 -> 0x12A4D0/67 | rowed base dtor; existing symbols.csv fold-proof also binds the real DynamicVectorClass dtor to this full 67 B body |

The handle/vector gap is **not spare padding**: it contains the live StringClass
datum. Direct image bytes at RVA 0x7ACCE0 are
`a18c52dd006a006a00b91ce9de00a31ce9de00e8083ee6ff8b0d1ce9de008a15188ce000685070bb008811e8e8c4e7ff59c3`;
callback 0x7B7050 is `b91ce9de00e9e699e5ff`.
The committed RecordTextureEnd row independently identifies the initializer
as textureStatisticsString. This is stronger than an inference from zero bytes.

CRT at RVA 0x9A4390, ten consecutive pointer values expressed as target RVAs:
7ACC60, 7ACC80, 7ACC9A, 7ACCA6, **7ACCC0, 7ACCE0, 7ACD20**, 7ACD40,
7ACD72, 7ACD90. Raw bytes:
`60ccba0080ccba009accba00a6ccba00c0ccba00e0ccba0020cdba0040cdba0072cdba0090cdba00`.
Thus native handle and vector registration entries are not adjacent. This
establishes order/identity, not the original C++ filename or arbitrary source
declaration order. Do not manufacture padding or reorder source to force it.

## Complete contracts: equal size is insufficient

The following are actual current definitions, not proposed replacement classes.
All four scoped handle views have private T *Referent and no base/virtuals, but
their complete class definitions are different:

| TU | RefCountPtr complete-definition differences | TextureStatisticsStruct / vector differences |
| --- | --- | --- |
| Shutdown | only ordinary dtor declaration | no record/vector definition; handle is extern, not owned |
| Record | ordinary default ctor declaration; pointer ctor; copy AddRef before store; inline dtor; dllimport forceinline assignment; comparisons, Peek, three query declarations; no Clear | explicit record ctor tex(0), implicit dtor/assignment; full six-slot base vector + derived members |
| Vector | inline zero ctor with dllimport forceinline; copy stores before AddRef; inline dtor; dllimport forceinline assignment; Clear, comparisons; no pointer ctor/Peek/queries | implicit record ctor/dtor/assignment; full base and derived vector |
| ID | Vector-like handle except ordinary assignment and AddRef declaration-only | record dtor/assignment explicitly declared; full base and derived vector |

AddRef visibility also differs: Record forceinline, Vector ordinary inline,
ID declaration-only. Record/Vector/ID's base/derived vector class declarations
agree, but their element and handle definitions do not. Native refcount access
is a 16-bit field at texture +4; release is out of line and does not clear the
handle. These facts do not justify copying one complete class definition over
all the others. In particular copy ordering and implicit default construction
must be reconciled, not inferred from pointer width.

Additional real views outside the four:

- TextureStatisticsVectorResize.cpp: default handle inline; copy/assignment
  increment the 16-bit field directly; inline dtor; no Clear/queries; record
  has only three fields, no comparisons; full base-vector declarations.
- DebugStatisticsRecordTextureEnd.cpp: a different TextureClass view (not the
  same declared base relationship); inline zero/copy/dtor handle with Peek and
  one query, missing ordinary assignment/comparisons/Clear; record three fields;
  VectorClass has no virtuals and DynamicVectorClass is empty. Its static vector
  is consequently an interior-data view, not a complete declaration of the
  native polymorphic object. Current generated data index binds it at RVA
  0x9EE924, size20, rather than proving a second native vector.
- Rva007B6880Thunks.cpp: forward-declared record, one-virtual vector view;
  **defines unsigned int g_Va009EE920**, casts its address for callback
  0x7B7060. This is an existing strong external storage definition, not an extern.
- The actual global RefCountPtr template used by streakRender.cpp is
  reference/shims/bfmestreak/ref_ptr.h:225, with the dtor at342. It has additional
  constructors, friend factories, assignment overloads and conversion/helpers.
  It is not token-identical to the private views. A textual inventory finds
  183 Code files defining class RefCountPtr; that is not a proven affected-class
  closure. No relevant canonical_classes.csv entry establishes a shared contract.

## Shutdown-owner architecture versus Record co-location

Shutdown is the better **conditional architecture**, not a verified four-file
implementation plan. Its ordinary opaque dtor demand is already target-backed.
A shared identical complete class declaration could in principle be used with
out-of-class template method definitions visible in optimizing consumers and
absent in the storage owner. All instantiation/ODR/inline obligations and the
existing real providers must still be satisfied. Moving an in-class definition
out of class is not proof that MSVC preserves Record's optimizations. That
specific legitimate topology has NOT been compiled or ruled out here.

For native init22/callback10 the sole owner must see the genuine ordinary
default ctor and dtor as out-of-line, while Record must still see method bodies
needed to optimize temporaries. A shared declaration cannot legally be two
different complete class definitions selected per TU. An explicitly inline
function cannot simply lack its required definition in an odr-using TU. Template
instantiation ownership needs a separate supported account; adding attributes,
aliases, invented classes/globals or suppression is not that account.

Record co-location would remove private storage duplicates but retain its
observed inline16 callback unless its visibility changed, which this trial
proved regresses two matched rows. Shutdown co-location separates those needs,
but currently owns neither datum and lacks the complete record/vector classes.
It must not grow a new name while the Common unsigned owner survives. If whole
native registration order is required, the intervening real StringClass owner
and its callback must also be reconciled, not duplicated.

## Smallest known verification expansion and normal-tool prerequisites

The held scopes remain the four files and their exact27 RVAs in rows.tsv.
They cover 1,763 B, not the complete proposed ownership change.

| Additional whole TU | All current ledger rows | Bytes | Relevant native rows |
| --- | ---: | ---: | --- |
| TextureStatisticsVectorResize.cpp | 5 | 454 | 129990/363,129770/53,76553B/17,765530/11,76554C/10 |
| DebugStatisticsRecordTextureEnd.cpp | 8 | 1,063 | 129E50/948,7ACCE0/50,7655C7/10,765590/11,7655A6/11,76559B/11,7655B1/11,7655BC/11 |
| Common/Rva007B6880Thunks.cpp | 909 | 9,058 | 7B7060/10 vector callback and 7B7050/10 string callback; many unrelated bodies |

These additions alone give a **949-row/12,338 B lower bound**, not a frozen
complete gate plan. Common is outside the delegated Device/WW3D2 edit scope.
Its /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD command and included
GameLogic farm-library header were NOT mapped/compiled for this investigation.
End uses /DNDEBUG /MD /EHsc, string.h; Resize uses /DNDEBUG and new.h plus its
existing region settings. No runtime mapping or generated probe was attempted.

Established method providers are also name-dependent scope if their contracts
change: streakRender.cpp (21 rows/2,408 B), fxshadernamespacesas.cpp
(72/11,702), RefCountPtrTextureAssign.cpp (1/40),
TextureBaseReleaseRefThunk.cpp (1/36). The ctor326BE6, dtor17098D,
assignment424D0 and release61ED10 relationships are existing, not new pin
requests. Provider-wide source/header dependencies and other same-template
consumers must be enumerated before any grant; no provider was compiled here.

Existing names are `g_Va00DEE918` (typed extern, no current strong owner in the
four) and `g_Va009EE920` (Common unsigned definition). Neither address has a
verified data_rows.csv or data_converged.csv ownership entry. The generated
data_ledger.csv reports handle unowned and vector provisional; it is an index,
not a typed ownership proof or an authorization to invent original names.
Changing unsigned vector storage to DynamicVectorClass changes decorated data
identity, not merely an identifier. All old demands/definitions and the interior
End view must be reconciled; no cast/second-name pin keeps the old storage alive.

Normal tooling, inspected but NOT executed:

- rehome_rows.py calls build.sh even without --apply, and requires every split
  row in the home. It cannot rehome the entire909-row Common TU for one callback.
- Existing add_match replacement/admission must move actual compiler-generated
  init/callback definitions coherently; _$E2 versus explicit rva callback is not
  an object-symbol alias opportunity. Renumbered _$E labels need full native
  identity and parent/unwind verification, not assumed stable spellings.
- rename.py global requires an existing single data_rows owner and performs an
  identifier migration, not the unsigned-to-class type/lifecycle repair. Its
  present preconditions are not met for these data. No automatic legal type-
  migration route was established; this is an explicit remaining prerequisite.
- data_rows --verify can generate sizeof/array/kind probe TUs under
  build/data_rows/probe and compile them. These were outside the four-file grant
  and require explicit source/command/include mapping and authorization.
- data_ledger is tool-written; data_check --converged absence does not prove
  unique storage. Shared headers also expand frozen/class and dependent gates.

Conclusion: retain the restored exact sources. Genuine declaration/definition
separation remains a reasonable hypothesis, not an exhausted compiler lane,
but **complete sole ownership is not bounded by the approved four TUs**.
The next prerequisite is contract and typed-data-owner reconciliation including
the real StringClass/interior vector consumer and Common storage, plus an
explicit normal admission/probe/dependent-source plan. No implementation is
proposed under the current scope. Keep all31 claims pending parent disposition;
no renewal is needed yet, no release and no further compile are authorized.

## Retained diagnostics

The patch, identity/callback proofs, full four-object emission comparison,
restoration comparison/debug difference, native witnesses, normal build/EH
outputs and execution receipts are adjacent. Full object snapshots, deps,
disassembly and raw guest receipts remain in ignored
build/orbstack/statistics-mapping-20261023/visibility-trial/. They are not new
source or admitted objects. trial-findings.md references those local full
snapshots; this bank keeps the compact outputs needed to resume.
