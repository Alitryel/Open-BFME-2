# Script destructor loop-shape sweep (seat5, 2026-10-19)

Target: `0x003B35B1..0x003B3662`, 177 bytes, `??1Script@@MAE@XZ`
(bank symbol `??1Rva003B35B1@@UAE@XZ`). Flags `/O1 /MD /EHsc`, RTM.
Harness: bank header in an ignored `build/` copy, one body per variant,
`tools/explain_mismatch.py '??1Rva003B35B1@@UAE@XZ' --rva 0x003B35B1 --size 177`.

## Target evidence (new)

WorldBuilder debug twin `0xAA79E0` (334 B, `tools/wb_show.py 0x003B35B1 --gd`):
- release of `+0x30` through two temporaries and the `?:` result slot, then
  `operator delete` (0x2FD60): the debug lowering of `::delete p` with a
  virtual destructor;
- `for (i = 0; i < 2; i++)` with `i` in `[ebp-0x10]`, the first local slot
  below the EH registration, so `i` is likely the first local declared in the
  function (C-style `Int i;` at the top), and `::delete m_34[i]`
  (`[this + i*4 + 0x34]`) in the body;
- string releases `+0x44, +0x1C, +0x0C, +0x08, +0x04` through releaseBuffer.

So the semantic source is the plain index loop. It is not the source shape that
reproduces retail's register allocation in our TU, though; see below.

## Results (each 177-byte family leaves 10 differing bytes)

- (a) pointer declared and initialised before the `+0x30` release, then
  `{ ::delete *pp; ++pp; }` (for, while(n--), or do/while): the loop is
  byte-exact to retail (memory counter `[ebp-0x10]`, `test ecx,ecx`, unmerged
  `push 0`/`xor eax,eax`, late `add edi,4`). The only defect is
  `lea edi,[esi+0x34]`, which cl hoists into the first release block (before its
  `je`) where retail has it after that block's `pop ecx`. This is the new bank
  (`::delete` through a real virtual dtor, no `v0(0)` model).
- (b) pointer declared after the release and read as `*pp++` (the older bank):
  `lea` is in place but `add edi,4` is hoisted before the null test.

Everything else emits 166 bytes: `push 2 / pop ebx` counter, plus
`xor eax,eax; cmp ecx,eax` zero merging in both releases. This covers:
index loops (`m_34[i]`, `this->m_34[i]`, `*(m_34+i)`), with ++i/i++, `<`, `!=`,
`<=`, countdown, unsigned/short/char/long counters, counter declared at the top
(as in the WB twin), in the loop, or initialised at the top; braces around the
body, the first release, or the loop; `++pp` as a separate statement, `pp += 1`,
`pp = pp + 1`, a `cur` copy; a reference-to-array alias; an inline accessor or
reference accessor; `__forceinline` member helpers for the loop or for both
releases; an inline by-value release helper (154 B); a `self = this` copy; a
`base` alias defined early; `pp = 0` or `pp = m_34` before the release and
reassigned after it (cl drops the dead store); `pp = &m_30` covering both
releases (168 B); a pointer-range loop (168 B); an inline element destructor.
Flags: /O2 (200 B), /Oy-, /Og /Os /Oy /Ob1 /Gs /GF /Gy, /G5, /G6, /G7,
/arch:SSE, /GS, /GX, /EHs, /Oa, /Ow, /Op, /Oi-, /GR, /Zi, /Ob0, /Ob2, /Ox /Os
give the same split, as do /Oy-, /GF /Gy, /Gr and /Ob1 /GS- on the index form.
Distinct element classes (OrCondition / ScriptAction deriving from a
MemoryPoolObject with a protected virtual dtor and class operator delete) do not
change the index form either (166 B).
The real `ScriptDtor.cpp` context (real AsciiString and Snapshot headers) with
`__declspec(novtable)` removed shows the same split: the WB-shaped index loop
with `int i;` at the top emits 166 B, and form (a) emits 177 B with the same
10-byte `lea` defect. (With novtable kept, the entry vtable store is missing.)

## Open hypothesis

Retail has the def-after-release `lea` together with the allocation that our
compiles get only when the pointer is live across the first call (a) or
post-incremented in the operand (b). The real string and Snapshot headers do not change this, so
the remaining candidates are the unit's other code (cl allocates per function,
but /O1 COMDAT and inlining state differ per TU), or a compiler
build outside the three supported profiles. Do not try more loop spellings.
