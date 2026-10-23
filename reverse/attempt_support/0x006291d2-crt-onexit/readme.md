# Whole CRT exit-registration member

`atonexit.obj` is now wholly authored C++ in the existing
`Code/Libraries/Source/WWVegas/WWDebug/AtexitThunk.cpp`: native `_onexit` (38B)
and the already recovered `atexit` adapter (18B). Original public C names are
preserved, replacing the former `object-symbol=__atexit` override. Its redundant
`_atexit` pin and both hatch register grants are removed. Only 38 unique retail
bytes move to C++ exact; the six-byte typed `__dllonexit` import provider replaces
an already C++-counted generator veneer and adds zero coverage.

Native COFF and retail establish the bodies, symbols, DLL-mode sentinel, table
addresses and call relationships; public `stdlib.h` corroborates the callback
ABI. The existing clean BFME1 atexit donor at the recorded pointer is retained.
No CRT implementation source was read. Complete raw object code and every
external relocation match the native member, independently of masked DIR32
patching. Both zero-initialized callback-table globals, originally four-byte
COMMONs, move with the member into one explicit C++ definition each and have
full data-row/sizeof proof. Startup and both existing free adapters use these
same C globals. The one existing canonical data record is regenerated from the
six current exact consumer rows as owned by this C++ unit; no baseline grows.
This ownership supersedes the native-COMMON snapshot in the earlier startup
batch, whose native byte/identity evidence remains valid.

The non-executed focused DLL forces 22 public routines across the accumulated
CRT/startup/free-adapter units. The original CRT archive supplies remaining
helpers; scoped IAT-only import entries supply the DLL slots for source-owned
callable names, including `_onexit` and `__dllonexit`. Explicit test doubles are
WinMain and the game-free function-pointer slot. The link succeeds without
public duplicates; its map assigns atexit and both table globals to the authored
unit. This is bounded closure, not full-game placement or runtime proof. No full
link cycle, census, smoke test or maintainer verification runner was run.

`verification.json` records the 38 new unique C++ bytes, existing adapter,
eight data bytes, exact native relocation proof, source hashes and two retired
hatches. `focused-link.json` records the precise closure scope and exit code.
`check_onexit.py` checks ordinary current build objects plus retail read-only,
with isolated sizeof probes through the existing data-row tool. Its output is
under ignored `build/resume-eh-local/`; run it after the ordinary source builds.
