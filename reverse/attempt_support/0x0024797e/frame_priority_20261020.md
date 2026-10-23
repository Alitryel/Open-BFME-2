# GameLogic::DoXfer frame-slot order (0x0024797E, 2195 B)

Result: blocked. The bank `reverse/attempts/0x0024797e.cpp` stays as it is. It builds 2195 B with 0 structural regions and 42 memory plus 22 register operand differences (`tools/align_diff.py`), every one a stack-slot displacement. Model claude-opus-5-5, 2026-10-20.

## The exact remaining mismatch

Retail keeps the buildable hash_map iterator `it` at [ebp-0x3c] (8 bytes, overlapping the empty `Rva0004224C` guard at [ebp-0x38]) and the `begin()` result temporary at [ebp-0x34] (sharing the [ebp-0x30] dword with tocID, status and the control-bar `slot` locals). The bank puts `it` at [ebp-0x1c] (sharing [ebp-0x18] with defaultTeam, `end` and the old-format name) and the begin temporary at [ebp-0x3c]. Because `it` widens the [ebp-0x18] group to 8 bytes, retail's slots [ebp-0x1c] to [ebp-0x30] (id, objectCount, the flag group, mode, second, the tocID group) all sit 4 bytes deeper in the bank. Everything below [ebp-0x3c] and the frame size (0x70) already match.

## How cl 7.1 places these slots (measured on this body, each probe n=1)

- Slots are assigned in a priority order, each object taking the first free run of dwords whose current occupants do not conflict with it. The empty guard occupies no space: it lands one dword below whatever has been placed when it is processed, and an 8-byte object then overlaps it in both builds.
- The priority depends on references. One extra use of `id` (a throwaway global store in the storing branch after the buildable loop) moved id ahead of the [ebp-0x18] group and of `it`; four extra uses of objectCount did the same for objectCount; one or three extra uses of `second` moved it only past mode and the flag group. So the key moves in coarse steps, not by a plain reference count.
- Unless `it` is both aliased and declared at function scope, it is processed right after the [ebp-0x18] group and before id. None of these spellings moved it: opaque `++` at for scope (a declared-only explicit specialization, which makes `it` aliased), a non-inline or `__declspec(noinline) inline` explicit specialization of `++` with STLport's body, `it` at function, block or for scope, `iterator` instead of `const_iterator`, assignment form, `begin()` as a separate statement, a const map view (NRVO, no copy), a single `*it` dereference, post-increment, a hoisted `end`, the loop in a `__forceinline` helper, and `/Ob2`.
- An aliased `it` declared at function scope (opaque `++` plus `BuildableMap::const_iterator it;` next to id and defaultTeam, loop `for (it = m_buildableOverrides.begin(); ...)`) is processed last, as in retail: every slot from [ebp-0x10] to [ebp-0x30] then sits at retail's offset (memory differences 42 to 34). An aliased `it` at for scope or at storing-block scope stays early. That variant is still not retail: the body reloads `_M_cur` after the AsciiString copy constructor (2190 B, 7 structural regions), the begin temporary lands at [ebp-0x38] instead of sharing the tocID dword at [ebp-0x34], the guard lands at [ebp-0x34], `it` at [ebp-0x40], and the frame grows to 0x74.
- Retail keeps `_M_cur` in ebx across the AsciiString copy constructor call (`lea eax,[ebx+4]` ... `mov eax,[ebx+8]`), so retail's `it` is unaliased in the loop body. Retail therefore reaches the late priority some other way. Binding `const BuildableStatusPair &entry = *it` with the aliased iterator caches node+4 in ebx instead of the node, which retail does not do.
- In every variant the begin temporary avoids the dword that tocID and status share. Removing the store-loop status local does not change that, so status is not the conflicting member.

## Next experiment worth running

Find what gives an unaliased iterator the low priority that the aliased function-scope iterator gets, while the loop body still caches `_M_cur` in ebx. A slot conflict alone would not do it, because an early `it` would only move to the next free near dword. The aliased result suggests the key penalises a live range that spans the function's later branches, so look for a retail-plausible source in which the unaliased iterator stays live that long. Separately, find which member of the tocID dword blocks the begin temporary (tocID, the load-loop status, or one of the two control-bar `slot` locals) by removing one candidate at a time in a scratch copy.

## Reproducing

Seat scratch (untracked): `build/w3_24797e/measure.sh <variant.cpp>` deletes the cached object, runs `align_diff.py`, and prints a retail-to-ours `[ebp-x]` slot map produced by `build/w3_24797e/fulldiff.py`. The bank needs `build/nbr/r6/24797e/GameLogicView.h`, which the Python snippet in the bank's `#if 0` block regenerates.
