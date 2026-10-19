# Handoffs, 2026-10-19 (claude-sonnet-5-5 / opus-5-5 session on Austin's PC)

Concise banks for two bodies whose log lines cite them. Neither matches; bank sources under `reverse/attempts/` are unchanged.

## 0x003E9062 evaluateSkirmishSpecialPowerIsReady (404 B)
- `0x003e9062-w2-loop-body.cpp.txt`: the loop spelling that gets retail's whole register allocation (396 B, 4 structural regions, 0 non-relocation memory lines, 2 register lines). It binds `Object *pObj = oiter.cur();` AFTER an `if (!oiter.cur()) continue;` in a `!oiter.done()` loop. Binding pObj before the null test (the shape in the old bank) forces EDI onto the list iterator (402 B, 11 regions).
- Residue vs retail: retail keeps a redundant second null test after the entry guard (jmp/reload of EDI at +0xDB) and compares done() in memory at the bottom (`cmp [ebp-0x34],0` at +0x14A); ours CSEs both into ECX.
- `0x003e9062-mk-wrapper.py.txt`: scratch recipe. It rewrites the TU `ScriptConditions_evaluateTeamStateIs.cpp` in memory (adds `/O1 /arch:SSE /G7` to the `// cl:` line, absolute include roots, the Parameter +0x20 cache field, OBJECT_STATUS_02, Object::getSpecialPowerModule/isDisabled, BitFlags::any) and appends a body file; run with `mk.py body.cpp out.cpp` then `explain_mismatch.py ... --rva 0x003E9062 --size 404 --source out.cpp`. The region flags must be added by hand: the unit's own `// cl:` line has no /O1.
- Inputs: master at c3580b3b4a, MSVC 13.10.3077.

## 0x004F9F39 auto-resolve record pass (470 B)
- `0x004f9f39-p1-select-body.cpp.txt`: body half of the bank with `TreeHintRef00217D4C *e = frontToBack ? &vec[k] : &vec[n - 1 - k]; unit = (Unit *)e->m_ptr;`. Size-exact 470 B and retail's two LEAs plus shared `mov edx,[ecx]`, but 3 regions / 16 memory / 5 register: the phase-2 webs swap (record cursor takes EDX, unit takes ESI; retail: cursor ESI, unit EDX).
- Ruled out with identical result: reference/if-else/inline-ternary/pointer-arith forms of the select; unit or e hoisted; compare/store through e->m_ptr; split continue tests; n-k-1; k++; unsigned n/k; count read after n; record cursor declared outside the loop; info read before count. Reading frontToBack from info inside the loop (469 B, 9 regions) and swapping the ternary arms (adds a region) are worse.
- Full headers/preludes are in `reverse/attempts/0x004f9f39.cpp`.
