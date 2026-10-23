# AptShapeContainer::render — exact C++ recovery

`?render@AptShapeContainer@@QAEXXZ`, native `0x000A9F98..0x000AA557`,
1,471 bytes, now passes the normal source, full-byte and relocation gates in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptAux.cpp`.
This completes the bank formerly at `reverse/attempts/0x000a9f98.cpp`.

## Identity and integration

WB `0x008A7F00` self-identifies `AptShapeContainer::render` and
`W3DAptAux.cpp:1190..1332`. The native body independently establishes the ECX
receiver and RET 0, shape vector at +4/+8, transform at +0x10, virtual shape
kind/cast slots, textured/solid triangle ranges, line-segment range and
32-byte output vertices. Earlier handoffs retain the detailed layout and
callee evidence. These are target facts; the source spelling of the locals
and inline helper variants is reconstructed compiler shape.

Only render-related declarations and the body were merged into the current
home TU. Previously split-out PostDraw/draw callback definitions were not
copied back from the old bank. The existing line-list wrapper is noinline so
render calls its independently owned 7-byte body. List-end calls use the owned
fastcall cursor ABI fixed in `f9cb8520de`; no alias pins were introduced.

## The last five instructions

The incoming bank had five differing instructions (15 bytes), all in the
first and last textured UV Y products. Earlier C2 traces established why
symbol-number padding could not change these temporary-versus-temporary
ordering ties. The new hypothesis was to constrain the point-Y read itself,
rather than alter local counts or matrix layout.

Reading `in.Y` through `const volatile float *` in the two specialized inline
UV helpers forces the native point/matrix load order and product schedule.
Both the isolated diagnostic and the current home TU become exact. This is a
local code-generation constraint: it does **not** claim the original matrix,
triangle storage or source member was volatile. It adds no load or store to
retail's instruction sequence and uses ordinary C++ expressions, with no
assembly, emitted bytes, optimization pragmas or extra pins.

The thirteen inherited unused integer padding declarations were removed.
The replacement constants are used for native triangle winding (textured
1/0/2 and solid 0/2/1), zero depth and one-vertex stepping. Const qualification
and integer depth matter to MSVC 7.1's expression identities; float depth or
non-const variants change allocation. No unusedSlot declarations remain.

Fresh independent reproduction of the initial exact variant gave:

- extent 1471; instruction-count delta 0;
- differing instructions 0; differing diagnostic bytes 0; unresolved calls 0;
- resolved/masked body SHA256
  `f27d4f4c864a89be08302a70acc35746cc34e20afcdfdb34f2d289763bebe521`.

That diagnostic uses DIR32 masking, so it is only a lead. Acceptance is the
normal `add_match.py` / `./build.sh` gate, which also verifies actual data,
string, float, import and call bindings. The home TU passed 17/17 functions,
six data rows, one literal plus two empty-string references, 17 float literals
and two named imports.

## Search record

Scratch variants are under `build/apt-render-signs-20261022/`; they are not
inputs to the match. Negative controls tested balanced-sign spelling (68),
paired UV sign choices (2048), matrix coefficient hoisting (300), WB-style
non-alias assumptions (378), caller reference bindings (504), split scalar
coefficient parameters (432) and integer-address views (160). None improved
the bank. A cast-to-float family was stopped when the ordered-read family found the
exact candidate; 406 completed controls were inert. No assumptions or compiler
barrier intrinsics were retained.

The ordered-read factorial had 81 variants; two were exact. Removing prefixes from
the inherited pad groups (144 variants) lost exactness. A first
pointer/reference replacement family (144) also failed. The used-constant
factorial (16) found the exact all-const, integer-depth source now installed.
Helper cleanup and integration into the current home TU retained exactness.

The previous interrupted session's scratch was also audited: loop-entry
(1000), matrix-address pivot (135), paired pivots (216), field controls (280),
shared matrix pivots (72), comma sequencing (508), scalar matrix parameters
(64), barrier controls (32), and 2336 of the planned full-barrier family did
not beat the five-instruction bank. Those experiments are superseded by this
recovery; barrier intrinsics are not in the landed code.

Inputs: MSVC 7.1 with the home TU's `/O1 /G7 /arch:SSE /EHsc /MD`
configuration; BFME 1 checkout `37c3022de1ab944c7ffe536440d637dc8199091c`
(last successful freshness check remains under 24 hours old). Model: `gpt-6.1-sol`.

Final acceptance: `check_csv.py` and `check_csv.py --staged` pass
(98,029 function rows); `find_declared_unmatched.py` passes for the home TU;
`git diff --check` passes. `link_check.py --refresh <home>` recompiled 558
stale ledger objects, refreshed 603 already rebuilt providers, and reports
LINKS with all 3,459 current home-TU bytes linked (published census: 1,990).
The initial no-refresh preview only lacked the two cursor-ABI names added
since that census; the current-provider check has no unresolved symbols.
