# Whole PDB member: numbering and genuine output reset controls

Native member pdblkup.obj has GetImageInfo at 0x75ACEE/849B, GetPdbDll at
0x75B03F/312B and _RTC_GetSrcLine at 0x75B177/847B. The prior CodeView,
identity, layout, ABI and boundary evidence remains in
../0x0075b177-pdb-source-lookup/ and ../pdb-lookup-visibility-20261019/.
No implementation source was read. Public SDK declarations alone are included.

The complete prior C++ bank was recovered from commit e505916b49f because
7375072eaf8 removed it as already matched: the current three owners are still
prebuilt msvcrt.lib rows, not clean C++. candidate.cpp.txt preserves that
stronger whole-member reconstruction without creating a stale attempts row.
Do not publish its unused private helpers while the original caller/member
must remain. This is evidence, not recovered C++ coverage.

New tests, all through ordinary tools/explain_mismatch.py with original
O1/G6/Oi/Ob1/MD/GX-/GS- flags and actual SDK include directory:

- 129 entry initialized-local counts k=0..128, per the new recipe.
- 24 permutations of a real four-output initializer resetting res, pline,
  source and moduleName; every argument is used, with no dummy calls.
- Six orders of a three-output initializer returning the actual zero result.

All 159 bodies are 847 bytes with every relocation resolved. None fixes the
four native parameter-load differences +17/+18/+1A/+1B. The original bank and
local-count family have only those differences; some output-reset controls
also differ at +2A..+2D. No improved candidate, Code edit, pin, ABI substitution
or verifier change resulted. results.json aggregates the strict patched-byte
comparisons. The two .py.txt replay scripts use the retained candidate and
write only isolated build/ sources and diagnostic output. The complete member
remains blocked on a new supported code-generation explanation for the two
commuted loads. Private-helper exactness is not a replacement of the member.
