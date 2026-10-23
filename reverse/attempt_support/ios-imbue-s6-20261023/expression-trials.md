# FINDINGS: basic_ios<wchar_t>::imbue @ 0x00016200 (238B) — conflicting narrow operator= suppression

Seat: s6 narrow isolated codegen research (scratch `build/wide-imbue-clean-s6/`, nothing
outside it written; no git operations, no census/link runners, no full builds).
All compiles are isolated scratch objects via `tools/build.py compiler_command(...)`
with the last argv swapped to the scratch source and `subprocess.run`; the shared
`build/match/` cache was never touched. Acceptance = strict `build.compile_function`
(bytes + relocations vs retail) **and** raw symbol extent exactly 238B (compile_function
truncates at the row extent, so a longer body could otherwise "match").

## Result

**Three byte-exact variants suppress the conflicting `basic_string<char>::operator=`
COMDAT while keeping the 238B imbue body, its relocations and its EH behavior identical
to the current production object.** Reproduced twice each (deterministic).

| variant | shape | result |
|---|---|---|
| v00 (production copy, baseline) | vendor body + explicit instantiation | EXACT 238B, but emits the conflicting 36B `??4?$basic_string@D...` COMDAT |
| v01 ref block + direct dispatch `__false_type()` | inner-scope `const string&` local | MISMATCH raw 245B, 101 diffs, first +0x83 |
| v02 ref block + vendor `assign(f,l)` | same | MISMATCH raw 245B, 101 diffs |
| v03 ref block + named `__false_type __tag;` | same | MISMATCH raw 245B, 101 diffs |
| v04 helper + direct dispatch `__false_type()` | const-ref argument helper | MISMATCH raw 238B, 12 diffs, first +0x8C |
| **v05 helper + vendor `assign(f,l)`** | + `#define protected public` | **EXACT 238B, operator= absent** |
| v06 function-scope `const string&` | lifetime extended | MISMATCH raw 240B, 102 diffs |
| v07 named `string __g` local | LEA selection | MISMATCH raw 240B, 102 diffs |
| **v08 helper + `reinterpret_cast` to `_String_base`** | no new define | **EXACT 238B, operator= absent — cleanest object** |
| **v09 helper + `const_cast<char*>(begin()/end())`** | owner-requested cleanup, no new define | **EXACT 238B, operator= absent; emits 2 extra external getter COMDATs** |

## The winning recipe (v08 text; v09 differs only in the helper's range expression)

1. Keep every production line verbatim (flags, malloc/CRT defines, forceinline
   allocator::deallocate specializations, `#define private public` on `<string>`,
   all existing decl-only suppressions). No asm, no pragma changes, no new aliases.
2. Replace the final explicit-instantiation line with an **explicit specialization**
   `template <> _STL::locale _STL::basic_ios<wchar_t, ...>::imbue(const _STL::locale &)`
   whose body is the **verbatim vendor `stl/_ios.c` logic**, with the single
   cached-grouping statement replaced by a call to a TU-local helper:
   `bfme_cached_grouping_assign(this->_M_cached_grouping, ((numpunct<char_type>*)_M_cached_numpunct)->grouping());`
3. The helper (namespace `_STL`, `static __forceinline`) carries the vendor
   copy-assignment shape — self-check plus pointer-range dispatch:
   - v05: `__dst.assign(__src._M_start, __src._M_finish);` (needs `#define protected public`
     added next to `#define private public`, `#undef protected` next to `#undef private`)
   - v08: range read as `reinterpret_cast<const _String_base<char, allocator<char> >&>(__src)._M_start/. _M_finish`
     (no new define; `_M_start/_M_finish` are public in `_String_base`, only the
     protected inheritance blocks the implicit conversion)
   - v09: range read as `const_cast<char *>(__src.begin()) / const_cast<char *>(__src.end())`
     (public accessors; const_cast restores the `char*` iterator type so the call
     still binds `_M_assign_dispatch<char*>` (PAD), not a PBD spelling)
4. Add a **declaration-only** explicit specialization of the narrow
   `basic_string<char>::operator=` (no definition) — matching the file's existing
   suppress-a-non-retail-copy pattern — so this TU cannot emit the conflicting COMDAT.

The helper's const-ref parameter binds the `grouping()` temporary exactly like the
vendor `operator=`'s `const _Self&` parameter did: the temporary keeps its
full-expression lifetime (destroyed right after the dispatch call, matching retail's
inline cleanup at 0x1629D..0x162B0) and the returned EAX (the temp's address) is
preserved through the self-check `cmp eax, ecx` and the argument loads.

## Evidence (v08 = v05 = v09 in all checks)

- `build.compile_function` on the live 0x16200 row: resolved bytes == retail target,
  zero unresolved, strict REL32 resolution to the pinned addresses
  (ios_base::imbue 0x1BD20, wide pubimbue 0x13660, ~locale 0x7150,
  locale::_M_get_facet 0x7190, numpunct<wchar_t>::grouping 0x15E50,
  `_M_assign_dispatch<char*>` 0x120F0, `_STL`-linkage free 0x30830; DIR32 facet ids).
- Raw symbol extent exactly 238B; capstone disassembly of the resolved bytes is
  instruction-identical to retail (`v*.disasm.txt`: "disassembly text identical").
- EH graph: `.text$x` (51B funclets), `.xdata$x` (52B unwind tables), `.rdata`,
  `.drectve` (205B linker directives) all **byte-identical to the production object**.
- Symbol delta vs production (multiset over all defined code-symbol bodies):
  the only change is the 36B `??4?$basic_string@D...operator=` COMDAT removed and a
  dead 24B `?bfme_cached_grouping_assign@_STL@@YAX...` body added — internal
  (`static`), unreferenced after inlining, no external name conflict.
  Everything else (dispatch 96B, grouping, pubimbue, dtors, string helpers) is
  byte-identical, so the link state for every other symbol is unchanged from today.
- v09 only: additionally emits two new trivial external COMDATs — 3B
  `?begin@...QBEPBDXZ` (`mov eax,[ecx]; ret`) and 4B `?end@...QBEPBDXZ` — because
  naming them odr-uses them even though both uses are inlined (same MSVC behavior
  that emitted `operator=` in v00). They are fold-eligible but are new external
  emissions; the owner's link preview should confirm they are harmless (or pick
  v08, which has no new external symbols).
- `$L` label renumbering, `.debug$S` (helper name string) and 3 `.sxdata` index
  bytes differ — per-object cosmetics, no link effect.

## Why the losing shapes lose (documented in `v*.disasm.txt` first-difference windows)

- Reference **local** (v01-v03, v06): MSVC materializes the temporary's address with
  `lea edx,[esp+0x10]` and compares against it (`cmp edx, ecx`) instead of preserving
  grouping()'s returned EAX (`cmp eax, ecx`) — the owner's EAX/LEA prediction
  confirmed; +7B and ~101 diffs. Function-scope binding (v06) additionally moves the
  temp's destructor past the return copy.
- Named string **local** (v07): LEA selection plus changed stack homes, 102 diffs.
- Direct `_M_assign_dispatch(__g._M_start, __g._M_finish, __false_type())` inside the
  helper (v04): MSVC pushes the tag address *before* loading `_M_finish`/`_M_start`,
  retail loads members first — 12 diffs. The vendor `assign(first, last)` member
  template layer (its `_Integral()` value-init) reproduces retail's exact scheduling
  (member loads, then `lea esi,[esp+0x30]`/pushes tag,l,f) — and in this TU the
  empty-tag value-init store is eliminated exactly as retail does (the 41B row owner
  compiles its store in a different TU context; see below).
- The parent's own scratch trial (annotating the primary-template `operator=` with
  `__declspec(dllimport) __forceinline` in a scratch `_string.h`) also failed with
  the +5B tag-zero store — consistent with the failed-trial history; declaration
  placement/annotation alone cannot solve it. The explicit-body expansion does.

## Why the emitted operator= conflicted (v00 evidence, `v00_production_copy.operator=.txt`)

The production TU instantiates the vendor `operator=` chain: retail's inline expansion
and the emitted standalone copy are the same 36B shape (no tag store in this TU's
context: `mov eax,[esp+4]; push esi; mov esi,ecx; cmp eax,esi; je; mov edx,[eax+4];
mov eax,[eax]; lea ecx,[esp+8]; push ecx; push edx; push eax; mov ecx,esi; call dispatch;
mov eax,esi; pop esi; ret 4`). The row owner at 0x120C0
(`stlport_narrow_string_assign_copy.cpp`) compiles a 41B body whose extra 5 bytes are
the value-init tag store (`mov byte ptr [esp+0x14],0`). Two different bodies under one
name: the link loses the retail 41B copy when the imbue TU's wins. Removing the odr-use
removes the conflict; the hand expansion inside the specialization reproduces the
inlined bytes exactly.

## Landing notes for the owner (production file adaptation, not done here)

- The adaptation is: (1) replace the final explicit instantiation with the explicit
  specialization carrying the verbatim vendor body + helper call, (2) add the
  declaration-only narrow `operator=` suppression, (3) add the TU-local static
  `__forceinline` helper (v08/v09 forms need no new define; v05 form adds
  `#define protected public` scoped like the existing `#define private public`).
- `tools/find_declared_unmatched.py`'s definition regex matches `Qualified::name(`
  shapes; a namespace-scope static free function is not in its candidate set, so the
  helper should not need a `present-unmatched`/`absent-from-retail` marker — verify at
  staging (its run on the scratch path only reported the zero-rows condition, which is
  a scratch-path artifact: the row's `source` field points at the production path).
- The emitted 24B helper body is dead internal code (it calls `_M_assign_dispatch`
  through a reloc); no external symbol is introduced in v05/v08. v09's getter COMDATs
  are external — check them in the current-provider link preview.
- A 4-byte local the compiler zeroes at entry and sets to 1 just before `~locale(__tmp)`
  ([esp+0xc] in the retail body) follows the vendor body verbatim and is byte-stable in
  every exact variant; it was not separately identified and needs no action.

## Reproduction

```
cd ~/decomp/s6
build/verifier-venv/bin/python build/wide-imbue-clean-s6/run.py \
    build/wide-imbue-clean-s6/v08_helper_reinterpret_base.cpp \
    build/wide-imbue-clean-s6/v09_helper_public_begin_end.cpp
# -> EXACT MATCH raw=238B extent_ok=True ... watch={'operator=': False, ...}
```

Per-variant artifacts: `v*.disasm.txt` (retail + resolved disassembly, first-difference
window, relocs, defined code symbols, raw hex), `v00_production_copy.operator=.txt`
(36B emitted operator= vs 41B retail), `disasm_target_16200.txt` / `_funclets.txt` /
`_narrow_twin.txt`, `results.txt` (all runs), generators `mkvariants.py`, `mk_v08.py`,
`mk_v09.py`, driver `run.py` (streams `reverse/functions.csv`; never
`build.compile_source`).
