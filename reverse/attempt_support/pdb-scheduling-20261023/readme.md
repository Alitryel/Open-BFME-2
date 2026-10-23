# Whole PDB member: allocation lifetime and parameter views

The stronger three-body bank remains ../pdb-numbering-20261021/candidate.cpp.txt,
SHA256 254d999e9f7cc22e22d8d3667ba4931bd0794b9be989ad465d0b35be5e40c9e8.
Native boundaries, CodeView/ABI facts and earlier exclusions remain in
../0x0075b177-pdb-source-lookup/, ../pdb-lookup-visibility-20261019/ and
../pdb-local-order-20261021/. No implementation source was read.

Host checkout: 6b48d28f03 plus evidence-only commit. Host BFME1 verified pin
42bba2dd remained unchanged. Experiments used the fixed native-disk VM archive
BFME2 5314e1e7f6 (production code a649b275f7), BFME1 37c3022d, pinned MSVC
13.10.3077 through Wine 8. They are isolated experiments, not verification of
newer host inputs. Baseline reproduces the complete 847-byte caller with the
known four differences at +17,+18,+1A,+1B and no unresolved relocations.

47 completed controls, all non-exact:

- Four initial baseline/parameter-identifier contexts: unchanged 847B/four
  differences. The first context run stopped after four completed results
  because Wine stalled; uncompleted variants are not counted. The full replay
  driver includes other identifier controls that were not run.
- Eighteen genuine inlined output-reset helpers also carry the allocation
  result, varying argument order and compiler-barrier placement. All 848B.
  The result is zeroed before alloca and held in ESI, changing the prologue.
- Four controls move result initialization into that same helper. All restore
  847B; the three barrier controls have 15 prefix differences, while the
  no-barrier control is back to the original four differences.
- Eight signature-preserving volatile lvalue views of existing parameter
  objects, capturing their values once into ordinary locals: 843/844/847B.
  Register allocation and frame homes change; no improvement.
- Six direct/self-assignment lvalue views without aliases: 843..848B, no
  improvement. The supplied prefix listings distinguish changed load order
  from changed register roles and frame slots.
- Seven established non-null-precondition/type-scope controls: all original
  847B/four differences. Preconditions only concern outputs the original
  function unconditionally dereferences.

No Code, ledger, ABI, pin or verifier change was made. The native archive
member and stronger bank remain. Exact private helpers were not published
without their caller. New work needs a supported way to order the two
independent argument loads while preserving original frame/coloring.

Replay: copy all six .py.txt drivers to build/ without the .txt suffix, and
copy the stronger candidate to build/pdb-context-input.cpp.txt. The dependent
drivers transform the corresponding base driver. Use a private Wine prefix
and capture Wine-service output to regular files; shared-prefix/output-pipe
stalls interrupted the first context run. results.json contains completed
controls with full extents and concise difference locations.
