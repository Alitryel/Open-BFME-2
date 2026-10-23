# AptScoreScreen 0x0051DE3D: native allocation, final call still indirect

Target: `?rva0051DE3D@AptScoreScreen@@QAEXXZ`, 1061 bytes, ending at
0x0051E262. Home:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScoreScreenCallbacks.cpp`.
BFME2 input: `1be9633cb6`; BFME1:
`37c3022de1ab944c7ffe536440d637dc8199091c`. Model: gpt-6.1-sol.
Started this body 2026-10-22 19:48 UTC, after recovering BuildAssistant.

## Current frontier

The new bank is a faithful allocation probe, not an exact reconstruction.
Immediately before the final state test it declares:

```cpp
typedef bool (AptScoreScreen::*Populate51)();
const Populate51 populate51 = &AptScoreScreen::PopulatePersistentUnitsListbox;
if (m_280 == 1)
    (this->*populate51)();
```

This restores the native 0x38 frame and the begin.p home at EBP-0x20 in
the hero loop. All instructions before native +0x3E2 have the native operands
and sizes after ordinary relocation resolution, except for branch distances
to the now longer tail. It changes no objective, army, hero or living-world
behavior. It introduces no runtime callback choice: the member pointer always
names the existing public nonvirtual method.

The remaining native differences are entirely at the final call:

```text
native +3E2: cmp dword ptr [ebx+280h],1
       +3E9: jne cleanup
       +3EB: mov ecx,ebx
       +3ED: call PopulatePersistentUnitsListbox

bank   +3E2: xor ecx,ecx             ; additional, unused zero adjustment
       +3E4: cmp dword ptr [ebx+280h],1
       +3EB: mov eax,PopulatePersistentUnitsListbox ; additional address load
       +3F0: jne cleanup
       +3F2: mov ecx,ebx
       +3F4: call eax               ; indirect, two bytes versus five
```

The body is **1065 bytes**, four too long, with **no unresolved references**.
Fresh fitness is **0.9806579794700435**, versus **0.9160674528160351** for the
unchanged incoming bank (1055 bytes). The scratch mnemonic-aligned diagnostic
reports two insertion regions and one changed call operand: ND=3, memory=0,
register=1. This metric ignores resolved relocation sites and consequent branch
offsets; it is not interchangeable with older align_diff counts or byte proof.
The normal 1061-byte extent remains unchanged. The bank is not game source.

`reproduce.py` compiles the current bank and restores the old direct-call form
for a control. It writes unique objects under build/, uses the normal compiler
command and relocation resolver, and never calls build.compile_source. Its
diagnostic scoring window accommodates the larger probe; it cannot approve a
ledger row. The complete source of the best body is in the normal bank.

## Prior evidence read before editing

Read pick-hard's target history and the w6 (20261019), w5/w3/w1 (20261020)
and c3 (20261021) handoffs. The incoming body already has live objective reads
and current image-setter spellings; do not reintroduce the older pointer/count
cache or retired setter name. Target identity, ABI, boundary and field evidence
remain those records' conclusions. The method remains address-named.

Already disproved before this session: all ten relevant visible retail helper
bodies, AsciiString and text-setter chains; natural hero vector push/sort;
inline get638/KindOf; direct bonus member; hiding Populate's body; size and
iterator/end-begin variants; inert aliases and empty inline calls; hundreds of
renames; ordinary flag permutation; VC7.1 SP1/DDK alternatives. Non-const
end-begin restores the home but rotates global register roles and adds six
bytes. The WorldBuilder dead upgraded counter and the previously tried loop
and tail rearrangements did not repair that.

## New experiments and what they rule out

`families.json` records completed families, valid/error counts and their best
scores. All objects were isolated; families used eight compiler workers each.
No compiler, gate, baseline, shared header, symbol pin or Code source was changed.

- **Control flow:** 512 loop-entry/guard/sign/slot combinations, then the 192
  scope-corrected objective-index cases. Also 96 duplicated sort/clear tails.
  None beats the original bank. Do not retry the unscoped index collisions as
  codegen evidence: those were compile errors and were corrected separately.
- **Lifetimes and declarations:** 470 address-path combinations, 1024 correctly
  target-scoped const-reference temporary combinations, 60 correctly scoped
  volatile/const loop-counter trials, and 400 pointer-copy/union/memcpy
  roundtrips. Pointer copies were entirely inert. The first temp_lifetimes and
  stack_counters runs accidentally changed the preceding sibling for some
  substitutions; the target_* reruns supersede those particular results.
- **Types and layout:** 256 volatile-read combinations, 144 by-value/reference
  screen-context combinations, 64 boundary constness/return-type cases,
  64 hero-record construction shapes, 576 iterator-parameter permutations and
  qualifiers, and 376 field-address lifetime combinations. The iterator family
  can restore a home while adding extra loads/stores; it does not give native
  hero instructions. Field-address lifetimes fix the hero allocation but break
  the objective prologue. No layout change was supported by native evidence.
- **Callee visibility and inlining:** 62 region-helper partitions; 76 key/string
  factories; 75 original member-call variants; then 384 member-pointer declaration
  trials, a 128-case corrected follow-up, 192 inline member wrappers and 144
  free helper argument/const-reference forms, then 120 inline call-object
  constructor/copy/scope forms. Inline wrappers either retain
  the same indirect call or fold to the old allocation. A PM equality/direct-call
  fast path also failed to combine the native frame with the direct call.
  The single-inheritance PM model is incompatible with the existing multiple
  inheritance callback ABI; its failed compiles are not useful negative codegen
  evidence. Changing the global PM pragma also breaks the AptTimeLine callback
  cast. Do not weaken those contracts to obtain a small PM representation.
- **Compiler settings:** eleven opaque callee throw specifications were inert.
  On the improved bank, 36 /O1,/O2,/Ox, /Ob1,/Ob2, /G5,/G6,/G7 and /Og combinations
  did not improve the call. The retained /O1 /G7 /arch:SSE profile is unchanged.
- **Barriers:** 237 intrinsic-placement trials and 128 initial-objective-cache
  combinations. A read/write barrier immediately after the null test fixes the
  hero allocation but introduces objective reload/prologue differences. A 1067-B
  form differs by only one extra objective-pointer load, but is a worse score
  and has an unresolved shifted vector-base call. It is a diagnostic, not a
  replacement bank. Some cache-only forms weaken live-read semantics and are
  excluded regardless of their scores.

## Compiler allocation evidence

Read-only winedbg breakpoints in the stock Wine/MSVC7.1 c2.dll were used; no
instructions, priorities, registers or compiler inputs were patched. DLL SHA256:
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Runtime base was 0x10700000. `allocator.json` retains compact observations without
heap-address dumps; raw traces remain in build/apt51de3d-oct22/.

The direct-call baseline's `_this` global record (index 12) has priority 56,
11 references and cost 21. A deliberately **nonlandable** control that stores
this to an added global immediately before sort gives priority 77, 12 references
and cost 24, and the native allocation apart from that extra store. The count
record has priority 57; other records have priorities 72 and 180. Thus this
crosses several competing priorities: count alone is not a proven cause.
The baseline takes seven allocation rounds, the control eight. `_this` retains
the same priority in every round of each run. Aggregate child identities inferred
from symbol parent chains are leads, not established C++ variable names.

The improved member-pointer bank was also traced: `_this` is index 15, priority
**79**, 11 references and cost 23 in all eight rounds. This is stronger evidence
than the artificial global-store control: the faithful expression itself moves
the receiver's allocation priority above the 57 and 72 competitors. It does not
prove which particular conflict makes begin.p spill.

Useful c2 offsets: +83AC8 before priority calculation, +83ACD after it,
+82978 at round start, +A8F54 at a split, +82273 after integer allocation.
Global-record hash heads are at 0x108807B8 (1024 entries); block count at
0x108817B8. Record dwords: symbol=0, priority=3, index=7, reference count=9,
next hash link=12, cost=16. Per-block priority sites are +82919, +83A45,
+83A7B and +C21CE. The attempted liveness-bitset decoder returned empty for
every block and is not trusted. Block weights observed were all one.

The new member-pointer form shows that a faithful expression can reproduce
the full native allocation. Its additional call machinery is the next concrete
problem. Repeating the old 1024 reference aliases or 400 pointer copies has no
support. A useful continuation should explain how a direct call can keep that
allocation, or why a different faithful expression affects the allocator's
competing web without adding native instructions.

## Checks and handoff

The Code home remains unchanged and its declared-unmatched check passes.
`check_csv.py` passes with 98042 functions, 15886 symbols and 2124 data rows;
`git diff --check` passes. `reproduce.py` independently reproduces both the
new bank and the incoming direct-call control; its results are retained in
`reproduction.json`. No exact candidate
was installed or declared matched, so this target has no byte-gate or link
acceptance claim. The already committed BuildAssistant recovery separately
passed the full home-TU byte/data/EH checks and link prediction.

The improved bank and score are recorded through re_log.py. The claim is released
for a safe session boundary; the standing assignment continues on this same
body. Scratch families, full traces and the original bank remain under
build/apt51de3d-oct22/ for this checkout.
