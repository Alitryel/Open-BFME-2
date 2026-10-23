# Subtitle field parser: source context and stack lifetime

Target `0x00688B10..0x0068913A`, 1,578 bytes. The complete source lead is
BFME1 `game/GameEngine/Source/GameClient/Rva0081DE40ParseSubTitleEntry.cpp`
at the committed reference `a18d9ed50607e9175de4d6568798d7d73119de09`.
Its function is a semantic source lead, not proof of the original target name.
The complete current `SubtitleManagerAccessors.cpp` and saved bank
`reverse/attempts/0x00688b10.cpp` were read and retained unchanged.

The existing target evidence still requires UnicodeString text: normal cleanup
calls wide releaseBuffer `0x00036E70`. The old narrow-string 1,578-byte bank
must not be restored just because its length agreed. The current shared-class
UnicodeString bank reproduces at 1,588 bytes, all direct calls resolved, first
positional mismatch `+0x46`.

## New hypotheses and results

- Separating the manager constructor/addSubtitle definitions from the parser
  tests real callee visibility rather than source ordering. Separating either
  context and using the donor's typed fetch-callback view still gives 1,588 B.
- The native third argument is tested for null, then its dead local slot holds
  the text object. An explicit placement lifetime with a genuine scoped
  UnicodeString destructor was tested without modifying caller memory. This
  increases the frame from `0x34` to `0x3C` and emits 1,589 B; rejected.
- Explicit local comparator values, both in the loop and the containing scope,
  do not restore native EBX comparator / EBP-zero allocation.
- Authenticated SP1 and DDK4035 compilers, EHs, both legacy for-scope settings,
  alias optimization options and Ob2 leave the bank at 1,588 B. Og-minus makes
  it worse (2,204 B). These options were scratch diagnostics only; none was
  selected for production.
- Moving text construction through the six other positions among the POD
  defaults, and copy/value initialization of the same canonical UnicodeString,
  also leave 1,588 B. No declaration-order variant improves the native homes.

`results.json` contains the successful official mismatch runs. The generators
are preserved beside this document; they start from the existing bank and
write private scratch sources. The placement trial is diagnostic only and is
not proposed as a source recovery. No naked body, inline assembly, private
UnicodeString declaration, extra pin or shared-header change was introduced.

The differing-instruction-line counts are diagnostic output, **not** similarity
scores or verified-byte percentages. With different instruction lengths, the
mismatch tool applies target relocation slots at positional offsets, so later
patched disassembly can be misleading; inspect the raw COFF bytes/relocations
before deriving a new target fact from such a line. Only a complete ordinary
byte gate, plus literal/identity/EH checks, can admit this body.

## Exact remaining difference and next prerequisite

Native prologue first stores the manager at `[esp+0x24]`, tests the incoming
third argument, then zeroes text in that argument's slot (`[esp+0x5C]` after
the additional EDI push). The bank stores manager at `+0x28`, keeps text at
`+0x10`, and later writes zero to the argument slot for another value. Native
keeps EBP as zero and EBX as the imported comparator; the bank retains manager
in EBX and uses EBP for the comparator. This shifts downstream homes and code.

INI::getFilename's real current definition in INILineAccessors.cpp was also
read: it forwards through the file table at `+0x838` using index `+0x10`.
Do not replace it with the BFME1 donor's inline `m_filename +4` access.
The canonical eight-byte INIException declaration and real formatter source
were checked; this investigation did not change their ABI or claim new EH or
literal verification.

Further work needs a supported explanation for stack packing/zero-versus-
comparator allocation. The tested provider visibility, comparator locals,
compiler options and declaration-order families are ruled out. No production
source or ledger row landed, and the existing better bank is preserved.

## 2026-10-19 follow-up (claude-opus-5-5): the allocation is a G6 LICM decision

Native vs the current bank (default `-O2`, explicit `/G6` identical):
native keeps the `_stricmp` IAT load **per iteration** at the token loop head
(`688BB4 mov ebx,[0xBBA518]`, loop back edge `jne 688BB4`), so EBX is free for
the color loop counter, EBP holds `color` (it is the prologue's zero register),
the manager is split (EBX outside the loop, `[esp+0x24]` inside) and `text`
packs into the dead arg3 slot. The bank hoists the IAT load to the preheader
(`mov ebp,[imp]` before an aligned head), keeps manager in EBX inside the loop
and spills `color` into the arg3 slot; `text` then needs its own frame slot.
The missing native loop alignment is a consequence (native heads need 12/13
pad bytes), not a separate lever.

`/G7` alone reproduces the whole native global allocation (prologue exact to
+0x58, text at `[esp+0x5C]`, `call ebx`, color in EBP, no padding, 1,581 B),
but it is not the retail setting: it emits `add/sub reg,1` where native has
`inc/dec`, other scratch registers and a different throw-block order. So the
retail body is G6 code whose optimizer did not hoist the import load. Tried
under G6 without change (all 1,588 B, first diff +0x46): `int` color, color
declared first/last in the block, `color <<= 8; color |= value`, `!color`,
`for(;;)`+break, `while ((token = ...) != 0)`, while with tail fetch, color
`do/while`. Moving color (or all PODs) to function scope, or testing `store`
instead of the `target` copy, regresses to +0x17. /O1, /Os, /G5, /GB, /Ox and
explicit /Og /Oi /Ot /Oy /Ob1 /Gs /GF /Gy also give no change or worse.
Next lever to look for: a source shape that stops G6 loop-invariant hoisting of
the IAT load (e.g. the comparisons reached through an inline helper or a
different loop/EH structure), not further declaration-order trials.
## Resolution (2026-10-20, claude-opus-5-5)

Landed exact in `Code/GameEngine/Source/GameClient/SubtitleManagerAccessors.cpp`.
The register-home residue was not frame or declaration order: reading the
separators through INI's inline getters (`getSeps()` +0x418,
`getSepsColon()` +0x420, as the donor and `INISeparatorGetters.cpp` do) instead
of the raw members fixed EBX/EBP homes, the manager slot, the loop alignment
and the scratch-register rotation in one step. The comparator import is
`_strcmpi` (msvcr71), not `_stricmp`. Diagnostic: /G7 alone had moved the homes
(62 regions) but emits add/sub for retail's inc/dec, so it was a regalloc-weight
tell, not retail's flag.
