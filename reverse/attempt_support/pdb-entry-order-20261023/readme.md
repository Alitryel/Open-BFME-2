# _RTC_GetSrcLine 0x0075B177: entry statement order (2026-10-23)

Base: ../pdb-numbering-20261021/candidate.cpp.txt, through ordinary
tools/explain_mismatch.py with its original flags. Model claude-opus-5-5.

New fact: the commuted EBX/ESI parameter loads at +17..+1B follow the source
position of `*moduleName=0` relative to `source[0]=0`.

- `*pline=0;*moduleName=0;source[0]=0;` (p021) and
  `*pline=0;*moduleName=0;source[0]=0;res=0;` (a1320) give retail's prefix
  through +0x25 (ebx=[ebp+18] before esi=[ebp+8]). The rest differs only in
  the order of the three entry stores: ours stores *moduleName before
  source[0]; retail stores pline, source, res, moduleName.
- The other 46 orders of {res, pline, source, moduleName} (alloca first or
  last) keep the original four commuted bytes or regress.
- An 8x3 sweep with _alloca between the entry stores regresses the frame
  (848B, register saves).
- `*moduleName=(source[0]=0,(char *)0)` and similar comma/chain forms: the
  RHS is evaluated first, so the original four bytes come back.
- `address-=info->BaseAddress` in place of imageAddr: 843B.

The byte store through `char *source` may alias `*moduleName`, so cl cannot
swap those two stores. Retail's IR therefore stores source before moduleName,
yet it schedules the moduleName load first. Plain statement order cannot give
that combination. Something still unknown raises the priority of moduleName's
load (a read of moduleName, or a construct the bank does not model).

## Resolution (same day): declaration scope from native CodeView

Native pdblkup.obj (msvcrt.lib member ..\build\intel\dll_obj\pdblkup.obj)
carries CodeView for _RTC_GetSrcLine. Its S_BPREL32 records (retail-codeview.txt,
dumped with cvdump.py.txt/cvrecs.py.txt) place `sectionIndexRes` and the local
static `PDBOK` in the function's top scope, between offsetRes and fo; the COFF
symbols also show labels $DONE0..$DONE4. The bank declared both in a nested
block. Declaring them at function scope (no statement moved) makes all three
member bodies exact: _RTC_GetSrcLine 847B, GetImageInfo 849B, GetPdbDll 312B.
The static keeps its native name ?PDBOK@?3??_RTC_GetSrcLine@@YAHKPADHPAHPAPAD@Z@4HA.
Found by a probe seat (model claude-opus-5-5) comparing /Z7 output with the
retail records. Lesson: when byte-level variants are exhausted on a .lib member,
its CodeView recovers the original declaration scopes.
