ControlPoint parser link repair
==============================

Baseline and result use the same published census, c2c5ac8c27, with the
explicit sources recompiled/current in each invocation. Color-before has
0/151 parser bytes linked and 185 exception-owner bytes linked. Color-after
has 151+185. Pair-before adds the unchanged ControlPoint parser (0/146),
and pair-after has all three units clean: 146+151+185 = 482, versus the
original 185. Thus the legacy prediction improves by 297 bytes. The old
census counts ControlPoint as 146 bytes; its current ledger bodies total
147. Do not interpret this as a closed-strict or full-link measurement.

Pre-publication shadow inspection also found ColorControlPoint's private
rescale used a 0.03 constant, while native 503E4F reads the frame-rate global.
Its corrected body uses BfmeClientFramesPerSecond and matches all 39 native
bytes (helper-exact.log). Bind it under the existing row name
msecToFramesRva00503E4F; the old donor helper spelling was not an allowed
owner binding even after its code was fixed. Identity now reports zero new
findings (identity.log); no symbol pins were added. This dependency repair
is required to make the claimed 151-byte consumer gain usable. The original
metadata-only intermediate was never pushed; the final paired result and
receipts are refreshed for the corrected source.

The two consumer declarations omitted INIException::~INIException and
reversed the pointer/int fields. The rowed INIExceptionCtor.cpp constructor,
copy constructor, assignment and destructor establish pointer at +0, int
at +4, size 8, nonvirtual destructor. Retail ThrowInfo at VA CFE2FC uses
copy 588C5 and destructor 2BD30. Adding the destructor fixes emitted
ThrowInfo, while all parser instructions remain exact. These declarations
are TU-scoped; no canonical header or compiler flags changed.

ControlPoint's rowed initFromINI operand reaches RVA 863C48. Six consecutive
16-byte retail entries independently read from game.dat are:

  token VA  callback VA  user data  offset
  BD398C    42F507       0          00  Position
  BE56E8    42EFC0       0          0C  Angle
  BD3920    42F0F7       0          18  Time
  C63C08    42EFC0       0          10  EaseIn
  C63C00    42EFC0       0          14  EaseOut
  0         0            0          00

Retained the data ledger's one existing table name; added its 96-byte
verified ownership row. The named callback code bodies are already rowed.
No new symbol pin or function identity was inferred from a byte placement.
The older BFME1 donor comments describe its own addresses and are not used
as evidence for BFME2 table values. Donor checkout reviewed: 64d369b90170.

Acceptance: self-strict receipts and normal gate pass all three current
functions, both data tables (including ColorControlPoint's existing table),
two parser strings and two float literals. No new COMDAT variants;
find_declared_unmatched and check_csv pass. Related exception-conflict units
were previewed in family.log; they also need unrelated missing record,
append and table providers, so no speculative prerequisite edits were made.
