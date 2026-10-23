# AptMpGameSetup 0x004404AC: allocator costs and independent source families

The bank remains the best candidate: 526 bytes, 183 instructions, zero
structural differences, seven memory and 24 register operand differences.
Every difference disappears under a mechanical ESI/EDI operand exchange.
Retail holds `this` in ESI and `slot` in EDI; the bank exchanges them. No
candidate in this session matches. No game source, ledger row, pin, verifier
or baseline was changed. The bank's score remains 0.9, without an inflated
claim of improvement. There were 11,177 generated variants: 11,165 compiled,
and twelve const-index forms produced the expected assignment error.

Inputs: BFME2 `4ea11ce18b23a518886b134ffbe1dd9afb98dc08`; verified BFME1
pointer `37c3022de1ab944c7ffe536440d637dc8199091c`; repository MSVC
13.10.3077 under Wine. The standalone bank carries its original home
`Code/GameEngine/Source/GameClient/GUI/Rva0043F483PopulatePlayerCombo.cpp`
at `0d2e55ad1c`, `/O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
/D_STLP_USE_STATIC_LIB`, with STLport. Source/body hashes and compact search
counts are in `results.json`.

Identity and layout are inherited from the bank and the earlier target
investigation: native range 0x004404AC..0x004406BA, ECX receiver, bool/int
arguments, slot clamp, observer and map flags, widget arrays, rules at
+0x15C/+0x160, GameInfo virtual calls +0x30/+0x34 and preview receiver +0x60.
No new donor identity, original qualifier or source spelling is asserted.
The neutral method name is retained. Native and WorldBuilder evidence, not
byte placement alone, support that interpretation.

## Exclusions reviewed before editing

Read the pick-hard history and the 20261019, 20261020 and 20261021 handoffs.
They already exclude the common control-flow/loop forms, scopes and local
names, inline rule/validity/map accessors, getter/copy-ctor visibility, an
empty visible destructor, broad compiler-profile changes, declaration-count
scans and the existing permuter family. An early slot copy gives the retail
roles but hoists the save/load before the game-null check. An early preview
address gives the roles but adds two bytes. Neither is an admissible match.
No inert declaration scan or permuter was repeated here.

The new starting hypothesis came from the exact 0x7586F0 recovery: qualifying
an existing access can change C2's costs without introducing another load.
The recent FoundationAIUpdate recipe suggested testing flag reads as well.

## New measurements and exclusions

- **Types and layout:** a 128-way existing-field read-qualification family;
  a 256-way rules-owner/reference/copy/getRule family; and a 256-way local
  index aggregate/signedness, observer type and enable-copy factorial.
  None improves the bank. Value-copy rule views and some type conversions
  change the actual code, so they are diagnostic trials only.
- **Callee visibility and exceptions:** all 4,096 combinations of twelve
  existing direct callee `throw()` declarations, plus sixteen combinations
  for the two receiver methods and the two virtual calls. The first family
  has only two emitted bodies: 2,048 baseline twins and 2,048 incorrect
  517-byte bodies after removal of required EH work. The sixteen additional
  variants are baseline twins. No callee is missing.
- **Inline source context:** all 729 combinations of direct, one-level and
  two-level inline getters at six existing field access sites emit the
  baseline byte sequence.
- **Control flow:** 1,024 consumed preview-address preparation variants and
  64 preview-call duplication variants; 64 conditional slot initialization
  variants. None closes the body. Compare complete bodies: row-sized
  truncation would hide trailing instructions or manufacture a missing-ret
  region in longer trials.
- **Variable lifetime:** 128 slot-copy placement/type/load variants, followed
  by 256 receiver alias kind/placement/use variants. The lower positional
  byte counts in some early-slot-copy trials are misleading: they relocate
  the save/load and restoration around the null branch. The structural
  mismatch remains. Twelve intentionally explored const-index forms do not
  compile because the clamp assigns to them; they are compiler errors, not
  gate false rejects or candidate blockers.
- **Individual reads:** all 64 combinations of volatile parameter/local
  declarations, followed by all 4,096 subsets of the six enable and six
  observer reads. Aggregate enable volatility adds `xor eax,eax; mov al,...`
  at the player-template call where retail directly pushes the argument.
  Neither declaration-wide nor individual read qualification closes the
  body. No artificial memory access was introduced into the bank.
- **Compiler settings:** retained the bank's recorded, previously tested
  home/profile. Prior profile tests remain exclusions; this session did not
  spend another sweep on them.

## Read-only allocator evidence

At C2 candidate-list insertion, return site `0x1078474f`, baseline `this`
(backend symbol 1, candidate 7) has priority 41 and reference count 12;
`slot` (symbol 2, candidate 16) has priority 49 and reference count 14.
Whole-parameter `volatile bool enable` changes the priorities to 40 and 50,
with the same receiver/index reference counts. Qualifying the five enable
condition reads but leaving its direct argument push ordinary (`read-0055`)
also gives 40 and 50. Thus these qualifiers move the cost gap the wrong way.
`allocator.json` preserves the initial insertion records for those three
unmodified-compiler runs. No debugger edits or modified-compiler objects
were used in this session.

The body is still a register allocation problem, with no unresolved call or
known missing-function prerequisite. Preserve the bank rather than a trial
which adds operations. A concrete next angle is to trace the individual
block contributions at C2+0x82897/0x82919 and compare the faithful bank with
the early-slot-copy control. The FoundationAIUpdate investigation mapped
these sites to candidate/block factors. This session traced the sorted-list
inputs only; it did not yet map which block contributes the receiver/index
gap. Use that distinction to choose the next source family instead of
repeating these thousands of equivalent spellings.

## Checks and reproduction

`check_csv.py` passed before and after work. BFME1 was already at the committed
verified pointer (successful freshness check 17:18 UTC); another seat held
the live update lock, so this seat did not start an update. The published
link index was fetched. `find_declared_unmatched.py` accepts the unchanged
home. All resolved baseline calls have established rows/pins; no admission
or successful full byte gate is claimed for this nonmatching body.

The final upstream rebase advanced the committed, upstream-verified BFME1
pointer to `42bba2ddbd5cb895d99293583891d3b7315fa49e`. A fresh isolated bank
compile under those inputs still gives exactly the same 526-byte candidate
and 31 operand differences. The family results above use the earlier input
revision. The existing collision recovery's ordinary byte gate also passes
2/2 bodies after that rebase, and the final ledger check passes 98,065 rows.

The isolated trial compiler uses `build.compiler_command`, never
`build.compile_source`, with objects under ignored `build/hard-4404ac/`.
Scoring resolves relocations, compares the complete COFF body extent and
then aligns mnemonics and operands. `residue.txt` shows the faithful bank's
remaining differences. Reproduction scripts are stored as `.py.txt`:
copy them into that build directory, remove `.txt`, and adjust ROOT/OUT if
needed. Start with empty scratch, or discard its objects when source,
headers, reference revision, flags or toolchain change: the scratch reuse
shortcut only checks source text and is valid within a fixed-input run.
`trace.py` uses the read-only `Dbg` helper from
`reverse/attempt_support/a9f98-c2keys-20261022/wdbg.py.txt`; put that helper
beside the copied script. No thousands of scratch objects need preserving.

Model: gpt-6.1-sol. Session duration and final checks are recorded in the
attempt log and runner metadata. The claim is released for continuation of
this same standing assignment; no other body was selected.
