# Recipes proven on near misses

Short, reusable fixes that turned near misses into byte matches. They were
proven in the solo fork (`dylanrussellmd/bfme2-solo`, private, so its commit
ids are not cited here); each recipe names the retail RVA where it closed a
body instead. `rg ',0x0042E014,' reverse/functions.csv` finds the landed row
and its source when this ledger has it; `reverse/attempts/<rva>.cpp` is the
bank where one is named. Advice tools: `tools/flag_hint.py` (flags from byte
tells), `tools/sig_check.py` (declaration vs retail), `tools/wpo_detect.py`
(private register conventions); `wb_draft.py` prints the first two with each
draft and `next_work.py` serves `wpo` candidates last.

## StrategicHUD `Impl` constructors (Apt movie clips)

- **Inline ctor calling the out-of-line callback binder.** The in-place
  callback reference gets an inline constructor that calls the rowed delegate
  binder; that is what orders the arg-slot `esp` save before `ecx`.
  HUD::Impl ctor 0x0042E014 (1801 B); CommandButtonMovieClip::Impl ctor
  0x005E136C.
- **Two-string `operator+` inline but not inlined.** Define the concat
  operator `inline` in each unit (a COMDAT at /O1, not expanded): visible, it
  lets the frame overlap the concat node with the arg-slot save as retail
  does; also the fold proof for its ICF address. New-turn indicator ctor
  0x0057C152, end-turn button ctor 0x00579575.
- **Separate button bases, nothrow base ctor.** Model the panel as an
  interface plus two button bases under their own vtables; with the base ctor
  nothrow no EH state is stored between them. Palantir panel ctor
  0x00578D22 (1811 B).
- **User-declared ctor on the text-plus-string node.** A non-POD node (a
  user-declared default ctor) lets the builder construct straight into the
  argument temporary instead of copying a temp. RegionDetailsMovieClip
  SetTabsState 0x005E314B; DynamicAutoResolveMovieClip::Impl ctor 0x005FC20E,
  which this closed from a 1013-vs-1001 B bank. The same lever in reverse:
  an out-of-line copy ctor fixed EH temp order in `0d47672ab0`
  (`__adjust_heap` 0x00428372).

## Headers and types

- **`<math.h>`, never hand-declared `fabs`/`floor`/`sqrt`.** The float
  overloads keep compares in float (dword constant, pop before `fxch`).
  0x002E3978, AIFollowWaypointPathState::onEnter 0x0034ED7B,
  isPosDifferent/isAngleDifferent 0x0028B0A8/0x0028B119.
  Calling `fabsf` directly is not the same as the `fabs(float)` overload: the
  overload's extra inline level (it forwards to `fabsf`) puts the first
  argument `pop ecx` after the `fxch`, and `fabsf` puts it before
  (W3DBoatWakeModelDraw::doDrawModule 0x000D0D24). A double operand
  anywhere in the subtraction moves both pops early instead.
- **Typed struct arrays, not byte-offset arithmetic.** Indexing a modelled
  array reproduces retail's `[index+base]` operand order. The TheAudio volume
  loops 0x0005244A and 0x000524AA.
- **Donor class shapes over flattened arrays.** A private Matrix3D with
  `float Row[3][4]` and hand-inlined identity stores missed two scheduling
  slots even with two `_ReadWriteBarrier()` calls. The donor's shapes matched:
  Vector4 rows, `Set` and `Make_Identity`, `sinf`/`cosf`, all forced inline
  as WWINLINE spells them. A plain `inline` Matrix3D is called out of line
  at /O1. Rva001040D5 camera setup 0x0010473F.
- **Constructor arguments run right to left.** When retail calls B before A
  and both values feed one object, build it as `T v(A(), B())`. That gave
  retail's getHeight-then-getWidth order and its float homes, which separate
  locals and member assignments did not. Same function.
- **Real STLport containers over hand-written views.** Use `_STL::vector`
  and friends from the vendored headers; private views drift in codegen and
  block linking. CreateAHeroManager::GetSubClassDefaultBlingId 0x0021BF11
  closed once a hand-written `ClassVector` view became
  `std::vector<CreateAHeroClass>`.
- **Inlined `DynamicVectorClass::Add` growth sum: read `GrowthStep` into a
  local.** Retail's `Resize(Length() + GrowthStep)` adds into the Length()
  register (`add ecx,eax; push 0; push ecx`). The shared vector.h spelling
  adds into EAX, and that one tie-break also swapped a later edi/ebx reload.
  Specialize the element's `Add` in the TU with `int growth = GrowthStep;`.
  Collect_Materials 0x001703D0, Render2DSentenceClass::Draw_Sentence
  0x00155B00.
- **Coord3D and Matrix3D math as the WB twin's member calls.** When the WB
  twin calls `Coord3D` mutators (`Sub`, `Scale`, `Add`, field copies through
  `this`), write them as inline members on a TU-local `struct C3 : Coord3D`
  view (`static_cast<C3 &>(delta).Sub(pos)`), initialisations included;
  explicit component arithmetic schedules the SSE step differently. Define
  `Coord3D::GetLength` / `normalize` noinline in the TU so the scaled stores
  to the escaped local die. Give `Matrix3D` WWMath's `Vector4 Row[3]` with
  an `operator[]` and use the verbatim `Rotate_Z`: a `float m_row[3][4]`
  view keeps two x87/SSE schedule swaps. An early-return inline setter
  (`if (test(bit)) return; set(bit);`) gives retail's byte-narrowed
  `test/or byte`. AIUpdateInterface::quickHordeUpdate 0x0026C4EB.
- **Coord2D the same way: a TU-local `struct C2 : Coord2D` view.** Spell the
  WB twin's MathCoord2D inlines as C2 members (`GetLengthSqrd` = `sqr(y) +
  x*x`, `GetLength` through `<math.h>` sqrt, `Normalize` with `inv =
  1.0f/len`, `Scale`, `Add`, `Set`). Free static helpers with the same
  arithmetic left an XMM-role permutation that 90 trials could not move.
  Include `Lib/Coord2DCtorView.h`: its user copy ctor gives the cached
  `fld/fstp` + `mov` copy. InGameUI::rva0029D9F9 0x0029D9F9.
- **Vector3::Rotate_Z(angle) as WWMath's nested `sinf`/`cosf`.** When the
  cos result's `fstp [c]; movss xmm, [c]` sits after independent SSE loads
  in retail but straight after `call cos` in ours, spell the angle overload
  `Rotate_Z(sinf(angle), cosf(angle))` with `<math.h>`'s inline float
  wrappers (as `vector3.h` does), not `float s = (float)sin(angle); float c
  = ...;` locals. Closed 14 schedule regions at four sites:
  Path::rva00365309 0x00365309; the same shape matches in
  GenericObjectCreationNugget::doStuffToObj 0x001F22A8.

## Flags

The region decides /O, /arch and /G for most units (`tools/flag_defaults.py`);
`flag_hint.py` compares tells with the flags the build really passes.

- **`/G7` tells.** `add reg, 1` / `add [mem], -1` instead of `inc`/`dec`
  (`flag_hint` p=1.00), and `imul` for a small scale such as `level*12`
  (p=0.93): CreateAHeroHero::SetButtonForLevel 0x0040737F and
  ShowBattleStepStateHandler::OnHitAnimDone 0x005EAEAF closed on the imul,
  the list max-scan 0x005CCCFC on `/G7 /arch:SSE`, and 18 banks improved
  with these flags and the `<math.h>` change above.
  `__EH_prolog` means `/O1`; an inline `fs:[0]` frame means not `/O1`.

## Frames, stores and locals

- **Retail reloads a global where yours keeps it in a register: declare the
  callee inline.** In 0x004BFE07 retail reloaded `TheGameLogic` before each
  `findObjectByID` call, but ours kept the condition's load in ECX. That
  happened with an out-of-line declaration and with const or non-const views,
  local copies and wrapper respellings. The fix was to declare
  `GameLogic::findObjectByID` as the header inline over the hash_map at +0xB4.
  MSVC still calls the out-of-line copy 0x00049DC5, but the inline candidate
  changes the IL. SpawnBehavior::onDie got its register homes the same way.
  Static mask tests in the same body (cached in EBX/EDI where retail keeps
  `damageInfo` there) need a different lever: route them through static
  inline helpers that take the object as a parameter. Helpers without that
  parameter changed nothing.
- **Re-fetch to defeat a second-level CSE.** If retail does
  `cmp [eax+0x250],0; je; mov eax,[eax+0x250]`, spell the second use through
  the base expression (`obj->getContainedBy()->getContain()`), not the cached
  local.
- **A stray vector-constructor-iterator call or a larger frame: spell the
  inline helpers' dead switch arms.** At /O1 even `__forceinline` helpers share
  one c2 inline budget per function, and an inlined switch's dead arms spend it
  although the argument is constant. With the DX8Wrapper Get_Transform and
  Set_Transform switches trimmed to their live arm, bfmeEnd982C 0x00110611
  inlined everything; retail ran out of budget at the last Matrix4 Transpose
  temp and builds its `Vector4 Row[4]` through `??_H` (callback the folded
  empty ctor 0x0047A6A9), which also gives its 0x98 ebp-biased frame. Every arm
  of the WB twin 0x0097C2C0 (WB is /Od with inlining and keeps them) closed all
  1773 B. Diagnostic: duplicating an inline call before the site makes the
  `??_H` appear.
- **A local object's fields held across calls: give every receiver of its
  address a body in the TU.** cl 7.1 does intra-TU escape analysis: when
  `&obj` reaches only functions defined in the same TU (in any order) that do
  not leak it, calls do not kill `obj`'s fields, which then stay in
  callee-saved registers. One declared-only receiver (ctor, `T&` method)
  reloads them after every call. Flags, `const` and member qualifiers do not
  reproduce this. Add_Mesh 0x00148180 went from 0.8152 to 0.9973 (with a
  missing `device_lock` member in AppendLockClass); landing it means rehoming
  the receivers' rows into the caller's TU:
  `reverse/attempt_support/148180-escape-20261020/readme.md`.
- **Register choice for values stored into struct fields: search the source
  order of the stores.** Retail's scheduled store order is not the source
  order, and plain reorders of eight independent `cfg.field = expr;` stores
  moved 0x000909B7 (Vp6Stream frame upload) from 0.929 to exact: which copy of
  `m_at34` / `m_at34 >> 1` lands in which register, and whether a later read
  of the field is a reload, follow the order. Generate random permutations
  (`random.shuffle` of the store lines), score them in parallel with
  `tools/variant.py`, then try single moves around the best. Retail's own
  store order and its reverse were both wrong. Copying from the twin field
  (`alpha.f = frame.f`) or deriving `uv = y >> 1` from a field was far worse.
- **A file-scope global used in hot loops: try `static`.** The same analysis
  covers globals. An `extern` or non-static object (even one defined in the
  TU) may be aliased by every store through a pointer, but a `static` one
  is TU-private. That moves the prologue load temps, biased induction
  variables (`add eax,8`, stores at `[eax-8]`) and which pointer gets a
  register. 0x0017A890 (12000 B, PointGroupClass vertex fill) went from
  0.9261 (non-static) to exact with `static VectorClass<Vector3> VertexLoc;`,
  although ZH/BFME 1 pointgr.cpp define it globally. Five sessions of
  dead-int and temp-numbering compensation for the extern were unnecessary.
  Try this before stack or temp numbering scans when a residue sits in
  loops that index a global buffer.
- **Outgoing ESP save without an EH frame: test the caller's nonthrowing
  contract.** Loader 0x000AB96D needed EH-enabled compilation to emit the
  stack save before its by-value ownership copy, but ordinary EH-enabled
  compilation also installed a frame absent from retail. Declaring the loader
  itself `throw()` retained the save and removed that frame: all 194 B match.
  Marking its callees nonthrowing alone did not recover it. Missing EH data
  alone does not prove this contract; distinguish the full instruction and
  cleanup shape. Evidence and controls:
  `reverse/attempt_support/animation-loader-ab96d-20261019.md`.
- **A store-order mismatch can require ordering the entire native write group.**
  Allocator growth 0x000334A0 was exactly 604 B except that an immediate 9
  store moved ahead of loading/storing two 8 markers. Writing those three
  existing marker words through volatile unsigned-int lvalues reproduced the
  complete body; ordering only the final word or only the first two did not.
  A full memory barrier moved unrelated header stores instead. This is a
  measured source-shape recipe, not proof of retail's original qualifiers;
  apply only to an independently established write group and verify all
  affected bodies. Controls and provenance:
  `reverse/attempt_support/allocator-growth-334a0-20261019.md`.
- **Inline helpers for Coord3D copies and zeroing.** Copying or zeroing a
  member Coord3D through a small `__forceinline` helper (Zero Hour's inline
  `Coord3D::set`/`zero`) stops cl forwarding just-stored members, so it
  re-reads them as retail does and keeps the retail store order; member-wise
  or struct assignment forwards them instead. Three Pathfinder functor
  constructors: 0x002ED72B, 0x002EE43A, 0x002ED484.
- **Block-scope address-taken locals.** Retail reuses the slot of a dead
  `&local` for later temporaries; cl does so only when the local's block has
  closed (frame 0x18 -> 0x10 in the `0x002EDCF7` bank).
- **Struct assignment moves the whole frame.** `Coord3D pos = *p;` made cl
  keep loop counters in memory and pack the range into a different dead
  parameter home; the unit's inline `copyCoord3D` (Zero Hour's `set`) gave
  retail's frame and registers (0.74 -> exact, Pathfinder::CanApproachToTarget
  0x002FA2DC). Try it first when a bank's slots and registers differ and the
  body copies a struct.

- **XMM numbering follows how each value was spelled.** cl numbers named
  locals (and inline parameters) ahead of a CSE'd constant such as 2.0f.
  Values it carries itself, such as a load read straight into an array and then
  forwarded to `color[i] *= 2.0f`, come after the constant. A uniform rotation
  (ours x0 y1 z2 k3, retail k0 x1 y2 z3) means retail had no named locals.
  Reading straight into an address-taken array keeps each load behind the
  previous store. Retail had loads first because each branch had its own array
  and call; cl shares the slot and merges the two calls, and the loads then
  hoist. Sas.AmbientLight Color 0x0014D5B0, about 30 earlier attempts.
- **A struct offset, added and subtracted.** Retail's frame was one slot
  larger (an unused dword beside `dx`), and its loop pointer sat on the last
  array the body touched. Both came from a `MathCoord2D offset(c * dist,
  s * dist)` applied with `operator+=` and `operator-=`. Scalar `dx`/`dy`
  locals gave a 0x30 frame and a pointer on the first array.
  Rva0010461F::rva00104359 0x00104359 (710 B), from nd 193.
- **Convert in its own statement for `fild; fmulp`.** `size = (Real)a;
  size = (Real)b * size / k;` stores the int before the call and loads it
  late with `fild`; `(Real)b * (Real)a` folds into `fimul`. Same function.
- **A float loaded once before the loop came from memory.** Sometimes retail
  loads a constant into an XMM register before the loop and again only after
  a call inside it. The source read a global into a local, and read it again
  after the call. cl reloads a literal at its first use in each iteration
  instead, however the local is spelt. 0x00100568, near-duplicate vertex
  removal.
- **Null-check spelling decides the order of the next block's loads.** After
  `p = call(); if (!p) continue;` cl interleaved each load with its subtract
  (`movss; subss; movss; subss`); `if (p) { ... } else continue;` gives the
  same branches with the three loads first. A snippet shows the same split
  with the pointer as a parameter (grouped) or a call result (interleaved).
  0x0050A4A2 (Made002CC8A4 cone test).
- **Name constructed temporaries.** `SailCoord3D xcol(m[0][0], m[1][0],
  m[2][0]); axis.dot(xcol)` gave retail's XMM numbering and hoisted the
  column loads; an unnamed `axis.dot(SailCoord3D(...))` did not. A named
  local with a destructor needs `/EHsc` on the unit's `// cl:` line: under the
  base `-EHsc-` cl wraps it in an `__EH_prolog` frame (650 B against 625).
  W3DSailModelDraw 0x000D08C3.
- **Parentheses stop cl reassociating by a power of two.** `distance * 2.0f
  * ease` compiled as `ease * distance * 2`; `(2.0f * distance) * ease` kept
  retail's order (0x0009B510 bank, nd 41 -> 37).
- **Inline member calls move registers far from the call.** Two in-class
  setters (`render->set00(2)` for `render->state = 2`) gave retail's integer
  registers for the whole prologue, but swapped two XMM values in a later
  block. Inline `RectClass::Width()`/`Height()` readers in that block put
  them back. When one inline fixes a block and breaks another, try inlines in
  the broken block before dropping the fix. The setters' parameters made no
  difference. Rva000471AD image clock bank, nd 24 -> 9.
- **Local count decides commutative operand order.** When a body is right
  except for a few swapped commutative operands (`mulss a, b` against
  `mulss b, a`, addition order of products), the count of initialized locals
  the body numbers can be the cause: cl breaks such ties by symbol number.
  Scan it with k inert `int unusedN = 0;` locals (positions do not matter;
  uninitialized or global ones count nothing; Vector3 counts 3, an empty
  ctor object 2; inline helpers' own locals count nothing) and land the
  smallest k that matches with a comment. The score is not monotonic in k.
  HTreeClass::Combo_Update 0x00165820: 38 diffs at k=0, exact at 23 and 31
  only (0..80 scanned; the shared-anim_num variant never went below 88).
  The same scan fixes load order at a store: Render2DClass::Render
  0x0011A040 inlines 27 StringClass terminator stores, buffer-first (`mov
  eax,[buf]; mov cl,[NullChar]`) or terminator-first (`mov al,[NullChar]`).
  k moves the boundary between the two forms; k=24 and 56 gave retail's
  (0..63 scanned, xargs -P 6) where dozens of source-shape trials had not.
  When one body inlines the same helper twice and only the second copy
  stays wrong for every k, the declaration order is wrong, not the count:
  HTreeClass::Blend_Update 0x001645B0 sat at 207 diffs in its generic loop
  for k=0..60 as `if (fast) {...} else {...}` with the generic transform at
  the top. WB's shape (fast block ends in `return`, the generic locals
  follow it at function scope) was exact at k=0.
  When no k fixes every site, scan k per site first: each site flips on its
  own window of k (period 32), and if no k lies in every site's good window,
  the sites' relative numbering is wrong. Find a real construct that adds
  temps between the sites. The 0x0073BFE0/0x0073C450 polygon rasters had
  four inlined edge `set` sites with the start sum in the wrong register.
  PREV/NEXT index-wrap macros left at least one site wrong for every k from
  0 to 160. The same ternaries as `__forceinline int prevIndex(int i, int n)`
  helpers were exact at k=0.
- **The float `tan` overload is two inline levels.** In `<math.h>`,
  `tan(float)` forwards to `tanf`, which calls `tan(double)`. Each level moves
  the call's `pop ecx` cleanup later. `tanf(x)` (one level) at one site and
  `tan(x)` (two levels) at another matched where `(float)tan(x)` did not.
  Same bank.
- **Field reads the WorldBuilder twin shows as calls want inline accessors.**
  An inline getter or setter inlines to the same load or store as a direct
  field access, but it still changes the IR enough to move global register
  choices. AptOnlineCustomMatch::ProcessGameSpyResponses 0x005A2DB7
  (9218 B) sat at 775 instruction diffs, with `this` in ESI where retail
  keeps a CSE'd 13 there, through about 2000 loop, lifetime, junk and
  callee-visibility trials. Spelling the slot reads that WorldBuilder calls
  (`getColor()` and the other saved-slot and slot getters in two cases) as
  inline accessors flipped it to retail's allocation: 2 diffs. The accessors
  in one case alone flipped it; the other case's accessors fixed the rest.
  Map every call the WorldBuilder build makes to a field read in the bank.
- **`[reg+reg+disp]` base/index order flipped: alias the member struct by
  reference.** In 0x0052F63F the only diff was one SIB byte, `[ecx+eax+0xc]`
  in retail against our `[eax+ecx+0xc]`, in one of two textually identical
  pinch loops. MSVC /O1 picks the order from IL state, so code-neutral IL
  changes flip it. Renaming, reordering declarations, const, increment forms,
  continue forms and dead locals did not flip it. A reference alias does:
  `const IRegion2D &extent=m_extent;` declared at function scope and used by
  the clamps and both loops closed the body, at the same code size. A
  factorial over alias placement and cell-pointer temps found it in 288
  compiles. Reproduce the effect in a small probe first; it showed the alias
  flips the order.
- **Stacked case labels versus separate identical bodies.** Retail's dispatch
  tail `sub eax,K; jne default; jmp X`, where our build has `je X; jmp
  default`, means the last case had a body of its own. Cross-jumping merged
  it into X but kept the fallthrough layout. Two cases whose bodies are both
  `m_setup.enable(); break;` were stacked labels in the bank and separate
  bodies in the original: the WorldBuilder jump table gives them distinct
  targets. Same body.

## c2 3077 levers traced on 2026-10-20

These are cl 7.1 backend rules, measured with the scratch c2 tracer, that
closed bodies on the same day. The evidence files are in
`reverse/attempt_support/` (named per RVA; `fp-paren-nodes-20261020.md` covers
the paren lever).
- **FP parentheses are IL nodes.** A parenthesized floating-point
  subexpression is a paren node. It delays folding and reassociation, adds
  scheduler height, adds a CSE hash var at that point, and leads its sum as a
  hash-var temporary. Spacing and names are inert; parentheses are not.
  - `float length = ((float)sqrt(e));` delays the `fstp` until independent
    loads have issued (0x004C6A20).
  - `return (x*r.x)+(y*r.y)+(z*r.z);` moves a dot `fmul` ahead of an unrelated
    load (0x0028F326).
  - `m[i][3] += m[i][0]*t[0] + (m[i][1]*t[1]) + (m[i][2]*t[2]);` keeps the
    identity's 1.0 in rows 1 and 2 unfolded through reassociation
    (0x00175E50).
  - `out->Z = ((A[0][2]*v->X) + A[1][2]*v->Y + A[2][2]*v->Z);` makes that
    product lead and fixes the xmm colouring after it (0x0055DDD1).
  - Per-component parens in a cross helper shift the hash-var numbering by one
    mod 4 (0x00561564).
- **Operand order follows FactCanonSort keys.** The larger key goes first and
  becomes the destination register.
  - temporary: 0x10000+32·X;
  - variable leaf: 0x10000|32·F;
  - memory through a hash-var base H: 0x10008+0x4000·(H mod 4);
  - memory through a named-local base: 0x10008+(((F&7)<<5)<<8);
  - inline pointer parameter p: 0x10008+0x2000·(F(p)&7);
  - MUL low half: k1+2·k2+0x30, which wraps every ~683 symbols for square
    terms. That is why reassociated `Length2` sums flip with the function's
    symbol count (0x00126433, 0x00743700).
  - Named local copies (`T *self=this;`) and removed pointer copies move F;
    inline accessors do not.
- **CSE hash vars are lexical.** Declaring a local once and sharing it between
  two branches turns the second branch's expressions into hits and renumbers
  every later hash var (0x0017D770).
- **Struct pieces.** Fields read directly in the body are numbered early, in
  source order. Fields touched only through inline members (`set`, `sub`,
  `scale`, `add`, or a `__forceinline` field accessor) are numbered late:
  x among the inline parameters, y and z after (0x00470DC1, 0x00509F3A).
- **Throwing calls carry the last EH-state alias set.** Under /EHsc or /GX a
  call to a C++ function that may throw also "may-uses" the address-taken
  locals of the function's last EH state, unless it is inside a nested
  destructor state. That adds stack-colouring conflicts. Declaring the callee
  `throw()` or `__declspec(nothrow)` removes them, and MSVC does not mangle
  exception specs (0x00095821).
- **Stack weights are counted before the tail and head merges.**
  AddStackElement counts one weight per IL reference at StackPacking.
  FgDoHeadMerge, FgTryTailMerge and FgTryCommonTailMerge delete references
  afterwards. A slot that needs one more weight than its final references can
  come from a store that was later merged away (0x0004826C).
- **Split-range reload order.** RewriteSplitGlobregs inserts reloads by the
  pieces' new candidate numbers. Those come from the `_FreeGlobs` list (LIFO),
  which coalesced copies refill. Building a matrix row-wise
  (`Row[i] = m[i]`, as WWMath's `Matrix4x4(const Matrix3D &)` does) left
  retail's free list (0x0007F0FB).
- **Address-taken status.** An out-of-line call taking `&local` makes the local
  address-taken for the whole function, so its fields are stored in every arm.
  An inline definition of the callee (for example `Coord3D::length` with
  coord3d.cpp's body) keeps them in registers until the join (0x00509F3A).
- **A dead initializer renumbers.** `Real range = 0.0f;` numbers `range`
  before later struct pieces, so they lead the products (0x0039321C).

## Linking

`tools/link_check.py FILE` judges every COMDAT a unit emits, inlined or not:
cl 7.1 emits each inline function the unit uses.

- **`sinf`/`cosf` when the census flags `?sin@@YAMM@Z`.** The `<math.h>`
  `sin(float)` and `cos(float)` overloads emit copies with `sinf` inlined,
  which lose to retail's proven copies. Calling `sinf`/`cosf` directly
  compiles to the same call sites and emits only `_sinf`/`_cosf`, which
  retail agrees with. 0x00104359.
- **A scoped `#pragma optimize("w", on)` for an `/Ow` unit's inline copies.**
  When a unit's inline members (MathCoord2D's copy ctor) differ from the
  copies an `/Ow` unit emits, and `/Ow` on the whole unit breaks the body,
  wrap only the class definition and admit the two lines with
  `tools/hatch_counters.py --admit`. Use it only for COMDATs with no retail
  address. 0x00104359.
- **`duplicate` for a header-inline member: make the strong body `inline`.**
  When one unit defines a member out of line (`Coord2D::Coord2D(float,
  float)` in coord2d.cpp) and a header gives the same member in-class, the
  strong definition and the select-any COMDAT collide. Mark the strong one
  `inline` and keep it emitted from an anchor function compiled under
  `#pragma inline_depth(0)`. InGameUIFormationFinalize.cpp went from 0 to 688
  linked bytes. 0x0029D9F9.

## Stack-slot packing: what does not explain it

Banks where retail packs locals into other dead slots, sinks a store to just
before a call, or saves `esp` after building a by-value argument were
tested together (13 banks, scratch compiles only). Do not retry these:

- **Compiler build.** game.dat's Rich header lists 1762 C++ and 184 C
  objects from 13.10.3077, the cl in `inputs/toolchains/vs2003`, and no
  LTCG or POGO entries: no other 7.1 build, no `/GL`.
- **Flags.** One at a time on each bank: `/O2`, `/Ox`, `/Ob1`, `/Ob2`,
  `/Oy-`, `/Oa`, `/Ow`, `/Op`, `/Ot`, `/Gs0`, `/GF`, `/Gy-`, `/GS`,
  `/G5|6|7`, `/GR`, `/EHa|s|sc`, `/Zi`, `/Oi-`, `/O1` minus `/Gs /GF /Gy`,
  and `#pragma optimize` `g` off, `a` on, `w` on, `y` off, `t` on. None
  was exact. The only gain was `/EHa` on `0x002080DA` (0.959 -> 0.975),
  and it made other banks worse.
- **Declaration order.** Nine orders of five function-scope locals
  (`0x002ECAFF`) compiled to the same bytes. cl 7.1 does not lay out the
  frame in declaration order.
- **Small source changes.** A const-reference parameter instead of a named
  `&local` gives the same code. So do init order, hoisting and block scope
  for the late `this` store (`0x002EDCF7`). Zero-init helper vs direct vs
  aggregate init and out-param temps change nothing (`0x002FA202`).
  Copy ctor, out-of-line ctor, virtual dtor and EH flags do not give the
  per-argument `esp` saves. A trivial dtor gives one save, but in the wrong
  place (`0x002F06A3`). An inline function returning the class by value
  copies it with `movsd` and gets no RVO. In matched code the save marks a
  class-type argument built in its own slot. Two examples: the inline
  `end()` iterators in `EnableComponents` (0x004117E8), and an out-of-line
  copy ctor (0x005E5A38). Start from those when you try this again.
- **Register-copy order.** Where `mov esi, ecx` lands next to the argument
  loads in the prologue (`0x00470717`) does not move with local order,
  inline casts or hoisting `this`.

## Shapes and order of work

- **WorldBuilder twins for loop shapes.** `python3 tools/wb_show.py 0xRVA --gd`
  shows the debug twin; its loop condition (top-tested, `break` after the
  call) is usually retail's under /O1. The first-match scan 0x002A8AB1,
  which 63 callers reach.
- **Call order in a `|` (or `+`) chain of calls.** cl evaluates such calls by a
  key: each constant argument counts about four declarations, and the callee
  declared later wins ties. Measured on two members `fA(x)|fB(0)`: fB goes
  first once more than 4x declarations separate them. Source order counts only
  among calls whose keys differ. So the order is set by where the callee views
  are declared, not by how the expression is written. For 0x0052E914's four
  setter chains, retail needed connect declared just after `SetType_Dirty`
  (the last member of PathfindCell), then layer, then E0A1 far below. That
  closed the 6-byte gap left after about 490 earlier arrangements. Map the
  constraints with a 2-function scratch TU before you search the real one.
- **Rewrite a goto bank from its COMDAT neighbours.** A unit's inline helpers
  sit just before its functions in .text, so the neighbours name the source's
  vocabulary. 0x00100568's bank was gotos and `_ReadWriteBarrier` at nd 118.
  The `Equal_Within_Epsilon` copy at 0x0010022F pointed to a plain `while`
  around a `for` that calls it, which reached nd 45 on the first compile.
- **Joined guards move the shared return-0 to the end.** When retail puts
  `xor eax,eax; jmp epilogue` inline after a guard and its epilogue right
  after the cleanup that precedes a rotated loop body, write the guards as
  separate `if (...) return 0;` statements. Joining two of them with `||` sent
  the merged return-0 block and the epilogue to the end of 0x002F64DD (+12
  bytes and an extra jump from the cleanup); loop, goal-list, success-path,
  label and scope respellings left that layout unchanged. Morphing the matched
  sibling GetHordeUnitPath (0x002F6075) toward the bank one region at a time
  isolated it in four compiles.
- **Fan-in first for repairs.** Fix the callee or spelling many rows share
  before single rows: calling SubsystemInterface's ctor through its one
  pinned `void` spelling restored 38 rows across 40 units; `link_rank.py`
  ranks by bytes held out.
- **A callee spelled `void` that returns `float`.** If the instruction after
  the call stores or uses st0 (`fstp`, `fst`, `fcomp` and so on), the callee
  returns a float. Respelling 0x002C9B80 (and its forwarder 0x002C9BC3) as
  float unblocked four callers, 1214 B in all: CanApproachToTarget,
  isWithinAttackRange, 0x002CB2D1 and HordeContain slot 20. A scan of all
  such call sites found no other member callee spelled void, only CRT import
  thunks.
- **Never hand-write `/alternatename`.** Bind callers to the ledger row's
  real spelling instead (nine units' placeholder callees were rebound this
  way); dead pragmas whose alias another object defines, or that no object
  references, can simply be dropped.
