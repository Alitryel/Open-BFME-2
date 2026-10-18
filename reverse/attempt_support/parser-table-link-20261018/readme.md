# Parser table and declaration linking repair, 2026-10-18

The same 14 current units measure 393 -> 854 legacy linked bytes (+461):
ParseForceBattle +133, ParseEyeTowerPointData +133, parseAnim2DDefinition +114,
and the address-named transition parser at 35DBA2 +81. Existing provider bytes
are excluded from the gain. The original inputs were restored for the combined
before measurement, then the final inputs restored and verified for after.

## Target evidence and declarations

* ForceBattle4E16D9 passes VA C61AE8. Its complete nine-entry 144-byte table
  contains eight 16-byte fields and a zero sentinel. Strings, callback targets,
  zero userData and offsets 4/8/10/18/1C/1D/C/20 are independently read from
  retail. Its append call reaches the existing 56652F owner row.
* EyeTower4E383D passes C62034: LookPoint -> rowed callback4E3816, zero data
  and offset, then the null sentinel, totaling32 bytes. Its append call reaches
  existing5669B7. Reference casts express the already observed 40-byte and
  12-byte argument representations; they do not assert recovered record names.
* Parser35DBA2 allocates40 hex bytes and calls35DB3F. Bind it to the existing
  Rva0035DA01 constructor rather than the obsolete BfmeC1137 candidate name.
  Both that parser and native buildFieldParse4BB0BB pass C6BB18, the existing
  shared four-int zero table. Record its actual owner with a data row.
* Animation2D7554 uses the already rowed tree lookup2D752D, as its sibling
  parseAnim2DTemplate does. Its existing table is protected (COFF access digit1),
  while the old consumer declared it public (digit2). Preserve protected access
  with INI friendship. Native C031F0 contains six fields plus a null sentinel,
  totaling112 bytes. Offsets are0/0/0/14/12/18. The AnimationMode entry points
  to DBCC84's seven string pointers plus null, totaling32 bytes. Make the
  existing header-local mode array this source's external data owner so every
  table relocation can be independently verified. Values and order are unchanged.

BFME1 parser donors and the existing ZH Anim2D source provide semantic guides;
all stated target addresses, table entries and ABI extents come from retail.
No new code pins, aliases, globals at converged addresses, or baseline entries.

## Acceptance and limits

`link_check.py --prepare-current` verifies50/50 function rows in14 sources,
five data rows (336 bytes), eight literals plus two empty-string references,
four float literals, and the existing EH funclet's parent graph. Frozen-source,
CSV, code identity (zero new findings), and enforced converged-data checks pass.
The data shadow reports three stale catalog-name findings: old unowned scalar
FieldParse names at C61AE8/C62034 and the old public declaration at C031F0.
Actual array owners and every initializer relocation pass the data byte gate.
No shadow baseline is expanded.

These are legacy linked gains with self-strict byte receipts, not closed-strict
or full link-cycle gains. The Anim2D.cpp provider remains excluded (1688 bytes):
MemoryPoolFactory::createMemoryPool, MemoryPool::freeBlock and INI::load names,
plus Anim2DCollection constructor and Anim2D COMDAT/vtable copies still block it.
No full census, link cycle, nightly, or boot runner was started.
