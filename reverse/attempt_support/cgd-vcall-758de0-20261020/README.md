# 0x00758DE0: virtual-call lowering follow-up

No byte-exact recovery or stronger bank was found. Keep
`reverse/attempts/0x00758de0.cpp` unchanged. This packet adds negative evidence;
it does not establish a compiler defect or prove that clean C++ cannot match.

## Reproduction and inputs

- Revision: `3c502511f6fafd2b479fcc4a2a8f802979fa8d1e`.
- BFME 1 pointer: `68c5ce2789e974f36b6c742d57437d157bc159e9`; checkout equals the committed pointer.
- Bank SHA256: `35c52a48f5de013aaf49c97758aaa8806c38918b28458bffc3f0b85e9e4a3259`. `baseline.cpp.txt` preserves the source text with LF line endings; its separate checksum is in observations.json.
- Native: 0x00758DE0..0x00758F2D, 333 bytes including the final RET; three INT3
  bytes follow. The ordinary align_diff boundary search runs into the next
  function, so diagnostics fix the independently established extent at 333.
- Ordinary compile: 333 bytes, 114 instructions, zero relocations, 41 positional
  byte differences, 10 aligned structural regions / 10 memory operands / 1
  register operand. The older 0.9069 bank score is an aligned-byte measure,
  not the positional measure. No function-body improvement is claimed.
- `BfmeThingCGD` is the inherited bank spelling. The production owner is the
  existing `CollisionManagerImpl`, already pinned at this RVA. Renaming the
  prototype and integrating it with the actual sibling views in
  `Code/GameEngine/Source/Common/Rva00758D10Finish.cpp` leaves the same mismatch.

## Findings worth keeping

1. **Link-time code generation did not explain this residue.** Both tested LTCG
   models emitted exactly the ordinary compiler's same 333 bytes, including
   all 41 wrong positional bytes. `observations.json` records hashes. The
   stock RTM toolchain lacks msobj71.dll and first fails with C1350/LNK1257.
   The isolated tests therefore explicitly use (a) RTM front/back ends with
   the existing pinned SP1 object/runtime DLLs and (b) the pinned SP1 compiler
   set. Both use the existing RTM link.exe copied into their private folder.
   These are named experimental mixtures, not an assertion about retail's
   original linker/compiler configuration or an official new build profile.
2. **One-word class and scalar return values have different ABIs here.** POD
   struct/union result models produce 357 bytes and extra return/copy work;
   scalar integer, function-pointer and member-pointer words leave the
   ordinary 333-byte mismatch. A four-byte size alone does not justify
   substituting a class-valued callback result.
3. **The callback-table alternative is not a hidden solution.** Free-function
   __thiscall pointer declarations are rejected by this compiler (C4234).
   One-word member-function-pointer dispatch was checked explicitly and
   compiles, but all seven prepare/test/respond combinations are worse.
4. **The real sibling-unit context is inert.** Appending or prepending the
   function to the real sibling's reconciled class/node views, preserving
   every measured member offset, still gives 333 bytes and the same residue.
5. **Declaration order is inert for these virtual calls.** Six permutations
   of the three real overrides, each pure and non-pure, preserve all inherited
   slots and produce the same mismatch. The direct-call ordering recipe in
   docs/recipes.md did not transfer to this case.

Other measured families in observations.json: pointer/reference argument
carriers, scalar and primitive-array argument types, implicit vector-to-array
conversions, deferred preparation, scoped argument locals, inline whole-contact
helpers, typed reference fields, ordinary const/register/interface/destructor
forms, negation/copy-elision forms, nothrow declarations, and additional
compiler context settings. None beat the existing bank. Four early malformed
non-pure-declaration trials accidentally removed index initialization; they
are excluded from the observations and conclusions. The corrected non-pure
trial is byte-identical to the baseline.

## Remaining question

Retail and the independently re-read WB twin 0x01803740 both push the normal
argument before the inner vtable load in the first test, and load the first
response's inner vtable after both arguments. The bank instead hoists those
loads and chooses different scratch registers. The reverse response's result
push / receiver reload order also differs. The iterator, branch destinations,
normal-copy/negation and total extent already match.

The next useful evidence is the actual callback declarations/source expression
or a minimal independently understood virtual-call lowering rule reproducing
those local dependencies. This packet does not identify a missing callee or
justify a blocker-on RVA. Repeating the listed flag/type/context families
without new evidence has no demonstrated benefit.

## Re-run the LTCG check

From the repository root:

```text
python3 reverse/attempt_support/cgd-vcall-758de0-20261020/reproduce_ltcg.py
```

On this Windows machine use the installed Python interpreter, as local
instructions require. The script uses existing toolchain files only, writes
private objects/DLLs under build/cgd758de0-ltcg-repro, and does not change the
normal compiler profile, object receipts, tools or source. No decoder source
was read. Active investigation including the packet: t=44 minutes, model=gpt-6.
