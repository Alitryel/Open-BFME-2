# FXShaderGeometry::Init: lock, allocator and complete STL context

2026-10-22/23, codexb2, gpt-6-astra. Target `0x0018C84E..0x0018D16B`,
2333 bytes. BFME 2 input `26163d4733`, upstream `e8fe1b3508`.
BFME 1 clean verified pointer `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Stock MSVC 13.10.3077; bank flags `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The bank remains **2333 bytes, nine differing bytes in seven remap instructions
at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. Its fresh private object equals the preceding session's
object in complete function bytes and relocations. Only comments change in
the bank. No production source, row, pin or verifier was changed.

## Continue here

The previous handoff's final index-lock visibility experiment is complete.
Ordinary out-of-line definitions, their placement and combinations with the
vertex locks are inert. The exact tree teardown/clear/erase helpers and the
full STLport vector/set headers are also inert under the controls below.
Do not repeat these visibility sweeps or the encoded-presence/null-arithmetic
families. No missing-callee prerequisite was identified.

Continue the allocator investigation on the original bank. A concrete next
trace is **where candidate 29 (second-position pointer) and the literal-zero
record enter candidate 51's initial flagged live list**, before its cost is
calculated at C2 `0x8292A`. Their contribution is known; this session did not
trace the creation of those two list entries. The cost/live handoffs establish
60 = 6*(3+7) versus diagnostic 48 = 6*(3+5). Treat literal zero as a value,
not a condition flag. The later split-pointer reload path at `0x8BB3A` and
the redundant-edge cleanup decisions are already covered by the split,
edges, phase and thread handoffs; do not rediscover them. Candidate IDs are
input/round specific. Use read-only tracing and verify the resulting object
against its ordinary control.

WorldBuilder still puts P/N copies inside the two-bone arm after weights.
The 2326-byte common-tail diagnostic is semantically unsuitable for landing.
The valid skip-join diagnostics retain extra tests/frame changes. On an exact
parent landing, also row unwind funclets `0x768841`, `0x76884B`, `0x768868`
and its emitted EH handler as required.

## What this session established

Counts are generated combinations, including controls, not unique objects.
The JSON summaries cover **1727 variants: 1696 compiled, 1590 resolved by the
scoring harness**. Two preceding failed full-vector integration controls bring
the total to 1729 generated variants. Failed integration controls are not
codegen evidence. Resolution alone is not an exact-body or extent gate pass.

| Family | Generated | Result and limitation |
| --- | ---: | --- |
| indexvis + bank | 17 | All 16 index-lock contexts equal bank bytes and relocations. Actual ctor/dtor independently visible, before/after Init, inline/noinline; layout checked at 24/12 B. |
| context | 256 | Four lock bodies independently opaque, ordinary external before/after, or explicit noinline before. Every Init byte and relocation equals bank. |
| restrict smoke | 4 | Control compiles. Three qualified forms fail C4235: `__restrict` unsupported in this compiler product. Do not expand that family. |
| presence | 864 | Encoded P/N presence state across four scopes, three types, OR/add/ternary encoding, switch/if/bit tests, complemented bits and case order. 832 resolve; 32 extent refusals. Best whole result 2355 B / 554 differences; no remap-region improvement. |
| realvector integration/access/final | 55 | Includes two initial failures, five signature repairs, 32 accessor/free controls and 16 final factorial controls. Four final full-vector controls reproduce all resolved bank bytes and EH EXACT. Details below. |
| freevis | 108 | Both existing C++ free spellings independently visible/opaque/inline before/after, crossed with real tree teardown. All 90 non-force-inlined free controls equal bank bytes/relocations. Forcing the main free wrapper inline gives 2332 B, large changes and unresolved vector-base teardown. |
| realtree | 16 | Complete STLport set/tree context; independently default/opaque/noinline/forceinline tree and set constructors. Twelve resolve to the bank's complete Init bytes. Four forced-set controls leave an unresolved Rva0018C262 ctor. |
| treevis | 25 | Tree clear and recursive erase independently visible, inline/noinline, before/after Init, with exact teardown. Every Init equals bank bytes/relocations. |
| nullarith | 384 | Eight independently selected unsigned nonzero predicates for P/N, bank/PN-join/NP-join CFG, reduced/full STL context. 336 resolve, 48 extent refusals. Best 2333 B / 11 differences: original remap residue plus two changed branches. |

The arithmetic predicates include unsigned decrement/complement tests,
negation/sign-bit tests and divide-by-two plus low-bit tests. They are
equivalent nonzero tests for the target's 32-bit unsigned pointer values.
The best remap-region diagnostic still has one remap difference and many
other changes (2347 B / 487 differences); it is worse than the already
preserved skip-join controls. `regional-results.json` records this explicitly.

### Helper evidence

The index bodies come from `WW3D2/dx8indexbuffer.cpp`, layout from
`reference/shims/indexbuffercount/dx8indexbuffer.h`, and const refcount methods
from the ZH declaration. In the trial's `/O1` context their emitted sizes are
**120/89 B versus retail 171/113 B**. The vertex context uses the real
`VertexBufferLockClasses.cpp` definitions. As in the previous session, these
lock trials test semantic visibility, not exact helper context or new matches.

The free wrappers use the existing `__gameMemFreePtr(block,3)` definition.
They emit 15 B under this `/O1` context, versus retail's 17 B; no alias/pin was
added. In contrast, the tree destructor, clear and recursive erase adapted
from the already rowed `Rva0018C262.cpp` independently verify over their
**complete 56/41/45 B bodies**, zero unresolved relocations. The destructor's
EH verifies EXACT too. Ordinary and explicit noinline visibility of this
exact three-body chain leaves Init unchanged. These are existing rows,
not new recovery credit.

### Full STLport context

The real headers used here are workspace `vendor/stlport`, with
`/D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
/Ireference/shims/bfmealloc` added. The reduced vector declaration is removed.
The short base/proxy constructor bodies stay visible noinline; erase and
allocation retain existing provider boundaries. The actual `vector::empty`
and allocator cleanup explain the initial differences:

* Default CRT C-linkage free removes the four-byte EH-state store at +0x811.
  Specializing `allocator<short>::deallocate` to the existing throwing C++
  `Rva00030830GameFree` restores that store. No new symbol is invented.
* Specializing `empty() const` to `begin()==end()` restores the other operand
  ordering changes. Further `operator[]` and allocator-proxy adaptations are
  inert. The four resulting controls exactly equal the bank's resolved Init
  bytes and have EH EXACT.

The initial custom `__distance` explicit specialization fails C2785/C2912
against the actual dependent-return template. The working control uses a
non-template overload and iterator typedefs. This is a context experiment,
not a proposed replacement for the bank or proof of its support helpers.
With `<set>` added, native iterators supply `_M_node` through the public
begin/end methods. The actual set/tree constructors emit 25/42 B but still
have unresolved downstream template names when checked independently;
they are not claimed exact. Init's calls itself resolve in twelve controls.
`full-stl-control.cpp.txt` preserves one reproducible control and these limits.

Workspace `_vector.h` has blob hash
`200a0c2cc88d4a5bc16ca835f125f9e631c9bc6a`; the BFME 1 vendor header has
`7ad440c58705439eac962e94855cb543c0913902`. The difference is resize's
const-reference versus by-value element argument. This experiment uses the
workspace header; Init still invokes its existing by-value resize provider.

## Checks, provenance and reproduction

`check_csv.py` passed at startup: 98,069 functions, 15,856 symbols, 2,135 data.
The clean BFME 1 checkout/pointer was preserved. Upstream freshness was
deferred under the live update lock owned by `claudec2`; neither its lock nor
the old success stamp was changed. The standing assignment skips broad queues.
No maintainer-only runner was started. `progress.py origin/master` reports
+0 authored/exact C++ bytes. This is an unfinished partial, not a byte-gate pass.

The bank, vector, free and tree verification JSON files preserve actual
resolved-byte/EH checks and explicit helper limitations. `context-verification`
records all 256 complete-byte/relocation comparisons. The summary and regional
files keep useful winners without archiving thousands of redundant variants.

Restore `*.py.txt` under ignored `build/fxinit-index22/`. Drivers use
`build/fxinit-seat22/search.py` from the schedule handoff. Its only local change
this session saves full compiler failures to `.errors` and filters error lines
in the returned record; it does not alter compilation or scoring. Recreate
`skipjoin_020000` from the edges handoff before `nullarith.py`. Run indexvisibility
before contextcross, realvector before realtree, freevisibility before
treevisibility; realtree must precede nullarith. The initial realvector fix
and access families remain generator functions in its driver; its default
entry point generates the final sixteen controls. No object was written to
the shared `build/match/` cache. Full scratch sources/objects remain in
`build/fxinit-index22/` for this seat.
