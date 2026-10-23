# Recorder relationship-name table ownership, 2026-10-15

Recorder.cpp referenced an undefined TheRelationshipNames. Define the existing
symbol once as ENEMIES, NEUTRAL, ALLIES, null and own its complete 16-byte retail
table in data_rows.csv. The generated data_ledger row now records its owner.
No code row, class layout, compiler flag, pin, alias or baseline changes.

Base: 862f9b6d84bdb260c7190a50c59c52aafcd53500. The source was file-claimed
before editing. The only current compiled consumer is Recorder.cpp.

## Target and reference evidence

The complete 1,897-byte dumpCommandHistory row at 0037BE15 directly indexes
VA 00DBA4D4; its operand is at RVA 0037C2F3. The verified body obtains the
index from Player::getRelationship and prints the selected relationship name.
Retail holds pointers 00BDA178, 00BED350, 00BDA180 and zero, whose complete
strings are ENEMIES, NEUTRAL and ALLIES. Compiler sizeof independently proves
the four-pointer extent; the data gate checks every pointer and string through
its terminator. proof.json records the full consumer hash and operand window.

ZH GeneralsMD/Code/GameEngine/Source/Common/System/GameCommon.cpp at the retained
BFME1 revision a7c38d3b2597121f178ab5190b3062478823257d supplies the same name
and ordering. BFME2's original identifier spelling is not independently proven;
the existing name is retained. This repair imports no donor layout or address.
Reviewed BFME1 linking repair 92a8d854746f059994f8ab370c133f3ba71eec24: use
the verified data owner rather than a separate undefined name. Its binding
principle applies, but this target table had no existing definition to reuse.

## Paired local evidence and acceptance

Both phases replace only the strictly prepared Recorder object in memory in
copies of one frozen index: update 19a2565407, 2026-10-15 09:33, underlying
census 5986a99448, 04:52. SHA256 and source/object/receipt hashes are in
proof.json. The committed status queue measured at 28269d8e8d served discovery
only. No index, link status or census artifact was rewritten.

- Strict preparation before and after, plus ./build.sh: all 16 code rows exact;
  41 string literals, 15 empty references and 29 imports verified, none skipped
  or baselined. The new data row is fully byte-verified.
- EH verifier: 6/6 EXACT; no missing objects or baselined/nonexact rows.
- All 83 retained COMDAT bodies, extents and relocation digests are identical.
  Every pre-existing nondebug section and normalized relocation is identical,
  including EH data, local code and linker directives. Only three string
  COMDATs and the 16-byte table section are added. Exactly the table symbol
  changes from undefined to defined; no other existing external binding changes.
- Paired legacy preview removes the sole unresolved binding; selected findings
  for GameMessage::GameMessage and Xfer::~Xfer remain identical. Total findings
  improve 3 -> 2 without additions. Ordinary link_check agrees: existing
  authored LINKED bytes remain 0 -> 0 (the unit has 5,939 nonpadding bytes).
- New-variant admission, class, declared-definition, whitespace and CSV checks
  pass. Converged-data enforcement checks eight protected addresses with zero
  second names or unjudged rows. Shadow data still reports the two unchanged
  names at A02EF0 (TheSkirmishGameInfo) and A02D86 (g_Rva00A02D86).
- The commit hook's shadow identity scan also reports appendNextCommand's
  existing GameMessage constructor binding at 0030F47A as wrong. That is the
  same independent constructor blocker retained by the paired preview; the
  complete section/relocation comparison proves its call is unchanged.
- Placement resweep: zero bodies and zero pins.

data_ledger.py generated a scratch ledger; only its exact 009BA4D4 row was
selected into the tracked ledger. Its log records 518 unrelated missing source
objects, so no claim is made that the whole inferred inventory is refreshed.
The touched object has a strict current receipt; its table has one definition
and one reference.

This is a verified dependency repair with 16 new data bytes and zero new
authored C++ code bytes. Strict receipts establish compiler input currency;
they do not establish self-strict executable placement or closed-strict link
closure. No such gain, full census gain or runtime result is claimed.
Broader link cycles, census rebuilds, nightlies and boot checks were not run.

## Remaining work

Recorder still depends on selected non-retail GameMessage constructor and Xfer
destructor definitions. Those independent shared-class repairs need their own
evidence and claims; they were not retried here.

Official BFME1 master was fetched at 3638ef61; the verified clean checkout and
gitlink remain a7c38d3b2597121f178ab5190b3062478823257d. Another worker holds
file:reference/open-bfme-1. The previously recorded comparative update still
requires the unfinished old-input full baseline rebuild (attempt record 53899).
No unchanged multi-hour rebuild was repeated, pointer advanced or successful
freshness stamp written. Freshness remains due.

proof.py is an evidence replay requiring this session's ignored snapshots in
build/relationship-names-link-20261015 and the recorded frozen index. It is not
an alternative acceptance gate. Model: gpt-6.1-sol.
