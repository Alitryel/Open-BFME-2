# HordeContain 0x0046D2C3: register-priority probes (w2, 2026-10-20)

Result: **blocked**, bank `reverse/attempts/0x0046d2c3.cpp` unchanged. Target `0x0046D2C3..0x0046D372`, 175 bytes, slot 69 of the +0x11C vtable (VA 0x00C44C58 holds 0x0046D27A, 0x0046D2C3, 0x0046D372 at indices 68, 69, 70). Model claude-opus-5-5.

## Where the bank stands in the current home unit

The bank body, appended to a copy of the current `HordeContainIface11CSlots.cpp` with the bank's slot and `ThingTemplate::isKindOf` declarations, measures with `align_diff.py`: ours 175 B / 70 insns against retail 175 B / 70 insns, 2 structural regions (only where `push edi` is scheduled), 13 memory differences (2 of them the TheGameLogic DIR32 slot), 8 register differences, 5 relocations. Every difference is the register assignment: ours this=EBX, list sentinel=EDI, list cursor=ESI, set iterator=ESI, found Object=EDI; retail this=EDI, sentinel=ESI, cursor=EBX, set iterator=ESI, found Object=EBX.

Bank maintenance: the home now declares `Object::isKindOf(KindOfType)` out of line (the rowed 0x0006F039, called by 0x0046EA94 and notifyOfMemberDeath), so the bank's listed edit "add an inline `Object::isKindOf`" would break those rows. Write the template test as `(*it)->getTemplate()->isKindOf((KindOfType)kind)` (or a differently named inline), declare `bool isKindOf(KindOfType) const;` on ThingTemplate (pin `?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z` at 0x000456AC exists), and move the `KindOfType` enum above ThingTemplate. Compiled that way the body is byte-identical to the measurement above.

## New finding: the size of the allocation gap

Greedy colouring explains both assignments. Retail's result needs the sentinel (or the set iterator) to outrank `this`, and `this` to outrank the list cursor and the found Object: max(sentinel, set iterator) > this > max(cursor, found Object). Ours ranks cursor > sentinel > this and set iterator > found Object > this.

Diagnostic probes (throwaway global stores, never landable) measured the gap:

| Probe added to the bank | Resulting webs |
| --- | --- |
| one `this` use before the slot-70 call, or right after it | this=ESI, sentinel=EBX, cursor=EDI, set iterator=EDI, Object=EBX |
| one `this` use in loop 1, its return arm, the front arm, between the halves, in loop 2 or its arm, or in the final arm | unchanged |
| two `this` uses between the halves | as the first row |
| one sentinel use after the list loop | sentinel=ESI, cursor=EDI, this=EBX |
| one `this` use before the call plus two sentinel uses right after `end` is taken | **this=EDI, sentinel=ESI, cursor=EBX, set iterator=ESI, Object=EBX, exactly retail's assignment**; the only remaining differences are the probe stores themselves |

So the wall is roughly one straight-line reference of `this` before the list loop plus one reference of the sentinel, with nothing else in the body changing. A natural construct that supplies those references without emitting code is the open question.

## Ruled out this run (all measured with align_diff and the webs read off the object)

- Slot 70 as a by-value return (hidden-pointer temporary, as 0x0046247D's `return &p` suggests): the named-local form compiles byte-identically to the bank; reading `.m04` off the temporary reads `[eax+4]` instead of retail's `[ebp-4]`; calling through a cast view adds a null check (+12 B).
- The visible-callee lever: `__declspec(noinline)` visible `ThingTemplate::isKindOf` (emitted 21 B, retail's size) alone and with its bit-test helper visible (31 B) leaves the allocation unchanged. The only address-taken local, the pair, escapes into a virtual call, so no visible body can unalias it.
- Compilers `vc71-sp1` and `vc71-ddk-4035`: identical. Flags `/G6`, no `/arch:SSE`, `/Ob2`, `/Ow`, `/Oi`, `/Ox /Os`: identical; `/O2` and `/Oa` worse.
- 16 combinations of `it++`/`k++`, nested `if (obj)` and the continue-form list test; `end` as a const local or a const reference, `front(end)`, swapped comparison operands, `!(a == b)`, `obj != 0 && ... == false`: all identical.
- Find-style list loops (`while (it != end && ...)`, `break` then `if (it != end)`, `for` with `&&`): +6 B, same webs. Reusing `it` for the front test: identical. `++it` past the end without a reset: 170 B. Begin derived from the sentinel: identical.
- An early-bound `m_170` reference or pointer (before or right after the call): identical.
- Wrapping the body after the call in `do {} while (0)`, `for (;;) { ... break; }`, a plain scope or `if (flag)`: same webs. Dropping the final set lookup: same webs.
- The d3 verdict's "two-web" state does not reproduce: the bank compiled against the home unit at commit 69a2583716 with its listed edits gives the same full rotation as today.

The trial harness (home-copy edits, measurement and the web extractor) is `horde-46d2c3-weight-probes-20261020-w2.py.txt` beside this file.
