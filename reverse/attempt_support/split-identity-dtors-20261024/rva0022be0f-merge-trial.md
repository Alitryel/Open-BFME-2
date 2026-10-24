# Rva003ED1FC -> Rva0022BE0FSubsystem merge trial (2026-10-24, claude-opus-5-5)

Base: master 177a667419, census index 2026-10-24 16:05 (7e43384268).

Identity (target evidence, both names placeholders): ctor 0x003ED340
(??0Rva0022BE0FSubsystem) stores vtable 0x00C36100; slot 0 = 0x003ED249
(??_GRva003ED1FC), which calls dtor 0x003ED1FC (??1Rva003ED1FC, REL32 at
0x003ED24C; pin in symbols.csv). data_ledger.csv already lists both
??_7Rva0022BE0FSubsystem and ??_7Rva003ED1FC at 0x00836100.

Prerequisite from the 83486 log row is gone: 0x003ED1BE now has its own row
(??1Rva003ED1BEMap, Rva000427195Dtor.cpp).

Trial (`rva0022be0f-merge-trial.patch`): rename the class token in
functions.csv (??1, __ehhandler$??1, two funclet parent=, ??_G), the
symbols.csv pin, Rva003ED1FCDtor.cpp and OpaqueScalarDeletingDtorsB07Deferred.cpp.

- ./build.sh (3 units): Functions OK 10/10. The two funclets verify past a
  renumbered label ($L5627/$L5628 -> $L6227/$L6228): a landing should update
  their object-symbol= notes too.
- link_check --refresh: Rva0022BE0FSubsystemCtor.cpp 0 -> 65 B LINKS;
  Rva003ED1FCDtor.cpp 92 B and OpaqueScalarDeletingDtorsB07Deferred.cpp 83 B
  keep linking (before: ctor unit unresolved ??1Rva0022BE0FSubsystem@@UAE@XZ).

Not landed: no prescribed path admits it.
- `rename.py class --name Rva003ED1FC --new Rva0022BE0FSubsystem` refuses:
  "new name Rva0022BE0FSubsystem is itself a placeholder or weak name".
- `add_match.py --replace-rva` takes over scaffold rows only (add_match.py
  replacement_scaffold); ??1Rva003ED1FC is a real claim.
- docs/naming.md "Renaming by hand" admits only placeholder -> canonical-grade
  names; the target here is itself a placeholder.
- 66af82a6f5's /alternatename route needs a hatch_baseline.tsv entry
  (Verifier-Change), which this seat may not edit.

Needs: a maintainer decision or a rename.py identity-merge mode (see readme.md).
Applying this patch plus the $L notes and deleted_rows.csv tombstones is the
whole change.
