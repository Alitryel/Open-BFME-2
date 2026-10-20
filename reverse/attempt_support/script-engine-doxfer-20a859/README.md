# ScriptEngine::DoXfer 0x0020A859 (6131 B), seat run 2026-10-20

## Result

Partial, re-banked. `reverse/attempts/0x0020a859.cpp` now holds the 2026-10-14 body (score 0.75) plus a two-argument `XferVersion` constructor. It replaces the unreviewed farm body (score 0.86), which is semantically wrong. All earlier comment lines of the bank are kept.

## Measurements

All with `python tools/align_diff.py <file> '?DoXfer@ScriptEngine@@UAEXPAVXfer@@@Z' 0x0020A859 6131`; "differing lines" counts structural lines plus memory and register operand lines, leaving out relocation and branch lines.

| body | size | structural regions | memory | register | differing lines of 2027 |
|---|---|---|---|---|---|
| farm bank (before this run) | 6193 B | 13 | 96 | 150 | 267 |
| 2026-10-14 body | 6137 B | 6 | 191 | 159 | 359 |
| this bank | 6137 B | 6 | 191 | 159 | 359 |

## Why the farm body was replaced

Its counters load loop is `i = 0; while (i < countersSize)` with no increment, so loading any save with script counters never ends. Retail increments the counter (`inc dword ptr [ebp+8]` at +0x2CB, `jl` back to +0x222 at +0x2D1), and the farm body's own diff shows the missing increment as structural regions at +0x215 and +0x2C7. Its lower memory count comes from `struct { XferVersion v; unsigned char pad[14]; }`, a padded local that only steers the frame, and its players loop test is the equal-arm `(1 ? (pit != pend) : (pit != pend))`.

## Retail facts checked in this run

- The players store loop advancing `it` instead of `pit` is retail's own behaviour: retail +0x67F loads `lea esi, [edi+0x10]` once and +0x6C6 jumps back to +0x682 unconditionally, so the loop never advances and never exits. Keep `++it`.
- Apart from the three loop entries, every remaining difference is a frame slot. All other operand differences outside `[ebp±x]` are relocations; no member offset, callee or non-frame register differs.
- Loop entries: retail enters the CRC conversion loops 1, 3 and 4 (+0x932, +0xA5F, +0xAFE) by `jmp` to the bottom test and loops 2 and 5 by a guard. All other loops of the function already agree with retail, including the jmp-entered vector loops, the `while (count > 0)` loops and the guarded map loops.
- The orphan `push 0; jmp +0x1298` after loop 1's entry jump is the cross-jumped tail shared by the named-object throw (+0x836) and the named-reveal throw (+0x11C5). It sits after the first unconditional jump that follows its origin, in both builds, so it is a consequence of the loop entry and not its cause.
- Frame: retail keeps the function-scope `i` in the dead `xfer` argument slot `[ebp+8]` (counters +0x219, flags +0x2EB, attack priorities +0x716) and also the cached `end` of the living-world store loops (+0x586, +0x5F9); it keeps the living-world `count` at -0x10. This body has `count` at `[ebp+8]` and `i` at -0x10. `slot-map.txt` lists every retail slot against this bank's slots with reference counts.
- WorldBuilder twin (`python tools/wb_show.py 0x0020A859`, WB 0xB42700, ScriptEngine.cpp 4309..4923): the version object is built from two materialized arguments, 5 first and then 1, which is a two-argument constructor call; WB's object is 8 bytes with more fields than retail's two stored bytes. WB destroys loop 1's name list out of line and inlines the destructor in loops 2 to 5, which does not follow retail's 1, 3, 4 pattern, so it does not explain the loop entries. WB compares and advances the list iterators without calls.

## Ruled out in this run

Each trial was measured against the 2026-10-14 body (6 regions, 191 memory, 159 register).

- `namedObjectsCount` declared after the three named-object locals (the farm's one source change besides the hacks): 9 regions.
- `countersSize` and `flagsSize` declared before `sequentialScriptCount`: identical bytes.
- Every counter loop with its own loop-scoped `Int i`: 6, 203, 159. Loop-scoped `i` only in the per-player loops, only in the counters and flags loops, or only in the attack loop: 6/191/159, 6/203/159 and 6/191/159. `Int i` declared at the counters section: identical.
- Living-world counts: one scoped `count` per load loop is identical; also splitting the store branch into initialized declarations gives 10 regions and +35 B; a function-scope `count` keeps 6 regions but grows the frame to 0xE8 and the body to 6166 B.
- Loop 1 as an `inline` helper is not expanded (worse); as `__forceinline` it is identical.
- `it._M_node != names.end()._M_node` in loops 1 to 5: identical.
- `/EHa`: 178 regions. `/EHsc`: identical.
- `XferVersion version(1, 5)` through a constructor: counts identical, but version moves from -0x1C (third slot) to -0x30, next to retail's -0x34. Kept in the bank because the WB twin supports it.

## What is left

The exact landing needs two things: retail's loop entries for loops 1, 3 and 4, and retail's frame assignment. No source spelling tried so far changes the loop entries; the prior bank lists the earlier loop trials (const_iterator, postfix, reversed compare, while, outer iterator, `(*it)`, dropping the local list `operator!=`). For the frame, the constructor result shows that how a local is initialized moves its slot while declaration order does not; the next candidates are the remaining member-store initializations (the timer and topple records, the counter key and value) and whatever decides that `i`, not `count`, takes `[ebp+8]`. The four ICF callee addresses the bank header names now have ledger rows; whether this body's own instantiation names resolve to them was not checked.

## Round 2 (2026-10-20, later): the frame wall pinned to the flags `bool`

The bank body is unchanged (6137 B, 6 / 191 / 159). Variants were scored with the
same `align_diff` call.

- **Root cause of the frame difference.** The flags loop's 1-byte `bool value`
  (`xfer->xferBool(&value)`) is packed into the 1-byte hole at `[ebp+0xB]` of the
  dead `xfer` argument slot. Its live range overlaps `i`, so `i` can no longer
  take `[ebp+8]`; `i` falls to -0x10 and the living-world `count` class takes
  `[ebp+8]`. Retail has `i` at +8, the count class at -0x10, the flags value at
  -0x2C (shared with the counters key's `second`), and uses +0xB only for the
  names-list allocator temps and the v3 byte-flag values.
- **Diagnostic proof** (`diagnostic-4byte-flag.patch`, not legit source, never
  compile it into `Code/`): wrapping the flag in a 4-byte struct
  (`struct { bool b; char pad[3]; } value;`) gives retail's whole frame: 6137 B,
  6 structural, 2 memory (only the unrelocated globals `[0xDFE78C]` and
  `[0xBBB8D8]`), 0 register. The only differences left are the three loop
  entries below.
- Size probes: a 2- or 3-byte struct goes to -0xE / -0x10 (wrong); 4 bytes goes to
  -0x2C (retail). So the retail object in the flags loop is either 4-byte aligned
  or is not packed into the +0xB hole for another reason.
- Inert (the bool still lands at +0xB, or worse): renaming `count`; splitting
  `count`; uninitialized-then-assigned value; value declared before the key;
  inserting a `value_type`; an extra nested block; a 1-byte struct; `bool[1]`;
  bool at loop or else scope; function-scope bool before or after `i` (worse);
  bool right after the key; a block-scoped `i` per player loop; unused int locals
  (k = 0..30 at the top, k = 1/2/4/8 in the loop); bool renames (flag, val, b,
  state, flagValue, v, isSet); `XferVersion` padding and TU-prefix pads.
- Untested hypothesis: address-taken locals are packed by scope first and the
  spilled non-address-taken `i` by live range afterwards. Then retail would have
  an address-taken 1-byte object whose scope encloses the flags loop and holds
  +0xB first, or the flag value is a 4-byte type in retail's header (an `Int`/
  `BOOL`-sized `Bool` typedef or an xfer overload taking a 4-byte value). The WB
  twin's flag value `local_75` is block-scoped right after the key
  (`local_74`/`local_70`) and is 1 byte, so the WB build does not settle it.
- WB local layout: `local_10` is `i`, used only in the counters, flags and
  attack loops (WB lines 252..260, 423..431, 1028..1038), the same three loops as
  ours. The small offsets `local_10..local_44` are function-scope variables;
  from about 0x48 the offsets follow the source order of nested declarations.

### Loop entries (independent of the frame)

Still guarded in all five loops in every variant, on top of the v5 frame:
`while` loop; `it++`; `const_iterator`; removing loop 2; `names.end() != it`;
`!(it == names.end())`; iterator declared before the `for`;
`it = it._M_node->_M_next` (does not compile, private). Retail loop 3/4 entry:
`mov eax,[ebp+8]; and [ebp-0x1C],0; and [ebp-0x18],0; mov edi,[eax]; jmp test`
(the timer record is zeroed before the entry jump). All loop dtors call
0x2FECBC (`_List_base<AsciiString>::~_List_base`, ICF-shared). Next ideas, not
tried: the names list filled by a different callee shape (retail's 0x20700F
helper inlined vs. not), and IL from the view-class casts the bank uses
(`((Rva002065C8 *)&m_flags)->...`) that may differ from retail's real member
types.

## Round 3 (2026-10-20, later): the loop-entry mechanism

The bank body is unchanged. Trials were applied to the diagnostic base (bank plus
`diagnostic-4byte-flag.patch`: 6137 B, 6 regions, 0 memory, 0 register), and the
five conversion-loop entries were read from the disassembly.

- **Mechanism (proven).** c2 rotates every list `for` loop and copies the
  test as a guard. If the guard's `names._M_node` load (`[ebp+8]`) is CSE'd with
  the `begin()` load, the guard becomes `cmp edi,eax; je`, which is our form and
  retail's form for loops 2 and 5. If something in the IL between `begin()` and
  the test may write `names`, the guard stays `cmp edi,[ebp+8]`, the same as the
  bottom test, and cross-jumping turns it into `jmp test`. That is retail's form
  for loops 1, 3 and 4. Proof: `it = names.begin(); zzExtern(); for (; it !=
  names.end(); ++it)` gives retail's loop-1 entry. The only remaining difference
  in that loop is the added call. The cold `push 0; jmp +0x1298` block then moves
  behind the new `jmp` exactly as in retail.
- With `begin()` before `m_completedVideo.clear()`, the entry is also un-rotated,
  but `begin()` loads before the call, which is the wrong load order.
- In retail the loop 3/4 order `mov eax,[ebp+8]; and; and; mov edi,[eax]; jmp` is
  only a scheduling result of the missing guard. It gives no alias clue: our
  guarded form puts both loads before the stores in every source order.
- So retail's source holds some construct between `begin()` and the loop test
  in loops 1, 3 and 4 that kills the CSE and leaves no code. Loops 2 and 5 do not
  have it. Retail's five loops are byte-identical apart from member offsets and,
  for loops 3/4, the timer element type.
- Inert, every loop entry still guarded (use `build/`-style scorers on the diag
  base; the classifier reads the five entries by `lea ecx,[esi+0x1a2xx]; call;
  mov eax,[ebp+8]`):
  - assignment-initialized iterator, before or after `clear()`;
    `const_iterator`;
  - loop through a `ListAsciiString *` or a reference;
  - loop 1 as a static helper taking references, pointers or a const reference
    (inlined);
  - a dummy block with a dead local between `clear()` and the loop;
  - timer zeroed by a constructor (`struct : BfmeSpecialPowerTimer8 { ctor }`),
    by an inline `zero(&timer)` after `begin()`, or declared after the iterator;
  - a function-scope timer shared by loops 3/4;
  - `memset` with `#pragma intrinsic` (gives `stosd`, worse);
  - `m_completedVideo` as `list<UnsignedInt>`;
  - an unknown call before the loop (the call must sit between `begin()` and
    the test);
  - template-order probes: a TU-level helper that iterates the same list types
    before `DoXfer`, or `template class _STL::list<AsciiString>;`;
  - global-limit probes: removing whole sections (counters/flags, living world,
    everything after loop 5) or duplicating sections before or after the loops.
  The loop entries never move, so it is no function-wide CSE table limit.
- Flags tried on the base (inert unless noted): `/Ob1 /Ob2 /Oy- /Op /Oi /GF /Gy-
  /Gs- /GS /Ow /GR-`, `/Os /Og /Oy /Ob1`. `/Ot /Ob0 /Oa /Og-` are worse.
- WB note: WB destroys loop 1's names list out of line (0xB47E70) and expands
  the destructor in place in loops 2-5. That splits 1 | 2-5, not 1,3,4 | 2,5, so
  it is another effect (probably c1's first-use expansion of the implicit
  `~list`).
- Next ideas, not tried: a construct around `names` that leaves no code, such as
  passing `names` by reference to an inline function between the fill and the
  loop that c2 expands only after CSE; a `const ListAsciiString &` bound to the
  fill helper's return value (the fill returns `Xfer *`, so retail's helper may
  return the list); iterating a list that the fill helper returns by reference.

## Round 3 (2026-10-20, later): frame wall solved by a class-typed flag value

Bank: 6137 B, 6 structural, 2 memory (the two unrelocated globals `[0xDFE78C]`
and `[0xBBB8D8]`, filled by relocations), 0 register. Only the three loop
entries below remain.

- **Fix.** The flags map's mapped type is a 1-byte class with a constructor,
  `struct ScriptFlag { Bool m_value; ScriptFlag() : m_value(false) {} };`,
  `typedef _STL::map<ScriptKey,ScriptFlag> ScriptFlagMap;`. The load loop
  declares `ScriptFlag flag;`, transfers `&flag.m_value` and inserts
  `make_pair(key, flag)`; the store loop transfers `&it->second.m_value`. This
  mirrors the counters loop (`ScriptCounter` with a constructor) and ZH's
  `TFlag`/`TCounter` pair. The WB twin inlines `ScriptCounter()` as member
  stores (a dword and two bytes, padding untouched, so a real constructor and not
  value-initialization), so its `mov byte [local_75],0` for the flag is the
  inlined `ScriptFlag()` as well.
- **Mechanism** (probe `build/` battery, flags section only): MSVC 7.1 packs
  address-taken scalars (and 1-byte POD structs used only by field) into frame
  holes before it places spilled register candidates, so a plain `bool` takes
  `[ebp+0xB]` of the dead `xfer` slot and pushes `i` off `[ebp+8]`. An object
  whose address is a `this` of an inlined constructor or member function is
  placed after the spills, like retail's flag. Weighting `i` with extra loops does
  not change the order.
- **Disproven in this round** (flag stays at `+0xB`): BFME's real `Xfer` API
  (`virtual Xfer &operator==(Bool &)` called as `*xfer == value`, or through an
  inline `xferBool(Bool *p) { *this == *p; }` wrapper, also `__forceinline`);
  `xferBool` by reference; union; aggregate-initialized POD struct; local
  `bool &`; char cast; `bool()`; user `operator=` not called; empty base;
  uninitialized flag; extra flag reads. A POD `ScriptFlag` without constructor
  also stays at `+0xB`.
- **Landing prerequisite.** The flags-map helpers DoXfer calls are rowed under
  `bool` names in `ScriptEngineRva0020881A.cpp` (`make_pair` 0x205670, the
  conversion constructor 0x204B33, `insert_unique` 0x2078D6 and the tree
  helpers). With `ScriptFlag` they mangle with `UScriptFlag@@` instead of `_N`;
  the rows (and `bfmeFlagForWrite`, `rva0020881A`, `evaluateFlag` users) must move
  to the struct type together, or DoXfer's relocations will not resolve.

## Round 4 (2026-10-20, latest): loop-entry wall solved, landing pending

Bank: 6131 B, **0 structural regions**, 2 memory (the two unrelocated globals),
0 register. DoXfer's own source is the round-3 body unchanged; what changed is
the TU around it.

- **Fix.** Retail compiles the two list fills, `Rva0020700FXfer` (0x20700F,
  loops 1/2/5) and `Rva00207F91XferList` (0x207F91, loops 3/4), in DoXfer's
  TU, before DoXfer, as ordinary external functions (ZH has them as
  `xferListAsciiString*` helpers in ScriptEngine.cpp). MSVC 7.1 c2 keeps a
  per-function summary of TU-local bodies even without /GL: when the fill's
  body does not let `list` escape, `&names` passed to it no longer marks
  `names` as escaped. The guard load `[ebp+8]` is then not CSE'd with
  `begin()`, and the guard cross-jumps to the bottom test (`jmp test`).
  Loops 2 and 5 stay guarded with the very same callee, which is retail's
  J,G,J,J,G pattern exactly. The bank defines stand-in fill bodies under the
  real names before DoXfer.
- **Escape rule, measured on the full body** (`ent5` classifier):
  - no call taking `&names` (nofill, an element address, a copy): J;
  - `&names` to any extern function, by pointer or reference, through inline
    wrappers, a derived `this`, an operator, a template, a `__cdecl` member of
    Xfer, an out-of-line thiscall, or `g_ptr = &names`: G;
  - a fill defined in the TU (non-static) with a non-escaping body: J;
  - an escaping body (`xfer->xferUser(list, 4)`): G;
  - a body calling an out-of-line member with `this = list` whose body is
    unknown in the TU (the current `Rva00207B90` hack class): G;
  - a `static` fill gets a custom register convention (list in ecx or ebx, no
    push). That is not retail's `lea eax,[ebp+8]; push eax; push ebx; call`,
    so retail's fills are non-static.
- **Disproven earlier this round** (all GGGGG): 18 loop control-flow forms
  (`genfc`), local-structure probes (`genfd`), fill spellings (`genfe/ff/fg/fh`).
- **Landing plan (next session).** This needs real work, not just a filing
  step:
  1. Create the DoXfer unit (`repair_queue.py dest` proposes
     `ScriptEngine.cpp`; `ScriptEngine_dtor.cpp` has other flags) with the
     bank's flags. Move the real bodies of 0x20700F (and its `__ehhandler`
     row 0x76C948) and 0x207F91 into it, ahead of DoXfer. Repoint their rows
     with `add_match --replace-existing` and delete the emptied files.
  2. Today those rows compile at -O2 /EHsc /MD with other Xfer views. Check
     their bytes under DoXfer's flags with one shared `Xfer` view: slot 11
     `Xfer &xferTypeName(const char *const &)`, slot 30 chained on its
     result.
  3. Each fill's push_back must have a known body in the TU. 0x20700F calls
     `list<AsciiString>::push_back` 0x1FD868 (a real-named row), so plain
     STLport `list->push_back(value)` fits. 0x207F91 calls 0x207B90, rowed as
     the placeholder `Rva00207B90::rva00207B90` with an unknown body, which
     gives G. Use the real `list<pair<const AsciiString,NoCaseTreeValue4>>::push_back`
     and rename the 0x207B90 owner row to that name (26 B `insert(end(), x)`
     wrapper; check that its file still emits it). Or move that row here too.
  4. Then land the flag-map rename (`ScriptFlag`, round 3 prerequisite), run
     pin_consistency and find_declared_unmatched, and land with add_match and
     `./build.sh`.
